#include <System/Maths/Matrixes.h>
#include <System/Maths/Vectors.h>
#include <System/Maths/Maths.h>

// Matrix3

Matrix3::Matrix3() { }
Matrix3::Matrix3(const Matrix3 &matrix) : c11(matrix.c11), c12(matrix.c12), c13(matrix.c13), c21(matrix.c21), c22(matrix.c22), c23(matrix.c23), c31(matrix.c31), c32(matrix.c32), c33(matrix.c33) { }
Matrix3::Matrix3(float c11, float c12, float c13, float c21, float c22, float c23, float c31, float c32, float c33) : c11(c11), c12(c12), c13(c13), c21(c21), c22(c22), c23(c23), c31(c31), c32(c32), c33(c33) { }

float Matrix3::Determinant()
{
    return c11 * (c22 * c33 - c32 * c23)
         - c12 * (c21 * c33 - c31 * c23)
         + c13 * (c21 * c32 - c31 * c22);
}
void Matrix3::Normalize()
{
    float x = Maths::Sqrt(c11 * c11 + c12 * c12 + c13 * c13),
          y = Maths::Sqrt(c21 * c21 + c22 * c22 + c23 * c23),
          z = Maths::Sqrt(c31 * c31 + c32 * c32 + c33 * c33);

    c11 /= x; c12 /= x; c13 /= x;
    c21 /= y; c22 /= y; c23 /= y;
    c31 /= z; c32 /= z; c33 /= z;
}

Matrix3& Matrix3::Normalize(const Matrix3 &matrix)
{
    Matrix3* result = new Matrix3(matrix);
    result->Normalize();
    return *result;
}

Matrix3& Matrix3::CreateRotation(float pitch, float yaw, float roll)
{
    Matrix3* matrix = new Matrix3
    (
        Maths::Cos(pitch) * Maths::Cos(yaw),
        Maths::Cos(pitch) * Maths::Sin(yaw) * Maths::Sin(roll) - Maths::Sin(pitch) * Maths::Cos(roll),
        Maths::Cos(pitch) * Maths::Sin(yaw) * Maths::Cos(roll) + Maths::Sin(pitch) * Maths::Sin(roll),
        Maths::Sin(pitch) * Maths::Cos(yaw),
        Maths::Sin(pitch) * Maths::Sin(yaw) * Maths::Sin(roll) + Maths::Cos(pitch) * Maths::Cos(roll),
        Maths::Sin(pitch) * Maths::Sin(yaw) * Maths::Cos(roll) - Maths::Cos(pitch) * Maths::Sin(roll),
        -Maths::Sin(yaw),
        Maths::Cos(yaw) * Maths::Sin(roll),
        Maths::Cos(yaw) * Maths::Cos(roll)
    );
    return *matrix;
}
Matrix3& Matrix3::CreateRotation(const Vector3& vector, float angle)
{
    float c = Maths::Cos(angle), s = Maths::Sin(angle), C = 1 - c;
    float x = vector.X, y = vector.Y, z = vector.Z,
          xs = x * s, ys = y * s, zs = z * s,
          xC = x * C, yC = y * C, zC = z * C,
          xyC = x * yC, yzC = y * zC, zxC = z * xC;
    
    Matrix3* matrix = new Matrix3(
        x * xC + c, xyC - zs, zxC + ys,
        xyC + zs, y * yC + c, yzC - xs,
        zxC - ys, yzC + xs, z * zC + c
    );
    return *matrix;
}

Matrix3& Matrix3::operator*=(const Matrix3 &matrix)
{
    c11 = matrix.c11 * c11 + matrix.c12 * c21 + matrix.c13 * c31;
    c12 = matrix.c11 * c12 + matrix.c12 * c22 + matrix.c13 * c32;
    c13 = matrix.c11 * c13 + matrix.c12 * c23 + matrix.c13 * c33;
    c21 = matrix.c21 * c11 + matrix.c22 * c21 + matrix.c23 * c31;
    c22 = matrix.c21 * c12 + matrix.c22 * c22 + matrix.c23 * c32;
    c23 = matrix.c21 * c13 + matrix.c22 * c23 + matrix.c23 * c33;
    c31 = matrix.c31 * c11 + matrix.c32 * c21 + matrix.c33 * c31;
    c32 = matrix.c31 * c12 + matrix.c32 * c22 + matrix.c33 * c32;
    c33 = matrix.c31 * c13 + matrix.c32 * c23 + matrix.c33 * c33;
    return *this;
}
Matrix3& Matrix3::operator*(const Matrix3 &matrix) const
{
    Matrix3* result = new Matrix3(
        c11 * matrix.c11 + c12 * matrix.c21 + c13 * matrix.c31,
        c11 * matrix.c12 + c12 * matrix.c22 + c13 * matrix.c32,
        c11 * matrix.c13 + c12 * matrix.c23 + c13 * matrix.c33,
        c21 * matrix.c11 + c22 * matrix.c21 + c23 * matrix.c31,
        c21 * matrix.c12 + c22 * matrix.c22 + c23 * matrix.c32,
        c21 * matrix.c13 + c22 * matrix.c23 + c23 * matrix.c33,
        c31 * matrix.c11 + c32 * matrix.c21 + c33 * matrix.c31,
        c31 * matrix.c12 + c32 * matrix.c22 + c33 * matrix.c32,
        c31 * matrix.c13 + c32 * matrix.c23 + c33 * matrix.c33
    );
    return *result;
}
Vector3& Matrix3::operator*(const Vector3 &vector) const
{
    Vector3* result = new Vector3(vector);
    //*result *= *this;
    return *result;
}

