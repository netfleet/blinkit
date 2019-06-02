// -------------------------------------------------
// BlinKit - blink Library
// -------------------------------------------------
//   File Name: exception_state.cpp
// Description: ExceptionState & Related Classes
//      Author: Ziming Li
//     Created: 2019-03-07
// -------------------------------------------------
// Copyright (C) 2019 MingYang Software Technology.
// -------------------------------------------------

#include "exception_state.h"

#include "base/logging.h"

namespace blink {

void ExceptionState::clearException(void)
{
    assert(false); // BKTODO:
}

void ExceptionState::throwDOMException(ExceptionCode exceptionCode, const String &message)
{
    m_exceptionCode = exceptionCode;
    m_message = message;
    BKLOG("DOM Exception (%d): %s", m_exceptionCode, m_message.to_string().c_str());
}

void ExceptionState::throwException(void)
{
    assert(false); // Not reached!
}

void ExceptionState::throwSecurityError(const String &sanitizedMessage, const String &unsanitizedMessage)
{
    assert(false); // BKTODO:
}

void ExceptionState::throwTypeError(const String &message)
{
    assert(false); // BKTODO:
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NonThrowableExceptionState::NonThrowableExceptionState(const char *fileName, int line)
    : m_fileName(fileName), m_line(line)
{
    // Nothing
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DummyExceptionStateForTesting::DummyExceptionStateForTesting(void)
{
    // Nothing
}

} // namespace blink
