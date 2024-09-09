#include "PSO.h"

PSO::PSO(){
    run();
}

double PSO::c1 = 0.5, PSO::c2 = 0.5, PSO::dt = 0.1;

/*
 *  Particle Swarm Optimization Fitness Function
 *
 *  mtj@cogitollc.com
 *
 */

double PSO::checkFitness( double x, double y )
{
    /* Sombrero Fitness Function */
    return ( (double)(6.0 * cos(sqrt(x*x+y*y))/(x*x+y*y+6.0)) );
}

/*
 *  Particle Swarm Optimization initialization functions
 *
 *  mtj@cogitollc.com
 *
 */

void PSO::storePbest( int index )
{
    /* Save the particle to its personal best */
    memcpy( (void *)&pbest[index], (void *)&particles[index], 
           sizeof(particle_t) );
    
    /* If this pbest is better than the gbest, save it */
    if (pbest[index].fitness > gbest.fitness) {
        gbest.position.x = pbest[index].position.x;
        gbest.position.y = pbest[index].position.y;
        gbest.fitness    = pbest[index].fitness;
    }
    
    return;
}

void PSO::initPopulation( void )
{
    int i;
    char filename[MAX_FILENAME+1];
    
    gbest.fitness = (double)-9999.0;  
    
    for ( i = 0 ; i < MAX_PARTICLES ; i++ ) {
        
        /* Initialize the output file pointer */
        sprintf( filename, "particle%02d.txt", i );
        particles[i].fp = fopen( filename, "w" );
        
        /* Initialize a particle's starting point and fitness*/
        particles[i].position.x = getPoint();
        particles[i].position.y = getPoint();
        particles[i].fitness = 
        checkFitness( particles[i].position.x, particles[i].position.y );
        
        /* Initialize the particle's dimensional velocity */
        particles[i].velocity.x = (getSRand() / (double)10.0);
        particles[i].velocity.y = (getSRand() / (double)10.0);
        
        /* Since this is the only fitness value, store this as pbest */
        storePbest( i );
        
        /* Store this position to the particles trace file */
        fprintf( particles[i].fp, "%lg, %lg, %lg\n",
                particles[i].position.x, particles[i].position.y, 
                particles[i].fitness );
        
    }
    
    return;
}

void PSO::closePopulation( void )
{
    int i;
    
    for ( i = 0 ; i < MAX_PARTICLES ; i++ ) {
        
        fclose( particles[i].fp );
        
    }
    
    return;
}

/*
 *  Particle Swarm Optimization swarm functions
 *
 *  mtj@cogitollc.com
 *
 */

void PSO::moveParticle( int i )
{
    
    /* Update the position of the particle */
    particles[i].position.x += (particles[i].velocity.x * dt);
    particles[i].position.y += (particles[i].velocity.y * dt);
    
    /* Since we're interested only in the -2PI-2PI range, we'll
     * calculate fitness only over this range.
     */
    if ( (particles[i].position.x > (-2.0 * PI)) && 
        (particles[i].position.x < ( 2.0 * PI)) &&
        (particles[i].position.y > (-2.0 * PI)) &&
        (particles[i].position.y < ( 2.0 * PI)) ) {
        
        particles[i].fitness = 
        checkFitness( particles[i].position.x, particles[i].position.y );
        
    }
    
    /* Write the particle's position and fitness to the trace file */
    fprintf( particles[i].fp, "%lg, %lg, %lg\n", 
            particles[i].position.x, particles[i].position.y, 
            particles[i].fitness );
    
    /* Update the velocity vector of the particle */
    particles[i].velocity.x +=
    ( (c1 * getSRand() * (gbest.position.x - particles[i].position.x)) + 
     (c2 * getSRand() * (pbest[i].position.x - particles[i].position.x)) );
    
    particles[i].velocity.y +=
    ( (c1 * getSRand() * (gbest.position.y - particles[i].position.y)) + 
     (c2 * getSRand() * (pbest[i].position.y - particles[i].position.y)) );
    
    return;
}

void PSO::moveSwarm( void )
{
    int j;
    
    /* Move each particle in the swarm */
    for ( j = 0 ; j < MAX_PARTICLES ; j++ ) {
        
        moveParticle( j );
        
        if ( particles[j].fitness > pbest[j].fitness ) storePbest( j );
        
    }
    
    return;
}

/*
 *  Particle Swarm Optimization main function
 *
 *  mtj@cogitollc.com
 *
 */

int PSO::run()//Main function from the original C-version
{
    int iter;
    
    /* Seed the random number generator */
    srand( time(NULL) );
    
    /* Initialize the swarm */
    initPopulation();
    
    /* Perform NUM_ITERATIONS number of iterations */
    for (iter = 0 ; iter < NUM_ITERATIONS ; iter++) {
        
        moveSwarm();
        printf( "%lg\n", gbest.fitness );
        
    }
    
    /* Cleanup the swarm */
    closePopulation();
    
    return 0;
}

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
