/*
 *  Backpropagation Algorithym -- Simple MLP Training Example
 *
 *  mtj@cogitollc.com
 *
 */

#include "MLP_BP.h"

MLP_BP::MLP_BP(){
    run();
};

double MLP_BP::rho  = 3.0;
double MLP_BP::HIGH = 0.9;
double MLP_BP::LOW  = 0.1;
double MLP_BP::MID  = (LOW + ((HIGH-LOW)/2.0));

/* Xor dataset */
MLP_BP::dataset_t MLP_BP::dataset[4] = {
    {  LOW,  LOW,  LOW},
    {  LOW, HIGH, HIGH},
    { HIGH,  LOW, HIGH},
    { HIGH, HIGH,  LOW}
};

double MLP_BP::sigmoid( double val )
{
    return (1.0 / (1.0 + exp(-val)));
}

double MLP_BP::sigmoidDerivative( double val )
{
    return (val * (1.0 - val));
}

void MLP_BP::initializeNetwork( void )
{
    w_hid0inp0 = RAND_WEIGHT; w_hid0inp1 = RAND_WEIGHT;
    w_hid1inp0 = RAND_WEIGHT; w_hid1inp1 = RAND_WEIGHT;
    w_outph0 = RAND_WEIGHT;    w_outph1 = RAND_WEIGHT;
    
    h0_bias = RAND_WEIGHT; h1_bias = RAND_WEIGHT; outp_bias = RAND_WEIGHT;
    
    return;
}

void MLP_BP::feedforward( void )
{
    /* First, calculate hidden node 0 */
    hid_0 = sigmoid( (inp_0 * w_hid0inp0) + (inp_1 * w_hid0inp1) + h0_bias );
    
    /* Next, calculate hidden node 1 */
    hid_1 = sigmoid( (inp_0 * w_hid1inp0) + (inp_1 * w_hid1inp1) + h1_bias );
    
    /* Finally, calculate the outpput node */
    outp = sigmoid(((hid_0 * w_outph0) + (hid_1 * w_outph1) + outp_bias));
    
    return;
}

void MLP_BP::backpropagate( void )
{
    double outp_err, hid0_err, hid1_err;
    
    /* Calculate outpput layer error */
    outp_err = (target - outp) * sigmoidDerivative(outp);  
    
    /* Calculate the hidden layer error */
    hid0_err = (outp_err * w_outph0) * sigmoidDerivative(hid_0);
    hid1_err = (outp_err * w_outph1) * sigmoidDerivative(hid_1);
    
    /* Updated the outpput layer weights (and bias) */
    w_outph0  += (rho * outp_err * hid_0);
    w_outph1  += (rho * outp_err * hid_1);
    outp_bias += (rho * outp_err);
    
    /* Update weights for hidden node 0 and bias */
    w_hid0inp0 += ((rho * hid0_err) * inp_0);
    w_hid0inp1 += ((rho * hid0_err) * inp_1);
    h0_bias += (rho * hid0_err);
    
    /* Update weights for hidden node 1 and bias */
    w_hid1inp0 += ((rho * hid1_err) * inp_0);
    w_hid1inp1 += ((rho * hid1_err) * inp_1);
    h1_bias += (rho * hid1_err);
    
    return;
}

int MLP_BP::run() //Main function from the original C-version
{
    double error;
    int epoch, i;
    
    srand(time(NULL));
    
    initializeNetwork();
    
    for (epoch = 0 ; epoch < NUM_EPOCHS ; epoch++) {
        
        i = getRand(4);
        inp_0 = dataset[i].inp0; 
        inp_1 = dataset[i].inp1;
        target = dataset[i].outp;
        
        feedforward();
        backpropagate();
        
        error = 0.5 * (sqr(target - outp));
        printf("%lg\n", error);
        
    }; 
    
    std::cout << "Testing..." << std::endl;
    
    /* Test the network */
    for (i = 0 ; i < 4 ; i++) {
        
        inp_0 = dataset[i].inp0;
        inp_1 = dataset[i].inp1;
        target = dataset[i].outp;
        feedforward();
        
        cout << "test " << inp_0 << "/" << inp_1 << " = " << outp << endl;
        
        outp = (outp >= MID) ? HIGH : LOW;
        
        if (outp == target) cout << "Success" << endl;
        else cout << "Failed" << endl;
        
    };
    
    return 0;
}

/*
 * Copyright (c) 2003-2005 Charles River Media.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or 
 * withoutp modification, is hereby granted withoutp fee provided 
 * that the following conditions are met:
 *
 *   1.  Redistributions of source code must retain the above 
 *       copyright notice, this list of conditions and the 
 *       following disclaimer.
 *   2.  Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the 
 *       following disclaimer in the documentation and/or other 
 *       materials provided with the distribution.
 *   3.  Neither the name of Charles River Media nor the names of 
 *       its contributors may be used to endorse or promote 
 *       products derived from this software withoutp specific 
 *       prior written permission.
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
 *
 */