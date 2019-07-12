#ifndef VECTOR_2D
#define VECTOR_2D

#include <math.h>

class Vector2D {
    public:
        Vector2D(float x, float y) : _x(x), _y(y) { }
        Vector2D() : _x(0), _y(0) { }

        float getX() { return _x; }
        float getY() { return _y; }
        
        void setX(float x) { _x = x; }
        void setY(float y) { _y = y; }

        float length() {
            return sqrt(pow(_x, 2) + pow(_y, 2));
        }

        void normalize() {
            float l = length();
            if (l != 0)
                (*this) *= 1/l;
        }

        //Multiplication
        Vector2D operator*(float scalar) {
            return Vector2D(_x * scalar, _y * scalar);
        }
        Vector2D& operator*=(float scalar) {
            _x *= scalar;
            _y *= scalar;
            return *this;
        }
        //Div
        Vector2D operator/(float scalar) {
            return Vector2D(_x / scalar, _y / scalar);
        }
        Vector2D& operator/=(float scalar) {
            _x /= scalar;
            _y /= scalar;
            return *this;
        }
        //Add
        Vector2D operator+(const Vector2D& other) {
            return Vector2D(_x + other._x, _y + other._y);
        }
        friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2) {
            v1._x += v2._x;
            v1._y += v2._y;
            return v1;
        }
        //Sub
        Vector2D operator-(const Vector2D& other) {
            return Vector2D(_x - other._x, _y - other._y);
        }
        friend Vector2D& operator-=(Vector2D& v1, Vector2D& v2) {
            v1._x -= v2._x;
            v1._y -= v2._y;
            return v1;
        }

        bool operator==(const Vector2D& other) {
            return (_x == other._x && _y == other._y);
        }
        bool operator!=(const Vector2D& other) {
            return !(_x == other._x && _y == other._y);
        }
        
    private:
        float _x, _y;
};

#endif