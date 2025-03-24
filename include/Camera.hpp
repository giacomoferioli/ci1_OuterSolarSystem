#include <Common.hpp>
#include "Matrix.hpp"
#include <util.hpp>
#include <vector>

#ifndef CAMERA
#define CAMERA

#define VIEWPLANEBOUNDARY 40

class Camera{
    private:
        sf::Image& img;

        Vec3 direction;         //where the camera is facing

        Matrix CameraToCanonMatrix;
        Matrix CanonToCameraMatrix;

        sf::Vector2f projectPoint(Vec3 a) const;
        bool projectLine(sf::Vector2f* dst1, sf::Vector2f* dst2, Vec3 a, Vec3 b) const;
        void calcCameraToCanonMatrix();

    public:
        Camera(sf::Image& img,const Vec3 direction = Vec3(1,0,0),double fov = M_PI/2,double viewPlaneDistance = .1);

        Vec3 getDirection() const {return direction;}
        
        const Matrix& getCanonToCameraMatrix() {return CanonToCameraMatrix;}
        const Matrix& getCameraTocanonMatrix() {return CameraToCanonMatrix;}

        void setHeading(const Vec3& hdg) { direction = hdg; calcCameraToCanonMatrix(); CanonToCameraMatrix = CameraToCanonMatrix.transpose();};

        void drawVector(Vec3 v,sf::Color color,int l = 15);
        void rotateX(double angle);
        void rotateY(double angle);
        void rotateZ(double angle);

        void drawPoint(const Vec3& point,int color=0x00FF00FF);        
};

#endif
