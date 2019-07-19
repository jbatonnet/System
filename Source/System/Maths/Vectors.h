#ifndef _SYSTEM_VECTORS_H_
#define _SYSTEM_VECTORS_H_

#include <System/Common.h>
#include <System/Maths/Maths.h>

/*namespace System
{
    //namespace Maths
    {*/
        struct Matrix3; // TODO: Remove

        struct Point2
        {
            s32 X;
            s32 Y;

            Point2() : X(0), Y(0) { }
            Point2(s32 n) : X(n), Y(n) { }
            Point2(s32 x, s32 y) : X(x), Y(y) { }

            // Operators
            bool operator==(const Point2& point)
            {
                return X == point.X && Y == point.Y;
            }
            bool operator!=(const Point2& point)
            {
                return X != point.X || Y != point.Y;
            }
            Point2& operator+=(const Point2& point)
            {
                X += point.X;
                Y += point.Y;
                return *this;
            }
            Point2& operator-=(const Point2& point)
            {
                X -= point.X;
                Y -= point.Y;
                return *this;
            }
            Point2 operator+(const Point2& point) const
            {
                Point2 result(*this);
                result += point;
                return result;
            }
            Point2 operator-(const Point2& point) const
            {
                Point2 result(*this);
                result -= point;
                return result;
            }

            static const Point2 Zero, One;
        };

        struct Point3
        {
            s32 X;
            s32 Y;
            s32 Z;

            Point3() : X(0), Y(0), Z(0) { }
            Point3(s32 n) : X(n), Y(n), Z(n) { }
            Point3(s32 x, s32 y, s32 z) : X(x), Y(y), Z(z) { }

            // Operators
            bool operator==(const Point3& point)
            {
                return X == point.X && Y == point.Y && Z == point.Z;
            }
            bool operator!=(const Point3& point)
            {
                return X != point.X || Y != point.Y || Z != point.Z;
            }

            static const Point3 Zero, One;
        };

        struct Vector2
        {
            float X;
            float Y;

            Vector2() : X(0), Y(0) { }
            Vector2(const Vector2& vector) : X(vector.X), Y(vector.Y) { }
            Vector2(float n) : X(n), Y(n) { }
            Vector2(float x, float y) : X(x), Y(y) { }
            Vector2(const Point2& point) : X(point.X), Y(point.Y) { }

            // Functions
            float Length() const
            {
                return Maths::Sqrt(X * X + Y * Y);
            }

            // Manipulation
            static Vector2 Lerp(const Vector2& v1, const Vector2& v2, float c)
            {
                return Vector2
                (
                    v1.X + (v2.X - v1.X) * c,
                    v1.Y + (v2.Y - v1.Y) * c
                );
            }
            static float Dot(const Vector2& v1, const Vector2& v2)
            {
                return v1.X * v2.X + v1.Y * v2.Y;
            }
            static Vector2 Normalize(const Vector2& vector)
            {
                Vector2 result(vector);
                result /= result.Length();
                return result;
            }
            static float Angle(const Vector2& v1, const Vector2& v2)
            {
                return Maths::Atan2(v2.Y - v1.Y, v2.X - v1.X);
            }
            static float Distance(const Vector2& v1, const Vector2& v2)
            {
                return Maths::Sqrt((v2.X - v1.X) * (v2.X - v1.X) + (v2.Y - v1.Y) * (v2.Y - v1.Y));
            }

            // Operators
            bool operator==(const Vector2& vector)
            {
                return X == vector.X && Y == vector.Y;
            }
            bool operator!=(const Vector2& vector)
            {
                return X != vector.X || Y != vector.Y;
            }
            Vector2& operator+=(const Vector2& vector)
            {
                X += vector.X;
                Y += vector.Y;
                return *this;
            }
            Vector2& operator-=(const Vector2& vector)
            {
                X -= vector.X;
                Y -= vector.Y;
                return *this;
            }
            Vector2& operator*=(float factor)
            {
                X *= factor;
                Y *= factor;
                return *this;
            }
            Vector2& operator*=(const Vector2& vector)
            {
                X *= vector.X;
                Y *= vector.Y;
                return *this;
            }
            Vector2& operator/=(float factor)
            {
                X /= factor;
                Y /= factor;
                return *this;
            }
            Vector2& operator/=(const Vector2& vector)
            {
                X /= vector.X;
                Y /= vector.Y;
                return *this;
            }
            Vector2 operator+(const Vector2& vector) const
            {
                Vector2 result(*this);
                result += vector;
                return result;
            }
            Vector2 operator-(const Vector2& vector) const
            {
                Vector2 result(*this);
                result -= vector;
                return result;
            }
            Vector2 operator*(float factor) const
            {
                Vector2 result(*this);
                result *= factor;
                return result;
            }
            Vector2 operator*(const Vector2& vector) const
            {
                Vector2 result(*this);
                result *= vector;
                return result;
            }
            Vector2 operator/(float factor) const
            {
                Vector2 result(*this);
                result /= factor;
                return result;
            }
            Vector2 operator/(const Vector2& vector) const
            {
                Vector2 result(*this);
                result /= vector;
                return result;
            }

            static const Vector2 Zero, One, Left, Up, Right, Down;
        };

        struct Vector3
        {
            float X;
            float Y;
            float Z;

            Vector3() : X(0), Y(0), Z(0) { }
            Vector3(const Vector3& vector) : X(vector.X), Y(vector.Y), Z(vector.Z) { }
            Vector3(float n) : X(n), Y(n), Z(n) { }
            Vector3(float x, float y, float z) : X(x), Y(y), Z(z) { }
            Vector3(const Vector2& vector, float z = 0) : X(vector.X), Y(vector.Y), Z(z) { }

            // Functions
            float Length() const
            {
                return Maths::Sqrt(X * X + Y * Y + Z * Z);
            }

            // Manipulation
            static Vector3 Lerp(const Vector3& v1, const Vector3& v2, float c)
            {
                return Vector3
                (
                    v1.X + (v2.X - v1.X) * c,
                    v1.Y + (v2.Y - v1.Y) * c,
                    v1.Z + (v2.Z - v1.Z) * c
                );
            }
            static Vector3 Cross(const Vector3& v1, const Vector3& v2)
            {
                return Vector3
                (
                    v1.Y * v2.Z - v1.Z * v2.Y,
                    v1.Z * v2.X - v1.X * v2.Z,
                    v1.X * v2.Y - v1.Y * v2.X
                );
            }
            static float Dot(const Vector3& v1, const Vector3& v2)
            {
                return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
            }
            static Vector3 Normalize(const Vector3& vector)
            {
                Vector3 result(vector);
                result /= result.Length();
                return result;
            }
            static float Distance(const Vector3& v1, const Vector3& v2)
            {
                return Maths::Sqrt((v2.X - v1.X) * (v2.X - v1.X) + (v2.Y - v1.Y) * (v2.Y - v1.Y) + (v2.Z - v1.Z) * (v2.Z - v1.Z));
            }

            // Operators
            bool operator==(const Vector3& vector)
            {
                return X == vector.X && Y == vector.Y && Z == vector.Z;
            }
            bool operator!=(const Vector3& vector)
            {
                return X != vector.X || Y != vector.Y || Z != vector.Z;
            }
            Vector3& operator+=(const Vector3& vector)
            {
                X += vector.X;
                Y += vector.Y;
                Z += vector.Z;
                return *this;
            }
            Vector3& operator-=(const Vector3& vector)
            {
                X -= vector.X;
                Y -= vector.Y;
                Z -= vector.Z;
                return *this;
            }
            Vector3& operator*=(float factor)
            {
                X *= factor;
                Y *= factor;
                Z *= factor;
                return *this;
            }
            Vector3& operator*=(const Vector3& vector)
            {
                X *= vector.X;
                Y *= vector.Y;
                Z *= vector.Z;
                return *this;
            }
            /*Vector3& operator*=(const Matrix3& matrix)
            {
                X = X * matrix.c11 + Y * matrix.c12 + Z * matrix.c13;
                Y = X * matrix.c21 + Y * matrix.c22 + Z * matrix.c23;
                Z = X * matrix.c31 + Y * matrix.c32 + Z * matrix.c33;
                return *this;
            }*/
            Vector3& operator/=(float factor)
            {
                X /= factor;
                Y /= factor;
                Z /= factor;
                return *this;
            }
            Vector3 operator+(const Vector3& vector) const
            {
                Vector3 result(*this);
                result += vector;
                return result;
            }
            Vector3 operator-(const Vector3& vector) const
            {
                Vector3 result(*this);
                result -= vector;
                return result;
            }
            Vector3 operator*(float factor) const
            {
                Vector3 result(*this);
                result *= factor;
                return result;
            }
            Vector3 operator*(const Vector3& vector) const
            {
                Vector3 result(*this);
                result *= vector;
                return result;
            }
            Vector3 operator/(float factor) const
            {
                Vector3 result(*this);
                result /= factor;
                return result;
            }
            Vector3 operator^(const Vector3& vector) const
            {
                return Vector3(Y * vector.Z - Z * vector.Y, Z * vector.X - X * vector.Z, X * vector.Y - Y * vector.X);
            }

            static const Vector3 Zero, One, Backward, Forward, Left, Right, Down, Up;
        };

        struct Quaternion
        {
            float X;
            float Y;
            float Z;
            union
            {
                float W;
                float Angle;
            };

            Quaternion();
            Quaternion(float x, float y, float z, float angle);
            Quaternion(const Vector3 vector, float angle);

            // Manipulation
            static Quaternion& Lerp(const Quaternion& q1, const Quaternion& q2, float c);

            static const Quaternion Identity;
        };
/*    }
}*/

#endif