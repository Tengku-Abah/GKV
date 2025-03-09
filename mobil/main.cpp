/*
 * Program: Mobil 2D dengan Latar Belakang Perkotaan
 * Deskripsi: Program ini menampilkan sebuah mobil 2D yang dapat dikontrol menggunakan WASD
 *           dengan latar belakang perkotaan di malam hari
 */

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Posisi dan dinamika mobil
float carPositionX = 0.0f;
float carPositionY = -0.25f;
float carAngle = 0.0f;
float moveSpeed = 0.001f;

// Warna mobil
float carColorR = 0.0f;
float carColorG = 0.0f;
float carColorB = 0.9f;

// Rotasi ban
float wheelRotation = 0.0f;
float wheelRotationSpeed = 5.0f;

// Status tombol
bool keyW = false;
bool keyA = false;
bool keyS = false;
bool keyD = false;

// Deklarasi fungsi
void drawCircle(float cx, float cy, float radius, int segments);
void drawWheel(float x, float y, float radius, float rotation);
void drawCar();
void drawBackground();
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void idle();
void display();
void reshape(int w, int h);

// Fungsi untuk menggambar lingkaran
void drawCircle(float cx, float cy, float radius, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)segments;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Fungsi untuk menggambar background perkotaan
void drawBackground() {
    glPushMatrix();
    
    // Pastikan transformasi mobil tidak mempengaruhi background
    glLoadIdentity();
    
    // Langit malam dengan gradien
    glBegin(GL_POLYGON);
    glColor3f(0.05f, 0.05f, 0.2f); // Biru gelap di atas
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glColor3f(0.2f, 0.2f, 0.4f);   // Biru agak terang di bawah
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();
    
    // Bulan
    glColor3f(1.0f, 1.0f, 0.8f);
    drawCircle(0.7f, 0.8f, 0.08f, 30);
    
    // Bintang-bintang
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glVertex2f(-0.8f, 0.9f);
    glVertex2f(-0.6f, 0.7f);
    glVertex2f(-0.4f, 0.85f);
    glVertex2f(-0.2f, 0.6f);
    glVertex2f(0.0f, 0.9f);
    glVertex2f(0.2f, 0.7f);
    glVertex2f(0.4f, 0.95f);
    glVertex2f(0.6f, 0.6f);
    glVertex2f(0.8f, 0.7f);
    glVertex2f(-0.7f, 0.6f);
    glVertex2f(-0.5f, 0.8f);
    glVertex2f(-0.3f, 0.7f);
    glVertex2f(-0.1f, 0.85f);
    glVertex2f(0.1f, 0.75f);
    glVertex2f(0.3f, 0.65f);
    glVertex2f(0.5f, 0.9f);
    glVertex2f(0.7f, 0.5f);
    glVertex2f(0.9f, 0.8f);
    glEnd();
    
    // Latar belakang tanah
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
    
    // Gedung 1
    glColor3f(0.3f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.95f, 0.0f);
    glVertex2f(-0.8f, 0.0f);
    glVertex2f(-0.8f, 0.5f);
    glVertex2f(-0.95f, 0.5f);
    glEnd();
    
    // Gedung 2
    glColor3f(0.2f, 0.2f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.75f, 0.0f);
    glVertex2f(-0.55f, 0.0f);
    glVertex2f(-0.55f, 0.7f);
    glVertex2f(-0.75f, 0.7f);
    glEnd();
    
    // Gedung 3
    glColor3f(0.4f, 0.4f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(-0.25f, 0.0f);
    glVertex2f(-0.25f, 0.4f);
    glVertex2f(-0.5f, 0.4f);
    glEnd();
    
    // Gedung 4
    glColor3f(0.25f, 0.25f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, 0.0f);
    glVertex2f(-0.02f, 0.0f);
    glVertex2f(-0.02f, 0.6f);
    glVertex2f(-0.2f, 0.6f);
    glEnd();
    
    // Gedung 5
    glColor3f(0.35f, 0.35f, 0.45f);
    glBegin(GL_POLYGON);
    glVertex2f(0.05f, 0.0f);
    glVertex2f(0.27f, 0.0f);
    glVertex2f(0.27f, 0.55f);
    glVertex2f(0.05f, 0.55f);
    glEnd();
    
    // Gedung 6
    glColor3f(0.3f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(0.35f, 0.0f);
    glVertex2f(0.55f, 0.0f);
    glVertex2f(0.55f, 0.65f);
    glVertex2f(0.35f, 0.65f);
    glEnd();
    
    // Gedung 7
    glColor3f(0.25f, 0.25f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(0.6f, 0.0f);
    glVertex2f(0.75f, 0.0f);
    glVertex2f(0.75f, 0.5f);
    glVertex2f(0.6f, 0.5f);
    glEnd();
    
    // Gedung 8
    glColor3f(0.3f, 0.3f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(0.8f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 0.45f);
    glVertex2f(0.8f, 0.45f);
    glEnd();
    
    // Jalan
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.15f);
    glVertex2f(1.0f, -0.15f);
    glVertex2f(1.0f, -0.35f);
    glVertex2f(-1.0f, -0.35f);
    glEnd();
    
    // Garis jalan
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Garis 1
    glBegin(GL_POLYGON);
    glVertex2f(-0.9f, -0.24f);
    glVertex2f(-0.7f, -0.24f);
    glVertex2f(-0.7f, -0.26f);
    glVertex2f(-0.9f, -0.26f);
    glEnd();
    
    // Garis 2
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.24f);
    glVertex2f(-0.3f, -0.24f);
    glVertex2f(-0.3f, -0.26f);
    glVertex2f(-0.5f, -0.26f);
    glEnd();
    
    // Garis 3
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, -0.24f);
    glVertex2f(0.1f, -0.24f);
    glVertex2f(0.1f, -0.26f);
    glVertex2f(-0.1f, -0.26f);
    glEnd();
    
    // Garis 4
    glBegin(GL_POLYGON);
    glVertex2f(0.3f, -0.24f);
    glVertex2f(0.5f, -0.24f);
    glVertex2f(0.5f, -0.26f);
    glVertex2f(0.3f, -0.26f);
    glEnd();
    
    // Garis 5
    glBegin(GL_POLYGON);
    glVertex2f(0.7f, -0.24f);
    glVertex2f(0.9f, -0.24f);
    glVertex2f(0.9f, -0.26f);
    glVertex2f(0.7f, -0.26f);
    glEnd();
    
    // Lampu jalan 1
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, -0.15f);
    glVertex2f(-0.58f, -0.15f);
    glVertex2f(-0.58f, 0.0f);
    glVertex2f(-0.6f, 0.0f);
    glEnd();
    
    // Lampu 1
    glColor3f(1.0f, 1.0f, 0.7f);
    drawCircle(-0.59f, 0.0f, 0.02f, 10);
    
    // Lampu jalan 2
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(0.58f, -0.15f);
    glVertex2f(0.6f, -0.15f);
    glVertex2f(0.6f, 0.0f);
    glVertex2f(0.58f, 0.0f);
    glEnd();
    
    // Lampu 2
    glColor3f(1.0f, 1.0f, 0.7f);
    drawCircle(0.59f, 0.0f, 0.02f, 10);
    
    // Trotoar atas
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.12f);
    glVertex2f(1.0f, -0.12f);
    glVertex2f(1.0f, -0.15f);
    glVertex2f(-1.0f, -0.15f);
    glEnd();
    
    // Trotoar bawah
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.35f);
    glVertex2f(1.0f, -0.35f);
    glVertex2f(1.0f, -0.38f);
    glVertex2f(-1.0f, -0.38f);
    glEnd();
    
    glPopMatrix();
}

