//---------------------------------------------------------------------
//---------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------
#include <cmath>
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
//---------------------------------------------------------------------
#define For(i,N) for (int (i) = 0; (i) < (N); (i)++)
//---------------------------------------------------------------------
class Game {
public:
    //-------------------------------------------------------
    Game(void);
    //-------------------------------------------------------
    void  ChangeSize(int w, int h);
    void  Draw();
    //-------------------------------------------------------
    void  NormalKeys(unsigned char key, int state);
    void  SpecialKeys(int key, int state);
    void  Mouse(int button, int state, int x, int y);
    void  MouseMotion(int x, int y);
    //-------------------------------------------------------
	void  InitMtxFont();
	void  Draw_MtxText(float x, float y, const char *fmt,...);
	void  Draw_MtxFont(float x, float y, Uint8 c);
    //-------------------------------------------------------
    float mW, mH;
    int   mCounter;
    int   mMouseX, mMouseY, mMouseMotionX, mMouseMotionY;
    int   mMouseButton, mMouseState;
    //-------------------------------------------------------
    char  (*mMtxFont)[7][5];
    //-------------------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
