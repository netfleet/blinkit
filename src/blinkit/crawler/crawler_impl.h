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

#include "sdk/include/BlinKit.h"
#include "frame_loader_client_impl.h"

namespace BlinKit {

class CrawlerFrame;

class CrawlerImpl final : public BkCrawler, public FrameLoaderClientImpl
{
public:
    CrawlerImpl(BkCrawlerClient &client);
    ~CrawlerImpl(void);

    std::string GetCookie(const std::string &URL) const;
private:
    // BkCrawler
    void BKAPI Destroy(void) override { delete this; }
    int BKAPI Load(const char *URI) override;
    void BKAPI SetUserAgent(const char *userAgent) override { m_userAgent = userAgent; }
    // blink::FrameClient
    bool IsCrawler(void) const override { return true; }
    // blink::FrameLoaderClient
    String userAgent(void) override;

    BkCrawlerClient &m_client;
    RefPtr<CrawlerFrame> m_frame;
    std::string m_userAgent;
};

DEFINE_TYPE_CASTS(CrawlerImpl, ::blink::FrameClient, client, client->IsCrawler(), client.IsCrawler());

} // namespace BlinKit

#endif // BLINKIT_BLINKIT_CRAWLER_IMPL_H
