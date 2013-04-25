//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       StereoNoTracking.cpp
//
//////////////////////////////////////////////////////////////////////////////
//StereoNoTracking.cpp
//Contains main program loop

#include <Windows.h>
#include <gl/GL.h>

#include "OpenGlScene.h"
#include "Utilities\ButtonManager.h"

#include "Utilities\OpenGlWindow.h"
#include "Utilities\ObjectTracker.h"

#include "ZSpace/Common/Math/MathConverterGl.h"
#include "ZSpace/Common/Math/Matrix4.h"

#include "ZSpace/Stereo/StereoFrustum.h"
#include "ZSpace/Stereo/StereoLeftRightDetect.h"
#include "ZSpace/Stereo/StereoViewport.h"
#include "ZSpace/Stereo/StereoWindow.h"




//////////////////////////////////////////////////////////////////////////
// Globals
//////////////////////////////////////////////////////////////////////////

OpenGlWindow* g_applicationWindow = NULL;

zspace::stereo::StereoWindow* g_stereoWindow     = NULL;
zspace::stereo::StereoViewport* g_stereoViewport = NULL;
zspace::stereo::StereoFrustum* g_stereoFrustum   = NULL;

ObjectTracker* objectTracker = NULL; //Handles tracking of head and stylus

bool* buttonStates = NULL; //Records whether or not each button on the zspace stylus is pressed

const int DEFAULT = 0;
const int POINT_SELECT_MODE = 0;
const int HEIGHT_FILTER_MODE = 1;
int interactionMode = POINT_SELECT_MODE;
int interactionState = DEFAULT;



//////////////////////////////////////////////////////////////////////////
// Function Prototypes
//////////////////////////////////////////////////////////////////////////

void zSpaceInitialize();
void zSpaceUpdate();
void zSpaceShutdown();
void renderFrame();
void renderScene(zspace::stereo::StereoFrustum::StereoEye eye);
void setupViewMatrix(zspace::stereo::StereoFrustum::StereoEye eye);
void setupProjectionMatrix(zspace::stereo::StereoFrustum::StereoEye eye);
void processStylusInput();


//////////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
                   HINSTANCE	hPrevInstance,	// Previous Instance
                   LPSTR		  lpCmdLine,			// Command Line Parameters
                   int			  nCmdShow)				// Window Show State
{
  //Creates Console window for diaplying all output
  AllocConsole();
  freopen("CONOUT$", "w+", stdout);

  g_applicationWindow = new OpenGlWindow("zSpace - Space-Time Cube", 0, 0, 1024, 768);
  
  zSpaceInitialize();
  OpenGlScene::initialize();

  MSG msg;
  while (TRUE)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    // If 'escape' was pressed, exit the application.
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
      PostMessage(g_applicationWindow->getWindowHandle(), WM_DESTROY, 0, 0);
	if (GetAsyncKeyState(VK_ESCAPE) & 0x51)
		interactionMode = HEIGHT_FILTER_MODE;
    // Render the current frame.
    zSpaceUpdate();
	processStylusInput();
    renderFrame();
  }

  zSpaceShutdown();

  if (g_applicationWindow)
    delete g_applicationWindow;

  return 0;
}


//////////////////////////////////////////////////////////////////////////
// Function Definitions
//////////////////////////////////////////////////////////////////////////

// <SampleCode zSpace Initialize>
void zSpaceInitialize()
{
  // zSpace Stereo Initialization.
  g_stereoWindow   = new zspace::stereo::StereoWindow();
  g_stereoViewport = new zspace::stereo::StereoViewport();

  g_stereoWindow->addStereoViewport(g_stereoViewport);
  g_stereoViewport->setUsingWindowSize(true);
  g_stereoFrustum = g_stereoViewport->getStereoFrustum();

  // Initialize zSpace Left/Right Detection.
  zspace::stereo::StereoLeftRightDetect::initialize(g_stereoWindow, zspace::stereo::StereoLeftRightDetect::WINDOW_TYPE_GL);

  //Create Tracker for head movement and stylus movement + input
  objectTracker = new ObjectTracker(g_stereoFrustum, g_stereoWindow);

  //Sets up button manager to keep track of button state
  ButtonManager::init();
}
// </SampleCode zSpace Initialize>

void processStylusInput()
{
	//if(buttonStates){
	//	/*if(buttonStates[1]){
	//		if(interactionMode != HEIGHT_FILTER_MODE)
	//			interactionState = DEFAULT;
	//		interactionMode = HEIGHT_FILTER_MODE;
	//	}
	//	else if(buttonStates[2]){
	//		if(interactionMode != POINT_SELECT_MODE)
	//			interactionState = DEFAULT;
	//		interactionMode = POINT_SELECT_MODE;
	//	}*/
	//	if(buttonStates[1]){
	//		OpenGlScene::rotateScene();
	//	}

	//	if(interactionMode == POINT_SELECT_MODE){
	//		if(buttonStates && buttonStates[0]){
	//			OpenGlScene::confirmSelection();
	//			cout << "Confirming Stylus Selection" << endl;
	//		}
	//	}
	//	else if (interactionMode == HEIGHT_FILTER_MODE){
	//		//OpenGlScene::setHeightFilter(interactionState);
	//	}
	//}
	
	//cout << "Processing Button input: " << "button[0]: " << buttonStates[0] << std::endl;

		if(ButtonManager::isButtonPressed(0)){
			OpenGlScene::confirmSelection();
			cout << "Confirming Stylus Selection" << endl;
		}
		
		if(ButtonManager::isButtonHeld(1)){
			OpenGlScene::rotateScene(-3.0);
		}
		if(ButtonManager::isButtonHeld(2)){
			OpenGlScene::rotateScene(3.0);
		}
	
}

