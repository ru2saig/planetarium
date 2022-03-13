#ifndef __VECTOR3_H__
#define __VECTOR3_H__

struct Vector3
{
    double x;
    double y;
    double z;
    
    Vector3(); // default, null/zero vector
    Vector3(double a);
    Vector3(double x, double y, double z);
    Vector3(Vector3&); // copy constructor
    //Vector3& operator=(Vector3&); // copy assignment
    Vector3 operator+(Vector3&);
    Vector3 operator-(Vector3&);
    Vector3 operator*(Vector3&);
    Vector3 cross(Vector3&, Vector3&);
    Vector3 normalize();
    Vector3 mag();


    

};


#endif