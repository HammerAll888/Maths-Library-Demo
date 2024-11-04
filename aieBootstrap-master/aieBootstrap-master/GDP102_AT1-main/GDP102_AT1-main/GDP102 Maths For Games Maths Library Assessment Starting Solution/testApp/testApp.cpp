// This was used for testing functionality and debugging. This file is not connected to the library
//

#include <iostream>
#include "vector.h"
#include "matrix.h"

int main()
{
    const float PI = 3.14159265358979323846f;
    Vector3 point(1, 0, 1);
    Matrix3 rotMat;
    rotMat.setIdentity();

    rotMat.setRotateZ(4*PI/3);
    
    Vector3 result;
    result = rotMat * point;

    std::cout << result;

    
}
