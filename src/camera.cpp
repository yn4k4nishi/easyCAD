#include "camera.hpp"

Camera::Camera(){
    back2home();
}

Camera::~Camera(){}

void Camera::update(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        x, y, z,
        focus_x, focus_y, focus_z,
        up_x, up_y, up_z
    );

    // std::cout << "=====================" << std::endl;
    // std::cout << "x = "       << x       << std::endl;
    // std::cout << "y = "       << y       << std::endl;
    // std::cout << "z = "       << z       << std::endl;

    // std::cout << "focus_x = " << focus_x << std::endl;
    // std::cout << "focus_y = " << focus_y << std::endl;
    // std::cout << "focus_z = " << focus_z << std::endl;

    // std::cout << "up_x = "    << up_x    << std::endl;
    // std::cout << "up_y = "    << up_y    << std::endl;
    // std::cout << "up_z = "    << up_z    << std::endl;
}

void Camera::move(float vx, float vy){
    // 画面右方向の単位ベクトルの計算
    float scr_x = (y - focus_y) * up_z - (z - focus_z) * up_y;
    float scr_y = (z - focus_z) * up_x - (x - focus_x) * up_z;
    float scr_z = (x - focus_x) * up_y - (y - focus_y) * up_x;

    float l = sqrt(scr_x*scr_x + scr_y*scr_y + scr_z*scr_z);
    scr_x /= l;
    scr_y /= l;
    scr_z /= l;

    // 画面x成分の平行移動
    x += vx * scr_x;
    y += vx * scr_y;
    z += vx * scr_z;

    focus_x += vx * scr_x;
    focus_y += vx * scr_y;
    focus_z += vx * scr_z;

    // 画面y成分の平行移動
    x += -vy * up_x;
    y += -vy * up_y;
    z += -vy * up_z;

    focus_x += -vy * up_x;
    focus_y += -vy * up_y;
    focus_z += -vy * up_z;

    update();
}

// カメラ中心で焦点を回す．
void Camera::rotate(float rx, float ry){
    // 焦点距離
    float r = sqrt((focus_x - x)*(focus_x - x) + (focus_y - y)*(focus_y - y) + (focus_z - z)*(focus_z - z));

    // カメラ座標での焦点の回転
    float cx = r * sin(rx);
    float cy = r * cos(rx);
    float cz = 0.0;

    // 画面右方向の単位ベクトルの計算
    float scr_x = (y - focus_y) * up_z - (z - focus_z) * up_y;
    float scr_y = (z - focus_z) * up_x - (x - focus_x) * up_z;
    float scr_z = (x - focus_x) * up_y - (y - focus_y) * up_x;

    float l = sqrt(scr_x*scr_x + scr_y*scr_y + scr_z*scr_z);
    scr_x /= l;
    scr_y /= l;
    scr_z /= l;

    // カメラ -> 焦点の単位ベクトル
    float c2f_x = focus_x - x;
    float c2f_y = focus_y - y;
    float c2f_z = focus_z - z;
    
    l = sqrt(c2f_x*c2f_x + c2f_y*c2f_y + c2f_z*c2f_z);
    c2f_x /= l;
    c2f_y /= l;
    c2f_z /= l;

    // カメラ座標への変換行列の逆行列化
    float a[3][3] = {
        {scr_x, scr_y, scr_z},
        {c2f_x, c2f_y, c2f_z},
        { up_x,  up_y,  up_z}
    };

    float det = a[0][0]*a[1][1]*a[2][2] + a[0][1]*a[1][2]*a[2][0] + a[0][2]*a[1][0]*a[2][1]
              - a[0][2]*a[1][1]*a[2][0] - a[0][1]*a[1][0]*a[2][2] - a[0][0]*a[1][2]*a[2][1];
    
    float inv[3][3]={
        { a[1][1]*a[2][2]-a[1][2]*a[2][1], -a[0][1]*a[2][2]+a[0][2]*a[2][1],  a[0][1]*a[1][2]-a[0][2]*a[1][1]},
        {-a[2][0]*a[2][2]+a[1][2]*a[2][0],  a[0][0]*a[2][2]-a[0][2]*a[2][0], -a[0][0]*a[1][2]+a[0][2]*a[1][0]},
        { a[1][0]*a[2][1]-a[1][1]*a[2][0], -a[0][0]*a[2][1]+a[0][1]*a[2][0],  a[0][0]*a[1][1]-a[0][1]*a[1][0]}
    };

    for(int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            inv[i][j] /= det;
        }
    }

    // グローバル座標への変換
    float gx = inv[0][0]*cx + inv[0][1]*cy + inv[0][2]*cz;
    float gy = inv[1][0]*cx + inv[1][1]*cy + inv[1][2]*cz;
    float gz = inv[2][0]*cx + inv[2][1]*cy + inv[2][2]*cz;

    

    focus_x = x + gx;
    focus_y = y + gy;
    focus_z = z + gz;

    update();
}

void Camera::zoom(float scroll){
    float l = (focus_x - x)*(focus_x - x)
             +(focus_y - y)*(focus_y - y)
             +(focus_z - z)*(focus_z - z);
    
    focus_x += scroll * (focus_x - x) / sqrt(l);
    focus_y += scroll * (focus_y - y) / sqrt(l);
    focus_z += scroll * (focus_z - z) / sqrt(l);

    x += scroll * (focus_x - x) / sqrt(l);
    y += scroll * (focus_y - y) / sqrt(l);
    z += scroll * (focus_z - z) / sqrt(l);

    update();
}

void Camera::back2home(){
    // カメラのグローバル座標
    x = -5.0;
    y = 0.0;
    z = 0.0;

    // 焦点
    focus_x = -1.0;
    focus_y = 0.0;
    focus_z = 0.0;
    
    up_x = 0.0;
    up_y = 0.0;
    up_z = 1.0;

    update();
}

void Camera::plotFocusPoint(){
    glColor4f(0, 1, 0, 1);

    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex3f( focus_x, focus_y, focus_z );
    glEnd();
}
