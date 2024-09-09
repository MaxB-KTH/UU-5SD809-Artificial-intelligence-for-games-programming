//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
//-----------------------------------------------------------------------
typedef unsigned char  UCHAR;
typedef unsigned short USHORT;
typedef unsigned int   UINT;
//-----------------------------------------------------------------------
class MidiGen {
public:
    //-----------------------------------
    MidiGen(void);
    ~MidiGen(void);
private:
	//-----------------------------------
	static const int TRACK_BUFFER_SIZE = 1 << 16;
    //-----------------------------------
    enum NOTE_STATE {NOTE_OFF,NOTE_ON};
    //-----------------------------------Core
    void   GenerateMidi();
    void   InsertVarLengthData(UINT value);
    //-----------------------------------
    void   InsertNote(UINT deltaTime, UCHAR pitch, UCHAR vel);
    void   Insert_MicroTempo(int microTempo);
    void   Insert_TimeSignature(UCHAR num, UCHAR den);
    USHORT FlipEndian(USHORT x);
    UINT   FlipEndian(UINT x);
    //-----------------------------------File
public:
    void F_ExportMidi();
private:
    void F_WriteFileHeader(USHORT numTracks);
    void F_WriteTrack();
    //-----------------------------------
    UCHAR *mTrack;
    int    mN;
    //-----------------------------------
    UCHAR  mChannel;
    USHORT mPPQN;
    float  mTempo;
    //-----------------------------------
    char * mFileName;
    ofstream mOutFile;
    //-----------------------------------
};
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------