void zSpaceUpdate()
{
  // <SampleCode zSpace Update L/R Detection>
  // Update zSpace Left/Right Frame Detection.
  zspace::stereo::StereoLeftRightDetect::update();
  // </SampleCode zSpace Update L/R Detection>

  // <SampleCode zSpace Window Move>
  // Check if the application window has moved.  If so, update the 
  // StereoWindow's position to reflect the application window's new position.
  int x = g_applicationWindow->getX();
  int y = g_applicationWindow->getY();

  if (g_stereoWindow->getX() != x || g_stereoWindow->getY() != y)
    g_stereoWindow->move(x, y);
  // </SampleCode zSpace Window Move>

  // <SampleCode zSpace Window Resize>
  // Check if the application window has been resized.  If so, update
  // the zSpace StereoWindow's dimensions to reflect the application 
  // window's new size.
  int width  = g_applicationWindow->getWidth();
  int height = g_applicationWindow->getHeight();

  if (g_stereoWindow->getWidth() != width || g_stereoWindow->getHeight() != height)
  {
    g_stereoWindow->resize(width, height);
    glViewport(0, 0, width, height);
  }

  //Update head and stylus tracking
  objectTracker->UpdateHead();
  objectTracker->UpdateStylus(buttonStates);
  // </SampleCode zSpace Window Resize>
}


// <SampleCode zSpace Shutdown>
void zSpaceShutdown()
{
  // Shutdown zSpace Left/Right Frame Detection.
  zspace::stereo::StereoLeftRightDetect::shutdown();

  // Remove references to any zSpace objects that have been allocated.
  if (g_stereoWindow)
    g_stereoWindow->removeReference();

  if (g_stereoViewport)
    g_stereoViewport->removeReference();

	if(objectTracker)
		delete objectTracker;
}
// </SampleCode zSpace Shutdown>


// <SampleCode zSpace Render Frame>
void renderFrame()
{
  // Set the application window's rendering context as the current rendering context.
  wglMakeCurrent(g_applicationWindow->getDeviceContext(), g_applicationWindow->getRenderingContext());

  // Orbit the monoscopic camera about the center of the scene.
  //OpenGlScene::rotateScene();

  // Render the scene for each eye.
  renderScene(zspace::stereo::StereoFrustum::STEREO_EYE_LEFT);
  renderScene(zspace::stereo::StereoFrustum::STEREO_EYE_RIGHT);

  // Flush the render buffers.
  SwapBuffers(g_applicationWindow->getDeviceContext());
}
// </SampleCode zSpace Render Frame>


// <SampleCode zSpace Render Scene>
void renderScene(zspace::stereo::StereoFrustum::StereoEye eye)
{
  // Push the stereo view and projection matrices onto the OpenGl matrix stack
  // so that we can pop them off after we're done rendering the scene
  // for a specified eye.  This will allow us to restore the mono (non-
  // stereoscopic) model-view and projection matrices.
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  // Set up the view and projection matrices for the specified eye.
  setupViewMatrix(eye);
  setupProjectionMatrix(eye);

  // Select appropriate back buffer to render to based on the specified eye.
  if (eye == zspace::stereo::StereoFrustum::STEREO_EYE_LEFT)
    glDrawBuffer(GL_BACK_LEFT);
  else if (eye == zspace::stereo::StereoFrustum::STEREO_EYE_RIGHT)
    glDrawBuffer(GL_BACK_RIGHT);

  // Render the scene.
  OpenGlScene::render();

  // Restore the mono (non-stereoscopic) model-view and projection matrices.
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}
// </SampleCode zSpace Render Scene>


// <SampleCode zSpace Setup View Matrix>
void setupViewMatrix(zspace::stereo::StereoFrustum::StereoEye eye)
{
  GLfloat viewMatrixGl[16];
  GLfloat monoModelViewGl[16];

  // Get the view matrix from the zSpace StereoFrustum for a specified eye
  // and convert it into OpenGl matrix format.
  zspace::common::Matrix4 viewMatrix;
  g_stereoFrustum->getViewMatrix(eye, viewMatrix);
  zspace::common::MathConverterGl::convertMatrix4ToMatrixGl(viewMatrix, viewMatrixGl);

  // Set the OpenGl MatrixMode to GL_MODELVIEW and get the mono (non-stereoscopic) 
  // model-view matrix.
  glMatrixMode(GL_MODELVIEW);
  glGetFloatv(GL_MODELVIEW_MATRIX, monoModelViewGl);

  // Set the model-view matrix for the specified eye and multiply it by the
  // mono (non-stereoscopic) model-view matrix.  This must be done because the
  // eye's view matrix only contains the eye offset (relative to the center of
  // the viewer's head) plus any rotation required for off-axis projection.
  glLoadMatrixf(viewMatrixGl);
  glMultMatrixf(monoModelViewGl);
}
// </SampleCode zSpace Setup View Matrix>


// <SampleCode zSpace Setup Projection Matrix>
void setupProjectionMatrix(zspace::stereo::StereoFrustum::StereoEye eye)
{
  GLfloat projectionMatrixGl[16];

  // Get the projection matrix from the zSpace StereoFrustum for a specified eye
  // and convert it into OpenGl matrix format.
  zspace::common::Matrix4 projectionMatrix;
  g_stereoFrustum->getProjectionMatrix(eye, projectionMatrix);
  zspace::common::MathConverterGl::convertMatrix4ToMatrixGl(projectionMatrix, projectionMatrixGl);

  // Set OpenGl MatrixMode to GL_PROJECTION and set the projection matrix.
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(projectionMatrixGl);
}
// </SampleCode zSpace Setup Projection Matrix>