//---------------------------------------------------------------------
//---------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <thread>
#include <GL\glut.h>//Or just "glut.h"
#include <iostream>
//---------------------------------------------------------------------
#define For(i,N)  for (int (i) = 0; (i) < (N); (i)++)
//---------------------------------------------------------------------
class Game {
public:
    //-------------------------------------------------------
    static const int GRID_SIZE_X = 50, GRID_SIZE_Y = 25;
    static const int SPACING     = 15, POINT_SIZE  = 12;
    //-------------------------------------------------------
    Game(void);
    ~Game(void);
    //-------------------------------------------------------
    void ChangeSize(int w, int h);
    void Draw();
    //-------------------------------------------------------
    void NormalKeys(unsigned char key, int x, int y);
    void SpecialKeys(int key, int x, int y);
    void Mouse(int button, int state, int x, int y);
    //-------------------------------------------------------
    int  mW, mH;
    //-------------------------------------------------------
private:
    int CountNeighbors(int y, int x);
    bool NextState(bool currentState, int neighbours);
    void ResetBuffers();
    void Add_Glider(int i, int j);
    void Add_LightweightSpaceship(int i, int j);
    void Add_GosperGliderGun(int i, int j);
    //-------------------------------------------------------
    void UpdateFrontBuffer();
    int  mMouseX, mMouseY;
    int  mMouseButton, mMouseState, mGlutGetModifiers;
    //-------------------------------------------------------
    bool (*mM)[GRID_SIZE_Y][GRID_SIZE_X];
    int  mFrontBufferIdx;
    //-------------------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
