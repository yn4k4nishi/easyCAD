#include "camera.hpp"

camera::camera(){
    // カメラのグローバル座標
    x = 1.0;
    y = 0.0;
    z = 0.0;

    // 焦点
    focus_x = 0.0;
    focus_y = 0.0;
    focus_z = 0.0;
    
    // カメラの頭上方向のベクトル
    up_x = 0.0;
    up_y = 0.0;
    up_z = 1.0;
}

camera::~camera(){}

camera::update(){
    gluLookAt(
        x, y, z,
        focus_x, focus_y, focus_z,
        up_x, up_y, up_z
    )
}

camera::move(float vx, float vy){
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

camera::rotate(float rx, float ry){
    // 画面右方向の単位ベクトルの計算
    float scr_x = (y - focus_y) * up_z - (z - focus_z) * up_y;
    float scr_y = (z - focus_z) * up_x - (x - focus_x) * up_z;
    float scr_z = (x - focus_x) * up_y - (y - focus_y) * up_x;

    float l = sqrt(scr_x*scr_x + scr_y*scr_y + scr_z*scr_z);
    scr_x /= l;
    scr_y /= l;
    scr_z /= l;

    // 焦点 -> カメラ のベクトル
    float tx = x - focus_x; 
    float ty = y - focus_y; 
    float tz = z - focus_z; 

    // 焦点距離 == 回転半径
    // float r = sqrt( tx*tx + ty*ty + tz*tz );

    // 回転角の計算
    float ax = scr_x * rx + up_x * (-ry);
    float ay = scr_y * rx + up_y * (-ry);
    float az = scr_z * rx + up_z * (-ry);

    // 回転
    x = focus_x 
        + ( cos(ax)*sin(ay)*cos(az) - sin(ax)*sin(az)) * tx
        + (-cos(ax)*cos(ay)*sin(az) - sin(ax)*cos(az)) * ty
        + ( cos(ax)*sin(ay)) * tz; 
    y = focus_y
        + ( sin(ax)*sin(ay)*cos(az) + cos(ax)*sin(az)) * tx
        + (-sin(ax)*cos(ay)*sin(az) + cos(ax)*cos(az)) * ty
        + ( sin(ax)*sin(ay)) * tz;
    z = focus_z
        + (-sin(ay)*cos(az)) * tx
        + ( sin(ay)*sin(az)) * ty
        + ( cos(ay)) * tz;
}

camera::zoom(float scroll){
    l = (focus_x - x)*(focus_x - x)
       +(focus_y - y)*(focus_y - y)
       +(focus_z - z)*(focus_z - z);
    
    focus_x += scroll * (focus_x - x) / sqrt(l);
    focus_y += scroll * (focus_y - y) / sqrt(l);
    focus_z += scroll * (focus_z - z) / sqrt(l);

    update();
}

/* gluLookAt
 *  eye_?    : カメラの位置
 *  center_? : 見ている場所
 *  up?      : カメラ上方向のベクトル
 */
