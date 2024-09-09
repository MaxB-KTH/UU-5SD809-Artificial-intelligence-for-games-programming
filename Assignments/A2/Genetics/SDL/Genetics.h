//---------------------------------------------------------------------
//---------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------
#include <Math.h>
#include <stdio.h>
#include <stdarg.h>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
//---------------------------------------------------------------------
#define For(i,N) for (int (i) = 0; (i) < (N); (i)++)
//---------------------------------------------------------------------
class Genetics {
    //-------------------------------------------------------
    static const int MAX_CHROMS_M = 100;
    static const int MAX_CITIES_N = 20;// > 3
    static const int MAX_NEW_GENS = 300;
    //-------------------------------------------------------
    static const int MPCS_PER_MUTATION = 3;
    static const int PARENTS_N = .7 * MAX_CHROMS_M;
    static const int GFX_GENS_PER_FRAME = MAX_NEW_GENS/200;
    //-------------------------------------------------------
public:
    //-------------------------------------------------------
    Genetics();
    //-------------------------------------------------------
    void Init();
    void ChangeSize(int w, int h);
    void Draw();
    //-------------------------------------------------------
    void  NormalKeys(unsigned char key, int state);
    void  SpecialKeys(int key, int state);
    void  Mouse(int button, int state, int x, int y);
    //-------------------------------------------------------
    int  mW, mH;
    //-------------------------------------------------------
private:
    //-------------------------------------------------------
    void InitGFX();
    void InitMtxFont();
    void GFX_Text(double x, double y, const char *fmt,...);
    void Draw_MtxFont(double x, double y, Uint8 c);
    //-------------------------------------------------------
    int    Rand(int m);
    double RandX();
    //-------------------------------------------------------
    double GoalFunc(int chromIdx);
    void   EvalGoalFuncs();
    //-------------------------------------------------------
    void CopyChroms(int fromChromIdx, int toChromIdx);
    void SwapChroms(int cIdx1, int cIdx2);
    bool IsEqual(int cIdx1, int cIdx2);
    void PartialSort();
    void CloneChroms();
    //-------------------------------------------------------
    void Mutate(int chromIdx);
    void Mutate(int chromIdx, int a, int b);
    void TransformGP();
    //-------------------------------------------------------
    void GenCityCoords();
    void InitFirstGen();
    void EvalNextGen();
    //-------------------------------------------------------
    void MPC(int chromIdx1, int chromIdx2);
    //-------------------------------------------------------
    void MPC_T_RepairChrom(int chromIdx);
    //-------------------------------------------------------
    int  mMouseX, mMouseY;
    int  mMouseButton, mMouseState, mGlutGetModifiers;
    //-------------------------------------------------------
    int  mM = MAX_CHROMS_M;
    int  mN = MAX_CITIES_N;
    int  mGenIdx;
    double mStartValueBestChrom;
    unsigned int sRandSeed;
    //-------------------------------------------------------
    int  mFromIdx, mToIdx, mWidth;
    //-------------------------------------------------------
    double * mChromIdx2GoalFunc;//[MAX_CHROMS_M]
    double   (*mCityCoordinates)[2];//[MAX_CITIES_N][X/Y]
    int      (*mGP)[MAX_CITIES_N];//[MAX_CHROMS_M][MAX_CITIES_N]
    //-------------------------------------------------------
    char  (*mMtxFont)[7][5];
    //-------------------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
