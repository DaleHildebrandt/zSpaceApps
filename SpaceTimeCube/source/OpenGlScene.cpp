//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       OpenGlScene.cpp
//  Content:    The OpenGlScene class for the zSpace OpenGl stereo samples.
//
//////////////////////////////////////////////////////////////////////////////

#include "OpenGlScene.h"

#include "ZSpace/Common/Math/AxisAlignedBox.h"
#include "ZSpace/Common/Math/MathConverterGl.h"
#include "ZSpace/Common/Math/Ray.h"

#include "DataAccess\DataAccessCSV.hpp"
#include "DrawnObjects\VisPlane.h"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <stdio.h>
#include <SOIL.h>

#include <sstream>

//////////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////////

GLfloat LIGHT_COLOR[]         = {0.4f, 0.4f, 0.4f, 1.0f};
GLfloat LIGHT_POSITION[]      = {0.2f, 0.2f, 0.6f, 1.0f}; 
GLfloat AMBIENT_LIGHT_MODEL[] = {0.5f, 0.5f, 0.5f, 1.0f}; 
GLfloat AMBIENT_MATERIAL[]    = {1.0f, 1.0f, 1.0f, 1.0f};


//////////////////////////////////////////////////////////////////////////
// Static Member Initialization
//////////////////////////////////////////////////////////////////////////

bool OpenGlScene::m_isStylusEnabled = false;
zspace::common::Matrix4 OpenGlScene::m_stylusTransform = zspace::common::Matrix4::IDENTITY();
float OpenGlScene::m_cubeHalfSize = 0.03f;

VisST *OpenGlScene::stMap;
DataAccessCSV *OpenGlScene::data;

vector<int> OpenGlScene::ids;
vector<Point3D> OpenGlScene::points;

zspace::common::Ray OpenGlScene::ray;
float OpenGlScene::rotation = 0.0f;

//////////////////////////////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////////////////////////////

void OpenGlScene::initialize()
{
  // Set up the scene's mono (non-stereoscopic) model-view matrix.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //gluLookAt(0.0f,   0.345f,   0.222f,   // Position
  //          0.0f,   0.0f,     0.0f,     // Lookat
  //          0.0f,   1.0f,     0.0f);    // Up 

    gluLookAt(0.0f,   0.4f,   0.65f,   // Position
            0.0f,   0.15f,     0.0f,     // Lookat
            0.0f,   1.0f,     0.0f);    // Up 

  // Set material light reflection properties
  glMaterialfv(GL_FRONT, GL_AMBIENT, AMBIENT_MATERIAL);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, AMBIENT_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

   //Enable a single OpenGl light.
  glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_COLOR);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AMBIENT_LIGHT_MODEL);

  // Enable lighting.
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);

  // Enable depth testing.
  glEnable(GL_DEPTH_TEST);

 // // Set up textures.
 // GLuint textureId;
 // glGenTextures(1, &textureId);
 // glBindTexture(GL_TEXTURE_2D, textureId);
 // glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

 // // Load texture from bmp file. If load fails, try parent dir.
 // if (!createTextureFromBmp("Infinite_Z_Logo.bmp"))
 //   createTextureFromBmp("..\\Infinite_Z_Logo.bmp");

 // // Set up and enable texture mapping
 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
 // glEnable(GL_TEXTURE_2D);


 // // Loads texture
	//texture = SOIL_load_OGL_texture(
	//			"C:\\images\\11.jpg",
	//			SOIL_LOAD_AUTO,
	//			SOIL_CREATE_NEW_ID,
	//			SOIL_FLAG_INVERT_Y
	//			);

	//// Set up and enable texture mapping
 //   glBindTexture(GL_TEXTURE_2D, texture);
 //   //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
 //   //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);

	//Dimensions of loaded texture should be a multiple of 4.
	
	data = new DataAccessCSV("data/dataset2/DataSet.csv", 0.5403, 0.5);
	ids = data->getIDs();
	stMap = new VisST(0.5, 0.5, "data/dataset2/11.jpg", data);
	
	rotation = 0;
	//data->loadData();
	//data->organizeData();

} 


void OpenGlScene::render()
{
  // Clear color and depth buffers
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //renderCube();

  renderStylus();

  //renderAxes();

  stMap->render();

  std::ostringstream ss;

  if (m_isStylusEnabled)
    renderStylus();
  std::string text = "test";
  //glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)(text.c_str()));
}


