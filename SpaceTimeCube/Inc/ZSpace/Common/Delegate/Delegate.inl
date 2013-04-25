//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       Delegate.inl
//  Content:    The generic C++ delegate class.
//  SVN Info:   $Id$
//
//////////////////////////////////////////////////////////////////////////////

#include "ZSpace/Common/Delegate/Delegate.h"
#include "ZSpace/Common/Preprocessor/PreprocessorDefines.h"

#include <assert.h>
#include <stdio.h>

ZSPACE_COMMON_NS_BEGIN

template <typename R ZS_COMMA_IF(ZS_DELEGATE_ARG_COUNT) ZS_LIST(ZS_DELEGATE_ARG_COUNT, typename P)>
class Delegate<R (ZS_LIST(ZS_DELEGATE_ARG_COUNT, P))>
{
public:
  Delegate(void)
  {
    m_stub.instance = NULL;
    m_stub.function = NULL;
  }

  /// Binds a free function
  template <R (*Function)(ZS_LIST(ZS_DELEGATE_ARG_COUNT, P))>
  void bind(void)
  {
    m_stub.instance = NULL;
    m_stub.function = &functionStub<Function>;
  }

  /// Binds a class method
  template <class C, R (C::*Function)(ZS_LIST(ZS_DELEGATE_ARG_COUNT, P))>
  void bind(C* instance)
  {
    m_stub.instance = instance;
    m_stub.function = &classMethodStub<C, Function>;
  }

  /// Check if the delegate is bound
  bool isBound() const
  {
    return (m_stub.function != NULL);
  }

  /// Invokes the delegate
  R invoke(ZS_DLIST(ZS_DELEGATE_ARG_COUNT, P, p)) const
  {
    assert(m_stub.function != NULL && "Cannot invoke unbound delegate. Call bind() first.");
    return m_stub.function(m_stub.instance ZS_COMMA_IF(ZS_DELEGATE_ARG_COUNT) ZS_LIST(ZS_DELEGATE_ARG_COUNT, p));
  }

  /// Equality operator overload
  inline bool operator ==(const Delegate& delegate) const
  {
    return (m_stub.function == delegate.m_stub.function);
  }

private:  
  typedef void* InstancePtr;
  typedef R (*FunctionPtr)(InstancePtr ZS_COMMA_IF(ZS_DELEGATE_ARG_COUNT) ZS_LIST(ZS_DELEGATE_ARG_COUNT, P));

  struct Stub
  {
    InstancePtr instance;
    FunctionPtr function;
  };

private:
  Stub m_stub;

private:
  // Turns a free function into our internal function stub.
  template <R (*Function)(ZS_LIST(ZS_DELEGATE_ARG_COUNT, P))>
  static ZS_INLINE R functionStub(InstancePtr instance ZS_COMMA_IF(ZS_DELEGATE_ARG_COUNT) ZS_DLIST(ZS_DELEGATE_ARG_COUNT, P, p))
  {
    return (Function)(ZS_LIST(ZS_DELEGATE_ARG_COUNT, p));
  }

  // Turns a member function into our internal function stub.
  template <class C, R (C::*Function)(ZS_LIST(ZS_DELEGATE_ARG_COUNT, P))>
  static ZS_INLINE R classMethodStub(InstancePtr instance ZS_COMMA_IF(ZS_DELEGATE_ARG_COUNT) ZS_DLIST(ZS_DELEGATE_ARG_COUNT, P, p))
  {
    // cast the instance pointer back into the original class instance
    return (static_cast<C*>(instance)->*Function)(ZS_LIST(ZS_DELEGATE_ARG_COUNT, p));
  }
};

ZSPACE_COMMON_NS_END