const Matrix3 Matrix3::Identity = Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);



// Matrix4

Matrix4::Matrix4() { }
Matrix4::Matrix4(float c11, float c12, float c13, float c14, float c21, float c22, float c23, float c24, float c31, float c32, float c33, float c34, float c41, float c42, float c43, float c44) : c11(c11), c12(c12), c13(c13), c14(c14), c21(c21), c22(c22), c23(c23), c24(c24), c31(c31), c32(c32), c33(c33), c34(c34), c41(c41), c42(c42), c43(c43), c44(c44) { }

float Matrix4::Determinant()
{
    return c11 * (c22 * (c33 * c44 - c43 * c34)
                - c23 * (c32 * c44 - c42 * c34)
                + c24 * (c32 * c43 - c42 * c33))
         - c12 * (c21 * (c33 * c44 - c43 * c34)
                - c23 * (c31 * c44 - c41 * c34)
                + c24 * (c31 * c43 - c41 * c33))
         + c13 * (c21 * (c32 * c44 - c42 * c34)
                - c22 * (c31 * c44 - c41 * c34)
                + c24 * (c31 * c42 - c41 * c32))
         - c14 * (c21 * (c32 * c43 - c42 * c33)
                - c22 * (c31 * c43 - c41 * c33)
                + c23 * (c31 * c42 - c41 * c32));
}

Matrix4& Matrix4::CreateTransformation(const Vector3 &translation, const Matrix3 &rotation, const Vector3 &scale)
{
    Matrix4* result = new Matrix4(
        rotation.c11 * scale.X, rotation.c12 * scale.Y, rotation.c13 * scale.Z, translation.X,
        rotation.c21 * scale.X, rotation.c22 * scale.Y, rotation.c23 * scale.Z, translation.Y,
        rotation.c31 * scale.X, rotation.c32 * scale.Y, rotation.c33 * scale.Z, translation.Z,
        0, 0, 0, 1
    );
    return *result;
}
Matrix4& Matrix4::CreateView(const Vector3 &position, const Vector3 &target, const Vector3 &up)
{
    Vector3 z = Vector3::Normalize(position - target);
    Vector3 x = Vector3::Normalize(up ^ z);
    Vector3 y = z ^ x;

    Matrix4* result = new Matrix4(
        x.X, x.Y, x.Z, -Vector3::Dot(x, position),
        y.X, y.Y, y.Z, -Vector3::Dot(y, position),
        z.X, z.Y, z.Z, -Vector3::Dot(z, position),
        0, 0, 0, 1
    );
    return *result;
}
Matrix4& Matrix4::CreateProjection(float fov, float aspect, float near, float far)
{
    float y = 1.0 / Maths::Tan(fov / 2);
    float x = y / aspect;
    float size = near - far;

    Matrix4* result = new Matrix4(
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, (far + near) / size, 2 * far * near / size,
        0, 0, -1, 0 
    );
    return *result;
}

Matrix4& Matrix4::operator*(const Matrix4 &matrix) const
{
    Matrix4* result = new Matrix4(
        c11 * matrix.c11 + c12 * matrix.c21 + c13 * matrix.c31 + c14 * matrix.c41,
        c11 * matrix.c12 + c12 * matrix.c22 + c13 * matrix.c32 + c14 * matrix.c42,
        c11 * matrix.c13 + c12 * matrix.c23 + c13 * matrix.c33 + c14 * matrix.c43,
        c11 * matrix.c14 + c12 * matrix.c24 + c13 * matrix.c34 + c14 * matrix.c44,
        c21 * matrix.c11 + c22 * matrix.c21 + c23 * matrix.c31 + c24 * matrix.c41,
        c21 * matrix.c12 + c22 * matrix.c22 + c23 * matrix.c32 + c24 * matrix.c42,
        c21 * matrix.c13 + c22 * matrix.c23 + c23 * matrix.c33 + c24 * matrix.c43,
        c21 * matrix.c14 + c22 * matrix.c24 + c23 * matrix.c34 + c24 * matrix.c44,
        c31 * matrix.c11 + c32 * matrix.c21 + c33 * matrix.c31 + c34 * matrix.c41,
        c31 * matrix.c12 + c32 * matrix.c22 + c33 * matrix.c32 + c34 * matrix.c42,
        c31 * matrix.c13 + c32 * matrix.c23 + c33 * matrix.c33 + c34 * matrix.c43,
        c31 * matrix.c14 + c32 * matrix.c24 + c33 * matrix.c34 + c34 * matrix.c44,
        c41 * matrix.c11 + c42 * matrix.c21 + c43 * matrix.c31 + c44 * matrix.c41,
        c41 * matrix.c12 + c42 * matrix.c22 + c43 * matrix.c32 + c44 * matrix.c42,
        c41 * matrix.c13 + c42 * matrix.c23 + c43 * matrix.c33 + c44 * matrix.c43,
        c41 * matrix.c14 + c42 * matrix.c24 + c43 * matrix.c34 + c44 * matrix.c44
    );
    return *result;
}

const Matrix4 Matrix4::Identity = Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);