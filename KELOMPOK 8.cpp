#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 8
//  Oktavian Alle M.P (672020031)
//  Andika Rossy Febrian (672020208)
//  Febriand Gysberth P.Z (672020239)
//  Felix Wisnu  P.M (672020054)
//  Evan Gunawan S (672020251)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion {
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init() {
    glClearColor(0.529, 0.807, 0.921, 0.0);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width / 2, height / 2);
}

void ground() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, 1000.0);

    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}
void fondasi() {
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-600.0, -0.0, 160);
    glVertex3f(-600.0, 120.0, 160);
    glVertex3f(600.0, 120.0, 160);
    glVertex3f(600.0, -0.0, 160);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-600.0, -0.0, -800);
    glVertex3f(-600.0, 120.0, -800);
    glVertex3f(600.0, 120.0, -800);
    glVertex3f(600.0, -0.0, -800);
    glEnd();

    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-600.0, -0.0, 160);
    glVertex3f(-600.0, 120.0, 160);
    glVertex3f(-600.0, 120.0, -800);
    glVertex3f(-600.0, -0.0, -800);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(600.0, -0.0, -800);
    glVertex3f(600.0, 120.0, -800);
    glVertex3f(600.0, 120.0, 160);
    glVertex3f(600.0, -0.0, 160);
    glEnd();

    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-600.0, 120.0, 160);
    glVertex3f(600.0, 120.0, 160);
    glVertex3f(600.0, 120.0, -800);
    glVertex3f(-600.0, 120.0, -800);
    glEnd();

    //pagar fondasi
     //depan1
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-600.0, 120.0, 160);
    glVertex3f(-600.0, 170.0, 160);
    glVertex3f(-200.0, 170.0, 160);
    glVertex3f(-200.0, 120.0, 160);
    glEnd();
    //depan2
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(600.0, 120.0, 160);
    glVertex3f(600.0, 170.0, 160);
    glVertex3f(200.0, 170.0, 160);
    glVertex3f(200.0, 120.0, 160);
    glEnd();


    //belakang
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-600.0, 120.0, -800);
    glVertex3f(-600.0, 170.0, -800);
    glVertex3f(600.0, 170.0, -800);
    glVertex3f(600.0, 120.0, -800);
    glEnd();
    //kiri
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-600.0, 120.0, 160);
    glVertex3f(-600.0, 170.0, 160);
    glVertex3f(-600.0, 170.0, -800);
    glVertex3f(-600.0, 120.0, -800);
    glEnd();
    //kanan
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(600.0, 120.0, -800);
    glVertex3f(600.0, 170.0, -800);
    glVertex3f(600.0, 170.0, 160);
    glVertex3f(600.0, 120.0, 160);
    glEnd();


}
void tanggadasar() {
    //tangga -1
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 180);
    glVertex3f(-200.0, 120.0, 180);
    glVertex3f(200.0, 120.0, 180);
    glVertex3f(200.0, -0.0, 180);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 180);
    glVertex3f(-200.0, 120.0, 180);
    glVertex3f(-200.0, 120.0, 160);
    glVertex3f(-200.0, -0.0, 160);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(200.0, -0.0, 180);
    glVertex3f(200.0, 120.0, 180);
    glVertex3f(200.0, 120.0, 160);
    glVertex3f(200.0, -0.0, 160);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, 120.0, 180);
    glVertex3f(200.0, 120.0, 180);
    glVertex3f(200.0, 120.0, 160);
    glVertex3f(-200.0, 120.0, 160);
    glEnd();
    //tangga 0
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 200);
    glVertex3f(-200.0, 100.0, 200);
    glVertex3f(200.0, 100.0, 200);
    glVertex3f(200.0, -0.0, 200);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 200);
    glVertex3f(-200.0, 100.0, 200);
    glVertex3f(-200.0, 100.0, 180);
    glVertex3f(-200.0, -0.0, 180);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(200.0, -0.0, 200);
    glVertex3f(200.0, 100.0, 200);
    glVertex3f(200.0, 100.0, 180);
    glVertex3f(200.0, -0.0, 180);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, 100.0, 200);
    glVertex3f(200.0, 100.0, 200);
    glVertex3f(200.0, 100.0, 180);
    glVertex3f(-200.0, 100.0, 180);
    glEnd();
    //tangga 1
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 220);
    glVertex3f(-200.0, 80.0, 220);
    glVertex3f(200.0, 80.0, 220);
    glVertex3f(200.0, -0.0, 220);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 220);
    glVertex3f(-200.0, 80.0, 220);
    glVertex3f(-200.0, 80.0, 200);
    glVertex3f(-200.0, -0.0, 200);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(200.0, -0.0, 220);
    glVertex3f(200.0, 80.0, 220);
    glVertex3f(200.0, 80.0, 200);
    glVertex3f(200.0, -0.0, 200);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, 80.0, 220);
    glVertex3f(200.0, 80.0, 220);
    glVertex3f(200.0, 80.0, 200);
    glVertex3f(-200.0, 80.0, 200);
    glEnd();
    //tangga 2
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 240);
    glVertex3f(-200.0, 60.0, 240);
    glVertex3f(200.0, 60.0, 240);
    glVertex3f(200.0, -0.0, 240);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 240);
    glVertex3f(-200.0, 60.0, 240);
    glVertex3f(-200.0, 60.0, 220);
    glVertex3f(-200.0, -0.0, 220);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(200.0, -0.0, 240);
    glVertex3f(200.0, 60.0, 240);
    glVertex3f(200.0, 60.0, 220);
    glVertex3f(200.0, -0.0, 220);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, 60.0, 240);
    glVertex3f(200.0, 60.0, 240);
    glVertex3f(200.0, 60.0, 220);
    glVertex3f(-200.0, 60.0, 220);
    glEnd();
    //tangga 3
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 260);
    glVertex3f(-200.0, 40.0, 260);
    glVertex3f(200.0, 40.0, 260);
    glVertex3f(200.0, -0.0, 260);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 260);
    glVertex3f(-200.0, 40.0, 260);
    glVertex3f(-200.0, 40.0, 240);
    glVertex3f(-200.0, -0.0, 240);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(200.0, -0.0, 260);
    glVertex3f(200.0, 40.0, 260);
    glVertex3f(200.0, 40.0, 240);
    glVertex3f(200.0, -0.0, 240);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, 20.0, 260);
    glVertex3f(200.0, 20.0, 260);
    glVertex3f(200.0, 20.0, 240);
    glVertex3f(-200.0, 20.0, 240);
    glEnd();
    //tangga 4
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 280);
    glVertex3f(-200.0, 20.0, 280);
    glVertex3f(200.0, 20.0, 280);
    glVertex3f(200.0, -0.0, 280);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, -0.0, 280);
    glVertex3f(-200.0, 20.0, 280);
    glVertex3f(-200.0, 20.0, 260);
    glVertex3f(-200.0, -0.0, 260);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(200.0, -0.0, 280);
    glVertex3f(200.0, 20.0, 280);
    glVertex3f(200.0, 20.0, 260);
    glVertex3f(200.0, -0.0, 260);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.67, 0.67, 0.67);
    glVertex3f(-200.0, 20.0, 280);
    glVertex3f(200.0, 20.0, 280);
    glVertex3f(200.0, 20.0, 260);
    glVertex3f(-200.0, 20.0, 260);
    glEnd();
}
void lantai1() {
    //depan1
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-420.0, 120.0, 20);
    glVertex3f(-420.0, 320.0, 20);
    glVertex3f(-80.0, 320.0, 20);
    glVertex3f(-80.0, 120.0, 20);
    glEnd();
    //depan2
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(80.0, 120.0, 20);
    glVertex3f(80.0, 320.0, 20);
    glVertex3f(420.0, 320.0, 20);
    glVertex3f(420.0, 120.0, 20);
    glEnd();
    //pintu gerbang1
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.27, 0.0);
    glVertex3f(-110.0, 120.0, 100);
    glVertex3f(-110.0, 320.0, 100);
    glVertex3f(-80.0, 320.0, 20);
    glVertex3f(-80.0, 120.0, 20);
    glEnd();
    //pintu gerbang2
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.27, 0.0);
    glVertex3f(80.0, 120.0, 20);
    glVertex3f(80.0, 320.0, 20);
    glVertex3f(110.0, 320.0, 100);
    glVertex3f(110.0, 120.0, 100);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-420.0, 120.0, -640);
    glVertex3f(-420.0, 320.0, -640);
    glVertex3f(420.0, 320.0, -640);
    glVertex3f(420.0, 120.0, -640);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-420.0, 120.0, 20);
    glVertex3f(-420.0, 320.0, 20);
    glVertex3f(-420.0, 320.0, -640);
    glVertex3f(-420.0, 120.0, -640);
    glEnd();
    //pintu kiri 1
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.27, 0.0);
    glVertex3f(-421.0, 120.0, -210);
    glVertex3f(-421.0, 320.0, -210);
    glVertex3f(-421.0, 320.0, -420);
    glVertex3f(-421.0, 120.0, -420);
    glEnd();
    //pintu kiri 2
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.27, 0.0);
    glVertex3f(-419.0, 120.0, -210);
    glVertex3f(-419.0, 320.0, -210);
    glVertex3f(-419.0, 320.0, -420);
    glVertex3f(-419.0, 120.0, -420);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(420.0, 120.0, -640);
    glVertex3f(420.0, 320.0, -640);
    glVertex3f(420.0, 320.0, 20);
    glVertex3f(420.0, 120.0, 20);
    glEnd();
    //pintu kanan 1
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.27, 0.0);
    glVertex3f(421.0, 120.0, -210);
    glVertex3f(421.0, 320.0, -210);
    glVertex3f(421.0, 320.0, -420);
    glVertex3f(421.0, 120.0, -420);
    glEnd();
    //pintu kanan 2
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.27, 0.0);
    glVertex3f(419.0, 120.0, -210);
    glVertex3f(419.0, 320.0, -210);
    glVertex3f(419.0, 320.0, -420);
    glVertex3f(419.0, 120.0, -420);
    glEnd();
    //bawah
    glBegin(GL_POLYGON);
    glColor3f(0.77, 0.15, 0.0);
    glVertex3f(-419.0, 121.0, 20);
    glVertex3f(419.0, 121.0, 20);
    glVertex3f(419.0, 121.0, -640);
    glVertex3f(-419.0, 121.0, -640);
    glEnd();


    //atas
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.27, 0.0);
    glVertex3f(-520.0, 320.0, 120);
    glVertex3f(520.0, 320.0, 120);
    glVertex3f(520.0, 320.0, -740);
    glVertex3f(-520.0, 320.0, -740);
    glEnd();
    //depan
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.53, 0.12);
    glVertex3f(-520.0, 320.0, 120);
    glVertex3f(-520.0, 380.0, 120);
    glVertex3f(520.0, 380.0, 120);
    glVertex3f(520.0, 320.0, 120);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.53, 0.12);
    glVertex3f(-520.0, 320.0, -740);
    glVertex3f(-520.0, 380.0, -740);
    glVertex3f(520.0, 380.0, -740);
    glVertex3f(520.0, 320.0, -740);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.53, 0.12);
    glVertex3f(-520.0, 320.0, 120);
    glVertex3f(-520.0, 380.0, 120);
    glVertex3f(-520.0, 380.0, -740);
    glVertex3f(-520.0, 320.0, -740);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.53, 0.12);
    glVertex3f(520.0, 320.0, -740);
    glVertex3f(520.0, 380.0, -740);
    glVertex3f(520.0, 380.0, 120);
    glVertex3f(520.0, 320.0, 120);
    glEnd();
}
void meja() {
    //depan
    glBegin(GL_POLYGON);
    glColor3f(0.64, 0.28, 0.0);
    glVertex3f(-140.0, 125.0, -500);
    glVertex3f(-140.0, 220.0, -500);
    glVertex3f(140.0, 220.0, -500);
    glVertex3f(140.0, 125.0, -500);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
    glColor3f(0.64, 0.28, 0.0);
    glVertex3f(-140.0, 125.0, -600);
    glVertex3f(-140.0, 220.0, -600);
    glVertex3f(140.0, 220.0, -600);
    glVertex3f(140.0, 125.0, -600);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
    glColor3f(0.64, 0.28, 0.0);
    glVertex3f(-140.0, 125.0, -500);
    glVertex3f(-140.0, 220.0, -500);
    glVertex3f(-140.0, 220.0, -600);
    glVertex3f(-140.0, 125.0, -600);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.64, 0.28, 0.0);
    glVertex3f(140.0, 125.0, -600);
    glVertex3f(140.0, 220.0, -600);
    glVertex3f(140.0, 220.0, -500);
    glVertex3f(140.0, 125.0, -500);
    glEnd();

    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.64, 0.28, 0.0);
    glVertex3f(-140.0, 220.0, -500);
    glVertex3f(140.0, 220.0, -500);
    glVertex3f(140.0, 220.0, -600);
    glVertex3f(-140.0, 220.0, -600);
    glEnd();
}
void jalan() {

    //kanan
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-600.0, 0.0, -1000);
    glVertex3f(-600.0, 10.0, -1000);
    glVertex3f(-600.0, 10.0, 1000);
    glVertex3f(-600.0, 0.0, 1000);
    glEnd();

    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-1000.0, 10.0, 1000);
    glVertex3f(-600.0, 10.0, 1000);
    glVertex3f(-600.0, 10.0, -1000);
    glVertex3f(-1000.0, 10.0, -1000);
    glEnd();

    //atas
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-810.0, 11.0, 1000);
    glVertex3f(-790.0, 11.0, 1000);
    glVertex3f(-790.0, 11.0, 800);
    glVertex3f(-810.0, 11.0, 800);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-810.0, 11.0, 700);
    glVertex3f(-790.0, 11.0, 700);
    glVertex3f(-790.0, 11.0, 500);
    glVertex3f(-810.0, 11.0, 500);
    glEnd();

    //atas
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-810.0, 11.0, 400);
    glVertex3f(-790.0, 11.0, 400);
    glVertex3f(-790.0, 11.0, 200);
    glVertex3f(-810.0, 11.0, 200);
    glEnd();

    //atas
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-810.0, 11.0, 100);
    glVertex3f(-790.0, 11.0, 100);
    glVertex3f(-790.0, 11.0, -100);
    glVertex3f(-810.0, 11.0, -100);
    glEnd();

    //atas
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-810.0, 11.0, -200);
    glVertex3f(-790.0, 11.0, -200);
    glVertex3f(-790.0, 11.0, -400);
    glVertex3f(-810.0, 11.0, -400);
    glEnd();

    //atas
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-810.0, 11.0, -500);
    glVertex3f(-790.0, 11.0, -500);
    glVertex3f(-790.0, 11.0, -700);
    glVertex3f(-810.0, 11.0, -700);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-810.0, 11.0, -800);
    glVertex3f(-790.0, 11.0, -800);
    glVertex3f(-790.0, 11.0, -1000);
    glVertex3f(-810.0, 11.0, -1000);
    glEnd();
}

