// -------------------------------------------------
// BlinKit - blink Library
// -------------------------------------------------
//   File Name: document_parser.cc
// Description: DocumentParser Class
//      Author: Ziming Li
//     Created: 2019-10-17
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

/*
 * Copyright (C) 2010 Google, Inc. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "third_party/blink/renderer/core/dom/document_parser.h"

#include <memory>
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/document_parser_client.h"
#include "third_party/blink/renderer/core/html/parser/text_resource_decoder.h"
#include "third_party/blink/renderer/platform/wtf/assertions.h"

namespace blink {

DocumentParser::DocumentParser(Document* document)
    : state_(kParsingState),
      document_was_loaded_as_part_of_navigation_(false),
      document_(document) {
  DCHECK(document);
}

DocumentParser::~DocumentParser() = default;

void DocumentParser::SetDecoder(std::unique_ptr<TextResourceDecoder>) {
  NOTREACHED();
}

TextResourceDecoder* DocumentParser::Decoder() {
  return nullptr;
}

void DocumentParser::PrepareToStopParsing() {
  DCHECK_EQ(state_, kParsingState);
  state_ = kStoppingState;
}

void DocumentParser::StopParsing() {
  state_ = kStoppedState;

  // Clients may be removed while in the loop. Make a snapshot for iteration.
  std::vector<DocumentParserClient *> clients_snapshot(clients_.begin(), clients_.end());
  for (DocumentParserClient* client : clients_snapshot) {
    if (clients_.find(client) == std::end(clients_))
      continue;

    client->NotifyParserStopped();
  }
}

void DocumentParser::Detach() {
  state_ = kDetachedState;
  document_ = nullptr;
}

void DocumentParser::PauseScheduledTasks() {}

void DocumentParser::UnpauseScheduledTasks() {}

void DocumentParser::AddClient(DocumentParserClient* client) {
  clients_.insert(client);
}

void DocumentParser::RemoveClient(DocumentParserClient* client) {
  clients_.erase(client);
}

}  // namespace blink