// Fungsi untuk menggambar roda
void drawWheel(float x, float y, float radius, float rotation) {
    glPushMatrix();
    
    // Posisikan di lokasi roda
    glTranslatef(x, y, 0.0f);
    
    // Putar roda
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);
    
    // Roda luar (ban)
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.0f, 0.0f, radius, 30);
    
    // Bagian dalam roda (velg)
    glColor3f(1.0f, 0.8f, 0.0f);
    drawCircle(0.0f, 0.0f, radius * 0.7f, 24);
    
    // Jari-jari velg
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // 8 jari-jari
    for (int i = 0; i < 8; i++) {
        float angle = i * 3.14159f / 4.0f;
        glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f((radius * 0.6f) * cosf(angle), (radius * 0.6f) * sinf(angle));
        glEnd();
    }
    
    // Lubang tengah roda
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.0f, 0.0f, radius * 0.1f, 12);
    
    // Titik tengah
    glColor3f(0.5f, 0.0f, 0.0f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);
    glEnd();
    
    glPopMatrix();
}

// Fungsi untuk menggambar badan mobil
void drawCar() {
    glPushMatrix();
    
    // Terapkan transformasi pada mobil
    glTranslatef(carPositionX, carPositionY, 0.0f);
    glRotatef(carAngle, 0.0f, 0.0f, 1.0f);
    
    // Body utama mobil
    glColor3f(carColorR, carColorG, carColorB);
    
    // Main body box
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, -0.08f);
    glVertex2f(0.4f, -0.08f);
    glVertex2f(0.4f, 0.15f);
    glVertex2f(-0.4f, 0.15f);
    glEnd();
    
    // Bagian bawah mobil hitam
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, -0.08f);
    glVertex2f(0.4f, -0.08f);
    glVertex2f(0.4f, -0.15f);
    glVertex2f(-0.4f, -0.15f);
    glEnd();
    
    // Bumper depan
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.4f, -0.08f);
    glVertex2f(0.43f, -0.08f);
    glVertex2f(0.43f, 0.05f);
    glVertex2f(0.4f, 0.05f);
    glEnd();
    
    // Bumper belakang
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, -0.08f);
    glVertex2f(-0.43f, -0.08f);
    glVertex2f(-0.43f, 0.05f);
    glVertex2f(-0.4f, 0.05f);
    glEnd();
    
    // Atap biru muda
    glColor3f(0.7f, 0.8f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.25f, 0.15f);
    glVertex2f(0.25f, 0.15f);
    glVertex2f(0.25f, 0.25f);
    glVertex2f(-0.25f, 0.25f);
    glEnd();
    
    // Tiang atap kiri
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.25f, 0.15f);
    glVertex2f(-0.23f, 0.15f);
    glVertex2f(-0.23f, 0.25f);
    glVertex2f(-0.25f, 0.25f);
    glEnd();
    
    // Tiang atap kanan
    glBegin(GL_POLYGON);
    glVertex2f(0.25f, 0.15f);
    glVertex2f(0.23f, 0.15f);
    glVertex2f(0.23f, 0.25f);
    glVertex2f(0.25f, 0.25f);
    glEnd();
    
    // Kaca depan
    glColor3f(0.8f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.23f, 0.15f);
    glVertex2f(0.23f, 0.25f);
    glVertex2f(0.1f, 0.25f);
    glVertex2f(0.1f, 0.15f);
    glEnd();
    
    // Kaca belakang
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, 0.15f);
    glVertex2f(-0.1f, 0.25f);
    glVertex2f(-0.23f, 0.25f);
    glVertex2f(-0.23f, 0.15f);
    glEnd();
    
    // Pilar tiang tengah
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.1f, 0.15f);
    glVertex2f(0.1f, 0.25f);
    glVertex2f(0.08f, 0.25f);
    glVertex2f(0.08f, 0.15f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(-0.08f, 0.15f);
    glVertex2f(-0.08f, 0.25f);
    glVertex2f(-0.1f, 0.25f);
    glVertex2f(-0.1f, 0.15f);
    glEnd();
    
    // Lampu depan
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.38f, 0.07f);
    glVertex2f(0.4f, 0.07f);
    glVertex2f(0.4f, 0.13f);
    glVertex2f(0.38f, 0.13f);
    glEnd();
    
    // Lampu belakang
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.38f, 0.07f);
    glVertex2f(-0.4f, 0.07f);
    glVertex2f(-0.4f, 0.13f);
    glVertex2f(-0.38f, 0.13f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(-0.38f, -0.02f);
    glVertex2f(-0.4f, -0.02f);
    glVertex2f(-0.4f, 0.04f);
    glVertex2f(-0.38f, 0.04f);
    glEnd();
    
    // Tiang suar (lampu)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.25f);
    glVertex2f(0.02f, 0.25f);
    glVertex2f(0.02f, 0.35f);
    glVertex2f(0.0f, 0.35f);
    glEnd();
    
    // Lampu suar
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(0.01f, 0.37f, 0.03f, 15);
    
    // Tiang belakang kiri
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.37f, 0.15f);
    glVertex2f(-0.35f, 0.15f);
    glVertex2f(-0.35f, 0.32f);
    glVertex2f(-0.37f, 0.32f);
    glEnd();
    
    // Tiang belakang tengah
    glBegin(GL_POLYGON);
    glVertex2f(-0.25f, 0.25f);
    glVertex2f(-0.23f, 0.25f);
    glVertex2f(-0.23f, 0.32f);
    glVertex2f(-0.25f, 0.32f);
    glEnd();
    
    // Tiang belakang kanan
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, 0.25f);
    glVertex2f(-0.08f, 0.25f);
    glVertex2f(-0.08f, 0.32f);
    glVertex2f(-0.1f, 0.32f);
    glEnd();
    
    // Palang horizontal atas
    glBegin(GL_POLYGON);
    glVertex2f(-0.37f, 0.32f);
    glVertex2f(-0.08f, 0.32f);
    glVertex2f(-0.08f, 0.34f);
    glVertex2f(-0.37f, 0.34f);
    glEnd();
    
    // Pintu
    glColor3f(0.0f, 0.0f, 0.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.05f, -0.05f);
    glVertex2f(0.25f, -0.05f);
    glVertex2f(0.25f, 0.15f);
    glVertex2f(0.05f, 0.15f);
    glEnd();
    
    // Gagang pintu
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.18f, 0.05f);
    glVertex2f(0.22f, 0.05f);
    glEnd();
    
    // Gambar roda
    drawWheel(-0.25f, -0.15f, 0.12f, wheelRotation);
    drawWheel(0.25f, -0.15f, 0.12f, wheelRotation);
    
    glPopMatrix();
}

