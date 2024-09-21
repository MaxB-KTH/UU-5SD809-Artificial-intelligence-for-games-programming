//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//  Class Template - Assignment 1.2
//  Artificial Intelligence for Game Programming I - 5SD809
//  Uppsala University
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Game.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
Game::Game(void){
    //--------------------------------------------
    mW = GRID_SIZE_X * SPACING;
    mH = GRID_SIZE_Y * SPACING;
    mMouseX = mMouseY = 0;
    mMouseButton = mMouseState = 0;
    //--------------------------------------------
    mFrontBufferIdx = 1;
    mM = new bool[2][GRID_SIZE_Y][GRID_SIZE_X];
    //--------------------------------------------
    ResetBuffers();
    //--------------------------------------------
    //Add_Glider(10,10);
    //Add_LightweightSpaceship(5,5);
    Add_GosperGliderGun(5,5);
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
Game::~Game(void){delete [] mM;}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::ChangeSize(int w, int h){
    mW = w, mH = h;
    glViewport(0,0,mW,mH);                         //Reset Viewport
    glMatrixMode(GL_PROJECTION); glLoadIdentity(); //Reset the Projection Matrix
    glOrtho(0.,double(mW),double(mH),0.,-1.,1.);   //Create Ortho View (0,0 At Top Left)
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();  //Reset the Modelview Matrix
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::Draw(void){
    //--------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(12);
    //--------------------------------------------
    int w = GRID_SIZE_X * SPACING;
    int h = GRID_SIZE_Y * SPACING;
    int offsetX = (mW - w + SPACING)/2;
    int offsetY = (mH - h + SPACING)/2;
    //--------------------------------------------
    glBegin(GL_POINTS);
    //--------------------------------------------Grid
    glColor3ub(0, 255, 127);//Green Shade
    For (i,GRID_SIZE_Y) For (j,GRID_SIZE_X){
        if (mM[mFrontBufferIdx][i][j])
            glVertex2f(offsetX + SPACING*j, offsetY + SPACING*i);
    }
    //--------------------------------------------
    glEnd();
    //--------------------------------------------
    UpdateFrontBuffer();
    mFrontBufferIdx = 1 - mFrontBufferIdx;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //--------------------------------------------
    glutSwapBuffers();
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------



//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::NormalKeys(unsigned char key, int x, int y){
	if (key >= '0' && key <= '9'){}
	if (key == 13){}//Return
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::SpecialKeys(int key, int x, int y){
    if (key == GLUT_KEY_LEFT){}
    if (key == GLUT_KEY_RIGHT){}
    if (key == GLUT_KEY_UP){}
    if (key == GLUT_KEY_DOWN){}
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::Mouse(int button, int state, int x, int y){
	mMouseButton = button;//GLUT_LEFT_BUTTON/GLUT_MIDDLE_BUTTON/GLUT_RIGHT_BUTTON
	mMouseState = state;//GLUT_DOWN/GLUT_UP
	mGlutGetModifiers = glutGetModifiers();
	mMouseX = x; mMouseY = y;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------



//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::ResetBuffers(){
    For (k,2) For (i,GRID_SIZE_Y) For (j,GRID_SIZE_X){
        mM[k][i][j] = false;}
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::Add_Glider(int i, int j){
    char A[][4] = {
        "***",
        "  *",
        " * ",
    };
    For (ii,3) For (jj,3) mM[0][i+ii][j+jj] = A[ii][jj] == '*';
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::Add_LightweightSpaceship(int i, int j){
    char A[][6] = {
        " ****",
        "*   *",
        "    *",
        "*  * ",
    };
    For (ii,4) For (jj,5) mM[0][i+ii][j+jj] = A[ii][jj] == '*';
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::Add_GosperGliderGun(int i, int j){
    char A[][39] = {
        "                       **         **  ",
        "                      * *         **  ",
        "**       **           **              ",
        "**      * *                           ",
        "        **      **                    ",
        "                * *                   ",
        "                *                     ",
        "                                   ** ",
        "                                   * *",
        "                                   *  ",
        "                                      ",
        "                                      ",
        "                        ***           ",
        "                        *             ",
        "                         *            ",
    };
    For (ii,15) For (jj,38) mM[0][i+ii][j+jj] = A[ii][jj] == '*';
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------

void Game::UpdateFrontBuffer() {

    bool currentGenerationIndex = 1 - mFrontBufferIdx;
    bool nextGenerationIndex = mFrontBufferIdx;

    For (y, GRID_SIZE_Y) For (x, GRID_SIZE_X) {
        int n = 0; // Neighbor counter.

        // Loop over the vertical neighbors (dy = -1, 0, 1).
        for (int dy = -1; dy <= 1; dy++) {
            int ny = y + dy; // Calculate the neighbor's y-coordinate.

            // Apply wrapping for the y-coordinate to handle grid edges (toroidal grid).
            if (ny < 0)
                ny = GRID_SIZE_Y - 1; // Wrap around to the bottom row.
            else if (ny >= GRID_SIZE_Y)
                ny = 0; // Wrap around to the top row.

            // Loop over the horizontal neighbors (dx = -1, 0, 1).
            for (int dx = -1; dx <= 1; dx++) {
                int nx = x + dx; // Calculate the neighbor's x-coordinate.

                // Apply wrapping for the x-coordinate.
                if (nx < 0)
                    nx = GRID_SIZE_X - 1; // Wrap around to the rightmost column.
                else if (nx >= GRID_SIZE_X)
                    nx = 0; // Wrap around to the leftmost column.

                // Skip counting the current cell as its own neighbor.
                if (dy == 0 && dx == 0)
                    continue;

                // If the neighbor cell at (ny, nx) is alive, increment the neighbor count.
                if (mM[currentGenerationIndex][ny][nx])
                    n++;
            }
        }

        // Retrieve the current state of the cell at (y, x).
        bool currentState = mM[currentGenerationIndex][y][x];

        // Apply the Game of Life rules to determine the cell's next state.
        // The cell becomes alive if it has exactly 3 neighbors,
        // or it stays alive if it has exactly 2 neighbors and is currently alive.
        // Otherwise, the cell dies or remains dead.
        mM[nextGenerationIndex][y][x] = (n == 3 || (n == 2 && currentState));
    }
}


//---------------------------------------------------------------------
//---------------------------------------------------------------------