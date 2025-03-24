#include <GL/glut.h>
#include <cmath>

// Posisi dan rotasi mobil
float posX = 0.0f, posZ = 0.0f;
float rotMobil = 0.0f;

// Warna dan bentuk mobil baru
void drawMobil() {
    // Body mobil (kuning)
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f);
        glScalef(2.5f, 0.5f, 1.2f);
        glutSolidCube(1.0);
    glPopMatrix();

    // Kabin mobil (oranye)
    glPushMatrix();
        glColor3f(1.0f, 0.5f, 0.0f);
        glTranslatef(0.0f, 0.5f, 0.0f);
        glScalef(1.2f, 0.5f, 0.9f);
        glutSolidCube(1.0);
    glPopMatrix();

    // Roda (hitam)
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
                glTranslatef(i * 1.1f, -0.25f, j * 0.5f);
                glutSolidTorus(0.05, 0.2, 12, 12);
            glPopMatrix();
        }
    }
}

// Grid lantai
void drawGrid() {
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_LINES);
    for (int i = -50; i <= 50; i++) {
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);
        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Kamera mengikuti mobil dari belakang
    glLoadIdentity();
    float camX = posX - sin(rotMobil * M_PI / 180.0f) * 5.0f;
    float camZ = posZ - cos(rotMobil * M_PI / 180.0f) * 5.0f;
    gluLookAt(camX, 3.0f, camZ, posX, 0.0f, posZ, 0.0f, 1.0f, 0.0f);

    // Lighting
    GLfloat light_pos[] = { 0.0f, 10.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Grid
    drawGrid();

    // Mobil
    glPushMatrix();
        glTranslatef(posX, 0.25f, posZ);
        glRotatef(rotMobil, 0.0f, 1.0f, 0.0f);
        drawMobil();
    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'w') { // maju
        posX += sin(rotMobil * M_PI / 180.0f) * 0.2f;
        posZ += cos(rotMobil * M_PI / 180.0f) * 0.2f;
    }
    if (key == 's') { // mundur
        posX -= sin(rotMobil * M_PI / 180.0f) * 0.2f;
        posZ -= cos(rotMobil * M_PI / 180.0f) * 0.2f;
    }
    if (key == 'a') { // belok kiri
        rotMobil += 5.0f;
    }
    if (key == 'd') { // belok kanan
        rotMobil -= 5.0f;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mobil 3D + Kamera Following");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

