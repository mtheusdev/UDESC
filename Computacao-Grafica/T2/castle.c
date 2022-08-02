// Matheus Henrique e Lucas Camilo
// gcc castle.c -lglut -lGL -lGLU -lm -o castle && ./castle

#include <GL/glut.h>

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

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
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };

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
    glClearColor(1, 1, 1, 1.0f);

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

        xRot = (GLfloat)((const int)xRot % 360);
        yRot = (GLfloat)((const int)yRot % 360);

    // Refresh the Window
    glutPostRedisplay();

}

void desenharCilindroCobertura(GLUquadricObj *gqo,float x, float y, float z){
    GLUquadricObj *pObj = gqo;
    glPushMatrix();
  //cilindro
  //cobertura
    glColor3f(0.82f,0.41f,0.12f);
    glTranslatef(0.0f+x, 1.2f+y, -3.0f+z);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 1.0f,0.0f, 1.5f,26,13);
    // glPopMatrix();

  //corpo
    glPushMatrix();
    glColor3f(0.3f,0,0);
    glTranslatef(0.0f, 0.0f, -2.5f);
    gluCylinder(pObj, 1.0f,1.0f, 2.5f,26,13);
    glPopMatrix();
    glPopMatrix();

    // para raio
    glPushMatrix();
    glTranslatef(x,2.5f+y,-3+z);
    glLineWidth(3.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 1.0f, 0);
    glVertex3f(0.0f, 0.0f, 0);
    glEnd();
    glPopMatrix();
}

void desenharParedeFrontal(GLUquadricObj *gqo, float x, float y, float z){

//face roxa, amarela e vermelha, precisam acompanhar a verde

glPushMatrix();

glTranslatef(0.0f+x, 1.2f+y, -3.0f+z);

glPushMatrix();
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
//        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f+6.6f, 1.0f-0.2f, -1.0f+0.8f);//a (a,d) ou (c,b)
        glVertex3f(-1.0f, 1.0f-0.2f, -1.0f+0.8f);//b
        glVertex3f(-1.0f, 1.0f-0.2f,  1.0f);//c
        glVertex3f( 1.0f+6.6f, 1.0f-0.2f,  1.0f);//d

        // Bottom face (y = -1.0f)
        // glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f+6.6f, -1.0f,  1.0f);//a
        glVertex3f(-1.0f, -1.0f,  1.0f);//b
        glVertex3f(-1.0f, -1.0f, -1.0f+0.8f);//c
        glVertex3f( 1.0f+6.6f, -1.0f, -1.0f+0.8f);//d

        // Front face  (z = 1.0f)

        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f+6.6f,  1.0f-0.2f, 1.0f);
        glVertex3f(-1.0f,  1.0f-0.2f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f( 1.0f+6.6f, -1.0f, 1.0f);

        // inicio luz front rigth (z = 1.0f)
        glColor3f(1.0f, 1.0f, 0.0f);     // yellow
        //glColor3f(0.91f,0.59f,0.48f);
        glVertex3f(-1.3f,  1.0f-0.4f, 1.0f+0.71f);
        glVertex3f(-1.7f,  1.0f-0.4f, 1.0f+0.71f);
        glVertex3f(-1.7f, -1.0+0.8f, 1.0f+0.71f);
        glVertex3f(-1.3f, -1.0f+0.8f, 1.0f+0.71f);

        // fim luz frontal


        // Back face (z = -1.0f)
        // glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f+6.6f, -1.0f, -1.0f+0.8f);
        glVertex3f(-1.0f, -1.0f, -1.0f+0.8f);
        glVertex3f(-1.0f,  1.0f-0.2f, -1.0f+0.8f);
        glVertex3f( 1.0f+6.6f,  1.0f-0.2f, -1.0f+0.8f);

        // Left face (x = -1.0f)
        // glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f(-1.0f,  1.0f-0.2f,  1.0f);
        glVertex3f(-1.0f,  1.0f-0.2f, -1.0f+0.8f);
        glVertex3f(-1.0f, -1.0f, -1.0f+0.8f);
        glVertex3f(-1.0f, -1.0f,  1.0f);

        // Right face (x = 1.0f)
        // glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f(1.0f+6.6f,  1.0f-0.2f, -1.0f+0.8f);
        glVertex3f(1.0f+6.6f,  1.0f-0.2f,  1.0f);
        glVertex3f(1.0f+6.6f, -1.0f,  1.0f);
        glVertex3f(1.0f+6.6f, -1.0f, -1.0f+0.8f);
     glEnd();
     glPopMatrix();
glPopMatrix();

}

