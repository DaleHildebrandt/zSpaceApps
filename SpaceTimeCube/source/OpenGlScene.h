//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       OpenGlScene.h
//  Content:    The OpenGlScene class for the zSpace OpenGl stereo samples.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZSPACE_OPEN_GL_SCENE_H__
#define __ZSPACE_OPEN_GL_SCENE_H__

#include "ZSpace/Common/Math/Matrix4.h"
#include "MathHelper\MathHelper.hpp"
#include "ZSpace/Common/Math/Ray.h"
#include "DrawnObjects\VisST.h"
#include <vector>
using namespace zspace::common;
using namespace MHTypes;
using namespace std;
class VisPlane;
class DataAccessCSV;
class OpenGlScene
{
public:
  static void initialize();
  static void render();

  static void setStylusVisualizationEnabled(bool isStylusEnabled);
  static void setStylusTransform(const zspace::common::Matrix4& stylusTransform);

  static void rotateScene(float degrees);
  static void confirmSelection();
  static float getRotation();

private:
  static bool                    m_isStylusEnabled;
  static zspace::common::Matrix4 m_stylusTransform;
  static float                   m_cubeHalfSize;
  static VisST*					stMap;
  static DataAccessCSV*			data;
  static vector<int> ids;
  static vector<Point3D> points;
  static Ray ray;

private:
  static bool createTextureFromBmp(const char* filename);

  static void renderCube();
  static void renderStylus();
  static void renderAxes();
  static float rotation;
};


#endif // __ZSPACE_OPEN_GL_SCENE_H__