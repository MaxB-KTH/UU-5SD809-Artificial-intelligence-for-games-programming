//---------------------------------------------------------------------
//---------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------
#include <cmath>
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
//---------------------------------------------------------------------
#define For(i,N) for (int (i) = 0; (i) < (N); (i)++)
//---------------------------------------------------------------------
class Game {
public:
    //-------------------------------------------------------
    Game(void);
    ~Game(void);
    //-------------------------------------------------------
    void  InitGFX();
    void  ChangeSize(int w, int h);
    void  Draw();
    //-------------------------------------------------------
    void  NormalKeys(unsigned char key, int state);
    void  SpecialKeys(int key, int state);
    void  Mouse(int button, int state, int x, int y);
    void  MouseMotion(int x, int y);
    //-------------------------------------------------------
    float mW, mH;
    int   mCounter;
    int   mMouseX, mMouseY, mMouseMotionX, mMouseMotionY;
    int   mMouseButton, mMouseState;
    //-------------------------------------------------------
    GLUquadricObj * mQuadratic;
    //-------------------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