void OpenGlScene::setStylusVisualizationEnabled(bool isStylusEnabled)
{
  m_isStylusEnabled = isStylusEnabled;
}


void OpenGlScene::setStylusTransform(const zspace::common::Matrix4& stylusTransform)
{
  m_stylusTransform = stylusTransform;
}


void OpenGlScene::rotateScene(float degrees)
{
  //glMatrixMode(GL_MODELVIEW);
  //glRotatef((GLfloat)degrees, (GLfloat)0.0, (GLfloat)1.0, (GLfloat)0.0);
	rotation += degrees;
	stMap->setRotation(rotation);
}



//////////////////////////////////////////////////////////////////////////
// Private Methods
//////////////////////////////////////////////////////////////////////////

// Fairly limited bmp texture loader. BMP files must be 
// single-plane 24-bit color format.
bool OpenGlScene::createTextureFromBmp(const char* filename)
{
  if (!filename)
    return false;

  FILE* fileHandle = NULL;
  fopen_s(&fileHandle, filename, "rb");

  if (!fileHandle)
    return false;

  // Read the bmp header.
  static const int bmpHeaderSize = 54;
  BYTE header[bmpHeaderSize];
  fread(header, bmpHeaderSize, 1, fileHandle);

  // Make sure we've got a bmp file.
  if ((header[0] != 'B' || header[1] != 'M'))
    goto fail;

  // Make sure have a V3 header.
  int dataOffset = *(int*)&header[10];
  if (dataOffset != bmpHeaderSize)
    goto fail;

  // Only handle single color planes.
  short numColorPlanes = *(short*)&header[26];
  if (numColorPlanes != 1)
    goto fail;

  // Only handle 24-bit color.
  short bitsPerPixel = *(short*)&header[28];
  if (bitsPerPixel != 24)
    goto fail;

  // Get image dimensions from header.
  int imageWidth  = *(int*)&header[18];
  int imageHeight = *(int*)&header[22];

  // Bmp is 4-byte aligned, compute row width.
  int rowWidth = (((imageWidth*3)+3)>>2)<<2;

  // Make sure we have the expected file size.
  int expectedFileSize = bmpHeaderSize + (rowWidth * imageHeight);
  int fileSize = *(int*)&header[2];
  if (fileSize != expectedFileSize)
    goto fail;

  // Allocate buffer.
  BYTE* data = (BYTE*)malloc(fileSize);
  if(!data)
    goto fail;

  // Read pixel data from bmp.
  fread(data, fileSize - bmpHeaderSize, 1, fileHandle);

  // Done with file.
  fclose(fileHandle);

  // Create a texture from the pixel data.
  glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidth, imageHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

  // glTexImage2D creates a texture from data[] so we can free it now.
  free(data);

  // Success.
  return true;

fail:
  fclose(fileHandle);
  return false;
}

void OpenGlScene::confirmSelection()
{
	stMap->confirmSelection();
}

float OpenGlScene::getRotation()
{
	return rotation;
}