// Fungsi untuk menangani keyboard saat tombol ditekan
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            keyW = true;
            break;
        case 's':
        case 'S':
            keyS = true;
            break;
        case 'a':
        case 'A':
            keyA = true;
            break;
        case 'd':
        case 'D':
            keyD = true;
            break;
        case 27: // Tombol Escape
            exit(0);
            break;
    }
}

// Fungsi untuk menangani keyboard saat tombol dilepas
void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            keyW = false;
            break;
        case 's':
        case 'S':
            keyS = false;
            break;
        case 'a':
        case 'A':
            keyA = false;
            break;
        case 'd':
        case 'D':
            keyD = false;
            break;
    }
}

// Fungsi idle
void idle() {
    // Kontrol pergerakan mobil dengan WASD
    bool isMoving = false;
    
    if (keyW) {
        carPositionY += moveSpeed;
        isMoving = true;
    }
    
    if (keyS) {
        carPositionY -= moveSpeed;
        isMoving = true;
    }
    
    if (keyA) {
        carPositionX -= moveSpeed;
        isMoving = true;
    }
    
    if (keyD) {
        carPositionX += moveSpeed;
        isMoving = true;
    }
    
    // Rotasi ban saat mobil bergerak
    if (isMoving) {
        wheelRotation += wheelRotationSpeed;
        if (wheelRotation > 360.0f) {
            wheelRotation -= 360.0f;
        }
    }
    
    glutPostRedisplay();
}

// Fungsi display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Gambar background
    drawBackground();
    
    // Gambar mobil
    drawCar();
    
    glutSwapBuffers();
}

// Fungsi reshape yang telah diperbarui
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Menggunakan proyeksi ortogonal tetap
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Fungsi utama
int main(int argc, char** argv) {
    // Inisialisasi random seed
    srand(time(NULL));
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil 2D dengan Latar Belakang Perkotaan");
    
    // Inisialisasi OpenGL
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}
