// Matheus Henrique e Lucas Camilo
// gcc humanoide.c -lglut -lGL -lGLU -lm -o humanoide && ./humanoide

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

    // Black blue background
    glClearColor(1, 1,1, 1.0);

}

// Respond to arrow keys
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

glPushMatrix();

  //cabeca
  glPushMatrix();
  glTranslatef(x, y, z);
  gluSphere(gqo,0.2f,26,13);
  glPopMatrix();

  //pescoco
  glPushMatrix();
  glTranslatef(x, y-0.25f, z);
  glRotatef(-90, 1.0f,0.0f,0.0f);
  // glColor3f(0.0f,0.0f,0.0f);
  gluCylinder(gqo,0.1f,0.1f,0.1f,26,13);
  glPopMatrix();


glPopMatrix();

}

void desenharCorpo(GLUquadricObj *gqo, float x, float y, float z){

  glPushMatrix();

  glTranslatef(x, y, z);

  glPushMatrix();
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
          // Top face (y = 1.0f)
          // Define vertices in counter-clockwise (CCW) order with normal pointing out
          glColor3f(0.0f, 1.0f, 0.0f);     // Green

          glVertex3f( 0.4f, 1.0f, 0.0f);//a (a,d) ou (c,b)
          glVertex3f(-0.4f, 1.0f, 0.0f);//b
          glVertex3f(-0.4f, 1.0f,  0.3f);//c
          glVertex3f( 0.4f, 1.0f,  0.3f);//d

          // Bottom face (y = -1.0f)
          glColor3f(1.0f, 0.5f, 0.0f);     //
          glVertex3f( 0.4f, -0.1f,  0.3f);//a
          glVertex3f(-0.4f, -0.1f,  0.3f);//b
          glVertex3f(-0.4f, -0.1f, 0.0f);//c
          glVertex3f( 0.4f, -0.1f, 0.0f);//d

          // Front face  (z = 1.0f)
          glColor3f(1.0f, 0.0f, 0.0f);     // Red

          glVertex3f( 0.4f,  1.0f, 0.3f);
          glVertex3f(-0.4f,  1.0f, 0.3f);
          glVertex3f(-0.4f, -0.1f, 0.3f);
          glVertex3f( 0.4f, -0.1f, 0.3f);

          // Back face (z = -1.0f)
          glColor3f(1.0f, 1.0f, 0.0f);     // Yellow

          glVertex3f( 0.4f, -0.1f, 0.0f);
          glVertex3f(-0.4f, -0.1f, 0.0f);
          glVertex3f(-0.4f,  1.0f, 0.0f);
          glVertex3f( 0.4f,  1.0f, 0.0f);

          // Left face (x = -1.0f)
          glColor3f(0.0f, 0.0f, 1.0f);     // Blue

          glVertex3f(-0.4f,  1.0f,  0.3f);
          glVertex3f(-0.4f,  1.0f, 0.0f);
          glVertex3f(-0.4f, -0.1f, 0.0f);
          glVertex3f(-0.4f, -0.1f,  0.3f);

          // Right face (x = 1.0f)
          glColor3f(1.0f, 0.0f, 1.0f);     // Magenta

          glVertex3f(0.4f,  1.0f, 0.0f);
          glVertex3f(0.4f,  1.0f,  0.3f);
          glVertex3f(0.4f, -0.1f,  0.3f);
          glVertex3f(0.4f, -0.1f, 0.0f);
       glEnd();
       glPopMatrix();

       //ombros
       glPushMatrix();
       glTranslatef(x-0.4, y, z+0.35f);
       gluSphere(gqo,0.1f,26,13);
       glPopMatrix();

       glPushMatrix();
       glTranslatef(x+0.4, y, z+0.35f);
       gluSphere(gqo,0.1f,26,13);
       glPopMatrix();

       //juntas
       glPushMatrix();
       glTranslatef(x-0.2, y-0.9f, z+0.35f);
       gluSphere(gqo,0.1f,26,13);
       glPopMatrix();

       //ombros
       glPushMatrix();
       glTranslatef(x-0.4, y, z+0.35f);
       gluSphere(gqo,0.1f,26,13);
       glPopMatrix();

       glPushMatrix();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(x+0.2, y-0.9f, z+0.35f);
       gluSphere(gqo,0.1f,26,13);
       glPopMatrix();

       //cotovelo direito
       glPushMatrix();
       glTranslatef(x-0.5, y-0.3f, z+0.35f);
       gluSphere(gqo,0.1f,26,13);
       glPopMatrix();

      // cotovelo direito
       glPushMatrix();
       glTranslatef(x+0.5, y-0.3f, z+0.35f);
       gluSphere(gqo,0.1f,26,13);
       glPopMatrix();

       //Joelho Direito
       glPushMatrix();
       glTranslatef(x-0.2, y-1.3f, z+0.35f);
       gluSphere(gqo,0.1f,26,13);
       glPopMatrix();

       //Joelho ESquerdo
       glPushMatrix();
       glTranslatef(x+0.2, y-1.3f, z+0.35f);
       gluSphere(gqo,0.1f,26,13);
       glPopMatrix();

  glPopMatrix();


}

