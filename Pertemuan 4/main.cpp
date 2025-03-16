#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h> /* Tambahkan ini untuk printf */

// Variabel sudut untuk rotasi berbagai bagian
static int shoulder = 0, elbow = 0;
static int wrist = 0;
static int finger1 = 0, finger2 = 0, finger3 = 0, finger4 = 0, finger5 = 0;
static int thumb_angle_x = 0;
static int thumb_angle_z = -30;

// Variabel warna dan tampilan
static int wireframe = 1;
static float arm_color[3] = {0.8f, 0.6f, 0.4f}; // Warna kulit
static float joint_color[3] = {0.7f, 0.7f, 0.7f}; // Warna sendi

// Variabel posisi dan rotasi kamera
static float camera_rotation = 0.0f;
static float camera_height = 0.0f;
static float camera_zoom = -8.0f;

void init(void) {
    // Inisialisasi tampilan
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_SMOOTH);
    
    // Aktifkan pencahayaan
    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void setMaterial(float r, float g, float b) {
    GLfloat mat_ambient[] = { r*0.3f, g*0.3f, b*0.3f, 1.0f };
    GLfloat mat_diffuse[] = { r, g, b, 1.0f };
    GLfloat mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// Fungsi untuk menggambar silinder (untuk representasi sendi yang lebih baik)
void drawCylinder(float radius, float height, int slices) {
    GLUquadricObj *cylinder = gluNewQuadric();
    
    if (!wireframe) {
        gluQuadricDrawStyle(cylinder, GLU_FILL);
        gluQuadricNormals(cylinder, GLU_SMOOTH);
    } else {
        gluQuadricDrawStyle(cylinder, GLU_LINE);
    }
    
    gluCylinder(cylinder, radius, radius, height, slices, 1);
    
    gluDeleteQuadric(cylinder);
}

// Fungsi untuk menggambar sendi
void drawJoint(float radius) {
    GLUquadricObj *sphere = gluNewQuadric();
    
    if (!wireframe) {
        gluQuadricDrawStyle(sphere, GLU_FILL);
        gluQuadricNormals(sphere, GLU_SMOOTH);
    } else {
        gluQuadricDrawStyle(sphere, GLU_LINE);
    }
    
    setMaterial(joint_color[0], joint_color[1], joint_color[2]);
    gluSphere(sphere, radius, 12, 12);
    
    gluDeleteQuadric(sphere);
}

// Fungsi untuk menggambar bagian lengan
void drawLimb(float width, float height, float depth) {
    if (wireframe) {
        glutWireCube(1.0f);
    } else {
        setMaterial(arm_color[0], arm_color[1], arm_color[2]);
        glutSolidCube(1.0f);
    }
}

// Fungsi untuk menggambar jari
void drawFinger(int angle, float length1, float length2, float width) {
    // Gambar ruas pertama
    glPushMatrix();
    glScalef(length1, width, width);
    drawLimb(1.0f, 1.0f, 1.0f);
    glPopMatrix();
    
    // Gambar sendi
    glTranslatef(length1/2, 0.0f, 0.0f);
    drawJoint(width/2.0f * 1.1f);
    
    // Rotasi untuk ruas kedua
    glRotatef((GLfloat)angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(length2/2, 0.0f, 0.0f);
    
    // Gambar ruas kedua
    glPushMatrix();
    glScalef(length2, width * 0.9f, width * 0.9f);
    drawLimb(1.0f, 1.0f, 1.0f);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Menyetel posisi kamera
    glLoadIdentity();
    glTranslatef(0.0f, camera_height, camera_zoom);
    glRotatef(camera_rotation, 0.0f, 1.0f, 0.0f);
    
    // Mulai gambar lengan
    glPushMatrix();
    
    // Posisi awal dan rotasi bahu
    glTranslatef(-1.0f, 0.0f, 0.0f);
    drawJoint(0.2f);
    
    glRotatef((GLfloat)shoulder, 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);
    
    // Menggambar lengan bagian atas (bahu)
    glPushMatrix();
    glScalef(2.0f, 0.4f, 0.4f);
    drawLimb(1.0f, 1.0f, 1.0f);
    glPopMatrix();
    
    // Posisi dan rotasi siku
    glTranslatef(1.0f, 0.0f, 0.0f);
    drawJoint(0.2f);
    
    glRotatef((GLfloat)elbow, 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);
    
    // Menggambar lengan bagian bawah (siku ke tangan)
    glPushMatrix();
    glScalef(2.0f, 0.4f, 0.4f);
    drawLimb(1.0f, 1.0f, 1.0f);
    glPopMatrix();
    
    // Posisi dan rotasi pergelangan tangan
    glTranslatef(1.0f, 0.0f, 0.0f);
    drawJoint(0.15f);
    
    glRotatef((GLfloat)wrist, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.4f, 0.0f, 0.0f);
    
    // Menggambar telapak tangan
    glPushMatrix();
    glScalef(0.8f, 0.6f, 0.2f);
    drawLimb(1.0f, 1.0f, 1.0f);
    glPopMatrix();
    
    // JARI PERTAMA (JEMPOL)
    glPushMatrix();
    glTranslatef(-0.2f, -0.3f, 0.0f);
    glRotatef((GLfloat)thumb_angle_z, 0.0f, 0.0f, 1.0f);
    glRotatef((GLfloat)thumb_angle_x, 1.0f, 0.0f, 0.0f);
    
    drawJoint(0.08f);
    glTranslatef(0.15f, 0.0f, 0.0f);
    
    drawFinger(finger1, 0.3f, 0.25f, 0.12f);
    glPopMatrix();
    
    // JARI KEDUA (TELUNJUK)
    glPushMatrix();
    glTranslatef(0.4f, 0.25f, 0.0f);
    drawJoint(0.06f);
    glRotatef((GLfloat)finger2, 0.0f, 0.0f, 1.0f);
    drawFinger(finger2/2, 0.35f, 0.25f, 0.1f);
    glPopMatrix();
    
    // JARI KETIGA (TENGAH)
    glPushMatrix();
    glTranslatef(0.4f, 0.08f, 0.0f);
    drawJoint(0.06f);
    glRotatef((GLfloat)finger3, 0.0f, 0.0f, 1.0f);
    drawFinger(finger3/2, 0.4f, 0.3f, 0.1f);
    glPopMatrix();
    
    // JARI KEEMPAT (MANIS)
    glPushMatrix();
    glTranslatef(0.4f, -0.08f, 0.0f);
    drawJoint(0.06f);
    glRotatef((GLfloat)finger4, 0.0f, 0.0f, 1.0f);
    drawFinger(finger4/2, 0.35f, 0.25f, 0.1f);
    glPopMatrix();
    
    // JARI KELIMA (KELINGKING)
    glPushMatrix();
    glTranslatef(0.4f, -0.25f, 0.0f);
    drawJoint(0.06f);
    glRotatef((GLfloat)finger5, 0.0f, 0.0f, 1.0f);
    drawFinger(finger5/2, 0.3f, 0.2f, 0.08f);
    glPopMatrix();
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0f, (GLfloat)w / (GLfloat)h, 1.0f, 30.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, camera_zoom);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Kontrol bahu
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        
        // Kontrol siku
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        
        // Kontrol pergelangan tangan
        case 'w': wrist = (wrist + 5) % 360; break;
        case 'W': wrist = (wrist - 5) % 360; break;
        
        // Kontrol jari (jempol)
        case '1': finger1 = (finger1 + 5) % 90; break;
        case '!': finger1 = (finger1 - 5) % 90; break;
        
        // Kontrol jari (telunjuk)
        case '2': finger2 = (finger2 + 5) % 90; break;
        case '@': finger2 = (finger2 - 5) % 90; break;
        
        // Kontrol jari (tengah)
        case '3': finger3 = (finger3 + 5) % 90; break;
        case '#': finger3 = (finger3 - 5) % 90; break;
        
        // Kontrol jari (manis)
        case '4': finger4 = (finger4 + 5) % 90; break;
        case '$': finger4 = (finger4 - 5) % 90; break;
        
        // Kontrol jari (kelingking)
        case '5': finger5 = (finger5 + 5) % 90; break;
        case '%': finger5 = (finger5 - 5) % 90; break;
        
        // Kontrol jempol spesial (axis x dan z)
        case 't': thumb_angle_x = (thumb_angle_x + 5) % 90; break;
        case 'T': thumb_angle_x = (thumb_angle_x - 5) % 90; break;
        case 'y': thumb_angle_z = (thumb_angle_z + 5) % 90; break;
        case 'Y': thumb_angle_z = (thumb_angle_z - 5) % 90; break;
        
        // Semua jari sekaligus
        case 'f': 
            finger1 = finger2 = finger3 = finger4 = finger5 = (finger1 + 10) % 90; 
            break;
        case 'F': 
            finger1 = finger2 = finger3 = finger4 = finger5 = (finger1 - 10) % 90; 
            break;
            
        // Toggle wireframe/solid rendering
        case 'q': wireframe = !wireframe; break;
        
        // Reset posisi
        case 'r': 
            shoulder = elbow = wrist = 0;
            finger1 = finger2 = finger3 = finger4 = finger5 = 0;
            thumb_angle_x = 0;
            thumb_angle_z = -30;
            camera_rotation = 0.0f;
            camera_height = 0.0f;
            camera_zoom = -8.0f;
            break;
            
        // Kontrol kamera
        case 'a': camera_rotation = (camera_rotation + 5.0f); break;
        case 'd': camera_rotation = (camera_rotation - 5.0f); break;
        case 'i': camera_height += 0.2f; break;
        case 'k': camera_height -= 0.2f; break;
        case '+': camera_zoom += 0.5f; break;
        case '-': camera_zoom -= 0.5f; break;
        
        // Keluar
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

// Fungsi untuk tampilan menu
void displayInstructions() {
    printf("\n==== PROGRAM ANIMASI LENGAN DENGAN JARI ====\n");
    printf("Kontrol Sendi:\n");
    printf("  s/S: Putar bahu ke atas/bawah\n");
    printf("  e/E: Putar siku ke atas/bawah\n");
    printf("  w/W: Putar pergelangan ke atas/bawah\n");
    printf("\nKontrol Jari:\n");
    printf("  1/!: Tekuk/luruskan jempol\n");
    printf("  2/@: Tekuk/luruskan telunjuk\n");
    printf("  3/#: Tekuk/luruskan jari tengah\n");
    printf("  4/$: Tekuk/luruskan jari manis\n");
    printf("  5/%%: Tekuk/luruskan kelingking\n");
    printf("  f/F: Tekuk/luruskan semua jari\n");
    printf("  t/T: Rotasi jempol axis-X\n");
    printf("  y/Y: Rotasi jempol axis-Z\n");
    printf("\nKontrol Kamera:\n");
    printf("  a/d: Putar kamera kiri/kanan\n");
    printf("  i/k: Naik/turunkan kamera\n");
    printf("  +/-: Zoom in/out\n");
    printf("\nLain-lain:\n");
    printf("  q: Toggle wireframe/solid\n");
    printf("  r: Reset posisi\n");
    printf("  Esc: Keluar\n");
    printf("========================================\n\n");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lengan dengan Jari-Jari 3D");
    
    init();
    displayInstructions();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
