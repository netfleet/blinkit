// -------------------------------------------------
// BlinKit - blink Library
// -------------------------------------------------
//   File Name: element_rare_data.cpp
// Description: ElementRareData Class
//      Author: Ziming Li
//     Created: 2019-11-16
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "element_rare_data.h"

#include "third_party/blink/renderer/core/dom/attr.h"

namespace blink {

struct SameSizeAsElementRareData : NodeRareData
{
    void* pointersOrStrings[5];
#ifndef NDEBUG
    std::shared_ptr<std::string> views;
#endif
};

#ifdef BLINKIT_CRAWLER_ONLY
ElementRareData::ElementRareData(void) = default;
#endif

ElementRareData::~ElementRareData(void)
{
    if (m_attrNodeList)
    {
        for (Attr *attr : *m_attrNodeList)
        {
            ASSERT(!attr->IsContextRetained());
            delete attr;
        }
        m_attrNodeList->clear();
    }
    ASSERT(!m_pseudoElementData);
}

AttrNodeList& ElementRareData::EnsureAttrNodeList(void)
{
    if (!m_attrNodeList)
        m_attrNodeList = std::make_unique<AttrNodeList>();
    return *m_attrNodeList;
}

static_assert(sizeof(ElementRareData) == sizeof(SameSizeAsElementRareData), "ElementRareData should stay small");

}  // namespace blink
