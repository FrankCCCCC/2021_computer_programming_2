#ifndef VECTOR2_H_INCLUDED
#define VECTOR2_H_INCLUDED

class Vector2
{
    public:
        //////Constructor//////
        Vector2();
        Vector2(float, float);
        //////functions//////
        void sets(float, float);
        float get_x();
        float get_y();
        Vector2 operator +(const Vector2&);

    protected:
        float x;
        float y;
};


#endif // VECTOR2_H_INCLUDED
