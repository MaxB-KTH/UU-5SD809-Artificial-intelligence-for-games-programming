//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Genetics.h"
//---------------------------------------------------------------------
Genetics G;
//---------------------------------------------------------------------
void Display(void){G.Draw();}
void NormalKeys(unsigned char key, int x, int y){
    G.NormalKeys(key,x,y);}
void SpecialKeys(int key, int x, int y){G.SpecialKeys(key,x,y);}
void Mouse(int button, int state, int x, int y){
    G.Mouse(button,state,x,y);}
void ChangeSize(int w, int h){G.ChangeSize(w,h);}
//---------------------------------------------------------------------
int main(int argc, char **argv){
	//----------------------Init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);    
	glutInitWindowPosition(0,0);
	glutInitWindowSize(G.mW,G.mH);
	glutCreateWindow("TSP");
    glutReshapeFunc(ChangeSize);
    G.Init();
    
	//----------------------Draw
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
    
    //----------------------Aux
	glutKeyboardFunc(NormalKeys);
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(Mouse);
    
	//----------------------Main
	glutMainLoop();
    return 0;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
