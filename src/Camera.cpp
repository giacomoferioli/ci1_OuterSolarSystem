#include "Camera.hpp"

#define SWAP(a,b) {auto __amogus=a;a=b;b=__amogus;}

Camera::Camera(sf::Image& img,const Vec3 direction,double viewPlaneBoundary) : img(img) , direction(direction), viewPlaneBoundary(viewPlaneBoundary) {
    calcCameraToCanonMatrix();
    CanonToCameraMatrix = CameraToCanonMatrix.transpose();
}


void Camera::calcCameraToCanonMatrix(){
    Vec3 vertical(0,0,1);

    vertical = (vertical - direction * vertical.dotprod(direction)).Normalize();

    Vec3 side = vertical.crossprod(direction);

    for(int i = 0; i < 3; i++){
        CameraToCanonMatrix.set(i,0,direction[i]);
        CameraToCanonMatrix.set(i,1,side[i]);
        CameraToCanonMatrix.set(i,2,vertical[i]);
    }
}
//TODO implement rotation about global z
void Camera::rotateX(double angle){
    double c = cos(angle), s = sin(angle);
    
    CanonToCameraMatrix = Matrix(
        { 1 , 0 , 0,
          0 , c , s,
          0 , -s, c})
          * CanonToCameraMatrix;
    CameraToCanonMatrix =CanonToCameraMatrix.transpose();
    direction[0] = CameraToCanonMatrix.get(0,0);
    direction[1] = CameraToCanonMatrix.get(1,0);
    direction[2] = CameraToCanonMatrix.get(2,0);
}
void Camera::rotateY(double angle){
    double c = cos(angle), s = sin(angle);
    
    CanonToCameraMatrix = Matrix(
        { c , 0 , -s,
          0 , 1 , 0,
          s , 0, c})
          * CanonToCameraMatrix;
    CameraToCanonMatrix =CanonToCameraMatrix.transpose();
    direction[0] = CameraToCanonMatrix.get(0,0);
    direction[1] = CameraToCanonMatrix.get(1,0);
    direction[2] = CameraToCanonMatrix.get(2,0);
}
void Camera::rotateZ(double angle){
    double c = cos(angle), s = sin(angle);
    
    CanonToCameraMatrix = Matrix(
        { c , s , 0,
          -s, c , 0,
          0 , 0 , 1})
          * CanonToCameraMatrix;
    CameraToCanonMatrix =CanonToCameraMatrix.transpose();
    direction[0] = CameraToCanonMatrix.get(0,0);
    direction[1] = CameraToCanonMatrix.get(1,0);
    direction[2] = CameraToCanonMatrix.get(2,0);
}

//HAS TO BE IN CAMERA COORDINATES
sf::Vector2f Camera::projectPoint(Vec3 a) const{
    static const sf::Vector2u size = img.getSize();
    //scommentare sta riga per averlo in pospettiva
    //a = a / a.x() * viewPlaneDistance;

    // lo schermo viene mappato ad un quadrato di lato 2 * viewPlaneBoundary centrato in 0
    // non mi ricordo perchè ho fatto sta roba col viewplaneboundary ma trusterò il processo
    return sf::Vector2f( size.x - ipol(-viewPlaneBoundary,viewPlaneBoundary,0,size.x,a.y()) , (double)size.y - ipol(-viewPlaneBoundary,viewPlaneBoundary,0,size.y,a.z()));
}

bool Camera::projectLine(sf::Vector2f* const dst1,sf::Vector2f* const dst2, Vec3 a,Vec3 b) const{
    /*
    proietta una linea sul viewplane
    se la linea interseca il viewplane calcola l'intersezione e ritorna il pt immutato in dst1 e il pt di intersezione in dst2
    se la linea giace dietro il viewplane ritorna false e non tocca dst1 e dst2
    */
   /*
    if(mode == SR::Global){
        //x // camera dir
        a = CanonToCameraMatrix * a;
        b = CanonToCameraMatrix * b;
    }
    */

    *dst1 = projectPoint(a);
    *dst2 = projectPoint(b);

    return true;
}

void Camera::drawPoint(const Vec3& point,int color){
    sf::Vector2f pt = projectPoint(CanonToCameraMatrix * point);

    int ix = round(pt.x), iy = round(pt.y);
    for(uint i = ix-1; i < ix+2; i++)
        for(uint j = iy-1; j < iy+2; j++)
            if(ix > 0 && ix < SIZE - 1 && iy > 0 && iy < SIZE - 1)
                img.setPixel(ix,iy,sf::Color(color));
}