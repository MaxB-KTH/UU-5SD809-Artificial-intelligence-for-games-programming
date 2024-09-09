/*
 *  Backpropagation Algorithym -- Simple MLP Training Example
 *
 *  mtj@cogitollc.com
 *
 */

#include <iostream>
#include <time.h>
#include <cstdlib> //GNU under Linux
#include <math.h>
using namespace std;

#define getRand(x)	(int)((float)(x)*rand()/(RAND_MAX+1.0))
#define RAND_WEIGHT	(((double)rand() / (double)RAND_MAX))
#define sqr(x)		((x) * (x))

class MLP_BP {
public:

    MLP_BP();
    
private:

    const static int NUM_EPOCHS = 10000;
    
    typedef struct {
        double inp0;
        double inp1;
        double outp;
    } dataset_t;
    
    double sigmoid(double val);
    double sigmoidDerivative(double val);
    void   initializeNetwork();
    void   feedforward();
    void   backpropagate();
    int    run();//Main function from the original C-version
    
    double inp_0, inp_1;
    double hid_0, hid_1;
    double outp;
    double target;
    
    double w_hid0inp0, w_hid0inp1, w_hid1inp0, w_hid1inp1;
    double w_outph0, w_outph1;
    double h0_bias, h1_bias, outp_bias;
    
    static dataset_t dataset[4];
    static double rho;
    
    static double HIGH;
    static double LOW;
    static double MID;
    
};

/*
 *  Copyright (c) 2003-2005 Charles River Media.  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or 
 *  withoutp modification, is hereby granted withoutp fee provided 
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
 *        products derived from this software withoutp specific 
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
 * ANY WAY outp OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

