//
// Created by xiaoc on 2018/9/18.
//

#ifndef DANMAKU_PARTICLE_H
#define DANMAKU_PARTICLE_H
#include <GLFW/glfw3.h>
#include <windows.h>
#include <GL/gl.h>
#include <cmath>
struct Vector3 {
    double x, y, z;

    Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    Vector3() : x(0), y(0), z(0) {}

    double lengthSquared() const { return x * x + y * y + z * z; }

    double length() const { return sqrt(lengthSquared()); }

    double dot(const Vector3 &v)const {
        return x * v.x + y * v.y + z * v.z;
    }
    Vector3 cross(const Vector3 &v)const{
        return Vector3();
    }
    Vector3& operator += (const Vector3 &v){
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    Vector3& operator -= (const Vector3 &v){
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    Vector3& operator *= (const Vector3 &v){
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    Vector3 operator + (const Vector3 &v){
        auto v2 = *this;
        v2 += v;
        return v2;
    }
    Vector3 operator - (const Vector3 &v){
        auto v2 = *this;
        v2 -= v;
        return v2;
    }
    Vector3 operator * (const Vector3 &v){
        auto v2 = *this;
        v2 *= v;
        return v2;
    }

};

Vector3 operator*(double k, const Vector3 &v) {
    return Vector3(k * v.x, k * v.y, k * v.z);
}

class Particle {
    Vector3 color;
    Vector3 pos, vel;
    bool dead;
public:
    Particle(const Vector3& c, const Vector3& p, const Vector3&v):color(c),pos(p),vel(v){dead =false;}
    void paint()const{
        glPointSize(2);
        glBegin(GL_POINTS);
        glColor3d(color.x,color.y,color.z);
        glVertex3d(pos.x,pos.y,pos.z);
        glEnd();
    }
    Vector3& getVel(){return vel;}
    inline void update(double dt = 0.01){
        pos += dt * vel;
        if(abs(pos.x)> 1 || abs(pos.y) >1)
            dead = true;
    }
    bool alive()const{return!dead;}
};


#endif //DANMAKU_PARTICLE_H
