// -------------------------------------------------
// BlinKit - blink Library
// -------------------------------------------------
//   File Name: script_forbidden_scope.cpp
// Description: ScriptForbiddenScope Class
//      Author: Ziming Li
//     Created: 2019-09-28
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

#include "script_forbidden_scope.h"

#include "third_party/blink/renderer/platform/wtf/wtf.h"

namespace blink {

static unsigned s_scriptForbiddenCount = 0;

void ScriptForbiddenScope::Enter(void)
{
    assert(IsMainThread());
    ++s_scriptForbiddenCount;
}

void ScriptForbiddenScope::Exit(void)
{
    assert(IsMainThread());
    assert(0 != s_scriptForbiddenCount);
    --s_scriptForbiddenCount;
}

bool ScriptForbiddenScope::IsScriptForbidden(void)
{
    return IsMainThread() && 0 != s_scriptForbiddenCount;
}

} // namespace blink