void desenharMembro(GLUquadricObj *gqo, float x, float y, float z){

  glPushMatrix();

  glTranslatef(x, y, z);

  glPushMatrix();
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
          // Top face (y = 1.0f)
          // Define vertices in counter-clockwise (CCW) order with normal pointing out
          glColor3f(0.0f, 1.0f, 0.0f);     // Green

          glVertex3f( 0.07f, 1.0f, 0.2f);//a (a,d) ou (c,b)
          glVertex3f(-0.07f, 1.0f, 0.2f);//b
          glVertex3f(-0.07f, 1.0f,  0.3f);//c
          glVertex3f( 0.07f, 1.0f,  0.3f);//d

          // Bottom face (y = -1.0f)
          glColor3f(1.0f, 0.5f, 0.0f);     //
          glVertex3f( 0.07f,  0.7f,  0.3f);//a
          glVertex3f(-0.07f,  0.7f,  0.3f);//b //CERTO
          glVertex3f(-0.07f,  0.7f, 0.2f);//c
          glVertex3f( 0.07f,  0.7f, 0.2f);//d


          // Front face  (z = 1.0f)
          glColor3f(1.0f, 0.0f, 0.0f);     // Red
          glVertex3f( 0.07f,  1.0f, 0.3f);
          glVertex3f(-0.07f,  1.0f, 0.3f);//// CERTO
          glVertex3f(-0.07f, 0.7f, 0.3f);
          glVertex3f( 0.07f, 0.7f, 0.3f);

          // Back face (z = -1.0f)
          glColor3f(1.0f, 1.0f, 0.0f);     // Yellow

          glVertex3f( 0.07f, 0.7f, 0.2f);
          glVertex3f(-0.07f, 0.7f, 0.2f);
          glVertex3f(-0.07f,  1.0f, 0.2f);
          glVertex3f( 0.07f,  1.0f, 0.2f);

          // Left face (x = -1.0f)
          glColor3f(0.0f, 0.0f, 1.0f);     // Blue

          glVertex3f(-0.07f,  1.0f,  0.3f);
          glVertex3f(-0.07f,  1.0f, 0.2f);//CERTO
          glVertex3f(-0.07f, 0.7f, 0.2f);
          glVertex3f(-0.07f, 0.7f,  0.3f);

          // Right face (x = 1.0f)
          glColor3f(1.0f, 0.0f, 1.0f);     // Magenta

          glVertex3f(0.07f,  1.0f, 0.2f);
          glVertex3f(0.07f,  1.0f,  0.3f);//CERTO
          glVertex3f(0.07f, 0.7f,  0.3f);
          glVertex3f(0.07f, 0.7f, 0.2f);
       glEnd();
       glPopMatrix();
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

  desenharCabeca(pObj,0,2.0f,0.0f);

  desenharCorpo(pObj,0.0f,0.8f,-0.2f);
    // Restore the matrix state

    //braços
    desenharMembro(pObj,0.5f,0.6f,-0.3f);
    desenharMembro(pObj,-0.5f,0.6f,-0.3f);
    //ante-braços
    desenharMembro(pObj,-0.5f, 0.3f,-0.3f);
    desenharMembro(pObj, 0.5f, 0.3f,-0.3f);
    //pernas
    desenharMembro(pObj,0.2f,-0.35f,-0.3f);
    desenharMembro(pObj,-0.2f,-0.35f,-0.3f);
    //canelinhas KKK
    desenharMembro(pObj,0.2f,-0.75f,-0.3f);
    desenharMembro(pObj,-0.2f,-0.75f,-0.3f);
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
