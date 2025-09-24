#include <GL/glut.h>
#include <cmath>
#include <string>

float handOpen = 0.0f;
bool openingHand = true;
float armBend = 30.0f;

// Texture IDs
GLuint metalTexture, carbonFiberTexture;

void createMetalTexture() {
    const int texSize = 64;
    unsigned char texture[texSize][texSize][3];

    for (int i = 0; i < texSize; i++) {
        for (int j = 0; j < texSize; j++) {
            float noise = (float)rand() / RAND_MAX * 0.2f + 0.8f;
            unsigned char color = (unsigned char)(noise * 255);
            texture[i][j][0] = color;
            texture[i][j][1] = color;
            texture[i][j][2] = color;
        }
    }

    glGenTextures(1, &metalTexture);
    glBindTexture(GL_TEXTURE_2D, metalTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texSize, texSize, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void createCarbonFiberTexture() {
    const int texSize = 64;
    unsigned char texture[texSize][texSize][3];

    for (int i = 0; i < texSize; i++) {
        for (int j = 0; j < texSize; j++) {
            float x = (float)i / texSize;
            float y = (float)j / texSize;
            float pattern = (sin(x * 50) * 0.5f + 0.5f) * (sin(y * 50) * 0.5f + 0.5f);
            unsigned char color = (unsigned char)(pattern * 100 + 50);
            texture[i][j][0] = color;
            texture[i][j][1] = color;
            texture[i][j][2] = color;
        }
    }

    glGenTextures(1, &carbonFiberTexture);
    glBindTexture(GL_TEXTURE_2D, carbonFiberTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texSize, texSize, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void init() {
    glClearColor(0.1f, 0.0f, 0.2f, 1.0f);  // Deep purple background
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    createMetalTexture();
    createCarbonFiberTexture();
}

void drawFinger(float angle) {
    glPushMatrix();
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.4f);
    glScalef(0.1f, 0.1f, 0.8f);
    glBindTexture(GL_TEXTURE_2D, metalTexture);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawProstheticArm() {
    glPushMatrix();
    glRotatef(armBend, 1.0f, 0.0f, 0.0f); // Bend the entire arm

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, carbonFiberTexture);
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.0f, 0.0f, -1.0f);
    glScalef(0.5f, 0.5f, 2.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, metalTexture);
    glColor3f(0.7f, 0.7f, 0.7f);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, carbonFiberTexture);
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.0f, 0.0f, 1.0f);
    glScalef(0.4f, 0.4f, 2.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 2.0f);
    glBindTexture(GL_TEXTURE_2D, metalTexture);
    glColor3f(0.7f, 0.7f, 0.7f);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 2.2f);
    glColor3f(0.7f, 0.7f, 0.7f);
    float fingerAngle = 90.0f * (1.0f - handOpen);

    glPushMatrix();
    glTranslatef(-0.2f, 0.0f, 0.0f);
    glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
    drawFinger(fingerAngle);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1f, 0.0f, 0.0f);
    drawFinger(fingerAngle);
    glPopMatrix();

    drawFinger(fingerAngle);

    glPushMatrix();
    glTranslatef(0.1f, 0.0f, 0.0f);
    drawFinger(fingerAngle);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2f, 0.0f, 0.0f);
    glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
    drawFinger(fingerAngle);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix(); // Pop the rotation for arm bending
}

void drawText(const char* text, float x, float y, float r, float g, float b, void* font) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1920, 0, 1080);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(4.0, 2.5, 5.0,  // Adjusted camera position
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Draw a colorful background
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.2f, 0.8f); // Bright purple
    glVertex3f(-50, -50, -10);
    glColor3f(0.2f, 0.2f, 0.8f); // Blue
    glVertex3f(50, -50, -10);
    glColor3f(0.8f, 0.2f, 0.2f); // Red
    glVertex3f(50, 50, -10);
    glColor3f(0.2f, 0.8f, 0.2f); // Green
    glVertex3f(-50, 50, -10);
    glEnd();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    drawProstheticArm();

    // Draw text with more advertising flair
    drawText("REVOLUTIONARY", 50, 1000, 1.0f, 1.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    drawText("PROSTHETIC ARM", 50, 950, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
    drawText("Experience the Future of Mobility", 50, 900, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
    drawText("Cutting-edge Technology | Seamless Integration | Enhanced Quality of Life", 50, 850, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);

    std::string handStatus = "Hand Status: " + std::string(openingHand ? "Opening" : "Closing");
    drawText(handStatus.c_str(), 50, 100, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle() {
    if (openingHand) {
        handOpen += 0.01f;
        if (handOpen >= 1.0f) {
            handOpen = 1.0f;
            openingHand = false;
        }
    } else {
        handOpen -= 0.01f;
        if (handOpen <= 0.0f) {
            handOpen = 0.0f;
            openingHand = true;
        }
    }

    armBend = 30.0f + 15.0f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.001f);

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Prosthetic Arm Animation");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
