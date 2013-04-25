//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       PreprocessorDefines.h
//  Content:    Common preprocessor defines.
//  SVN Info:   $Id$
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZSPACE_PREPROCESSOR_DEFINES_H__
#define __ZSPACE_PREPROCESSOR_DEFINES_H__

// Join Macros
#define ZS_JOIN(x, y)         ZS_INNER_JOIN(x, y)
#define ZS_INNER_JOIN(x, y)   x##y

// Boolean Macros
#define ZS_TO_BOOL_0		      0
#define ZS_TO_BOOL_1		      1
#define ZS_TO_BOOL_2		      1
#define ZS_TO_BOOL_3		      1
#define ZS_TO_BOOL_4		      1
#define ZS_TO_BOOL_5		      1
#define ZS_TO_BOOL_6		      1
#define ZS_TO_BOOL_7		      1
#define ZS_TO_BOOL_8		      1
#define ZS_TO_BOOL(x)		      ZS_JOIN(ZS_TO_BOOL_, x)

// Comma If Macros
#define ZS_COMMA_IF_0
#define ZS_COMMA_IF_1		      ,
#define ZS_COMMA_IF(cond)		  ZS_JOIN(ZS_COMMA_IF_, ZS_TO_BOOL(cond))

// List Macros
#define ZS_LIST_0(x)
#define ZS_LIST_1(x)		      x##1
#define ZS_LIST_2(x)		      ZS_LIST_1(x), x##2
#define ZS_LIST_3(x)		      ZS_LIST_2(x), x##3
#define ZS_LIST_4(x)		      ZS_LIST_3(x), x##4
#define ZS_LIST_5(x)		      ZS_LIST_4(x), x##5
#define ZS_LIST_6(x)		      ZS_LIST_5(x), x##6
#define ZS_LIST_7(x)		      ZS_LIST_6(x), x##7
#define ZS_LIST_8(x)		      ZS_LIST_7(x), x##8
#define ZS_LIST(count, x)		  ZS_JOIN(ZS_LIST_, count)(x)

#define ZS_DLIST_0(x, y)
#define ZS_DLIST_1(x, y)		  x##1 y##1
#define ZS_DLIST_2(x, y)		  ZS_DLIST_1(x, y), x##2 y##2
#define ZS_DLIST_3(x, y)		  ZS_DLIST_2(x, y), x##3 y##3
#define ZS_DLIST_4(x, y)		  ZS_DLIST_3(x, y), x##4 y##4
#define ZS_DLIST_5(x, y)		  ZS_DLIST_4(x, y), x##5 y##5
#define ZS_DLIST_6(x, y)		  ZS_DLIST_5(x, y), x##6 y##6
#define ZS_DLIST_7(x, y)		  ZS_DLIST_6(x, y), x##7 y##7
#define ZS_DLIST_8(x, y)		  ZS_DLIST_7(x, y), x##8 y##8
#define ZS_DLIST(count, x, y)	ZS_JOIN(ZS_DLIST_, count)(x, y)

// Inline Macros
#ifdef _WIN32
#define ZS_INLINE __forceinline
#else
#define ZS_INLINE inline
#endif

#endif // __ZSPACE_PREPROCESSOR_DEFINES_H__