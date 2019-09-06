// -------------------------------------------------
// BlinKit SDK
// -------------------------------------------------
//   File Name: bk_http.h
//      Author: Ziming Li
//     Created: 2019-09-04
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

#ifndef BLINKIT_SDK_HTTP_H
#define BLINKIT_SDK_HTTP_H

#pragma once

#include "bk_def.h"

#ifdef __cplusplus
extern "C" {
#endif

BK_DECLARE_HANDLE(BkRequest, RequestImpl);

struct BkRequestClient {
    void *UserData;
    void (BKAPI * RequestComplete)(BkResponse, void *);
    void (BKAPI * RequestFailed)(int errorCode, void *);
    bool_t (BKAPI * RequestRedirect)(BkResponse, void *);
};

BKEXPORT BkRequest BKAPI BkCreateRequest(const char *URL, struct BkRequestClient *client);

BKEXPORT int BKAPI BkPerformRequest(BkRequest request);

BKEXPORT void BKAPI BkSetRequestMethod(BkRequest request, const char *method);
BKEXPORT void BKAPI BkSetRequestHeader(BkRequest request, const char *name, const char *value);
BKEXPORT void BKAPI BkSetRequestBody(BkRequest request, const void *data, size_t dataLength);
BKEXPORT void BKAPI BkSetRequestTimeout(BkRequest request, unsigned timeout /* in seconds */);
BKEXPORT void BKAPI BkSetRequestProxy(BkRequest request, const char *proxy);

BKEXPORT BkWorkController BKAPI BkGetRequestController(BkRequest request);

BKEXPORT int BKAPI BkGetResponseStatusCode(BkResponse response);

enum ResponseData {
    BK_RE_CURRENT_URL = 0,
    BK_RE_ORIGINAL_URL,
    BK_RE_BODY
};

BKEXPORT int BKAPI BkGetResponseData(BkResponse response, int data, struct BkBuffer *dst);

BKEXPORT int BKAPI BkGetResponseHeader(BkResponse response, const char *name, struct BkBuffer *dst);

BKEXPORT size_t BKAPI BkGetResponseCookiesCount(BkResponse response);
BKEXPORT int BKAPI BkGetResponseCookie(BkResponse response, size_t index, struct BkBuffer *dst);

#ifdef __cplusplus
} // extern "C"

namespace BlinKit {

class BkRequestClientImpl
{
public:
    operator BkRequestClient* (void) { return &m_client; }
protected:
    BkRequestClientImpl(void)
    {
        memset(&m_client, 0, sizeof(BkRequestClient));
        m_client.UserData = this;
        m_client.RequestComplete = RequestCompleteImpl;
        m_client.RequestFailed = RequestFailedImpl;
        m_client.RequestRedirect = RequestRedirectImpl;
    }
private:
    virtual void RequestComplete(BkResponse response) = 0;
    virtual void RequestFailed(int errorCode) { assert(BK_ERR_SUCCESS == errorCode); }
    virtual bool_t RequestRedirect(BkResponse response) { return true; }

    static void BKAPI RequestCompleteImpl(BkResponse response, void *userData)
    {
        BkRequestClientImpl *This = reinterpret_cast<BkRequestClientImpl *>(userData);
        This->RequestComplete(response);
    }
    static void BKAPI RequestFailedImpl(int errorCode, void *userData)
    {
        BkRequestClientImpl *This = reinterpret_cast<BkRequestClientImpl *>(userData);
        This->RequestFailed(errorCode);
    }
    static bool_t BKAPI RequestRedirectImpl(BkResponse response, void *userData)
    {
        BkRequestClientImpl *This = reinterpret_cast<BkRequestClientImpl *>(userData);
        return This->RequestRedirect(response);
    }

    BkRequestClient m_client;
};

} // namespace BlinKit

#endif

#endif // BLINKIT_SDK_HTTP_H
