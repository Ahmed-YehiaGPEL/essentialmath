//===============================================================================
// @ Game.cpp
// ------------------------------------------------------------------------------
// Game core routines
//
// Copyright (C) 2008 by Elsevier, Inc. All rights reserved.
//
//
//
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <IvRendererHelp.h>
#include <IvRenderer.h>
#include <IvVector4.h>
#include <IvMatrix44.h>
#include <IvEventHandler.h>
#include <GLUT/glut.h>
#include <OpenGL/CGLCurrent.h>
#include <OpenGL/OpenGL.h>

//*** delete this
#include <IvAABB.h>
#include <IvRay3.h>

#include "Game.h"
#include "Player.h"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

bool mUseFriction = false;

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ IvGame::Create()
//-------------------------------------------------------------------------------
// Static constructor
//-------------------------------------------------------------------------------
bool
IvGame::Create()
{
    IvGame::mGame = new Game();
    return ( IvGame::mGame != 0 );

}   // End of IvGame::Create()


//-------------------------------------------------------------------------------
// @ Game::Game()
//-------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------
Game::Game()
{
    // init variables
    mPlayer = 0;            // main player object
    
    mUseCollision = false;
    mUseFriction = false;

}   // End of Game::Game()


//-------------------------------------------------------------------------------
// @ Game::~Game()
//-------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------
Game::~Game()
{
    delete mPlayer;
    mPlayer = 0;

    mNumObjects = 0;
}   // End of Game::~Game()


//-------------------------------------------------------------------------------
// @ Game::PostRendererInitialize()
//-------------------------------------------------------------------------------
// Set up internal subsystems
//-------------------------------------------------------------------------------
bool 
Game::PostRendererInitialize()
{
    // Set up base class 
    IvGame::PostRendererInitialize();
    
    // set up initial player object
    mPlayer = new Player();
    if (!mPlayer)
        return false;
    mObjects[mNumObjects].Reset();
    mObjects[mNumObjects].SetTranslate( IvVector3( 0.0f, -20.0f, 0.0f ) );    
    mPlayer->mObject = &mObjects[mNumObjects++];

    // set up obstacles
    float yDiff = 15.0f;
    mObjects[mNumObjects].Reset();
    mObjects[mNumObjects++].SetTranslate( IvVector3( 0.0f, 3.8f+yDiff, 0.0f ) );
    mObjects[mNumObjects].Reset();
    mObjects[mNumObjects++].SetTranslate( IvVector3( 0.0f, 3.0f+yDiff, 0.0f ) );
    mObjects[mNumObjects].Reset();
    mObjects[mNumObjects++].SetTranslate( IvVector3( 0.0f, 2.2f+yDiff, 0.0f ) );
    mObjects[mNumObjects].Reset();
    mObjects[mNumObjects++].SetTranslate( IvVector3( 0.8f, 3.0f+yDiff, 0.0f ) );
    mObjects[mNumObjects].Reset();
    mObjects[mNumObjects++].SetTranslate( IvVector3( -0.8f, 3.0f+yDiff, 0.0f ) );
    mObjects[mNumObjects].Reset();
    mObjects[mNumObjects++].SetTranslate( IvVector3( 0.8f, 2.2f+yDiff, 0.0f ) );
    mObjects[mNumObjects].Reset();
    mObjects[mNumObjects++].SetTranslate( IvVector3( -0.8f, 2.2f+yDiff, 0.0f ) );
    mObjects[mNumObjects].Reset();
    mObjects[mNumObjects++].SetTranslate( IvVector3( 0.8f, 3.8f+yDiff, 0.0f ) );
    mObjects[mNumObjects].Reset();
    mObjects[mNumObjects++].SetTranslate( IvVector3( -0.8f, 3.8f+yDiff, 0.0f ) );
    
    ::IvSetDefaultLighting();
    
    //*** delete this
    IvAABB box(IvVector3(-1.0f, -1.0f, -1.0f), IvVector3(1.0f, 1.0f, 1.0f));
    IvRay3 ray(IvVector3(1.0, 0.0f, 0.0), IvVector3(-0.0f, -1.0f, -0.0f));
    
    return box.Intersect(ray);

    return true;
}   // End of Game::PostRendererInitialize()


static bool lastF;
static bool lastC;

