// Matheus Henrique e Lucas Camilo
// Snowman in Chernobyl
// gcc ChernobylSnowman.c -lglut -lGL -lGLU -lm -o ChernobylSnowman && ./ChernobylSnowman

#include <GL/glut.h>

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;

// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
    {
    GLfloat fAspect;

    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w/(GLfloat)h;

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
    gluPerspective(35.0f, fAspect, 1.0, 40.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }


// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.
void SetupRC(){

    // Light values and coordinates
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat  lightPos[] = { -20.f, 5.0f, 5.0f, 1.0f };

    glEnable(GL_DEPTH_TEST);    // Hidden surface removal
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);     // Do not calculate inside

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

// cor de fundo
    glClearColor(1.25f, 0.25f, 0.50f, 1.0f);

}

// movimentação com as setas
void SpecialKeys(int key, int x, int y){

    if(key == GLUT_KEY_UP)
        xRot-= 5.0f;

    if(key == GLUT_KEY_DOWN)
        xRot += 5.0f;

    if(key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if(key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    if(key == GLUT_KEY_HOME)
	zRot += 5.0f;

        xRot = (GLfloat)((const int)xRot % 360);
        yRot = (GLfloat)((const int)yRot % 360);
	zRot = (GLfloat)((const int)zRot % 360);

    // Refresh the Window
    glutPostRedisplay();

}


void desenharCabeca(GLUquadricObj *gqo, float x, float y, float z){
//        | |
//       (   )
//     (       )
//      (    )
//

glPushMatrix();

  glPushMatrix();
  glTranslatef(x, y, z);
  glColor3f(1.0f, 1.0f, 1.0f);
  gluSphere(gqo,0.3f,26,13);
  glPopMatrix();


// Cone chapeu
  glPushMatrix();
  glTranslatef(x, y+0.25f, z);
  glRotatef(-90, 1.0f,0.0f,0.0f);
  glColor3f(0.0f,0.0f,0.0f);
  gluCylinder(gqo,0.28f,0.0f,0.8f,26,13); // MEXER AQUI
  glPopMatrix();
//disc
  glPushMatrix();
  glTranslatef(x, 0.25f+y, z);
  glRotatef(-90, 1.0f,0.0f,0.0f);
  glDisable(GL_CULL_FACE);
	gluDisk(gqo, 0.17f, 0.28f, 26, 13);
	glEnable(GL_CULL_FACE);
  glPopMatrix();
//fim chapeu

  //olhos
  glPushMatrix();
  glTranslatef(-0.1f+x, y+0.1, z+0.3f);
  glColor3f(1.0f,0.0f,2.0f);
  gluSphere(gqo,0.02f,26,13);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.1f+x, y+0.1, z+0.3f);
  glColor3f(1.0f,0.0f,2.0f);
  gluSphere(gqo,0.02f,26,13);
  glPopMatrix();

  //nariz
  glPushMatrix();
  glTranslatef(x, y, z+0.3f);
  glColor3f(0.0f,1.0f,0.0f);
  gluCylinder(gqo,0.04f,0.0f,0.2f,26,13);
  glPopMatrix();

  glPopMatrix();

}

void desenharCorpo(GLUquadricObj *gqo, float x, float y, float z){

  glPushMatrix();

    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluSphere(gqo,0.4f,26,13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, y-0.8f, z);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluSphere(gqo,0.6f,26,13);
    glPopMatrix();
/////
//Braços
    glPushMatrix();
    glTranslatef(-0.2f+x, y, z);
    glLineWidth(2.5);
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.6f, 0.0, 0.0);
    glVertex3f(0.9f, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.3f+x, y, z);
    glLineWidth(2.5);
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.6f, 0.0, 0.0);
    glVertex3f(0.9f, 0, 0);
    glEnd();
    glPopMatrix();
// fim braços
// Pernas
// perna esquerda
  glPushMatrix();
  glTranslatef( x,-1.3f+y,z);
  glLineWidth(3.0);
  glColor3f(1.0f, 0.0f, 1.0f);
  glBegin(GL_LINES);
  glVertex3f(-0.3f, 0.9f, 0);
  glVertex3f(0.8f, 0.0f, 0);
  glEnd();
  glPopMatrix();

// perna direita
glPushMatrix();
glTranslatef( x,-1.3f+y,z);
glLineWidth(3.0);
glColor3f(1.0f, 0.0f, 1.0f);
glBegin(GL_LINES);
glVertex3f(0.3f, 0.9f, 0);
glVertex3f(-0.8f, 0.0f, 0);
glEnd();
glPopMatrix();

/*
glPushMatrix();
glTranslatef(-1.3f+x, y, z);
glLineWidth(2.5);
glColor3f(1.0f, 0.0f, 1.0f);
glBegin(GL_LINES);
glVertex3f(0.6f, 0.0, 0.0);
glVertex3f(0.9f, 0, 0);
glEnd();
glPopMatrix();
*/
// Fim pernas



glPopMatrix();
}

// Called to draw scene
void RenderScene(void){

    GLUquadricObj *pObj;    // Quadric Object

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Save the matrix state and do the rotations
    glPushMatrix();

	// Move object back and do in place rotation
	glTranslatef(0.0f, -1.0f, -5.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);


	// Draw something
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

  desenharCabeca(pObj,0,1.5f,0);

  desenharCorpo(pObj,0,0.9f,0);

    // Restore the matrix state
    glPopMatrix();

    // Buffer swap
    glutSwapBuffers();

}


int main(int argc, char *argv[]){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Modeling with Quadrics");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;

}
