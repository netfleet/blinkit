// -------------------------------------------------
// BlinKit - blink Library
// -------------------------------------------------
//   File Name: html_document_parser.h
// Description: HTMLDocumentParser Class
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

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_HTML_PARSER_HTML_DOCUMENT_PARSER_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_HTML_PARSER_HTML_DOCUMENT_PARSER_H_

#include <memory>
#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/dom/parser_content_policy.h"
#include "third_party/blink/renderer/core/dom/scriptable_document_parser.h"
#include "third_party/blink/renderer/core/html/parser/html_input_stream.h"
#include "third_party/blink/renderer/core/html/parser/html_parser_options.h"
#include "third_party/blink/renderer/core/html/parser/html_parser_reentry_permit.h"
#include "third_party/blink/renderer/core/html/parser/html_preload_scanner.h"
#include "third_party/blink/renderer/core/html/parser/html_source_tracker.h"
#include "third_party/blink/renderer/core/html/parser/html_token.h"
#include "third_party/blink/renderer/core/html/parser/html_tokenizer.h"
#include "third_party/blink/renderer/core/html/parser/html_tree_builder_simulator.h"
#include "third_party/blink/renderer/core/html/parser/preload_request.h"
#include "third_party/blink/renderer/core/html/parser/text_resource_decoder.h"
#include "third_party/blink/renderer/core/script/html_parser_script_runner_host.h"
#include "third_party/blink/renderer/platform/web_task_runner.h"
#include "third_party/blink/renderer/platform/wtf/deque.h"
#include "third_party/blink/renderer/platform/wtf/text/text_position.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace blink {

class BackgroundHTMLParser;
class CompactHTMLToken;
class Document;
class DocumentEncodingData;
class DocumentFragment;
class Element;
class HTMLDocument;
class HTMLParserScriptRunner;
class HTMLPreloadScanner;
class HTMLResourcePreloader;
class HTMLTreeBuilder;

