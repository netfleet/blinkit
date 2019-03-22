// -------------------------------------------------
// BlinKit - BlinKit Library
// -------------------------------------------------
//   File Name: request_impl.cpp
// Description: RequestImpl Class
//      Author: Ziming Li
//     Created: 2018-09-27
// -------------------------------------------------
// Copyright (C) 2018 MingYang Software Technology.
// -------------------------------------------------

#include "request_impl.h"

#include "http/request_controller_impl.h"
#include "http/response_impl.h"

namespace BlinKit {

const unsigned long RequestImpl::TimeOutInMs = 30000;

RequestImpl::RequestImpl(const char *URL, BkRequestClient &client) : m_URL(URL), m_client(client), m_method("GET")
{
    m_headers["Accept"] = "*/*";
}

RequestImpl::~RequestImpl(void)
{
    if (nullptr != m_response)
        m_response->Release();
}

std::string RequestImpl::GetAllHeaders(void) const
{
    std::string headers;
    for (const auto &it : m_headers)
    {
        headers.append(it.first);
        headers.append(": ");
        headers.append(it.second);
        headers.append("\r\n");
    }
    return headers;
}

void RequestImpl::Release(void)
{
    if (0 == --m_refCount)
        delete this;
}

BkRequestController* BKAPI RequestImpl::RequireLifecycleController(void)
{
    ++m_refCount;
    return new RequestControllerImpl(*this);
}

void BKAPI RequestImpl::SetHeader(const char *name, const char *value)
{
    m_headers[name] = value;
}

} // namespace BlinKit