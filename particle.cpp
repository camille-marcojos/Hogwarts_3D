/*****************************
 * 
 * 32. OpenGL Particle Engine, Citation: http://www.swiftless.com/tutorials/opengl/particles.html
 * 
 *********************************/
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

GLfloat texture[10];

const unsigned long ParticleCount = 100;

typedef struct
{
    double Xpos;
    double Ypos;
    double Zpos;
    double Xmov;
    double Zmov;
    double Red;
    double Green;
    double Blue;
    double Direction;
    double Acceleration;
    double Deceleration;
    double Scalez;
    bool Visible;
} PARTICLES;

PARTICLES Particle[ParticleCount];

GLuint LoadTextureRAW(const char *filename, int width,
                      int height);
void FreeTexture(GLuint texturez);

void square(void)
{
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0);
    glVertex2d(-1.0,-1.0);
    glTexCoord2d(1.0, 0.0);
    glVertex2d(1.0,-1.0);
    glTexCoord2d(1.0, 1.0);
    glVertex2d(1.0, 1.0);
    glTexCoord2d(0.0, 1.0);
    glVertex2d(-1.0, 1.0);
    glEnd();
}

void glCreateParticles(void)
{
    int i;
    for (i = 1; i < ParticleCount; i++)
    {
        Particle[i].Xpos = 0;
        Particle[i].Ypos = 0;
        Particle[i].Zpos = 0;
        Particle[i].Xmov = (((((((2 - 1 + 1) * rand() % 3) + 1) - 1 + 1) *
                              rand() % 3) +
                             1) *
                            0.005) - (((((((2 - 1 + 1) * rand() % 3) + 1) - 1 + 1) * rand() % 3) + 1) * 0.005);
        Particle[i].Zmov = (((((((2 - 1 + 1) * rand() % 3) + 1) - 1 + 1) *
                              rand() % 3) +
                             1) *
                            0.005) - (((((((2 - 1 + 1) * rand() % 3) + 1) - 1 + 1) * rand() % 3) + 1) * 0.005);
        Particle[i].Red = 1;
        Particle[i].Green = 1;
        Particle[i].Blue = 1;
        Particle[i].Scalez = 0.25;
        Particle[i].Direction = 0;
        Particle[i].Acceleration = ((((((8 - 5 + 2) * rand() % 3) + 5) - 1 + 1) * rand() % 3) + 1) * 0.02;
        Particle[i].Deceleration = 0.0025;
    }
}

void glUpdateParticles(void)
{
    int i;
    for (i = 1; i < ParticleCount; i++)
    {

        glColor3f(Particle[i].Red, Particle[i].Green,
                  Particle[i].Blue);

        Particle[i].Ypos = Particle[i].Ypos + Particle[i]
                                                  .Acceleration - Particle[i]
                                                  .Deceleration;
        Particle[i].Deceleration = Particle[i].Deceleration +
                                   0.0025;

        Particle[i].Xpos = Particle[i].Xpos + Particle[i].Xmov;
        Particle[i].Zpos = Particle[i].Zpos + Particle[i].Zmov;

        Particle[i].Direction = Particle[i].Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand() % 3) + 1) - 1 + 1) * rand() % 3) + 1);

        if (Particle[i].Ypos < 0)
        {
            Particle[i].Xpos = 0;
            Particle[i].Ypos = 0;
            Particle[i].Zpos = 0;
            Particle[i].Red = 1;
            Particle[i].Green = 1;
            Particle[i].Blue = 1;
            Particle[i].Direction = 0;
            Particle[i].Acceleration = ((((((8 - 5 + 2) * rand() % 3) + 5) - 1 + 1) * rand() % 3) + 1) * 0.02;
            Particle[i].Deceleration = 0.0025;
        }
    }
}

void glDrawParticles(void)
{
    int i;
    for (i = 1; i < ParticleCount; i++)
    {
        glPushMatrix();
        glTranslatef(Particle[i].Xpos, Particle[i].Ypos, Particle[i].Zpos);
        glRotatef(Particle[i].Direction - 90, 0, 0, 1);
        glScalef(Particle[i].Scalez, Particle[i].Scalez, Particle[i].Scalez);

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        glBlendFunc(GL_DST_COLOR, GL_ZERO);
        glBindTexture(GL_TEXTURE_2D, texture[0]);

        glBegin(GL_QUADS);
            glTexCoord2d(0, 0);
            glColor3f(.9,.5,.2);
            glVertex3f(-1, -1, 0);
            glTexCoord2d(1, 0);
            glColor3f(.9,.5,.2);
            glVertex3f(1, -1, 0);
            glTexCoord2d(1, 1);
            glColor3f(.9,.5,.2);
            glVertex3f(1, 1, 0);
            glTexCoord2d(0, 1);
            glColor3f(.9,.5,.2);
            glVertex3f(-1, 1, 0);
        glEnd();

        glBlendFunc(GL_ONE, GL_ONE);
        glBindTexture(GL_TEXTURE_2D, texture[1]);

        glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex3f(-1, -1, 0);
        glTexCoord2d(1, 0);
        glVertex3f(1, -1, 0);
        glTexCoord2d(1, 1);
        glVertex3f(1, 1, 0);
        glTexCoord2d(0, 1);
        glVertex3f(-1, 1, 0);
        glEnd();
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);

        glPopMatrix();
    }
}

// void display(void)
// {
//     glClearDepth(1);
//     glClearColor(0.0, 0.0, 0.0, 1.0);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glLoadIdentity();
//     glTranslatef(0, 0,-10);
//     glUpdateParticles();
//     glDrawParticles();
//     glutSwapBuffers();
// }

void init(void)
{
    //glEnable(GL_TEXTURE_2D);
    //glEnable(GL_DEPTH_TEST);

    glCreateParticles();

    texture[0] = LoadTextureRAW( "particle_mask.raw", 256, 256); //load our texture
    texture[1] = LoadTextureRAW( "particle.raw", 256, 256);
    //load our texture
}

// void reshape(int w, int h)
// {
//     glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
//     glMatrixMode(GL_MODELVIEW);
// }

// int main(int argc, char **argv)
// {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//     glutInitWindowSize(500, 500);
//     glutInitWindowPosition(100, 100);
//     glutCreateWindow("A basic OpenGL Window");
//     init();
    // glutDisplayFunc(display);
    // glutIdleFunc(display);
    // glutReshapeFunc(reshape);
    //glutMainLoop();
//     return 0;
// }

//function to load the RAW file

GLuint LoadTextureRAW(const char *filename, int width,
                      int height)
{
    GLuint texture;
    unsigned char *data;
    FILE *file;

    file = fopen(filename, "rb" );
    if (file == NULL)
        return 0;

    data = (unsigned char *)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    GL_REPEAT);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
              GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
                      GL_RGB, GL_UNSIGNED_BYTE, data);

    free(data);

    return texture;
}

void FreeTexture(GLuint texture)
{
    glDeleteTextures(1, &texture);
}