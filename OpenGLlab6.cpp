#include <iostream>
#include <glut.h>
#include "stb_image.h"

#define _USE_MATH_DEFINES
#include <math.h>

GLuint bottomTexture, sideTexture, topTexture;

double cylinderRotateX = 0;
double cylinderRotateY = 0;

float cylinderRadius, cylinderHeight;
int countOfCylinderSides;

struct vector
{
    float x, y, z;
};

struct point
{
    float x, y, z;
};

#define sqr(a) (a)*(a)
void CalculateNormal(point a, point b, point c, vector *n)
{
    float wrki;
    vector v1, v2;
    v1.x = a.x - b.x;
    v1.y = a.y - b.y;
    v1.z = a.z - b.z;
    v2.x = b.x - c.x;
    v2.y = b.y - c.y;
    v2.z = b.z - c.z;

    n->x = (v1.y * v2.z - v1.z * v2.y);
    n->y = (v1.z * v2.x - v1.x * v2.z);
    n->z = (v1.x * v2.y - v1.y * v2.x);
    wrki = sqrt(sqr(n->x) + sqr(n->y) + sqr(n->z));
    n->x /= wrki;
    n->y /= wrki;
    n->z /= wrki;
}

void DrawCylinder(float radius, float height, int countOfSides)
{
    float a = 0.5f;
    float b = 0.5f;
    float c = 0.25f;
    vector n;
    point A, B, C;

    glBindTexture(GL_TEXTURE_2D, sideTexture);
    glBegin(GL_QUAD_STRIP);
    for (int i = 1; i <= countOfSides; i++) {
        A.x = radius * cos(2 * M_PI * i / countOfSides);
        A.y = radius * sin(2 * M_PI * i / countOfSides);
        A.z = -height / 2;
        B.x = radius * cos(2 * M_PI * i / countOfSides);
        B.y = radius * sin(2 * M_PI * i / countOfSides);
        B.z = height / 2;
        C.x = radius * cos(2 * M_PI * (i - 1) / countOfSides);
        C.y = radius * sin(2 * M_PI * (i - 1) / countOfSides);
        C.z = height / 2;
        CalculateNormal(A, B, C, &n);
        glTexCoord2f((i - 1) / (float)countOfSides, 0.0f + c);
        glNormal3f(n.x, n.y, n.z);
        glVertex3f(radius * cos(2 * M_PI * i / countOfSides), radius * sin(2 * M_PI * i / countOfSides), -height / 2);
        glTexCoord2f((i - 1) / (float)countOfSides, 1.0f - c);
        glNormal3f(n.x, n.y, n.z);
        glVertex3f(radius * cos(2 * M_PI * i / countOfSides), radius * sin(2 * M_PI * i / countOfSides), height / 2);
    }
    A.x = radius * cos(2 * M_PI * 1 / countOfSides);
    A.y = radius * sin(2 * M_PI * 1 / countOfSides);
    A.z = -height / 2;
    B.x = radius * cos(2 * M_PI * 1 / countOfSides);
    B.y = radius * sin(2 * M_PI * 1 / countOfSides);
    B.z = height / 2;
    C.x = radius * cos(2 * M_PI * countOfSides - 1 / countOfSides);
    C.y = radius * sin(2 * M_PI * countOfSides - 1 / countOfSides);
    C.z = height / 2;
    CalculateNormal(A, B, C, &n);
    glTexCoord2f(1.0f, 0.0f + c);
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(radius * cos(2 * M_PI * 1 / countOfSides), radius * sin(2 * M_PI * 1 / countOfSides), -height / 2);
    glTexCoord2f(1.0f, 1.0f - c);
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(radius * cos(2 * M_PI * 1 / countOfSides), radius * sin(2 * M_PI * 1 / countOfSides), height / 2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, bottomTexture);
    glBegin(GL_POLYGON);
    A.x = radius * cos(2 * M_PI * 3 / 10);
    A.y = radius * sin(2 * M_PI * 3 / 10);
    A.z = -height / 2;
    B.x = radius * cos(2 * M_PI * 2 / 10);
    B.y = radius * sin(2 * M_PI * 2 / 10);
    B.z = -height / 2;
    C.x = radius * cos(2 * M_PI * 1 / 10);
    C.y = radius * sin(2 * M_PI * 1 / 10);
    C.z = -height / 2;
    CalculateNormal(A, B, C, &n);
    for (int i = 1; i <= countOfSides; i++) {
        glTexCoord2f(a + b * cos(2 * M_PI * i / countOfSides), a + b * sin(2 * M_PI * i / countOfSides));
        glNormal3f(n.x, n.y, n.z);
        glVertex3f(radius * cos(2 * M_PI * i / countOfSides), radius * sin(2 * M_PI * i / countOfSides), -height / 2);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, topTexture);
    glBegin(GL_POLYGON);
    A.x = radius * cos(2 * M_PI * 1 / 10);
    A.y = radius * sin(2 * M_PI * 1 / 10);
    A.z = height / 2;
    B.x = radius * cos(2 * M_PI * 2 / 10);
    B.y = radius * sin(2 * M_PI * 2 / 10);
    B.z = height / 2;
    C.x = radius * cos(2 * M_PI * 3 / 10);
    C.y = radius * sin(2 * M_PI * 3 / 10);
    C.z = height / 2;
    CalculateNormal(A, B, C, &n);
    for (int i = 1; i <= countOfSides; i++) {
        glTexCoord2f(a + b * cos(2 * M_PI * i / countOfSides), a + b * sin(2 * M_PI * i / countOfSides));
        glNormal3f(n.x, n.y, n.z);
        glVertex3f(radius * cos(2 * M_PI * i / countOfSides), radius * sin(2 * M_PI * i / countOfSides), height / 2);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    GLfloat light0_ambient[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    GLfloat light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    GLfloat light0_position[] = { -1.0f, -1.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glEnable(GL_LIGHT0);

    glPushMatrix();
    glRotatef(cylinderRotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(cylinderRotateY, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    DrawCylinder(cylinderRadius, cylinderHeight, countOfCylinderSides);
    glPopMatrix();

    glutSwapBuffers();
}

void RotateСylinder(int key, int x, int y)
{
    switch (key) {
    case (GLUT_KEY_RIGHT): {
        cylinderRotateY += 3;
        break;
    }
    case (GLUT_KEY_LEFT): {
        cylinderRotateY -= 3;
        break;
    }
    case (GLUT_KEY_UP): {
        cylinderRotateX += 3;
        break;
}
    case (GLUT_KEY_DOWN): {
        cylinderRotateX -= 3;
        break;
    }
    }

    glutPostRedisplay();
}

void LoadTexture(GLuint *texture, const char *imageName)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    int width, height, cnt;
    unsigned char *data = stbi_load(imageName, &width, &height, &cnt, 0);
    if (data) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 
                                    0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    } 
    else std::cout << "Failed to load texture" << std::endl;
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("OpenGL lab 6");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    LoadTexture(&bottomTexture, "bottomTexture.jpg");
    LoadTexture(&sideTexture, "sideTexture.png"); 
    LoadTexture(&topTexture, "topTexture.jpg");

    std::cout << "Enter the radius of the cylinder(for example 0.35): \n";
    std::cin >> cylinderRadius;
    std::cout << "Enter the height of the cylinder(for example 1.5): \n";
    std::cin >> cylinderHeight;
    std::cout << "Enter the number of polygons of the cylinder(for example 20): \n";
    std::cin >> countOfCylinderSides;
    std::cout << "You can rotate the object using the arrows on the keyboard\n";

    glutDisplayFunc(Display);
    glutSpecialFunc(RotateСylinder);

    glutMainLoop();

    return 0;
}