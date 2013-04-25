//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       ITrackerTapCapability.h
//  Content:    Pure virtual interface for accessing tap capabilities on 
//              tracker targets.
//  SVN Info:   $Id$
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZSPACE_I_TRACKER_TAP_CAPABILITY_H__
#define __ZSPACE_I_TRACKER_TAP_CAPABILITY_H__

#include "ZSpace/Tracker/TrackerDefines.h"
#include "ZSpace/Tracker/ITrackerCapability.h"

#include "ZSpace/Common/Delegate/Delegate.h"

ZSPACE_TRACKER_NS_BEGIN

/**
* @addtogroup Tracker
* @{
*/

class ITrackerTapCapability: public ITrackerCapability
{
public:
  struct TapEventArgs
  {
    double timestamp; /**< Time in seconds. */
  };

  typedef zspace::common::Delegate<void (const TapEventArgs&)> TapEventHandler;

public:
  virtual ~ITrackerTapCapability() = 0;

  virtual bool isTapPressed() = 0;

  virtual double getTapHoldThreshold() = 0;
  virtual void setTapHoldThreshold(const double seconds) = 0;

  virtual bool addTapHandler(const TapEventHandler& eventHandler) = 0;
  virtual bool removeTapHandler(const TapEventHandler& eventHandler) = 0;

  virtual bool addDoubleTapHandler(const TapEventHandler& eventHandler) = 0;
  virtual bool removeDoubleTapHandler(const TapEventHandler& eventHandler) = 0;

  virtual bool addPressHandler(const TapEventHandler& eventHandler) = 0;
  virtual bool removePressHandler(const TapEventHandler& eventHandler) = 0;

  virtual bool addReleaseHandler(const TapEventHandler& eventHandler) = 0;
  virtual bool removeReleaseHandler(const TapEventHandler& eventHandler) = 0;

  virtual bool addHoldHandler(const TapEventHandler& eventHandler) = 0;
  virtual bool removeHoldHandler(const TapEventHandler& eventHandler) = 0;
};


inline ITrackerTapCapability::~ITrackerTapCapability()
{
}

/** @} */   // End of group: Tracker

ZSPACE_TRACKER_NS_END

#endif // __ZSPACE_I_TRACKER_TAP_CAPABILITY_H__