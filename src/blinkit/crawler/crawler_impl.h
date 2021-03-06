// -------------------------------------------------
// BlinKit - BlinKit Library
// -------------------------------------------------
//   File Name: crawler_impl.h
// Description: CrawlerImpl Class
//      Author: Ziming Li
//     Created: 2019-03-20
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

#ifndef BLINKIT_BLINKIT_CRAWLER_IMPL_H
#define BLINKIT_BLINKIT_CRAWLER_IMPL_H

#pragma once

#include <functional>
#include "bk_crawler.h"
#include "blinkit/blink_impl/local_frame_client_impl.h"

class CrawlerImpl final : public BlinKit::LocalFrameClientImpl
{
public:
    CrawlerImpl(const BkCrawlerClient &client);
    ~CrawlerImpl(void);

    // BkCrawlerClient Wrappers
    std::string GetConfig(int cfg) const;
    void ProcessRequestComplete(BkResponse response, BkWorkController controller);
    bool HijackRequest(const char *URL, std::string &dst) const;
    void HijackResponse(BkResponse response);
    bool ApplyConsoleMessager(std::function<void(int, const char *)> &dst) const;
    void ProcessDocumentReset(void);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Exports
    int Run(const char *URL);
    BkJSContext GetScriptContext(void);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0 // BKTODO:
    std::string GetCookies(const std::string &URL) const;

    void CancelLoading(void);
#endif
private:
#if 0 // BKTODO:
    // BkCrawler
    int BKAPI RegisterCrawlerFunction(const char *name, BkCallback &functionImpl) override;
    int BKAPI AccessCrawlerMember(const char *name, BkCallback &callback) override;
#endif
    // LocalFrameClient
    bool IsCrawler(void) const override { return true; }
    String UserAgent(void) override;
    void TransitionToCommittedForNewPage(void) override;
    void DispatchDidReceiveTitle(const String &title) override {}
    void DispatchDidFailProvisionalLoad(const blink::ResourceError &error) override;
    void DispatchDidFinishLoad(void) override;

    BkCrawlerClient m_client;
    std::unique_ptr<blink::LocalFrame> m_frame;
};

DEFINE_TYPE_CASTS(CrawlerImpl, ::blink::LocalFrameClient, client, client->IsCrawler(), client.IsCrawler());

#endif // BLINKIT_BLINKIT_CRAWLER_IMPL_H
