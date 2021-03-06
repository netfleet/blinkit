// -------------------------------------------------
// BlinKit - blink Library
// -------------------------------------------------
//   File Name: http_names.cpp
// Description: HTTP Names
//      Author: Ziming Li
//     Created: 2019-10-11
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

#include "http_names.h"

#include <iterator>
#include <mutex>

namespace blink {
namespace http_names {

void* names_storage[kNamesCount * ((sizeof(AtomicString) + sizeof(void *) - 1) / sizeof(void *))];

const AtomicString &kContentDisposition = reinterpret_cast<AtomicString *>(&names_storage)[0];
const AtomicString &kContentLanguage = reinterpret_cast<AtomicString *>(&names_storage)[1];
const AtomicString &kContentType = reinterpret_cast<AtomicString *>(&names_storage)[2];
const AtomicString &kGET = reinterpret_cast<AtomicString *>(&names_storage)[3];
const AtomicString &kReferer = reinterpret_cast<AtomicString *>(&names_storage)[4];
const AtomicString &kRefresh = reinterpret_cast<AtomicString *>(&names_storage)[5];
const AtomicString &kUserAgent = reinterpret_cast<AtomicString *>(&names_storage)[6];

void Init(void)
{
    struct NameEntry {
        const char* name;
        unsigned hash;
        unsigned char length;
    };

    static const NameEntry kNames[] = {
        { "Content-Disposition",   362682,  19 },
        { "Content-Language",     3105184,  16 },
        { "Content-Type",         7448957,  12 },
        { "GET",                  1490282,  3  },
        { "Referer",             15797945,  7  },
        { "Refresh",              7822740,  7  },
        { "User-Agent",          13018365,  10 },
    };

    const auto worker = []
    {
        for (size_t i = 0; i < std::size(kNames); ++i)
        {
            StringImpl *impl = StringImpl::CreateStatic(kNames[i].name, kNames[i].length, kNames[i].hash);
            void* address = reinterpret_cast<AtomicString *>(&names_storage) + i;
            new (address) AtomicString(impl);
        }
    };

    std::once_flag s_loadFlag;
    std::call_once(s_loadFlag, worker);
}

} // namespace http_names
} // namespace blink
