// -------------------------------------------------
// BlinKit - blink Library
// -------------------------------------------------
//   File Name: mutation_observer_interest_group.h
// Description: MutationObserverInterestGroup Class
//      Author: Ziming Li
//     Created: 2019-12-31
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
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

#ifndef BLINKIT_BLINK_MUTATION_OBSERVER_INTEREST_GROUP_H
#define BLINKIT_BLINK_MUTATION_OBSERVER_INTEREST_GROUP_H

#pragma once

#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/platform/heap/handle.h"

namespace blink {

class MutationRecord;

class MutationObserverInterestGroup final : public GarbageCollected<MutationObserverInterestGroup>
{
public:
    static MutationObserverInterestGroup* CreateForCharacterDataMutation(Node &target)
    {
        if (!target.GetDocument().HasMutationObserversOfType(kMutationTypeCharacterData))
            return nullptr;

        ASSERT(false); // BKTODO:
        return nullptr;
    }
    static MutationObserverInterestGroup* CreateForAttributesMutation(Node &target, const QualifiedName &attributeName)
    {
        if (!target.GetDocument().HasMutationObserversOfType(kMutationTypeAttributes))
            return nullptr;

        ASSERT(false); // BKTODO:
        return nullptr;
    }

    void EnqueueMutationRecord(MutationRecord *mutation);
};

} // namespace blink

#endif // BLINKIT_BLINK_MUTATION_OBSERVER_INTEREST_GROUP_H
