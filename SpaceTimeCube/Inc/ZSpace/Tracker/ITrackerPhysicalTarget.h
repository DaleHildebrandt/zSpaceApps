//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       ITrackerPhysicalTarget.h
//  Content:    The pure virtual interface for ZSpace tracker target plugins.
//  SVN Info:   $Id$
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZSPACE_I_TRACKER_PHYSICAL_TARGET_H__
#define __ZSPACE_I_TRACKER_PHYSICAL_TARGET_H__

#include "ZSpace/Tracker/TrackerDefines.h"
#include "ZSpace/Tracker/ITrackerCapability.h"
#include "ZSpace/Tracker/TrackerTarget.h"

ZSPACE_TRACKER_NS_BEGIN

/**
* @addtogroup Tracker
* @{
*/

/**
* Used as the basis for setting/getting properties of a target.
*
* @remark
*   Enable, disable and query state of the target. Queries
*   tracker capabilities (see ITrackerCapability). Sets/gets the
*   initial pose. Checks whether a specified target is visible
*   to its corresponding tracker device.
*/
class ITrackerPhysicalTarget
{
public:
  virtual ~ITrackerPhysicalTarget() = 0;

  /**
  * Get a tracker capability based on a specified type.
  *
  * @param[in] type
  *   The type of the tracker capability.
  *
  * @return
  *   A pointer to an ITrackerCapability. If the specified capability does not exist,
  *   NULL is returned.
  */
  virtual ITrackerCapability* getCapability(ITrackerCapability::Type type) = 0;

  /**
  * Set whether or not the physical target is enabled.
  */
  virtual bool setEnabled(bool isEnabled) = 0;

  /**
  * Check whether or not the physical target is enabled.
  */
  virtual bool isEnabled() = 0;

  /**
  * Set the initial pose of a specified target.
  *
  * @remark
  *   This is only applicable for devices that support relative poses.
  *   For example: The space navigator only generates relative positions
  *   and orientations, so the initial pose will act effectively as a
  *   world transform offset.
  *
  * @param[in] pose
  *   The initial pose for the target.
  *
  * @return
  *   True for success, false for failure.
  */
  virtual bool setInitialPose(const zspace::common::Matrix4& initialPose) = 0;

  /**
  * Get the local pose of a specified target.
  *
  * @param[out] localPose
  *   The local pose of the target. This is the raw pose extracted from the
  *   physical device without any calibration applied.
  *
  * @return
  *   True for success, false for failure.
  */
  virtual bool getLocalPose(zspace::common::Matrix4& localPose) = 0;

  /**
  * Check whether or not a specified target is visible to its corresponding 
  * tracker device.
  */
  virtual bool isVisible() = 0;

  /**
  * Add a move event handler.
  *
  * @param[in] eventHandler
  *   A move event handler.
  *
  * @return
  *   True if the handler was registered, false if not.
  */
  virtual bool addMoveHandler(const zspace::tracker::TrackerTarget::MoveEventHandler& eventHandler) = 0;

  /**
  * Remove a move event handler.
  *
  * @param[in] eventHandler
  *   A move event handler.
  *
  * @return
  *   True if the handler was unregistered, false if not.
  */
  virtual bool removeMoveHandler(const zspace::tracker::TrackerTarget::MoveEventHandler& eventHandler) = 0;

  /**
  * Set the time threshold to control the frequency of move events.
  *
  * @remark
  *   This threshold is satisfiable independent of distance and rotation thresholds.
  *
  * @param[in] time
  *   Time in seconds.
  *
  * @return
  *   True if setting the time threshold was successful.  False otherwise.
  */
  virtual bool setMoveEventTimeThreshold(float time) = 0;

  /**
  * Get the time threshold which controls the frequency of move events.
  *
  * @param[out] time
  *   Time in seconds.
  *
  * @return
  *   True if getting the time threshold was successful.  False otherwise.
  */
  virtual bool getMoveEventTimeThreshold(float& time) = 0;

  /**
  * Set the distance threshold to control the frequency of move events.
  *
  * @remark
  *   This threshold is satisfiable independent of time and rotation thresholds.
  *
  * @param[in] distance
  *   Distance in meters.
  *
  * @return
  *   True if setting the distance threshold was successful.  False otherwise.
  */
  virtual bool setMoveEventDistanceThreshold(float distance) = 0;

  /**
  * Get the distance threshold which controls the frequency of move events.
  *
  * @param[out] distance
  *   Distance in meters.
  *
  * @return
  *   True if getting the distance threshold was successful.  False otherwise.
  */
  virtual bool getMoveEventDistanceThreshold(float& distance) = 0;

  /**
  * Set the rotation threshold to control the frequency of move events.
  *
  * @remark
  *   This threshold is satisfiable independent of time and distance thresholds.
  *
  * @param[in] rotation
  *   Rotation in degrees.
  *
  * @return
  *   True if setting the rotation threshold was successful.  False otherwise.
  */
  virtual bool setMoveEventRotationThreshold(float rotation) = 0;

  /**
  * Get the rotation threshold which controls the frequency of move events.
  *
  * @param[out] rotation
  *   Rotation in degrees.
  *
  * @return
  *   True if getting the rotation threshold was successful.  False otherwise.
  */
  virtual bool getMoveEventRotationThreshold(float& rotation) = 0;
};


inline ITrackerPhysicalTarget::~ITrackerPhysicalTarget()
{
}

/** @} */   // End of group: Tracker

ZSPACE_TRACKER_NS_END

#endif // __ZSPACE_I_TRACKER_PHYSICAL_TARGET_H__