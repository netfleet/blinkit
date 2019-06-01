// -------------------------------------------------
// BlinKit - BlinKit Library
// -------------------------------------------------
//   File Name: http_response_task.cpp
// Description: HTTPResponseTask Class
//      Author: Ziming Li
//     Created: 2019-03-22
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

#include "http_response_task.h"

#include "crawler/crawler_impl.h"

#include "platform/network/HTTPParsers.h"
#include "public/platform/WebTraceLocation.h"

using namespace blink;

namespace BlinKit {

HTTPResponseTask::HTTPResponseTask(CrawlerImpl &crawler, WebURLLoader *loader, WebURLLoaderClient *client, ResponseData &responseData)
    : ResponseTask(loader, client, responseData), m_crawler(crawler)
{
    // Nothing
}

static std::string ExtractMIMEType(const BkResponse &response)
{
    std::string contentType;
    response.GetHeader("Content-Type", BkMakeBuffer(contentType).Wrap());

    AtomicString mediaType = AtomicString::fromUTF8(contentType.data(), contentType.length());
    return extractMIMETypeFromMediaType(mediaType).lower().to_string();
}

void BKAPI HTTPResponseTask::RequestComplete(const BkResponse &response)
{
    response.GetCurrentURL(BkMakeBuffer(m_currentURL).Wrap());
    m_responseData->StatusCode = response.StatusCode();
    m_responseData->MimeType = ExtractMIMEType(response);
    response.GetBody(BkMakeBuffer(m_responseData->Body).Wrap());

    m_taskRunner->postTask(BLINK_FROM_HERE, this);
}

void BKAPI HTTPResponseTask::RequestFailed(int errorCode)
{
    BkCrawlerClient *client = &(m_crawler.Client());
    m_taskRunner->postTask(BLINK_FROM_HERE, [client, errorCode] {
        client->RequestFailed(errorCode);
    });
    delete this;
}

void HTTPResponseTask::run(void)
{
    int statusCode = m_responseData->StatusCode;
    const char *body = reinterpret_cast<const char *>(m_responseData->Body.data());
    size_t length = m_responseData->Body.size();
    if (!m_crawler.Client().RequestComplete(&m_crawler, m_currentURL.c_str(), statusCode, body, length))
        return;

    ResponseTask::run();
}

} // namespace BlinKit