class CORE_EXPORT HTMLDocumentParser : public ScriptableDocumentParser
                                     , private HTMLParserScriptRunnerHost
                                     , public std::enable_shared_from_this<HTMLDocumentParser>
{
  USING_GARBAGE_COLLECTED_MIXIN(HTMLDocumentParser);

 public:
  static std::shared_ptr<HTMLDocumentParser> Create(Document& document)
  {
    return base::WrapShared(new HTMLDocumentParser(document));
  }
  ~HTMLDocumentParser() override;

  // TODO(alexclarke): Remove when background parser goes away.
  void Dispose();

  static void ParseDocumentFragment(
      const String&,
      DocumentFragment*,
      Element* context_element,
      ParserContentPolicy = kAllowScriptingContent);

  // Exposed for testing.
  HTMLParserScriptRunnerHost* AsHTMLParserScriptRunnerHostForTesting() {
    return this;
  }

  HTMLTokenizer* Tokenizer() const { return tokenizer_.get(); }

  TextPosition GetTextPosition() const final;
  bool IsParsingAtLineNumber() const final;
  OrdinalNumber LineNumber() const final;

  void PauseScheduledTasks() final;
  void UnpauseScheduledTasks() final;

  HTMLParserReentryPermit* ReentryPermit() { return reentry_permit_.get(); }

  struct TokenizedChunk {
    USING_FAST_MALLOC(TokenizedChunk);

   public:
    CompactHTMLTokenStream tokens;
    PreloadRequestStream preloads;
#ifndef BLINKIT_CRAWLER_ONLY
    ViewportDescriptionWrapper viewport;
#endif
    HTMLTokenizer::State tokenizer_state;
    HTMLTreeBuilderSimulator::State tree_builder_state;
    TokenPreloadScannerCheckpoint preload_scanner_checkpoint;
    bool starting_script;
    // Index into |tokens| of the last <meta> csp tag in |tokens|. Preloads will
    // be deferred until this token is parsed. Will be noPendingToken if there
    // are no csp tokens.
    int pending_csp_meta_token_index;

    static constexpr int kNoPendingToken = -1;
  };
  void EnqueueTokenizedChunk(std::unique_ptr<TokenizedChunk>);
  void DidReceiveEncodingDataFromBackgroundParser(const DocumentEncodingData&);

  void AppendBytes(const char* bytes, size_t length) override;
  void Flush() final;
  void SetDecoder(std::unique_ptr<TextResourceDecoder>) final;

 protected:
  void insert(const String&) final;
  void Append(const String&) override;
  void Finish() final;

  HTMLDocumentParser(Document&);
  HTMLDocumentParser(DocumentFragment*,
                     Element* context_element,
                     ParserContentPolicy);

  HTMLTreeBuilder* TreeBuilder() const { return tree_builder_.Get(); }

  void ForcePlaintextForTextDocument();

 private:
  static HTMLDocumentParser* Create(DocumentFragment* fragment,
                                    Element* context_element,
                                    ParserContentPolicy parser_content_policy) {
    return new HTMLDocumentParser(fragment, context_element,
                                  parser_content_policy);
  }
  HTMLDocumentParser(Document&,
                     ParserContentPolicy);

  // DocumentParser
  void Detach() final;
  bool HasInsertionPoint() final;
  void PrepareToStopParsing() final;
  void StopParsing() final;
  bool IsPaused() const {
    return IsWaitingForScripts() || is_waiting_for_stylesheets_;
  }
  bool IsWaitingForScripts() const final;
  bool IsExecutingScript() const final;
  void ExecuteScriptsWaitingForResources() final;
  void DidAddPendingStylesheetInBody() final;
  void DidLoadAllBodyStylesheets() final;
  void CheckIfBodyStylesheetAdded();
  void DocumentElementAvailable() override;

  // HTMLParserScriptRunnerHost
  void NotifyScriptLoaded(PendingScript*) final;
  HTMLInputStream& InputStream() final { return input_; }
  bool HasPreloadScanner() const final { return preload_scanner_.get(); }
  void AppendCurrentInputStreamToPreloadScannerAndScan() final;

  bool CanTakeNextToken();
  void PumpTokenizer();
  void PumpTokenizerIfPossible();
  void ConstructTreeFromHTMLToken();
  void ConstructTreeFromCompactHTMLToken(const CompactHTMLToken&);

  void RunScriptsForPausedTreeBuilder();
  void ResumeParsingAfterPause();

  void AttemptToEnd();
  void EndIfDelayed();
  void AttemptToRunDeferredScriptsAndEnd();
  void end();

  bool IsParsingFragment() const;
  bool InPumpSession() const { return pump_session_nesting_level_ > 0; }
  bool ShouldDelayEnd() const {
    return InPumpSession() || IsPaused() || IsExecutingScript();
  }

  std::unique_ptr<HTMLPreloadScanner> CreatePreloadScanner(
      TokenPreloadScanner::ScannerType);

  // Let the given HTMLPreloadScanner scan the input it has, and then preloads
  // resources using the resulting PreloadRequests and |preloader_|.
  void ScanAndPreload(HTMLPreloadScanner*);
  void FetchQueuedPreloads();

  HTMLToken& Token() { return *token_; }

  HTMLParserOptions options_;
  HTMLInputStream input_;
  scoped_refptr<HTMLParserReentryPermit> reentry_permit_;

  std::unique_ptr<HTMLToken> token_;
  std::unique_ptr<HTMLTokenizer> tokenizer_;
  Member<HTMLParserScriptRunner> script_runner_;
  Member<HTMLTreeBuilder> tree_builder_;

  std::unique_ptr<HTMLPreloadScanner> preload_scanner_;
  // A scanner used only for input provided to the insert() method.
  std::unique_ptr<HTMLPreloadScanner> insertion_preload_scanner_;

  std::shared_ptr<base::SingleThreadTaskRunner> loading_task_runner_;
  HTMLSourceTracker source_tracker_;
  TextPosition text_position_;

  // FIXME: last_chunk_before_pause_, tokenizer_, token_, and input_ should be
  // combined into a single state object so they can be set and cleared together
  // and passed between threads together.
  std::unique_ptr<TokenizedChunk> last_chunk_before_pause_;
  Deque<std::unique_ptr<TokenizedChunk>> speculations_;
  Member<HTMLResourcePreloader> preloader_;
  PreloadRequestStream queued_preloads_;

  // If this is non-null, then there is a meta CSP token somewhere in the
  // speculation buffer. Preloads will be deferred until a token matching this
  // pointer is parsed and the CSP policy is applied. Note that this pointer
  // tracks the *last* meta token in the speculation buffer, so it overestimates
  // how long to defer preloads. This is for simplicity, as the alternative
  // would require keeping track of token positions of preload requests.
  CompactHTMLToken* pending_csp_meta_token_;

  TaskHandle resume_parsing_task_handle_;

  bool end_was_delayed_;
  bool tasks_were_paused_;
  unsigned pump_session_nesting_level_;
  unsigned pump_speculations_session_nesting_level_;
  bool is_parsing_at_line_number_;
  bool tried_loading_link_headers_;
  bool added_pending_stylesheet_in_body_;
  bool is_waiting_for_stylesheets_;
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_HTML_PARSER_HTML_DOCUMENT_PARSER_H_
