#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os, sys

REPO_ROOT = os.path.normpath(os.path.join(os.path.abspath(os.path.dirname(__file__)), os.pardir))
def get_full_path(repo_path):
    return os.path.normpath(os.path.join(REPO_ROOT, repo_path))
def run(cmd_line):
    print cmd_line
    return os.system(cmd_line)
def run_script(rel_path, args = ''):
    cmd_line = os.path.normpath(rel_path)
    if args:
        cmd_line += ' '
        cmd_line += args
    return run(cmd_line)

# Apply path for python modules
sys.path.append(get_full_path('src/chromium/third_party'))

GPERF = ''
if 'win32' == sys.platform:
    GPERF = ' --gperf ' + get_full_path('helpers\\gperf.exe')

# Apply `WebKit/Source` as work directory
current_dir = get_full_path('src/chromium/third_party/WebKit/Source')
os.chdir(current_dir)

core_event_idl_files = (
    'css/FontFaceSetLoadEvent.idl',
    'css/MediaQueryListEvent.idl',
    'events/AnimationEvent.idl',
    'events/AnimationPlayerEvent.idl',
    'events/ApplicationCacheErrorEvent.idl',
    'events/AutocompleteErrorEvent.idl',
    'events/BeforeUnloadEvent.idl',
    'events/ClipboardEvent.idl',
    'events/CompositionEvent.idl',
    'events/CustomEvent.idl',
    'events/DragEvent.idl',
    'events/ErrorEvent.idl',
    'events/Event.idl',
    'events/FocusEvent.idl',
    'events/HashChangeEvent.idl',
    'events/KeyboardEvent.idl',
    'events/MouseEvent.idl',
    'events/MutationEvent.idl',
    'events/PageTransitionEvent.idl',
    'events/PointerEvent.idl',
    'events/PopStateEvent.idl',
    'events/ProgressEvent.idl',
    'events/RelatedEvent.idl',
    'events/ResourceProgressEvent.idl',
    'events/SecurityPolicyViolationEvent.idl',
    'events/TextEvent.idl',
    'events/TouchEvent.idl',
    'events/TransitionEvent.idl',
    'events/UIEvent.idl',
    'events/WheelEvent.idl',
    'html/track/TrackEvent.idl',
    'svg/SVGZoomEvent.idl',
    'xmlhttprequest/XMLHttpRequestProgressEvent.idl'
)
with open(os.path.normpath('gen/core_event_idl_files'), 'w') as f:
    for file_entry in core_event_idl_files:
        f.write(os.path.normpath('core/' + file_entry) + '\n')
run_script('bindings/scripts/generate_event_interfaces.py', \
    '--event-idl-files-list ' + os.path.normpath('gen/core_event_idl_files') + ' '  \
    '--event-interfaces-file ' + os.path.normpath('gen/EventInterfaces.in') + ' '   \
    '--write-file-only-if-changed 0'    \
)

run_script('build/scripts/make_names.py',   \
    os.path.normpath('gen/EventInterfaces.in') + ' '    \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_names.py',   \
    os.path.normpath('core/events/EventTargetFactory.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_names.py',   \
    os.path.normpath('core/events/EventTypeNames.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_element_factory.py', \
    os.path.normpath('core/html/HTMLTagNames.in') + ' ' + os.path.normpath('core/html/HTMLAttributeNames.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_css_property_names.py',  \
    os.path.normpath('core/css/CSSProperties.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  + GPERF \
)

run_script('build/scripts/make_css_value_keywords.py',  \
    os.path.normpath('core/css/CSSValueKeywords.in') + ' ' + os.path.normpath('core/css/SVGCSSValueKeywords.in') + ' '  \
    '--output_dir ' + os.path.normpath('gen/core')  + GPERF \
)

run_script('build/scripts/make_names.py',  \
    os.path.normpath('platform/network/HTTPNames.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/platform')  \
)

run_script('build/scripts/make_media_feature_names.py', \
    os.path.normpath('core/css/MediaFeatureNames.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_names.py',  \
    os.path.normpath('platform/fonts/FontFamilyNames.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/platform')  \
)

run_script('build/scripts/make_element_type_helpers.py',    \
    os.path.normpath('core/html/HTMLTagNames.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_qualified_names.py', \
    os.path.normpath('core/html/parser/MathMLTagNames.in') + ' ' +  \
    os.path.normpath('core/html/parser/MathMLAttributeNames.in') + ' '  \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_names.py',  \
    os.path.normpath('core/html/forms/InputTypeNames.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_element_factory.py', \
    os.path.normpath('core/svg/SVGTagNames.in') + ' ' + os.path.normpath('core/svg/SVGAttributeNames.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_qualified_names.py', \
    os.path.normpath('core/svg/xlinkattrs.in') + ' '    \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_element_type_helpers.py',    \
    os.path.normpath('core/svg/SVGTagNames.in') + ' '   \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_qualified_names.py', \
    os.path.normpath('core/xml/xmlnsattrs.in') + ' '    \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_qualified_names.py', \
    os.path.normpath('core/xml/xmlattrs.in') + ' '  \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_settings.py',    \
    os.path.normpath('core/frame/Settings.in') + ' '    \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_names.py',  \
    os.path.normpath('core/fetch/FetchInitiatorTypeNames.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core/fetch')    \
)

run_script('build/scripts/make_element_lookup_trie.py', \
    os.path.normpath('core/html/HTMLTagNames.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_names.py',  \
    os.path.normpath('core/html/parser/HTMLTokenizerNames.in') + ' '    \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_names.py',  \
    os.path.normpath('core/css/MediaTypeNames.in') + ' '    \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_style_shorthands.py',    \
    os.path.normpath('core/css/CSSProperties.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_style_builder.py',   \
    os.path.normpath('core/css/CSSProperties.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_css_tokenizer_codepoints.py',    \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run_script('build/scripts/make_media_features.py',  \
    os.path.normpath('core/css/MediaFeatureNames.in') + ' ' \
    '--output_dir ' + os.path.normpath('gen/core')  \
)

run('python ' + os.path.normpath('core/html/parser/create-html-entity-table') + ' ' \
    '-o ' + os.path.normpath('gen/core/HTMLEntityTable.cpp') + ' '  \
    + os.path.normpath('core/html/parser/HTMLEntityNames.in')   \
)
