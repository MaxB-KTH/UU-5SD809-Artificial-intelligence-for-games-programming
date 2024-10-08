/*
 *  Particle Swarm Optimization types and symbolics
 *
 *  mtj@cogitollc.com
 *
 */
 
#pragma once

#include <iostream>
#include <math.h>
#include <time.h>

#define PI          ((double)3.1415926)
#define getSRand()  ((double)rand() / (double)RAND_MAX)
#define getPoint()  (((4.0 * PI) * getSRand()) - (2.0 * PI))

class PSO {
public:

	PSO(void);
    
private:
    
    const static int    MAX_FILENAME = 80,
                        MAX_PARTICLES = 5,
                        NUM_ITERATIONS = 100;

    typedef struct {
        double x;
        double y;
    } vector_t;
    
    typedef struct {
        FILE *fp;
        vector_t position;
        vector_t velocity;
        double fitness;
    } particle_t;
    
    double checkFitness( double x, double y );
    
    void storePbest( int index );
    void initPopulation( void );
    void closePopulation( void );
    
    void moveParticle( int i );
    void moveSwarm( void );
    
    int  run();//Main function from the original C-version

    static double c1, c2, dt;
    
    /* Array of particles within the solution space */
    particle_t particles[MAX_PARTICLES];
    particle_t pbest[MAX_PARTICLES];
    
    /* Global Best particle */
    particle_t gbest;
    
};

/*
 * Copyright (c) 2003-2005 Charles River Media.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, is hereby granted without fee provided
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
 *       its contributors may be used to endorse or promote products
 *       derived from this software without specific prior
 *       written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY CHARLES RIVER MEDIA AND CONTRIBUTORS
 * 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CHARLES
 * RIVER MEDIA OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARAY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
