// -------------------------------------------------
// BlinKit - blink Library
// -------------------------------------------------
//   File Name: background_html_parser.h
// Description: BackgroundHTMLParser Class
//      Author: Ziming Li
//     Created: 2019-10-23
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

/*
 * Copyright (C) 2013 Google, Inc. All Rights Reserved.
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
 * THIS SOFTWARE IS PROVIDED BY GOOGLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL GOOGLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_HTML_PARSER_BACKGROUND_HTML_PARSER_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_HTML_PARSER_BACKGROUND_HTML_PARSER_H_

#include <memory>

#include "base/macros.h"
#include "base/single_thread_task_runner.h"
#include "third_party/blink/renderer/core/dom/document_encoding_data.h"
#include "third_party/blink/renderer/core/html/parser/background_html_input_stream.h"
#include "third_party/blink/renderer/core/html/parser/compact_html_token.h"
#include "third_party/blink/renderer/core/html/parser/html_parser_options.h"
#include "third_party/blink/renderer/core/html/parser/html_preload_scanner.h"
#include "third_party/blink/renderer/core/html/parser/html_source_tracker.h"
#include "third_party/blink/renderer/core/html/parser/html_tree_builder_simulator.h"
#include "third_party/blink/renderer/core/html/parser/text_resource_decoder.h"

namespace blink {

class HTMLDocumentParser;

class BackgroundHTMLParser {
  USING_FAST_MALLOC(BackgroundHTMLParser);

 public:
  struct Configuration {
    USING_FAST_MALLOC(Configuration);

   public:
    Configuration();
    HTMLParserOptions options;
    std::weak_ptr<HTMLDocumentParser> parser;
    std::unique_ptr<TextResourceDecoder> decoder;
  };

  // The returned BackgroundHTMLParser must first be initialized by calling
  // init(), and free by calling stop().
  static std::weak_ptr<BackgroundHTMLParser> Create(
      std::unique_ptr<Configuration>,
      std::shared_ptr<base::SingleThreadTaskRunner>);
  ~BackgroundHTMLParser(void);
  void Init(const BlinKit::BkURL& document_url,
            std::unique_ptr<CachedDocumentParameters>,
            const MediaValuesCached::MediaValuesCachedData&);

  struct Checkpoint {
    USING_FAST_MALLOC(Checkpoint);

   public:
    std::weak_ptr<HTMLDocumentParser> parser;
    std::unique_ptr<HTMLToken> token;
    std::unique_ptr<HTMLTokenizer> tokenizer;
    HTMLTreeBuilderSimulator::State tree_builder_state;
    HTMLInputCheckpoint input_checkpoint;
    TokenPreloadScannerCheckpoint preload_scanner_checkpoint;
    String unparsed_input;
  };

  void AppendRawBytesFromMainThread(std::unique_ptr<Vector<char>>);
  void SetDecoder(std::unique_ptr<TextResourceDecoder>);
  void Flush();
  void ResumeFrom(std::unique_ptr<Checkpoint>);
  void StartedChunkWithCheckpoint(HTMLInputCheckpoint);
  void Finish();
  void Stop();

  void ForcePlaintextForTextDocument();

 private:
  BackgroundHTMLParser(std::unique_ptr<Configuration>,
                       std::shared_ptr<base::SingleThreadTaskRunner>);

  void AppendDecodedBytes(const String&);
  void MarkEndOfFile();
  void PumpTokenizer();

  void EnqueueTokenizedChunk();
  void UpdateDocument(const String& decoded_data);

  BackgroundHTMLInputStream input_;
  HTMLSourceTracker source_tracker_;
  std::unique_ptr<HTMLToken> token_;
  std::unique_ptr<HTMLTokenizer> tokenizer_;
  HTMLTreeBuilderSimulator tree_builder_simulator_;
  HTMLParserOptions options_;
  std::weak_ptr<HTMLDocumentParser> parser_;

  CompactHTMLTokenStream pending_tokens_;
  PreloadRequestStream pending_preloads_;
#ifndef BLINKIT_CRAWLER_ONLY
  ViewportDescriptionWrapper viewport_description_;
#endif

  std::unique_ptr<TokenPreloadScanner> preload_scanner_;
  std::unique_ptr<TextResourceDecoder> decoder_;
  DocumentEncodingData last_seen_encoding_data_;
  std::shared_ptr<base::SingleThreadTaskRunner> loading_task_runner_;

  // Index into |pending_tokens_| of the last <meta> csp token found. Will be
  // |TokenizedChunk::kNoPendingToken| if none have been found.
  int pending_csp_meta_token_index_;

  bool starting_script_;

  std::shared_ptr<BackgroundHTMLParser> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(BackgroundHTMLParser);
};

}  // namespace blink

#endif
