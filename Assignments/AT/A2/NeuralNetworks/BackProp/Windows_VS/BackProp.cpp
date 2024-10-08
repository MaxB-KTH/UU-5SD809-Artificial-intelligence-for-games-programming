/*
 *  Backpropagation Algorithm
 *
 *  mtj@cogitollc.com
 *
 */

#include "BackProp.h"

BackProp::BackProp(){
    //Modified [
    strings = new char[4][16];
    strcpy(strings[0],"Attack");//Or strcpy_s for some compilers
    strcpy(strings[1],"Run");
    strcpy(strings[2],"Wander");
    strcpy(strings[3],"Hide");
    //Modified ]
    run();
}

double BackProp::LEARN_RATE = 0.2;

/*  H    K    G    E     A    R    W    H  */
BackProp::ELEMENT BackProp::samples[BackProp::MAX_SAMPLES] = {
    { 2.0, 0.0, 0.0, 0.0, {0.0, 0.0, 1.0, 0.0} },
    { 2.0, 0.0, 0.0, 1.0, {0.0, 0.0, 1.0, 0.0} }, 
    { 2.0, 0.0, 1.0, 1.0, {1.0, 0.0, 0.0, 0.0} }, 
    { 2.0, 0.0, 1.0, 2.0, {1.0, 0.0, 0.0, 0.0} },
    { 2.0, 1.0, 0.0, 2.0, {0.0, 0.0, 0.0, 1.0} },
    { 2.0, 1.0, 0.0, 1.0, {1.0, 0.0, 0.0, 0.0} },
    
    { 1.0, 0.0, 0.0, 0.0, {0.0, 0.0, 1.0, 0.0} },
    { 1.0, 0.0, 0.0, 1.0, {0.0, 0.0, 0.0, 1.0} },
    { 1.0, 0.0, 1.0, 1.0, {1.0, 0.0, 0.0, 0.0} },
    { 1.0, 0.0, 1.0, 2.0, {0.0, 0.0, 0.0, 1.0} },
    { 1.0, 1.0, 0.0, 2.0, {0.0, 0.0, 0.0, 1.0} },
    { 1.0, 1.0, 0.0, 1.0, {0.0, 0.0, 0.0, 1.0} },
    
    { 0.0, 0.0, 0.0, 0.0, {0.0, 0.0, 1.0, 0.0} },
    { 0.0, 0.0, 0.0, 1.0, {0.0, 0.0, 0.0, 1.0} },
    { 0.0, 0.0, 1.0, 1.0, {0.0, 0.0, 0.0, 1.0} },
    { 0.0, 0.0, 1.0, 2.0, {0.0, 1.0, 0.0, 0.0} },
    { 0.0, 1.0, 0.0, 2.0, {0.0, 1.0, 0.0, 0.0} },
    { 0.0, 1.0, 0.0, 1.0, {0.0, 0.0, 0.0, 1.0} }
};

//char *BackProp::strings[4]={"Attack", "Run", "Wander", "Hide"};//Original

/*
 *  assignRandomWeights()
 *
 *  Assign a set of random weights to the network.
 *
 */

void BackProp::assignRandomWeights(){
    int hid, inp, out;
    
    for (inp = 0 ; inp < INPUT_NEURONS+1 ; inp++) {
        for (hid = 0 ; hid < HIDDEN_NEURONS ; hid++) {
            wih[inp][hid] = RAND_WEIGHT;
        }
    }
    
    for (hid = 0 ; hid < HIDDEN_NEURONS+1 ; hid++) {
        for (out = 0 ; out < OUTPUT_NEURONS ; out++) {
            who[hid][out] = RAND_WEIGHT;
        }
    }
    
}

/*
 *  sigmoid()
 *
 *  Calculate and return the sigmoid of the val argument.
 *
 */

double BackProp::sigmoid(double val)
{
    return (1.0 / (1.0 + exp(-val)));
	//return atan(val);
}

/*
 *  sigmoidDerivative()
 *
 *  Calculate and return the derivative of the sigmoid for the val argument.
 *
 */

double BackProp::sigmoidDerivative(double val)
{
    return ( val * (1.0 - val) );
    //return 1/(1+val*val);
}

/*
 *  feedForward()
 *
 *  Feedforward the inputs of the neural network to the outputs.
 *
 */

void BackProp::feedForward()
{
    int inp, hid, out;
    double sum;
    
    /* Calculate input to hidden layer */
    for (hid = 0 ; hid < HIDDEN_NEURONS ; hid++) {
        
        sum = 0.0;
        for (inp = 0 ; inp < INPUT_NEURONS ; inp++) {
            sum += inputs[inp] * wih[inp][hid];
        }
        
        /* Add in Bias */
        sum += wih[INPUT_NEURONS][hid];
        
        hidden[hid] = sigmoid( sum );
        
    }
    
    /* Calculate the hidden to output layer */
    for (out = 0 ; out < OUTPUT_NEURONS ; out++) {
        
        sum = 0.0;
        for (hid = 0 ; hid < HIDDEN_NEURONS ; hid++) {
            sum += hidden[hid] * who[hid][out];
        }
        
        /* Add in Bias */
        sum += who[HIDDEN_NEURONS][out];
        
        actual[out] = sigmoid( sum );
        
    }
    
}

/*
 *  backPropagate()
 *
 *  Backpropagate the error through the network.
 *
 */