void OpenGlScene::renderCube()
{
  glColor3f(1.0f, 1.0f, 1.0f);

  // Render the cube
  glBegin(GL_QUADS);			
  const float halfSize = m_cubeHalfSize;

  // Side 1
  glNormal3f(0.0f, 0.0f, -1.0f);
  glTexCoord2d(1.0,0.0); glVertex3f(-halfSize, -halfSize, -halfSize);
  glTexCoord2d(1.0,1.0); glVertex3f(-halfSize,  halfSize, -halfSize);
  glTexCoord2d(0.0,1.0); glVertex3f( halfSize,  halfSize, -halfSize);        
  glTexCoord2d(0.0,0.0); glVertex3f( halfSize, -halfSize, -halfSize);		

  // Side 2
  glNormal3f(0.0f, 0.0f, 1.0f);
  glTexCoord2d(0.0,1.0); glVertex3f(-halfSize,  halfSize, halfSize);
  glTexCoord2d(0.0,0.0); glVertex3f(-halfSize, -halfSize, halfSize);        
  glTexCoord2d(1.0,0.0); glVertex3f( halfSize, -halfSize, halfSize);
  glTexCoord2d(1.0,1.0); glVertex3f( halfSize,  halfSize, halfSize);

  // Side 3
  glNormal3f(0.0f, 1.0f, 0.0f);
  glTexCoord2d(0.0,1.0); glVertex3f(-halfSize, halfSize, -halfSize);
  glTexCoord2d(0.0,0.0); glVertex3f(-halfSize, halfSize,  halfSize);
  glTexCoord2d(1.0,0.0); glVertex3f( halfSize, halfSize,  halfSize);        
  glTexCoord2d(1.0,1.0); glVertex3f( halfSize, halfSize, -halfSize);

  // Side 4
  glNormal3f(0.0f, -1.0f, 0.0f);
  glTexCoord2d(0.0,1.0); glVertex3f(-halfSize, -halfSize,  halfSize);
  glTexCoord2d(0.0,0.0); glVertex3f(-halfSize, -halfSize, -halfSize);
  glTexCoord2d(1.0,0.0); glVertex3f( halfSize, -halfSize, -halfSize);
  glTexCoord2d(1.0,1.0); glVertex3f( halfSize, -halfSize,  halfSize);

  // Side 5
  glNormal3f(1.0f, 0.0f, 0.0f);
  glTexCoord2d(1.0,1.0); glVertex3f( halfSize,  halfSize, -halfSize);
  glTexCoord2d(0.0,1.0); glVertex3f( halfSize,  halfSize,  halfSize);        
  glTexCoord2d(0.0,0.0); glVertex3f( halfSize, -halfSize,  halfSize);
  glTexCoord2d(1.0,0.0); glVertex3f( halfSize, -halfSize, -halfSize);

  // Side 6
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glTexCoord2d(0.0,1.0); glVertex3f(-halfSize,  halfSize, -halfSize);
  glTexCoord2d(0.0,0.0); glVertex3f(-halfSize, -halfSize, -halfSize);        
  glTexCoord2d(1.0,0.0); glVertex3f(-halfSize, -halfSize,  halfSize);
  glTexCoord2d(1.0,1.0); glVertex3f(-halfSize,  halfSize,  halfSize);

  glEnd();
}

void OpenGlScene::renderAxes()
{

	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glLineWidth(1);
	glColor3f(1.0, 1.0, 1.0);

}


void OpenGlScene::renderStylus()
{
  float stylusLength = 0.5f;
  zspace::common::Vector4 color = zspace::common::Vector4::WHITE();

  // Create an intersection ray based on the position and direction
  // of the stylus world pose.
  zspace::common::Vector3 position = m_stylusTransform.getTrans();
  zspace::common::Vector3 direction(-m_stylusTransform[0][2], -m_stylusTransform[1][2], -m_stylusTransform[2][2]);
  ray = zspace::common::Ray(position, direction);

  // In the OpenGl stereo samples, it may look like the cube is rotating, 
  // but we are actually orbiting the monoscopic camera about 
  // the cube.  So, we can create an axis aligned box (AABB) based 
  // on the half extents of the cube.  An AABB can be used to represent
  // the cube because the cube is axis-aligned and never has its orientation 
  // modified.  
  zspace::common::AxisAlignedBox box = 
    zspace::common::AxisAlignedBox(-m_cubeHalfSize, -m_cubeHalfSize, -m_cubeHalfSize, m_cubeHalfSize, m_cubeHalfSize, m_cubeHalfSize);

  // Perform a ray vs. AABB intersection query to determine if the stylus
  // is intersecting with the cube.
  //std::pair<bool, float> result = ray.intersects(box);

  std::pair<bool, float> result = stMap->testIntersection(ray, stylusLength);

  stMap->setPlane(ray.getPoint(stylusLength));

  // If the stylus intersected the cube, change the stylus color to red
  // and set its length to the intersection distance.
  if (result.first == true)
  {
    // Since the intersection uses an infinite ray, we need to check that
    // the intersection distance is less than the stylus beam's original
    // length for it to be considered a valid intersection.
    if (result.second < stylusLength)
    {
      stylusLength = result.second;
      color = zspace::common::Vector4::RED();
    }
  }

  // Render the stylus beam.
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // Convert the stylus world pose to OpenGl matrix format and apply it to
  // the virtual stylus beam's transform.
  GLfloat stylusTransformGl[16];
  zspace::common::MathConverterGl::convertMatrix4ToMatrixGl(m_stylusTransform, stylusTransformGl);
  glMultMatrixf(stylusTransformGl);

  glColor3f(color.x, color.y, color.z);
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, -stylusLength);
  glEnd();
  glEnable(GL_LIGHTING);

  glPopMatrix();
}