//-------------------------------------------------------------------------------
// @ Game::Update()
//-------------------------------------------------------------------------------
// Update object information
//-------------------------------------------------------------------------------
void
Game::UpdateObjects( float dt )
{
    if (mEventHandler->IsKeyDown(' '))
    {
        mNumObjects = 0;
        mObjects[mNumObjects].Reset();
        mObjects[mNumObjects].SetTranslate( IvVector3( 0.0f, -20.0f, 0.0f ) );    
        mPlayer->mObject = &mObjects[mNumObjects++];
        
        // set up obstacles
        float yDiff = 15.0f;
        mObjects[mNumObjects].Reset();
        mObjects[mNumObjects++].SetTranslate( IvVector3( 0.0f, 3.8f+yDiff, 0.0f ) );
        mObjects[mNumObjects].Reset();
        mObjects[mNumObjects++].SetTranslate( IvVector3( 0.0f, 3.0f+yDiff, 0.0f ) );
        mObjects[mNumObjects].Reset();
        mObjects[mNumObjects++].SetTranslate( IvVector3( 0.0f, 2.2f+yDiff, 0.0f ) );
        mObjects[mNumObjects].Reset();
        mObjects[mNumObjects++].SetTranslate( IvVector3( 0.8f, 3.0f+yDiff, 0.0f ) );
        mObjects[mNumObjects].Reset();
        mObjects[mNumObjects++].SetTranslate( IvVector3( -0.8f, 3.0f+yDiff, 0.0f ) );
        mObjects[mNumObjects].Reset();
        mObjects[mNumObjects++].SetTranslate( IvVector3( 0.8f, 2.2f+yDiff, 0.0f ) );
        mObjects[mNumObjects].Reset();
        mObjects[mNumObjects++].SetTranslate( IvVector3( -0.8f, 2.2f+yDiff, 0.0f ) );
        mObjects[mNumObjects].Reset();
        mObjects[mNumObjects++].SetTranslate( IvVector3( 0.8f, 3.8f+yDiff, 0.0f ) );
        mObjects[mNumObjects].Reset();
        mObjects[mNumObjects++].SetTranslate( IvVector3( -0.8f, 3.8f+yDiff, 0.0f ) );
    }

    bool currF = mEventHandler->IsKeyDown('f');
    if (lastF != currF && currF)
    {
        mUseFriction = !mUseFriction;
    }
    lastF = currF;
    
    bool currC = mEventHandler->IsKeyDown('c');
    if (lastC != currC && currC)
    {
        mUseCollision = !mUseCollision;
    }
    lastC = currC;
    
    // update player
    mPlayer->Update( dt );
    
    if (mUseCollision)
    {
    for (unsigned int i = 0; i < mNumObjects; ++i)
    {
        for (unsigned int j = i+1; j < mNumObjects; ++j)
        {
            mObjects[i].HandleCollision( &mObjects[j] );
        }
    }
    }
    
    for (unsigned int i = 0; i < mNumObjects; ++i)
    {
        mObjects[i].Update( dt );
    }

    
}   // End of Game::UpdateObjects()


//-------------------------------------------------------------------------------
// @ Game::Render()
//-------------------------------------------------------------------------------
// Render stuff
//-------------------------------------------------------------------------------
void 
Game::Render()                                  // Here's Where We Do All The Drawing
{
    // Reset The View
    IvMatrix44 ortho;
    float left = -40.0f;
    float right = 40.0f;
    float bottom = -30.f;
    float top = 30.0f;
    float nearZ = -10.0f; 
    float farZ = 10.0f;
	if ( IvRenderer::mRenderer->GetAPI() == kOpenGL )
	{
		float recipX = 1.0f/(right-left);
		float recipY = 1.0f/(top-bottom);
		float recipZ = 1.0f/(nearZ-farZ);

		ortho(0,0) = 2.0f*recipX;
		ortho(0,3) = -(right+left)*recipX;

		ortho(1,1) = 2.0f*recipY;
		ortho(1,3) = -(top+bottom)*recipY;

		ortho(2,2) = 2.0f*recipZ;
		ortho(2,3) = (nearZ+farZ)*recipZ;
	}
	else
	{
		float recipX = 1.0f/(right-left);
		float recipY = 1.0f/(top-bottom);
		float recipZ = 1.0f/(farZ-nearZ);

		ortho(0,0) = 2.0f*recipX;
		ortho(0,3) = -(right+left)*recipX;

		ortho(1,1) = 2.0f*recipY;
		ortho(1,3) = -(top+bottom)*recipY;

		ortho(2,2) = recipZ;
		ortho(2,3) = -nearZ*recipZ;
	}

    // send to renderer
    ::IvSetProjectionMatrix( ortho );
        
    // draw axes
    ::IvDrawAxes();
    
    for (unsigned int i = 0; i < mNumObjects; ++i)
    {
        mObjects[i].Render();
    }
    
    // draw the collision state
    IvSetWorldIdentity();
    glRasterPos3f(-37, 27, 0);
    char outString[256];
    strncpy(outString, "Collision: ", 255);
    if (mUseCollision)
    {
        strncat(outString, "On", 244);
    }
    else
    {
        strncat(outString, "Off", 244);
    }
    for (char* c=outString; *c != '\0'; c++) 
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    
    // draw the collision state
    glRasterPos3f(-37, 25, 0);
    strncpy(outString, "Friction: ", 255);
    if (mUseFriction)
    {
        strncat(outString, "On", 244);
    }
    else
    {
        strncat(outString, "Off", 244);
    }
    for (char* c=outString; *c != '\0'; c++) 
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    
}