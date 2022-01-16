#include <iostream>
#include <string>
#include "11443.h"

namespace oj
{
    Sphere::Sphere(double R, double P)
    {
        double V;
        radius = R;
        pi = P;
        if(R*P<=0) setVolume(0.0);
        else
        {
            V = (4.0/3.0)*pi*radius*radius*radius;
            setVolume(V);
        }
    }

    Cone::Cone(double R, double H, double P)
    {
        double V;
        radius = R;
        height = H;
        pi = P;
        if(R*H*P <= 0) setVolume(0.0);
        else
        {
            V = (1.0/3.0)*pi*radius*radius*height;
            setVolume(V);
        }
    }

    Cuboid::Cuboid(double L, double W, double H)
    {
        double V;
        length = L;
        width = W;
        height = H;
        if(L*W*H <= 0) setVolume(0);
        else
        {
            V = length*width*height;
            setVolume(V);
        }
    }

    Cube::Cube(double S)
    :Cuboid(S,S,S)
    {
        if(S<=0) setVolume(0);
        else
        {
            double V = S*S*S;
            setVolume(V);
        }
    }
}
