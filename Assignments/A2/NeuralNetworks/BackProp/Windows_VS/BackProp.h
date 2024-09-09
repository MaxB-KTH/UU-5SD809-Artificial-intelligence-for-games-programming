/*
 *  Backpropagation Algorithm
 *
 *  mtj@cogitollc.com
 *
 */

#include <iostream>
#include <math.h>
#include <cstdlib> //GNU under Linux
#include <time.h>
using namespace std;

#define sqr(x)          ((x) * (x))
#define RAND_WEIGHT     ( ((float)rand() / (float)RAND_MAX) - 0.5)
#define getSRand()      ((float)rand() / (float)RAND_MAX)
#define getRand(x)      (int)((float)(x)*rand()/(RAND_MAX+1.0))

class BackProp {
public:

    BackProp();
    
private:

    static const int INPUT_NEURONS  = 4,
                     HIDDEN_NEURONS = 3,
                     OUTPUT_NEURONS = 4,
                     MAX_SAMPLES    = 18;

    typedef struct {
        double health;
        double knife;
        double gun;
        double enemy;
        double out[OUTPUT_NEURONS];
    } ELEMENT;
    
    void   assignRandomWeights();
    double sigmoid(double val);
    double sigmoidDerivative(double val);
    void   feedForward();
    void   backPropagate(void);
    int    action( double *vector );
    int    run();//Main function from the original C-version
    
    /* Weight Structures */
    
    /* Input to Hidden Weights (with Biases) */
    double wih[INPUT_NEURONS+1][HIDDEN_NEURONS];
    
    /* Hidden to Output Weights (with Biases) */
    double who[HIDDEN_NEURONS+1][OUTPUT_NEURONS];
    
    /* Activations */
    double inputs[INPUT_NEURONS];
    double hidden[HIDDEN_NEURONS];
    double target[OUTPUT_NEURONS];
    double actual[OUTPUT_NEURONS];
    
    /* Unit Errors */
    double erro[OUTPUT_NEURONS];
    double errh[HIDDEN_NEURONS];
    
    static double LEARN_RATE;
    static ELEMENT samples[MAX_SAMPLES];    
    //static char *strings[4];//Original
    char (*strings)[16];//Modified
};

/*
 *  Copyright (c) 2003-2005 Charles River Media.  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or 
 *  without modification, is hereby granted without fee provided 
 *  that the following conditions are met:
 * 
 *    1.  Redistributions of source code must retain the above 
 *        copyright notice, this list of conditions and the 
 *        following disclaimer.
 *    2.  Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the 
 *        following disclaimer in the documentation and/or other 
 *        materials provided with the distribution.
 *    3.  Neither the name of Charles River Media nor the names of 
 *        its contributors may be used to endorse or promote 
 *        products derived from this software without specific 
 *        prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY CHARLES RIVER MEDIA AND CONTRIBUTORS 
 * 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CHARLES
 * RIVER MEDIA OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

