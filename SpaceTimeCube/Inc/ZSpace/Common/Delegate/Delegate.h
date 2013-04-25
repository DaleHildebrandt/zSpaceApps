//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       Delegate.h
//  Content:    The generic C++ delegate class.
//  SVN Info:   $Id$
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZSPACE_DELEGATE_H__
#define __ZSPACE_DELEGATE_H__

#include "ZSpace/Common/CommonDefines.h"

ZSPACE_COMMON_NS_BEGIN

// Base Template
template <typename T>
class Delegate {};

ZSPACE_COMMON_NS_END

#define ZS_DELEGATE_ARG_COUNT 0
#include "Delegate.inl"
#undef ZS_DELEGATE_ARG_COUNT

#define ZS_DELEGATE_ARG_COUNT 1
#include "Delegate.inl"
#undef ZS_DELEGATE_ARG_COUNT

#define ZS_DELEGATE_ARG_COUNT 2
#include "Delegate.inl"
#undef ZS_DELEGATE_ARG_COUNT

#define ZS_DELEGATE_ARG_COUNT 3
#include "Delegate.inl"
#undef ZS_DELEGATE_ARG_COUNT

#define ZS_DELEGATE_ARG_COUNT 4
#include "Delegate.inl"
#undef ZS_DELEGATE_ARG_COUNT

#define ZS_DELEGATE_ARG_COUNT 5
#include "Delegate.inl"
#undef ZS_DELEGATE_ARG_COUNT

#define ZS_DELEGATE_ARG_COUNT 6
#include "Delegate.inl"
#undef ZS_DELEGATE_ARG_COUNT

#define ZS_DELEGATE_ARG_COUNT 7
#include "Delegate.inl"
#undef ZS_DELEGATE_ARG_COUNT

#define ZS_DELEGATE_ARG_COUNT 8
#include "Delegate.inl"
#undef ZS_DELEGATE_ARG_COUNT

#endif // __ZSPACE_DELEGATE_H__