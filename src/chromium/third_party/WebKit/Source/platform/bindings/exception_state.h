// -------------------------------------------------
// BlinKit - blink Library
// -------------------------------------------------
//   File Name: exception_state.h
// Description: ExceptionState & Related Classes
//      Author: Ziming Li
//     Created: 2019-01-21
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

#ifndef BLINKIT_BLINK_EXCEPTION_STATE_H
#define BLINKIT_BLINK_EXCEPTION_STATE_H

#pragma once

#include "wtf/Allocator.h"
#include "wtf/Noncopyable.h"

namespace blink {

class ExceptionState
{
    STACK_ALLOCATED();
    WTF_MAKE_NONCOPYABLE(ExceptionState);
};

class NonThrowableExceptionState final : public ExceptionState
{
public:
    NonThrowableExceptionState(const char *fileName, int line);

    ExceptionState& ReturnThis(void) { return *this; }
private:
    const char *m_fileName;
    const int m_line;
};

class DummyExceptionStateForTesting final : public ExceptionState
{
public:
    DummyExceptionStateForTesting(void);

    ExceptionState& ReturnThis(void) { return *this; }
};

} // namespace blink

#ifdef _DEBUG
#   define ASSERT_NO_EXCEPTION  (::blink::NonThrowableExceptionState(__FILE__, __LINE__).ReturnThis())
#else
#   define ASSERT_NO_EXCEPTION  (::blink::DummyExceptionStateForTesting().ReturnThis())
#endif

#define IGNORE_EXCEPTION_FOR_TESTING    (::blink::DummyExceptionStateForTesting().ReturnThis())

#endif // BLINKIT_BLINK_EXCEPTION_STATE_H