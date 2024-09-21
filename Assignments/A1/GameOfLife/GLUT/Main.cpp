//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Game.h"
#include <iostream>
//---------------------------------------------------------------------
//---------------------------------------------------------------------
Game G;
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Display(void){G.Draw();}
void NormalKeys(unsigned char key, int x, int y){G.NormalKeys(key,x,y);}
void SpecialKeys(int key, int x, int y){G.SpecialKeys(key,x,y);}
void Mouse(int button, int state, int x, int y){G.Mouse(button, state, x, y);}
void ChangeSize(int w, int h){G.ChangeSize(w, h);}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main(int argc, char **argv){
	//For(y, Game::GRID_SIZE_Y) For(x, Game::GRID_SIZE_X) std::cout << "y =" << y << ' ' << "x=" << x << std::endl;


	//----------------------Init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    
	//----------------------Window
	glutInitWindowPosition(0,0);
	glutInitWindowSize(G.mW,G.mH);
	glutCreateWindow("Game of Life");
	glutReshapeFunc(ChangeSize);
    
	//----------------------Draw
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1);
    
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
    
	glutKeyboardFunc(NormalKeys);
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(Mouse);
    
	//----------------------Main
	glutMainLoop();
    return 0;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
