//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       ITrackerButtonCapability.h
//  Content:    Pure virtual interface for accessing button capabilities on 
//              tracker targets.
//  SVN Info:   $Id$
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZSPACE_I_TRACKER_BUTTON_CAPABILITY_H__
#define __ZSPACE_I_TRACKER_BUTTON_CAPABILITY_H__

#include "ZSpace/Tracker/TrackerDefines.h"
#include "ZSpace/Tracker/ITrackerCapability.h"

#include "ZSpace/Common/Delegate/Delegate.h"

ZSPACE_TRACKER_NS_BEGIN

/**
* @addtogroup Tracker
* @{
*/

/**
* Determine number of tracker buttons and their state.
*
* @remarks
*    This class indicates the number of buttons on the tracking
*    device and if a given button has been pressed as described
*    by the integer ID of the button, which generally starts with
*    0 but could be implementation-dependent.
*/
class ITrackerButtonCapability: public ITrackerCapability
{
public:
  struct ButtonEventArgs
  {
    unsigned int buttonBits; /**< bit 0 -> button 1; bit 1 ->b button 2; bit 2 -> button 3 */
    double timestamp; /**< Time in seconds. */
  };

  typedef zspace::common::Delegate<void (const ButtonEventArgs&)> ButtonEventHandler;

public:
  virtual ~ITrackerButtonCapability() = 0;

  /**
  * Get the number of buttons supported.
  */
  virtual unsigned int getNumButtons() = 0;

  /**
  * Check whether or not a specified button is pressed.
  *
  * @param[in] buttonId
  *   The integer id of the button.
  *
  * @return
  *   True if the button is pressed, false if not.
  */
  virtual bool isButtonPressed(unsigned int buttonId) = 0;

  /**
  * Register a button press event handler.
  *
  * @param[in] eventHandler
  *   A button event delegate.
  *
  * @return
  *   True if the handler was successfully registered, false if not.
  */
  virtual bool addButtonPressHandler(const ButtonEventHandler& eventHandler) = 0;

  /**
  * Unregister a button press event handler.
  *
  * @param[in] eventHandler
  *   A button event delegate.
  *
  * @return
  *   True if the handler was successfully unregistered, false if not.
  */
  virtual bool removeButtonPressHandler(const ButtonEventHandler& eventHandler) = 0;

  /**
  * Register a button release event handler.
  *
  * @param[in] eventHandler
  *   A button event delegate.
  *
  * @return
  *   True if the handler was successfully registered, false if not.
  */
  virtual bool addButtonReleaseHandler(const ButtonEventHandler& eventHandler) = 0;

  /**
  * Unregister a button release event handler.
  *
  * @param[in] eventHandler
  *   A button event delegate.
  *
  * @return
  *   True if the handler was successfully unregistered, false if not.
  */
  virtual bool removeButtonReleaseHandler(const ButtonEventHandler& eventHandler) = 0;

  /**
  * Register a button click event handler.
  *
  * @param[in] eventHandler
  *   A button event delegate.
  *
  * @return
  *   True if the handler was successfully registered, false if not.
  */
  virtual bool addButtonClickHandler(const ButtonEventHandler& eventHandler) = 0;

  /**
  * Unregister a button click event handler.
  *
  * @param[in] eventHandler
  *   A button event delegate.
  *
  * @return
  *   True if the handler was successfully unregistered, false if not.
  */
  virtual bool removeButtonClickHandler(const ButtonEventHandler& eventHandler) = 0;

  /**
  * Register a button double click event handler.
  *
  * @param[in] eventHandler
  *   A button event delegate.
  *
  * @return
  *   True if the handler was successfully registered, false if not.
  */
  virtual bool addButtonDoubleClickHandler(const ButtonEventHandler& eventHandler) = 0;

  /**
  * Unregister a button double click event handler.
  *
  * @param[in] eventHandler
  *   A button event delegate.
  *
  * @return
  *   True if the handler was successfully unregistered, false if not.
  */
  virtual bool removeButtonDoubleClickHandler(const ButtonEventHandler& eventHandler) = 0;
};


inline ITrackerButtonCapability::~ITrackerButtonCapability()
{
}

/** @} */   // End of group: Tracker

ZSPACE_TRACKER_NS_END

#endif // __ZSPACE_I_TRACKER_BUTTON_CAPABILITY_H__