void desenharParedeLateral(GLUquadricObj *gqo, float x, float y, float z){

//face roxa, amarela e vermelha, precisam acompanhar a verde

glPushMatrix();

glTranslatef(0.0f+x, 1.2f+y, -3.0f+z);

glPushMatrix();
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
        // glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f-0.8f, 1.0f-0.2f, -1.0f-6.6f);//a (a,d) ou (c,b)
        glVertex3f(-1.0f, 1.0f-0.2f, -1.0f-6.6f);//b
        glVertex3f(-1.0f, 1.0f-0.2f,  1.0f);//c
        glVertex3f( 1.0f-0.8f, 1.0f-0.2f,  1.0f);//d

        // Bottom face (y = -1.0f)
        // glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f-0.8f, -1.0f,  1.0f);//a
        glVertex3f(-1.0f, -1.0f,  1.0f);//b
        glVertex3f(-1.0f, -1.0f, -1.0f-6.6f);//c
        glVertex3f( 1.0f-0.8f, -1.0f, -1.0f-6.6f);//d

        // Front face  (z = 1.0f)
        // glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f-0.8f,  1.0f-0.2f, 1.0f);
        glVertex3f(-1.0f,  1.0f-0.2f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f( 1.0f-0.8f, -1.0f, 1.0f);

        // Back face (z = -1.0f)
        // glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f-0.8f, -1.0f, -1.0f-6.6f);
        glVertex3f(-1.0f, -1.0f, -1.0f-6.6f);
        glVertex3f(-1.0f,  1.0f-0.2f, -1.0f-6.6f);
        glVertex3f( 1.0f-0.8f,  1.0f-0.2f, -1.0f-6.6f);

        // Left face (x = -1.0f)
        // glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f(-1.0f,  1.0f-0.2f,  1.0f);
        glVertex3f(-1.0f,  1.0f-0.2f, -1.0f-6.6f);
        glVertex3f(-1.0f, -1.0f, -1.0f-6.6f);
        glVertex3f(-1.0f, -1.0f,  1.0f);

        // Right face (x = 1.0f)
        // glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f(1.0f-0.8f,  1.0f-0.2f, -1.0f-6.6f);
        glVertex3f(1.0f-0.8f,  1.0f-0.2f,  1.0f);
        glVertex3f(1.0f-0.8f, -1.0f,  1.0f);
        glVertex3f(1.0f-0.8f, -1.0f, -1.0f-6.6f);
     glEnd();
     glPopMatrix();
glPopMatrix();

}


void desenharCasa(GLUquadricObj *gqo, float x, float y, float z){
glPushMatrix();
//face roxa, amarela e vermelha, precisam acompanhar a verde
//base
glPushMatrix();

glTranslatef(0.0f+x, 1.2f+y, -3.0f+z);

glPushMatrix();
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
        // glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glColor3f(0.72f,0.25f,0.05f);
        glVertex3f( 1.0f+2.0f, 1.2f, -1.0f-2.0f);//a (a,d) ou (c,b)
        glVertex3f(-1.0f, 1.2f, -1.0f-2.0f);//b
        glVertex3f(-1.0f, 1.2f,  1.0f);//c
        glVertex3f( 1.0f+2.0f, 1.2f,  1.0f);//d

        // Bottom face (y = -1.0f)
        // glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glColor3f(0.72f,0.25f,0.05f);
        glVertex3f( 1.0f+2.0f, -1.0f,  1.0f);//a
        glVertex3f(-1.0f, -1.0f,  1.0f);//b
        glVertex3f(-1.0f, -1.0f, -1.0f-2.0f);//c
        glVertex3f( 1.0f+2.0f, -1.0f, -1.0f-2.0f);//d

        // Front face  (z = 1.0f)
        // glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glColor3f(0.72f,0.25f,0.05f);
        glVertex3f( 1.0f+2.0f,  1.2f, 1.0f);
        glVertex3f(-1.0f,  1.2f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f( 1.0f+2.0f, -1.0f, 1.0f);

        // Back face (z = -1.0f)
        // glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glColor3f(0.72f,0.25f,0.05f);
        glVertex3f( 1.0f+2.0f, -1.0f, -1.0f-2.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f-2.0f);
        glVertex3f(-1.0f,  1.2f, -1.0f-2.0f);
        glVertex3f( 1.0f+2.0f,  1.2f, -1.0f-2.0f);

        // Left face (x = -1.0f)
        // glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glColor3f(0.72f,0.25f,0.05f);
        glVertex3f(-1.0f,  1.2f,  1.0f);
        glVertex3f(-1.0f,  1.2f, -1.0f-2.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f-2.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);

        // Right face (x = 1.0f)
        // glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        glColor3f(0.72f,0.25f,0.05f);
        glVertex3f(1.0f+2.0f,  1.2f, -1.0f-2.0f);
        glVertex3f(1.0f+2.0f,  1.2f,  1.0f);
        glVertex3f(1.0f+2.0f, -1.0f,  1.0f);
        glVertex3f(1.0f+2.0f, -1.0f, -1.0f-2.0f);
     glEnd();
     glPopMatrix();
glPopMatrix();
//torre central
glPushMatrix();

glTranslatef(0.0f+x+1.2f, 1.2f+y, -3.0f+z-1.0f);

glPushMatrix();
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
        //glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f-0.3f, 1.0f+1.7f, -1.0f);//a (a,d) ou (c,b)
        glVertex3f(-1.0f, 1.0f+1.7f, -1.0f);//b
        glVertex3f(-1.0f, 1.0f+1.7f,  1.0f);//c
        glVertex3f( 1.0f-0.3f, 1.0f+1.7f,  1.0f);//d

        // Bottom face (y = -1.0f)
        // glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f-0.3f, -1.0f,  1.0f);//a
        glVertex3f(-1.0f, -1.0f,  1.0f);//b
        glVertex3f(-1.0f, -1.0f, -1.0f);//c
        glVertex3f( 1.0f-0.3f, -1.0f, -1.0f);//d

        // Front face  (z = 1.0f)
        //glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f-0.3f,  1.0f+1.7f, 1.0f);
        glVertex3f(-1.0f,  1.0f+1.7f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f( 1.0f-0.3f, -1.0f, 1.0f);

        // porta front face  (z = 1.0f)
        glColor3f(0.3f, 0.0f, 0.0f);     // Red
        //glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f-0.8f,  1.0f+1.4f, 1.01f);
        glVertex3f(-1.0f+0.6f,  1.0f+1.4f, 1.01f);
        glVertex3f(-1.0f+0.6f, -1.0f, 1.01f);
        glVertex3f( 1.0f-0.8f, -1.0f, 1.01f);
        // Fim front face porta


        // Back face (z = -1.0f)
        // glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f-0.3f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f+1.7f, -1.0f);
        glVertex3f( 1.0f-0.3f,  1.0f+1.7f, -1.0f);

        // Left face (x = -1.0f)
        // glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f(-1.0f,  1.0f+1.7f,  1.0f);
        glVertex3f(-1.0f,  1.0f+1.7f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);

        // Right face (x = 1.0f)
        // glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f(1.0f-0.3f,  1.0f+1.7f, -1.0f);
        glVertex3f(1.0f-0.3f,  1.0f+1.7f,  1.0f);
        glVertex3f(1.0f-0.3f, -1.0f,  1.0f);
        glVertex3f(1.0f-0.3f, -1.0f, -1.0f);
     glEnd();
     glPopMatrix();
glPopMatrix();
        // cruz torre central
        glPushMatrix();
        glTranslatef(0.1f,3.8f,-7.5f);
        glLineWidth(3.0);
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex3f(0.0f, 2.0f, 0);
        glVertex3f(0.0f, 0.0f, 0);
          // glEnd();
        glPopMatrix();
        //cobertura torre
        glPushMatrix();
        glTranslatef(-0.f,3.8f,-7.5f);
        glLineWidth(3.0);
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex3f(0.8f, 1.5f, 0);
        glVertex3f(-0.8f, 1.5f, 0);
           glEnd();
        glPopMatrix();

glPushMatrix();

glTranslatef(0.0f+x+1.2f, 1.2f+y+3.7f, -3.0f+z-1.0f);

glPushMatrix();
  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
        // glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 0.0f, 0.0f, 0.0f);//a (a,d) ou (c,b)
        glVertex3f(0.0f, 0.0f, 0.0f);//b
        glVertex3f(0.0f, 0.0f,  0.0f);//c
        glVertex3f( 0.0f, 0.0f,  0.0f);//d

        // Bottom face (y = -1.0f)
        // glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f( 1.0f-0.3f, -1.0f,  1.0f);//a
        glVertex3f(-1.0f, -1.0f,  1.0f);//b
        glVertex3f(-1.0f, -1.0f, -1.0f);//c
        glVertex3f( 1.0f-0.3f, -1.0f, -1.0f);//d

        // Front face  (z = 1.0f)
        // glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glColor3f(0.82f,0.41f,0.12f);
        glVertex3f( 1.0f-0.3f,  0.5f, 0.0f);
        glVertex3f(-1.0f,  0.5f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f( 1.0f-0.3f, -1.0f, 1.0f);

        // Back face (z = -1.0f)
        // glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glColor3f(0.82f,0.41f,0.12f);
        glVertex3f( 1.0f-0.3f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f,  0.5f, 0.0f);
        glVertex3f( 1.0f-0.3f,  0.5f, 0.0f);

        // Left face (x = -1.0f)
        // glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f(-1.0f,  0.5f,  0.0f);
        glVertex3f(-1.0f,  0.5f, 0.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);

        // Right face (x = 1.0f)
        // glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        glColor3f(0.91f,0.59f,0.48f);
        glVertex3f(1.0f-0.3f,  0.5f, 0.0f);
        glVertex3f(1.0f-0.3f,  0.5f,  0.0f);
        glVertex3f(1.0f-0.3f, -1.0f,  1.0f);
        glVertex3f(1.0f-0.3f, -1.0f, -1.0f);
     glEnd();
     glPopMatrix();
glPopMatrix();

glPopMatrix();

}

void desenharPortao(GLUquadricObj *gqo, float x, float y, float z){

  //torre central
  glPushMatrix();

  glTranslatef(0.0f+x, 1.2f+y, -3.0f+z);

  glPushMatrix();
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
          // Top face (y = 1.0f)
          // Define vertices in counter-clockwise (CCW) order with normal pointing out
          // glColor3f(0.0f, 1.0f, 0.0f);     // Green
          glColor3f(0.72f,0.25f,0.05f);
          glVertex3f( 1.0f-0.3f, 1.0f+0.2f, -1.0f);//a (a,d) ou (c,b)
          glVertex3f(-1.0f, 1.0f+0.2f, -1.0f);//b
          glVertex3f(-1.0f, 1.0f+0.2f,  1.0f);//c
          glVertex3f( 1.0f-0.3f, 1.0f+0.2f,  1.0f);//d

          // Bottom face (y = -1.0f)
          // glColor3f(1.0f, 0.5f, 0.0f);     // Orange
          glColor3f(0.72f,0.25f,0.05f);
          glVertex3f( 1.0f-0.3f, -1.0f,  1.0f);//a
          glVertex3f(-1.0f, -1.0f,  1.0f);//b
          glVertex3f(-1.0f, -1.0f, -1.0f);//c
          glVertex3f( 1.0f-0.3f, -1.0f, -1.0f);//d

          // Front face  (z = 1.0f)
          //glColor3f(1.0f, 0.0f, 0.0f);     // Red
          glColor3f(0.72f,0.25f,0.05f);
          glVertex3f( 1.0f-0.3f,  1.0f+0.2f, 1.0f);
          glVertex3f(-1.0f,  1.0f+0.2f, 1.0f);
          glVertex3f(-1.0f, -1.0f, 1.0f);
          glVertex3f( 1.0f-0.3f, -1.0f, 1.0f);

          // portao (z = 1.0f)
          glColor3f(0.3f, 0.0f, 0.0f);     // Red
          //glColor3f(0.72f,0.25f,0.05f);
          glVertex3f( 1.0f-0.6f,  0.6f, 1.01f);
          glVertex3f(-1.0f+0.3f,  0.6f, 1.01f);
          glVertex3f(-1.0f+0.3f, -1.0f, 1.01f);
          glVertex3f( 1.0f-0.6f, -1.0f, 1.01f);

          // Back face (z = -1.0f)
          // glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
          glColor3f(0.72f,0.25f,0.05f);
          glVertex3f( 1.0f-0.3f, -1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f,  1.0f+0.2f, -1.0f);
          glVertex3f( 1.0f-0.3f,  1.0f+0.2f, -1.0f);

          // Left face (x = -1.0f)
          // glColor3f(0.0f, 0.0f, 1.0f);     // Blue
          glColor3f(0.72f,0.25f,0.05f);
          glVertex3f(-1.0f,  1.0f+0.2f,  1.0f);
          glVertex3f(-1.0f,  1.0f+0.2f, -1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f,  1.0f);

          // Right face (x = 1.0f)
          // glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
          glColor3f(0.72f,0.25f,0.05f);
          glVertex3f(1.0f-0.3f,  1.0f+0.2f, -1.0f);
          glVertex3f(1.0f-0.3f,  1.0f+0.2f,  1.0f);
          glVertex3f(1.0f-0.3f, -1.0f,  1.0f);
          glVertex3f(1.0f-0.3f, -1.0f, -1.0f);
       glEnd();
       glPopMatrix();

       //cobertura torre

       glPushMatrix();

       glTranslatef(0.0f+x-0.2f, 1.2f+y+2.5f, 0.0f+z);

       glPushMatrix();
         glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
               // Top face (y = 1.0f)
               // Define vertices in counter-clockwise (CCW) order with normal pointing out
               // glColor3f(0.0f, 1.0f, 0.0f);     // Green
               glColor3f(0.82f,0.41f,0.12f);
               glVertex3f( 0.0f, 0.0f, 0.0f);//a (a,d) ou (c,b)
               glVertex3f(0.0f, 0.0f, 0.0f);//b
               glVertex3f(0.0f, 0.0f,  0.0f);//c
               glVertex3f( 0.0f, 0.0f,  0.0f);//d

               // Bottom face (y = -1.0f)
               // glColor3f(1.0f, 0.5f, 0.0f);     // Orange
               glColor3f(0.82f,0.41f,0.12f);
               glVertex3f( 1.0f-0.3f, -1.0f,  1.0f);//a
               glVertex3f(-1.0f, -1.0f,  1.0f);//b
               glVertex3f(-1.0f, -1.0f, -1.0f);//c
               glVertex3f( 1.0f-0.3f, -1.0f, -1.0f);//d

               // Front face  (z = 1.0f)
               // glColor3f(1.0f, 0.0f, 0.0f);     // Red
               glColor3f(0.82f,0.41f,0.12f);
               glVertex3f( 1.0f-1.0f-0.1f,  0.1f, 0.0f);
               glVertex3f(-1.0f+1.0f-0.1f,  0.1f, 0.0f);
               glVertex3f(-1.0f, -1.0f, 1.0f);
               glVertex3f( 1.0f-0.3f, -1.0f, 1.0f);

               // Back face (z = -1.0f)
               // glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
               glColor3f(0.82f,0.41f,0.12f);
               glVertex3f( 1.0f-0.3f, -1.0f, -1.0f);
               glVertex3f(-1.0f, -1.0f, -1.0f);
               glVertex3f(-1.0f+1.0f-0.1f,  0.1f, 0.0f);
               glVertex3f( 1.0f-1.0f-0.1f,  0.1f, 0.0f);

               // Left face (x = -1.0f)
               // glColor3f(0.0f, 0.0f, 1.0f);     // Blue
               glColor3f(0.82f,0.41f,0.12f);
               glVertex3f(-1.0f+1.0f-0.1f,  0.1f,  0.0f);
               glVertex3f(-1.0f+1.0f-0.1f,  0.1f, 0.0f);
               glVertex3f(-1.0f, -1.0f, -1.0f);
               glVertex3f(-1.0f, -1.0f,  1.0f);

               // Right face (x = 1.0f)
               // glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
               glColor3f(0.82f,0.41f,0.12f);
               glVertex3f(1.0f-1.0f-0.1f,  0.1f, 0.0f);
               glVertex3f(1.0f-1.0f-0.1f,  0.1f,  0.0f);
               glVertex3f(1.0f-0.3f, -1.0f,  1.0f);
               glVertex3f(1.0f-0.3f, -1.0f, -1.0f);
            glEnd();
            glPopMatrix();
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
	glTranslatef(0.0f, -1.0f, -25.0f);
//rotacao
   glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	 glRotatef(yRot, 0.0f, 1.0f, 0.0f);
//rotacao
//teste

glTranslatef(0.0f, 0.0f, 5.0f);

	// Draw something
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);


//Cilindros

  //tras
   desenharCilindroCobertura(pObj,-5,0,-9);
   desenharCilindroCobertura(pObj,5,0,-9);

//frente
  desenharCilindroCobertura(pObj,-5,0,0);
  desenharCilindroCobertura(pObj,5,0,0);

//parede frontal
  desenharParedeFrontal(pObj, -3.4f, -1.5f, -0.7f);
//
//parede traseira
 desenharParedeFrontal(pObj, -3.4f, -1.5f, -9.1f);

//parede esquerda
desenharParedeLateral(pObj, -4.1f, -1.5f, -1.0f);

//parede direita
desenharParedeLateral(pObj, 4.8f, -1.5f, -1.0f);

//casa central
desenharCasa(pObj, -1.0f, -1.5f, -3.5f);

//portao
desenharPortao(pObj, 0.2f, -1.5f, 0.0f);

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