void BackProp::backPropagate(void)
{
    int inp, hid, out;
    
    /* Calculate the output layer error (step 3 for output cell) */
    for (out = 0 ; out < OUTPUT_NEURONS ; out++) {
        erro[out] = (target[out] - actual[out]) * sigmoidDerivative( actual[out] );
    }
    
    /* Calculate the hidden layer error (step 3 for hidden cell) */
    for (hid = 0 ; hid < HIDDEN_NEURONS ; hid++) {
        
        errh[hid] = 0.0;
        for (out = 0 ; out < OUTPUT_NEURONS ; out++) {
            errh[hid] += erro[out] * who[hid][out];
        }
        
        errh[hid] *= sigmoidDerivative( hidden[hid] );
        
    }
    
    /* Update the weights for the output layer (step 4 for output cell) */
    for (out = 0 ; out < OUTPUT_NEURONS ; out++) {
        
        for (hid = 0 ; hid < HIDDEN_NEURONS ; hid++) {
            who[hid][out] += (LEARN_RATE * erro[out] * hidden[hid]);
        }
        
        /* Update the Bias */
        who[HIDDEN_NEURONS][out] += (LEARN_RATE * erro[out]);
        
    }
    
    /* Update the weights for the hidden layer (step 4 for hidden cell) */
    for (hid = 0 ; hid < HIDDEN_NEURONS ; hid++) {
        
        for (inp = 0 ; inp < INPUT_NEURONS ; inp++) {
            wih[inp][hid] += (LEARN_RATE * errh[hid] * inputs[inp]);
        }
        
        /* Update the Bias */
        wih[INPUT_NEURONS][hid] += (LEARN_RATE * errh[hid]);
        
    }
    
}

/*
 *  action()
 *
 *  Select an action using winner-takes-all network strategy.
 *
 */

int BackProp::action( double *vector )
{
    int index, sel;
    double max;
    
    sel = 0;
    max = vector[sel];
    
    for (index = 1 ; index < OUTPUT_NEURONS ; index++) {
        if (vector[index] > max) {
            max = vector[index]; sel = index;
        }
    }
    
    return( sel );
}

/*
 *  main()
 *
 *  Main function for the backpropagation network.
 *
 */

int BackProp::run() //Main function from the original C-version
{
    double err;
    int i, sample=0, iterations=0;
    int sum = 0;
    
    /* Seed the random number generator */
    srand( time(NULL) );
    
    assignRandomWeights();
    
    while (1) {
        
        if (++sample == MAX_SAMPLES) sample = 0;
        
        inputs[0] = samples[sample].health;
        inputs[1] = samples[sample].knife;
        inputs[2] = samples[sample].gun;
        inputs[3] = samples[sample].enemy;
        
        target[0] = samples[sample].out[0];
        target[1] = samples[sample].out[1];
        target[2] = samples[sample].out[2];
        target[3] = samples[sample].out[3];
        
        feedForward();
        
        /* need to iterate through all ... */
        
        err = 0.0;
        for (i = 0 ; i < OUTPUT_NEURONS ; i++) {
            err += sqr( (samples[sample].out[i] - actual[i]) );
        }
        err = 0.5 * err;
        
        if (iterations++ > 20000) break;
        
        backPropagate();
        
    }
    
    /* Test the network */
    for (i = 0 ; i < MAX_SAMPLES ; i++) {
        
        inputs[0] = samples[i].health;
        inputs[1] = samples[i].knife;
        inputs[2] = samples[i].gun;
        inputs[3] = samples[i].enemy;
        
        target[0] = samples[i].out[0];
        target[1] = samples[i].out[1];
        target[2] = samples[i].out[2];
        target[3] = samples[i].out[3];
        
        feedForward();
        
        if (action(actual) != action(target)) {
            
            cout << " " <<
                inputs[0] << ": " <<
                inputs[1] << ": " <<
                inputs[2] << ": " <<
                inputs[3] << " " <<
                strings[action(actual)] << " (" <<
                strings[action(target)] << ")"  << endl;
            
        } else {
            sum++;
        }
        
    }
    
    cout << "Network is " <<
        ((float)sum / (float)MAX_SAMPLES) * 100.0 <<
        "% correct" << endl;
    
    /* Run some tests */
    
    /*  Health            Knife            Gun              Enemy */
    inputs[0] = 2.0; inputs[1] = 1.0; inputs[2] = 1.0; inputs[3] = 1.0;
    feedForward();
    cout << "2111 Action " << strings[action(actual)] << endl;
    
    inputs[0] = 1.0; inputs[1] = 1.0; inputs[2] = 1.0; inputs[3] = 2.0;
    feedForward();
    cout << "1112 Action " << strings[action(actual)] << endl;
    
    inputs[0] = 0.0; inputs[1] = 0.0; inputs[2] = 0.0; inputs[3] = 0.0;
    feedForward();
    cout << "0000 Action " << strings[action(actual)] << endl;
    
    inputs[0] = 0.0; inputs[1] = 1.0; inputs[2] = 1.0; inputs[3] = 1.0;
    feedForward();
    cout << "0111 Action " << strings[action(actual)] << endl;
    
    inputs[0] = 2.0; inputs[1] = 0.0; inputs[2] = 1.0; inputs[3] = 3.0;
    feedForward();
    cout << "2013 Action " << strings[action(actual)] << endl;
    
    inputs[0] = 2.0; inputs[1] = 1.0; inputs[2] = 0.0; inputs[3] = 3.0;
    feedForward();
    cout << "2103 Action " << strings[action(actual)] << endl;

    inputs[0] = 0.0; inputs[1] = 1.0; inputs[2] = 0.0; inputs[3] = 3.0;
    feedForward();
    cout << "0103 Action " << strings[action(actual)] << endl;
    
    return 0;
}

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

