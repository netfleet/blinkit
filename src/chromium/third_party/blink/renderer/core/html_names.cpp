// -------------------------------------------------
// BlinKit - blink Library
// -------------------------------------------------
//   File Name: html_names.cpp
// Description: HTML Names
//      Author: Ziming Li
//     Created: 2019-11-21
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

#include "html_names.h"

#include <iterator>

namespace blink {
namespace html_names {

static void* ns_uri_storage[(sizeof(AtomicString) + sizeof(void *) - 1) / sizeof(void *)];
const AtomicString &xhtmlNamespaceURI = *reinterpret_cast<AtomicString *>(&ns_uri_storage);

// Tags
static void* tag_storage[kTagsCount * ((sizeof(HTMLQualifiedName) + sizeof(void *) - 1) / sizeof(void *))];
const HTMLQualifiedName &kATag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[0];
const HTMLQualifiedName &kAddressTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[1];
const HTMLQualifiedName &kAppletTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[2];
const HTMLQualifiedName &kAreaTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[3];
const HTMLQualifiedName &kArticleTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[4];
const HTMLQualifiedName &kAsideTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[5];
const HTMLQualifiedName &kBTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[6];
const HTMLQualifiedName &kBaseTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[7];
const HTMLQualifiedName &kBasefontTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[8];
const HTMLQualifiedName &kBgsoundTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[9];
const HTMLQualifiedName &kBigTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[10];
const HTMLQualifiedName &kBlockquoteTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[11];
const HTMLQualifiedName &kBodyTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[12];
const HTMLQualifiedName &kBrTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[13];
const HTMLQualifiedName &kButtonTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[14];
const HTMLQualifiedName &kCaptionTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[15];
const HTMLQualifiedName &kCenterTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[16];
const HTMLQualifiedName &kCodeTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[17];
const HTMLQualifiedName &kColTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[18];
const HTMLQualifiedName &kColgroupTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[19];
const HTMLQualifiedName &kCommandTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[20];
const HTMLQualifiedName &kContentTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[21];
const HTMLQualifiedName &kDdTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[22];
const HTMLQualifiedName &kDetailsTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[23];
const HTMLQualifiedName &kDirTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[24];
const HTMLQualifiedName &kDivTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[25];
const HTMLQualifiedName &kDlTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[26];
const HTMLQualifiedName &kDtTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[27];
const HTMLQualifiedName &kEmTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[28];
const HTMLQualifiedName &kEmbedTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[29];
const HTMLQualifiedName &kFieldsetTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[30];
const HTMLQualifiedName &kFigcaptionTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[31];
const HTMLQualifiedName &kFigureTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[32];
const HTMLQualifiedName &kFontTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[33];
const HTMLQualifiedName &kFooterTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[34];
const HTMLQualifiedName &kFormTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[35];
const HTMLQualifiedName &kFrameTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[36];
const HTMLQualifiedName &kFramesetTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[37];
const HTMLQualifiedName &kH1Tag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[38];
const HTMLQualifiedName &kH2Tag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[39];
const HTMLQualifiedName &kH3Tag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[40];
const HTMLQualifiedName &kH4Tag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[41];
const HTMLQualifiedName &kH5Tag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[42];
const HTMLQualifiedName &kH6Tag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[43];
const HTMLQualifiedName &kHeadTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[44];
const HTMLQualifiedName &kHeaderTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[45];
const HTMLQualifiedName &kHgroupTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[46];
const HTMLQualifiedName &kHrTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[47];
const HTMLQualifiedName &kHTMLTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[48];
const HTMLQualifiedName &kITag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[49];
const HTMLQualifiedName &kIFrameTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[50];
const HTMLQualifiedName &kImageTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[51];
const HTMLQualifiedName &kImgTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[52];
const HTMLQualifiedName &kInputTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[53];
const HTMLQualifiedName &kKeygenTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[54];
const HTMLQualifiedName &kLiTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[55];
const HTMLQualifiedName &kLinkTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[56];
const HTMLQualifiedName &kListingTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[57];
const HTMLQualifiedName &kMainTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[58];
const HTMLQualifiedName &kMarqueeTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[59];
const HTMLQualifiedName &kMenuTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[60];
const HTMLQualifiedName &kMetaTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[61];
const HTMLQualifiedName &kNavTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[62];
const HTMLQualifiedName &kNobrTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[63];
const HTMLQualifiedName &kNoembedTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[64];
const HTMLQualifiedName &kNoframesTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[65];
const HTMLQualifiedName &kNoscriptTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[66];
const HTMLQualifiedName &kObjectTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[67];
const HTMLQualifiedName &kOlTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[68];
const HTMLQualifiedName &kOptgroupTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[69];
const HTMLQualifiedName &kOptionTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[70];
const HTMLQualifiedName &kPTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[71];
const HTMLQualifiedName &kParamTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[72];
const HTMLQualifiedName &kPlaintextTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[73];
const HTMLQualifiedName &kPreTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[74];
const HTMLQualifiedName &kRbTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[75];
const HTMLQualifiedName &kRpTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[76];
const HTMLQualifiedName &kRtTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[77];
const HTMLQualifiedName &kRTCTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[78];
const HTMLQualifiedName &kRubyTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[79];
const HTMLQualifiedName &kSTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[80];
const HTMLQualifiedName &kScriptTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[81];
const HTMLQualifiedName &kSectionTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[82];
const HTMLQualifiedName &kSelectTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[83];
const HTMLQualifiedName &kSmallTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[84];
const HTMLQualifiedName &kSourceTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[85];
const HTMLQualifiedName &kSpanTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[86];
const HTMLQualifiedName &kStrikeTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[87];
const HTMLQualifiedName &kStrongTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[88];
const HTMLQualifiedName &kStyleTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[89];
const HTMLQualifiedName &kSubTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[90];
const HTMLQualifiedName &kSummaryTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[91];
const HTMLQualifiedName &kSupTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[92];
const HTMLQualifiedName &kTableTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[93];
const HTMLQualifiedName &kTbodyTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[94];
const HTMLQualifiedName &kTdTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[95];
const HTMLQualifiedName &kTemplateTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[96];
const HTMLQualifiedName &kTextareaTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[97];
const HTMLQualifiedName &kTfootTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[98];
const HTMLQualifiedName &kThTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[99];
const HTMLQualifiedName &kTheadTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[100];
const HTMLQualifiedName &kTitleTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[101];
const HTMLQualifiedName &kTrTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[102];
const HTMLQualifiedName &kTrackTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[103];
const HTMLQualifiedName &kTtTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[104];
const HTMLQualifiedName &kUTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[105];
const HTMLQualifiedName &kUlTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[106];
const HTMLQualifiedName &kVarTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[107];
const HTMLQualifiedName &kVideoTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[108];
const HTMLQualifiedName &kWbrTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[109];
const HTMLQualifiedName &kXmpTag = reinterpret_cast<HTMLQualifiedName *>(&tag_storage)[110];

// Attributes
static void* attr_storage[kAttrsCount * ((sizeof(QualifiedName) + sizeof(void *) - 1) / sizeof(void *))];
const QualifiedName &kCharsetAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[0];
const QualifiedName &kClassAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[1];
const QualifiedName &kColorAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[2];
const QualifiedName &kContentAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[3];
const QualifiedName &kDirAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[4];
const QualifiedName &kFaceAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[5];
const QualifiedName &kFormAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[6];
const QualifiedName &kFrameAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[7];
const QualifiedName &kHrefAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[8];
const QualifiedName &kHttpEquivAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[9];
const QualifiedName &kIdAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[10];
const QualifiedName &kIsAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[11];
const QualifiedName &kLanguageAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[12];
const QualifiedName &kLinkAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[13];
const QualifiedName &kNameAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[14];
const QualifiedName &kNomoduleAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[15];
const QualifiedName &kObjectAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[16];
const QualifiedName &kReferrerpolicyAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[17];
const QualifiedName &kSelectAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[18];
const QualifiedName &kSizeAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[19];
const QualifiedName &kSpanAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[20];
const QualifiedName &kSrcAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[21];
const QualifiedName &kStyleAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[22];
const QualifiedName &kSummaryAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[23];
const QualifiedName &kTitleAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[24];
const QualifiedName &kTypeAttr = reinterpret_cast<QualifiedName *>(&attr_storage)[25];

void Init(void)
{
    struct NameEntry {
        const char* name;
        unsigned hash;
        unsigned char length;
        unsigned char isTag;
        unsigned char isAttr;
    };

    // Namespace
    // Use placement new to initialize the globals.
    AtomicString ns_uri("http://www.w3.org/1999/xhtml");
    void *dst = const_cast<AtomicString *>(&xhtmlNamespaceURI);
    new (dst) AtomicString(ns_uri);

    static const NameEntry kNames[] = {
        { "a", 9778235, 1, 1, 0 },
        { "address", 10008206, 7, 1, 0 },
        { "applet", 7823075, 6, 1, 0 },
        { "area", 7355486, 4, 1, 0 },
        { "article", 2968800, 7, 1, 0 },
        { "aside", 10128566, 5, 1, 0 },
        { "b", 7170995, 1, 1, 0 },
        { "base", 4376626, 4, 1, 0 },
        { "basefont", 5439393, 8, 1, 0 },
        { "bgsound", 9424179, 7, 1, 0 },
        { "big", 2330122, 3, 1, 0 },
        { "blockquote", 6047050, 10, 1, 0 },
        { "body", 4862692, 4, 1, 0 },
        { "br", 5574895, 2, 1, 0 },
        { "button", 679691, 6, 1, 0 },
        { "caption", 2437650, 7, 1, 0 },
        { "center", 909285, 6, 1, 0 },
        { "charset", 14273970, 7, 0, 1 },
        { "class", 1023741, 5, 0, 1 },
        { "code", 11588001, 4, 1, 0 },
        { "col", 12850806, 3, 1, 0 },
        { "colgroup", 3733719, 8, 1, 0 },
        { "color", 2734929, 5, 0, 1 },
        { "command", 2099501, 7, 1, 0 },
        { "content", 6894765, 7, 1, 1 },
        { "dd", 16480447, 2, 1, 0 },
        { "details", 4653180, 7, 1, 0 },
        { "dir", 5122803, 3, 1, 1 },
        { "div", 9762591, 3, 1, 0 },
        { "dl", 5117854, 2, 1, 0 },
        { "dt", 8177126, 2, 1, 0 },
        { "em", 2724661, 2, 1, 0 },
        { "embed", 855371, 5, 1, 0 },
        { "face", 12427611, 4, 0, 1 },
        { "fieldset", 37097, 8, 1, 0 },
        { "figcaption", 13388641, 10, 1, 0 },
        { "figure", 13776479, 6, 1, 0 },
        { "font", 4588695, 4, 1, 0 },
        { "footer", 13359933, 6, 1, 0 },
        { "form", 10060301, 4, 1, 1 },
        { "frame", 3408403, 5, 1, 1 },
        { "frameset", 11229107, 8, 1, 0 },
        { "h1", 3953979, 2, 1, 0 },
        { "h2", 9378819, 2, 1, 0 },
        { "h3", 1803164, 2, 1, 0 },
        { "h4", 15343268, 2, 1, 0 },
        { "h5", 8065295, 2, 1, 0 },
        { "h6", 9566891, 2, 1, 0 },
        { "head", 11457121, 4, 1, 0 },
        { "header", 5896178, 6, 1, 0 },
        { "hgroup", 8927907, 6, 1, 0 },
        { "hr", 7182703, 2, 1, 0 },
        { "href", 5797448, 4, 0, 1 },
        { "html", 7123128, 4, 1, 0 },
        { "http-equiv", 12415310, 10, 0, 1 },
        { "i", 16149244, 1, 1, 0 },
        { "id", 6145549, 2, 0, 1 },
        { "iframe", 16643553, 6, 1, 0 },
        { "image", 10287573, 5, 1, 0 },
        { "img", 11398162, 3, 1, 0 },
        { "input", 10365436, 5, 1, 0 },
        { "is", 15617733, 2, 0, 1 },
        { "keygen", 5603105, 6, 1, 0 },
        { "language", 4109061, 8, 0, 1 },
        { "li", 11097939, 2, 1, 0 },
        { "link", 7010491, 4, 1, 1 },
        { "listing", 15674586, 7, 1, 0 },
        { "main", 13501767, 4, 1, 0 },
        { "marquee", 1416619, 7, 1, 0 },
        { "menu", 13428288, 4, 1, 0 },
        { "meta", 14067019, 4, 1, 0 },
        { "name", 8774809, 4, 0, 1 },
        { "nav", 15269619, 3, 1, 0 },
        { "nobr", 419763, 4, 1, 0 },
        { "noembed", 11476379, 7, 1, 0 },
        { "noframes", 13751064, 8, 1, 0 },
        { "nomodule", 10903441, 8, 0, 1 },
        { "noscript", 10168152, 8, 1, 0 },
        { "object", 6907086, 6, 1, 1 },
        { "ol", 6672076, 2, 1, 0 },
        { "optgroup", 10180907, 8, 1, 0 },
        { "option", 2998548, 6, 1, 0 },
        { "p", 587733, 1, 1, 0 },
        { "param", 15210019, 5, 1, 0 },
        { "plaintext", 2551274, 9, 1, 0 },
        { "pre", 16061734, 3, 1, 0 },
        { "rb", 4749743, 2, 1, 0 },
        { "referrerpolicy", 13927145, 14, 0, 1 },
        { "rp", 4502666, 2, 1, 0 },
        { "rt", 8494892, 2, 1, 0 },
        { "rtc", 4350543, 3, 1, 0 },
        { "ruby", 12793227, 4, 1, 0 },
        { "s", 11249530, 1, 1, 0 },
        { "script", 7137273, 6, 1, 0 },
        { "section", 8056235, 7, 1, 0 },
        { "select", 210571, 6, 1, 1 },
        { "size", 12715024, 4, 0, 1 },
        { "small", 14362904, 5, 1, 0 },
        { "source", 341674, 6, 1, 0 },
        { "span", 11168892, 4, 1, 1 },
        { "src", 11517827, 3, 0, 1 },
        { "strike", 15072495, 6, 1, 0 },
        { "strong", 13282129, 6, 1, 0 },
        { "style", 10993676, 5, 1, 1 },
        { "sub", 15782866, 3, 1, 0 },
        { "summary", 1148260, 7, 1, 1 },
        { "sup", 8741418, 3, 1, 0 },
        { "table", 8181317, 5, 1, 0 },
        { "tbody", 14028375, 5, 1, 0 },
        { "td", 10309076, 2, 1, 0 },
        { "template", 12693000, 8, 1, 0 },
        { "textarea", 10510497, 8, 1, 0 },
        { "tfoot", 13009441, 5, 1, 0 },
        { "th", 3915297, 2, 1, 0 },
        { "thead", 13349519, 5, 1, 0 },
        { "title", 2337488, 5, 1, 1 },
        { "tr", 16624306, 2, 1, 0 },
        { "track", 10988706, 5, 1, 0 },
        { "tt", 9170852, 2, 1, 0 },
        { "type", 1916283, 4, 0, 1 },
        { "u", 13317144, 1, 1, 0 },
        { "ul", 12324505, 2, 1, 0 },
        { "var", 9573901, 3, 1, 0 },
        { "video", 16765639, 5, 1, 0 },
        { "wbr", 8290101, 3, 1, 0 },
        { "xmp", 8764488, 3, 1, 0 },
    };

    size_t tag_i = 0, attr_i = 0;
    for (size_t i = 0; i < std::size(kNames); ++i)
    {
        StringImpl *impl = StringImpl::CreateStatic(kNames[i].name, kNames[i].length, kNames[i].hash);
        if (kNames[i].isTag)
        {
            void *address = reinterpret_cast<HTMLQualifiedName *>(&tag_storage) + tag_i;
            QualifiedName::CreateStatic(address, impl, ns_uri);
            ++tag_i;
        }

        if (!kNames[i].isAttr)
            continue;

        void *address = reinterpret_cast<QualifiedName *>(&attr_storage) + attr_i;
        QualifiedName::CreateStatic(address, impl);
        ++attr_i;
    }

    ASSERT(kTagsCount == tag_i);
    ASSERT(kAttrsCount == attr_i);
}

} // namespace html_names
} // namespace blink