void draw() {
    //dasar jendela kiri 1
    glPushMatrix();
    glTranslatef(-340, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(8);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 70.0, 0);
    glVertex3f(-45.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //dalam jendela
    //horozontal 1
    glPushMatrix();
    glTranslatef(-340, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //horizontal 2
    glPushMatrix();
    glTranslatef(-340, 220, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //horizontal 3
    glPushMatrix();
    glTranslatef(-340, 240, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 1
    glPushMatrix();
    glTranslatef(-340, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 2
    glPushMatrix();
    glTranslatef(-375, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 3
    glPushMatrix();
    glTranslatef(-305, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();

    //dasar jendela kiri 2
    glPushMatrix();
    glTranslatef(-183, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(8);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 70.0, 0);
    glVertex3f(-45.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //horozontal 1
    glPushMatrix();
    glTranslatef(-183, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //horizontal 2
    glPushMatrix();
    glTranslatef(-183, 220, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //horizontal 3
    glPushMatrix();
    glTranslatef(-183, 240, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 1
    glPushMatrix();
    glTranslatef(-183, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 2
    glPushMatrix();
    glTranslatef(-148, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 3
    glPushMatrix();
    glTranslatef(-218, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();

    //dasar jendela kanan 1
    glPushMatrix();
    glTranslatef(340, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(8);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 70.0, 0);
    glVertex3f(-45.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //dalam jendela
    //horozontal 1
    glPushMatrix();
    glTranslatef(340, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //horizontal 2
    glPushMatrix();
    glTranslatef(340, 220, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //horizontal 3
    glPushMatrix();
    glTranslatef(340, 240, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 1
    glPushMatrix();
    glTranslatef(340, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 2
    glPushMatrix();
    glTranslatef(375, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 3
    glPushMatrix();
    glTranslatef(305, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();

    //dasar jendela kanan 2
    glPushMatrix();
    glTranslatef(183, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(8);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 70.0, 0);
    glVertex3f(-45.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //horozontal 1
    glPushMatrix();
    glTranslatef(183, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //horizontal 2
    glPushMatrix();
    glTranslatef(183, 220, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //horizontal 3
    glPushMatrix();
    glTranslatef(183, 240, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.0, .0, 0);
    glVertex3f(45.0, 0.0, 0);
    glVertex3f(45.0, 20.0, 0);
    glVertex3f(-45.0, 20.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 1
    glPushMatrix();
    glTranslatef(183, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 2
    glPushMatrix();
    glTranslatef(148, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //vertikal 3
    glPushMatrix();
    glTranslatef(218, 200, 24);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, .0, 0);
    glVertex3f(10.0, 0.0, 0);
    glVertex3f(10.0, 70.0, 0);
    glVertex3f(-10.0, 70.0, 0);
    glEnd();
    glPopMatrix();
    //tiang//
    //tiang depan kiri 1
    glPushMatrix();
    glTranslatef(-260, 320, 20);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang depan kiri 2
    glPushMatrix();
    glTranslatef(-105, 320, 20);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang depan kiri 3
    glPushMatrix();
    glTranslatef(-420, 320, 20);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang kiri 1
    glPushMatrix();
    glTranslatef(-420, 320, -115);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang kiri 2
    glPushMatrix();
    glTranslatef(-420, 320, -215);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang kiri 3
    glPushMatrix();
    glTranslatef(-420, 320, -525);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();
    //tiang kiri 4
    glPushMatrix();
    glTranslatef(-420, 320, -425);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();



    //tiang depan kanan 1
    glPushMatrix();
    glTranslatef(260, 320, 20);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang depan kanan 2
    glPushMatrix();
    glTranslatef(105, 320, 20);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang depan kanan 3
    glPushMatrix();
    glTranslatef(420, 320, 20);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang kanan 1
    glPushMatrix();
    glTranslatef(420, 320, -115);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang kanan 2
    glPushMatrix();
    glTranslatef(420, 320, -215);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang kanan 3
    glPushMatrix();
    glTranslatef(420, 320, -525);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();
    //tiang kanan 4
    glPushMatrix();
    glTranslatef(420, 320, -425);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang belakang kiri 1
    glPushMatrix();
    glTranslatef(-260, 320, -640);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();
    //tiang belakang kiri 2
    glPushMatrix();
    glTranslatef(-105, 320, -640);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();
    //tiang belakang kiri 3
    glPushMatrix();
    glTranslatef(-420, 320, -640);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang belakang kanan 1
    glPushMatrix();
    glTranslatef(260, 320, -640);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();
    //tiang belakang kanan 2
    glPushMatrix();
    glTranslatef(105, 320, -640);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();
    //tiang belakang kanan 3
    glPushMatrix();
    glTranslatef(420, 320, -640);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 20.0f, 20.0f, 200.0f, 32, 32);
    glPopMatrix();

    //tiang//

    //meja kecil
    glPushMatrix();
    glTranslatef(191.5, 163, -551);
    glColor3f(0.64, 0.51, 0.0);
    glutSolidCube(80.0);
    glPopMatrix();
    //meja kecil 2
    glPushMatrix();
    glTranslatef(-191, 163, -551);
    glColor3f(0.64, 0.51, 0.0);
    glutSolidCube(80.0);
    glPopMatrix();
    //gentong
    glPushMatrix();
    glTranslatef(169, 159, 76.5);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidTorus(10.0, 20.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(169, 146, 76.5);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidTorus(10.0, 15.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(167, 129, 72);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidTorus(10.0, 10.0, 20, 20);
    glPopMatrix();
    // tiang penyangga 1
    glPushMatrix();
    glTranslatef(135, 318, 104);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 200.0f, 32, 32);
    glPopMatrix();
    // tiang penyangga 2
    glPushMatrix();
    glTranslatef(-135, 318, 104);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 200.0f, 32, 32);
    glPopMatrix();
    // tiang penyangga 3
    glPushMatrix();
    glTranslatef(-500, 318, -104);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 200.0f, 32, 32);
    glPopMatrix();
    // tiang penyangga 4
    glPushMatrix();
    glTranslatef(500, 318, -404);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 200.0f, 32, 32);
    glPopMatrix();
    // tiang penyangga 5
    glPushMatrix();
    glTranslatef(135, 318, -720);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 200.0f, 32, 32);
    glPopMatrix();
    // tiang penyangga 6
    glPushMatrix();
    glTranslatef(-135, 318, -720);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 200.0f, 32, 32);
    glPopMatrix();

    // teko
    glPushMatrix();
    glTranslatef(192, 208, -548);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidTeapot(10.0);
    glPopMatrix();
    //kursi kiri depan
    glPushMatrix();
    glTranslatef(-254, 120, -338);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 70.0, 0);
    glVertex3f(-95.0, 70.0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-254, 145, -338);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 0.0, -40);
    glVertex3f(-95.0, 0.0, -40);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-254, 120, -378);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 25.0, 0);
    glVertex3f(-95.0, 25.0, 0);
    glEnd();
    glPopMatrix();

    //kursi kanan depan
    glPushMatrix();
    glTranslatef(254, 120, -338);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 70.0, 0);
    glVertex3f(-95.0, 70.0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(254, 145, -338);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 0.0, -40);
    glVertex3f(-95.0, 0.0, -40);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(254, 120, -378);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 25.0, 0);
    glVertex3f(-95.0, 25.0, 0);
    glEnd();
    glPopMatrix();

    //kursi kiri belakang
    glPushMatrix();
    glTranslatef(-254, 120, -138);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 70.0, 0);
    glVertex3f(-95.0, 70.0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-254, 145, -138);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 0.0, -40);
    glVertex3f(-95.0, 0.0, -40);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-254, 120, -178);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 25.0, 0);
    glVertex3f(-95.0, 25.0, 0);
    glEnd();
    glPopMatrix();

    //kursi kanan belakang
    glPushMatrix();
    glTranslatef(254, 120, -138);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 70.0, 0);
    glVertex3f(-95.0, 70.0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(254, 145, -138);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 0.0, -40);
    glVertex3f(-95.0, 0.0, -40);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(254, 120, -178);
    glColor3f(0.49f, 0.33, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-95.0, .0, 0);
    glVertex3f(95.0, 0.0, 0);
    glVertex3f(95.0, 25.0, 0);
    glVertex3f(-95.0, 25.0, 0);
    glEnd();
    glPopMatrix();

    //pohon 
    glPushMatrix();
    glTranslatef(618, 20, 693);
    glColor3f(0.51f, 0.35f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(618, 50, 693);
    glColor3f(0.51f, 0.35f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(618, 100, 693);
    glColor3f(0.51f, 0.35f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(618, 150, 693);
    glColor3f(0.51f, 0.35f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(618, 200, 693);
    glColor3f(0.51f, 0.35f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(618, 250, 693);
    glColor3f(0.51f, 0.35f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(618, 300, 693);
    glColor3f(0.51f, 0.35f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(618, 350, 693);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(668, 250, 693);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(568, 250, 693);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(618, 250, 743);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(618, 250, 643);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(618, 250, 593);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(618, 250, 793);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(718, 250, 693);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(518, 250, 693);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(668, 250, 693);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(668, 250, 743);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(568, 250, 743);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(668, 250, 643);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(568, 250, 643);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(668, 300, 693);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(568, 300, 693);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(618, 300, 743);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(618, 300, 643);
    glColor3f(0.0f, 0.61f, 0.0f);
    glutSolidCube(50.0);
    glPopMatrix();

    //lantai 2
    glPushMatrix();
    glTranslatef(0, 572, -270);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidCube(500.0);
    glPopMatrix();

    //tiang lt 2_1
    glPushMatrix();
    glTranslatef(312, 779, -240);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 450.0f, 32, 32);
    glPopMatrix();

    //tiang lt 2_2
    glPushMatrix();
    glTranslatef(100, 779, 100);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 450.0f, 32, 32);
    glPopMatrix();

    //tiang lt 2_3
    glPushMatrix();
    glTranslatef(-100, 779, 100);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 450.0f, 32, 32);
    glPopMatrix();

    //tiang lt 2_4
    glPushMatrix();
    glTranslatef(-312, 779, -240);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 450.0f, 32, 32);
    glPopMatrix();

    //tiang lt 2_5
    glPushMatrix();
    glTranslatef(-100, 779, -650);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 450.0f, 32, 32);
    glPopMatrix();

    //tiang lt 2_6
    glPushMatrix();
    glTranslatef(100, 779, -650);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 450.0f, 32, 32);
    glPopMatrix();

    //pintu lt 2
    glPushMatrix();
    glTranslatef(30, 322, -19);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-70, 0, 0);
    glVertex3f(70, 0, 0);
    glVertex3f(70, 200, 0);
    glVertex3f(-70, 200, 0);
    glEnd();
    glPopMatrix();
    //pintu lt 2
    glPushMatrix();
    glTranslatef(-20, 322, -19);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-70, 0, 0);
    glVertex3f(70, 0, 0);
    glVertex3f(70, 200, 0);
    glVertex3f(-70, 200, 0);
    glEnd();
    glPopMatrix();

    //atap lantai 2_1
    glPushMatrix();
    glTranslatef(-20, 731, 188);
    glRotatef(60, -1.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-350, 0, 0);
    glVertex3f(350, 0, 0);
    glVertex3f(250, 200, 0);
    glVertex3f(-250, 200, 0);
    glEnd();
    glPopMatrix();

    //atap lantai 2_2
    glPushMatrix();
    glTranslatef(-20, 731, -738);
    glRotatef(60, 1.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-350, 0, 0);
    glVertex3f(350, 0, 0);
    glVertex3f(250, 200, 0);
    glVertex3f(-250, 200, 0);
    glEnd();
    glPopMatrix();

    //atap lantai 2_3
    glPushMatrix();
    glTranslatef(-384, 659, -252);
    glRotatef(60, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, -350);
    glVertex3f(0, 0, 350);
    glVertex3f(200, 0, 250);
    glVertex3f(200, 0, -250);
    glEnd();
    glPopMatrix();

    //atap lantai 2_4
    glPushMatrix();
    glTranslatef(274, 838, -271);
    glRotatef(60, 0.0, 0.0, -1.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, -200);
    glVertex3f(0, 0, 200);
    glVertex3f(200, 0, 350);
    glVertex3f(200, 0, -350);
    glEnd();
    glPopMatrix();

    //jendela lt 2_1
    glPushMatrix();
    glTranslatef(171, 466, -59);
    glBegin(GL_POLYGON);
    glColor3f(0.92, 0.89, 0.06);
    glVertex3f(-40, -40, 40);
    glVertex3f(-40, 40, 40);
    glVertex3f(40, 40, 40);
    glVertex3f(40, -40, 40);
    glEnd();
    glPopMatrix();

    //jendela lt 2_1
    glPushMatrix();
    glTranslatef(171, 466, -53);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-35, -35, 35);
    glVertex3f(-35, 35, 35);
    glVertex3f(35, 35, 35);
    glVertex3f(35, -35, 35);
    glEnd();
    glPopMatrix();

    //jendela lt 2_2
    glPushMatrix();
    glTranslatef(-170, 466, -59);
    glBegin(GL_POLYGON);
    glColor3f(0.92, 0.89, 0.06);
    glVertex3f(-40, -40, 40);
    glVertex3f(-40, 40, 40);
    glVertex3f(40, 40, 40);
    glVertex3f(40, -40, 40);
    glEnd();
    glPopMatrix();

    //jendela lt 2_2
    glPushMatrix();
    glTranslatef(-170, 466, -53);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-35, -35, 35);
    glVertex3f(-35, 35, 35);
    glVertex3f(35, 35, 35);
    glVertex3f(35, -35, 35);
    glEnd();
    glPopMatrix();


    
    //lantai 3
    glPushMatrix();
    glTranslatef(0, 1000, -270);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidCube(400.0);
    glPopMatrix();

    //atas lantai 3
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-320.0, 825.0, 120);
    glVertex3f(320.0, 825.0, 120);
    glVertex3f(320.0, 825.0, -640);
    glVertex3f(-320.0, 825.0, -640);
    glEnd();

    // pagar lantai_3kanan
    glBegin(GL_POLYGON);
    glColor3f(1.56, 0.50, 0.0);
    glVertex3f(320.0, 825.0, -640);
    glVertex3f(320.0, 880.0, -640);
    glVertex3f(320.0, 880.0, 120);
    glVertex3f(320.0, 825.0, 120);
    glEnd();

    //pagar lantai_3kiri
    glBegin(GL_POLYGON);
    glColor3f(1.56, 0.50, 0.0);
    glVertex3f(-320.0, 825.0, 120);
    glVertex3f(-320.0, 880.0, 120);
    glVertex3f(-320.0, 880.0, -640);
    glVertex3f(-320.0, 825.0, -640);
    glEnd();

    //pagar lantai_3belakang
    glBegin(GL_POLYGON);
    glColor3f(1.56, 0.50, 0.0);
    glVertex3f(-320.0, 825.0, -640);
    glVertex3f(-320.0, 880.0, -640);
    glVertex3f(320.0, 880.0, -640);
    glVertex3f(320.0, 825.0, -640);
    glEnd();

    //pagar lantai_3depan
    glBegin(GL_POLYGON);
    glColor3f(1.56, 0.50, 0.0);
    glVertex3f(-320.0, 825.0, 120);
    glVertex3f(-320.0, 880.0, 120);
    glVertex3f(320.0, 880.0, 120);
    glVertex3f(320.0, 825.0, 120);
    glEnd();

    //jendela lt 3_1
    glPushMatrix();
    glTranslatef(141, 910, -109);
    glBegin(GL_POLYGON);
    glColor3f(0.92, 0.89, 0.06);
    glVertex3f(-40, -40, 40);
    glVertex3f(-40, 40, 40);
    glVertex3f(40, 40, 40);
    glVertex3f(40, -40, 40);
    glEnd();
    glPopMatrix();

    //jendela lt 3_1
    glPushMatrix();
    glTranslatef(141, 910, -102);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-35, -35, 35);
    glVertex3f(-35, 35, 35);
    glVertex3f(35, 35, 35);
    glVertex3f(35, -35, 35);
    glEnd();
    glPopMatrix();

    //jendela lt 3_2
    glPushMatrix();
    glTranslatef(-141, 910, -109);
    glBegin(GL_POLYGON);
    glColor3f(0.92, 0.89, 0.06);
    glVertex3f(-40, -40, 40);
    glVertex3f(-40, 40, 40);
    glVertex3f(40, 40, 40);
    glVertex3f(40, -40, 40);
    glEnd();
    glPopMatrix();

    //jendela lt 3_2
    glPushMatrix();
    glTranslatef(-141, 910, -102);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-35, -35, 35);
    glVertex3f(-35, 35, 35);
    glVertex3f(35, 35, 35);
    glVertex3f(35, -35, 35);
    glEnd();
    glPopMatrix();


    //atas lantai 4
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-320.0, 1210.0, 120);
    glVertex3f(320.0, 1210.0, 120);
    glVertex3f(320.0, 1210.0, -640);
    glVertex3f(-320.0, 1210.0, -640);
    glEnd();

    // pagar lantai_3kanan
    glBegin(GL_POLYGON);
    glColor3f(1.56, 0.50, 0.0);
    glVertex3f(320.0, 1210.0, -640);
    glVertex3f(320.0, 1290.0, -640);
    glVertex3f(320.0, 1290.0, 120);
    glVertex3f(320.0, 1210.0, 120);
    glEnd();

    //pagar lantai_3kiri
    glBegin(GL_POLYGON);
    glColor3f(1.56, 0.50, 0.0);
    glVertex3f(-320.0, 1210.0, 120);
    glVertex3f(-320.0, 1290.0, 120);
    glVertex3f(-320.0, 1290.0, -640);
    glVertex3f(-320.0, 1210.0, -640);
    glEnd();

    //pagar lantai_3belakang
    glBegin(GL_POLYGON);
    glColor3f(1.56, 0.50, 0.0);
    glVertex3f(-320.0, 1210.0, -640);
    glVertex3f(-320.0, 1290.0, -640);
    glVertex3f(320.0, 1290.0, -640);
    glVertex3f(320.0, 1210.0, -640);
    glEnd();

    //pagar lantai_3depan
    glBegin(GL_POLYGON);
    glColor3f(1.56, 0.50, 0.0);
    glVertex3f(-320.0, 1210.0, 120);
    glVertex3f(-320.0, 1290.0, 120);
    glVertex3f(320.0, 1290.0, 120);
    glVertex3f(320.0, 1210.0, 120);
    glEnd();



    // LANTAI 4
    glPushMatrix();
    glTranslatef(0, 1300, -270);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidCube(400.0);
    glPopMatrix();

    //tiang 1 (TITIK)
    glPushMatrix();
    glTranslatef(278, 1459, 69);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 2
    glPushMatrix();
    glTranslatef(145, 1459, 69);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 3 (TITIK)
    glPushMatrix();
    glTranslatef(3, 1459, 69);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 4
    glPushMatrix();
    glTranslatef(-134, 1459, 69);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 5
    glPushMatrix();
    glTranslatef(-275, 1459, 69);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 6
    glPushMatrix();
    glTranslatef(278, 1459, -67);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 7
    glPushMatrix();
    glTranslatef(272, 1459, -212);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 8
    glPushMatrix();
    glTranslatef(253, 1459, -460);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 9
    glPushMatrix();
    glTranslatef(276, 1459, -603);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 10 (ketengah)
    glPushMatrix();
    glTranslatef(253, 1459, -316);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 11
    glPushMatrix();
    glTranslatef(148, 1459, -565);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 12
    glPushMatrix();
    glTranslatef(19, 1459, -599);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 13
    glPushMatrix();
    glTranslatef(-114, 1459, -595);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 14
    glPushMatrix();
    glTranslatef(-295, 1458, -595);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 15
    glPushMatrix();
    glTranslatef(-295, 1459, -456);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 16
    glPushMatrix();
    glTranslatef(-295, 1459, -335);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 17
    glPushMatrix();
    glTranslatef(-295, 1459, -217);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //tiang 18
    glPushMatrix();
    glTranslatef(-291, 1459, -72);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 250.0f, 32, 32);
    glPopMatrix();

    //atap lantai 4_3 (asas)
    glPushMatrix();
    glTranslatef(-39, 1549, -255);
    glRotatef(180.0, 0.0, 1.0, 0.0);
    glColor3f(0.0f, 1.1f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(-370, 0, 370);
    glVertex3f(370, 0, 370);
    glEnd();
    glPopMatrix();

    //atap lantai 4_3
    glPushMatrix();
    glTranslatef(-39, 1549, -251);
    glRotatef(-165, 0.0, 0.0, 60.0);
    glColor3f(0.0f, 1.1f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);

    glVertex3f(370, 0, 370);
    glVertex3f(370, 0, -370);
    glEnd();
    glPopMatrix();

    //atap lantai 4_3 (baru)
    glPushMatrix();
    glTranslatef(-39, 1549, -251);
    glRotatef(15.0, 1.0, 0.0, 0.0);
    glColor3f(0.0f, 1.1f, 0.0f);;
    glBegin(GL_POLYGON);
    glVertex3f(-370, 0, 370);
    glVertex3f(370, 0, 370);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

    //atap lantai 4_4
    glPushMatrix();
    glTranslatef(-40, 1544, -251);
    glRotatef(-350, 0.0, 0.0, -90.0);
    glColor3f(0.0f, 1.1f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);

    glVertex3f(370, 0, 370);
    glVertex3f(370, 0, -370);
    glEnd();
    glPopMatrix();






    fondasi();
    tanggadasar();
    lantai1();
    meja();
    jalan();


    ground();
    cout << "X_GESER = " << x_geser << "    Y_GESER = " << y_geser << "    Z_GESER = " << z_geser << "                                                                               ";
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y) {
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera() {
    if (motion.Forward) {
        camX += cos((yaw + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
    }
    if (motion.Backward) {
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
    }
    if (motion.Left) {
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
    }
    if (motion.Right) {
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
    }
    if (motion.Naik) {
        terbang -= 2.0;
    }
    if (motion.Turun) {
        terbang += 2.0;
    }

    if (pitch >= 70)
        pitch = 70;
    if (pitch <= -90)
        pitch = -90;


    glRotatef(-pitch, 1.0, 0.0, 0.0);
    glRotatef(-yaw, 0.0, 1.0, 0.0);

    glTranslatef(-camX, -terbang, -350 - camZ);
    if (terbang < 25)
        terbang = 24;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'E':
    case 'e':
        motion.Naik = true;
        break;
    case 'Q':
    case 'q':
        motion.Turun = true;
        break;
    case '6':
        x_geser += 0.5;
        break;
    case '4':
        x_geser -= 0.5;
        break;
    case '8':
        y_geser += 0.5;
        break;
    case '2':
        y_geser -= 0.5;
        break;
    case '9':
        z_geser -= 0.5;
        break;
    case '1':
        z_geser += 0.5;
        break;
    case '`': // KELUAR DARI PROGRAM
        exit(1);
    }
}

void keyboard_up(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'E':
    case 'e':
        motion.Naik = false;
        break;
    case 'Q':
    case 'q':
        motion.Turun = false;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM KELOMPOK 8");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glutMainLoop();
    return 0;
}
