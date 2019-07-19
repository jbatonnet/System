#ifndef _SYSTEM_MATRIXES_H_
#define _SYSTEM_MATRIXES_H_

/*namespace System
{
    //namespace Maths
    {*/
        struct Vector3;
        struct Quaternion;

        struct Matrix3
        {
	        union
            {
		        struct
                {
			        float c11, c12, c13;
			        float c21, c22, c23;
			        float c31, c32, c33;
		        };
		        float components[9];
	        };

            Matrix3();
            Matrix3(const Matrix3& matrix);
            Matrix3(float c11, float c12, float c13, float c21, float c22, float c23, float c31, float c32, float c33);

            // Functions
            float Determinant();
            Matrix3& Transpose();
            void Normalize();

            // Manipulation
            static Matrix3& Normalize(const Matrix3& matrix);

            // Creators
            static Matrix3& CreateRotation(float pitch, float yaw, float roll);
            static Matrix3& CreateRotation(float x, float y, float z, float angle); // TODO
            static Matrix3& CreateRotation(const Vector3& vector, float angle);
            static Matrix3& CreateRotation(const Quaternion& quaternion); // TODO
            static Matrix3& CreateTranslation(float x, float y, float z); // TODO
            static Matrix3& CreateTranslation(const Vector3& vector); // TODO
            static Matrix3& CreateScale(float x, float y, float z); // TODO
            static Matrix3& CreateScale(const Vector3& vector); // TODO

            // Operators
            Matrix3& operator+=(const Matrix3& matrix); // TODO
            Matrix3& operator-=(const Matrix3& matrix); // TODO
            Matrix3& operator*=(const Matrix3& matrix); // TODO
            Matrix3& operator/=(const Matrix3& matrix); // TODO
            Matrix3& operator+(const Matrix3& matrix) const; // TODO
            Matrix3& operator-(const Matrix3& matrix) const; // TODO
            Matrix3& operator*(const Matrix3& matrix) const;
            Vector3& operator*(const Vector3& vector) const;
            Matrix3& operator/(const Matrix3& matrix) const; // TODO

            static const Matrix3 Identity;
        };

        struct Matrix4
        {
	        union
            {
		        struct
                {
			        float c11, c12, c13, c14;
			        float c21, c22, c23, c24;
			        float c31, c32, c33, c34;
                    float c41, c42, c43, c44;
		        };
		        float components[16];
	        };

            Matrix4();
            Matrix4(float c11, float c12, float c13, float c14, float c21, float c22, float c23, float c24, float c31, float c32, float c33, float c34, float c41, float c42, float c43, float c44);
            Matrix4(const Matrix3& matrix);

            // Functions
            Matrix4& Transpose();
            float Determinant();

            // Creators
            static Matrix4& CreateTransformation(const Vector3& translation, const Matrix3& rotation, const Vector3& scale);
            static Matrix4& CreateView(const Vector3& position, const Vector3& target, const Vector3& up);
            static Matrix4& CreateProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

            // Operators
            Matrix4& operator*(const Matrix4& matrix) const;

            static const Matrix4 Identity;
        };
/*    }
}*/

#endif