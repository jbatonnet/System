#include <System/Maths/Vectors.h>
#include <System/Maths/Matrixes.h>
#include <System/Maths/Maths.h>

// Point2
const Point2 Point2::Zero = Point2(0),
             Point2::One = Point2(1);

// Point3
const Point3 Point3::Zero = Point3(0),
             Point3::One = Point3(1);

// Vector2
const Vector2 Vector2::Zero = Vector2(0),
              Vector2::One = Vector2(1),
              Vector2::Left = Vector2(-1, 0),
              Vector2::Up = Vector2(0, -1),
              Vector2::Right = Vector2(1, 0),
              Vector2::Down = Vector2(0, 1);

// Vector3
const Vector3 Vector3::Zero = Vector3(0),
              Vector3::One = Vector3(1),
              Vector3::Backward = Vector3(0, 0, 1),
              Vector3::Forward = Vector3(0, 0, -1),
              Vector3::Left = Vector3(-1, 0, 0),
              Vector3::Right = Vector3(1, 0, 0),
              Vector3::Down = Vector3(0, -1, 0),
              Vector3::Up = Vector3(0, 1, 0);

// Quaternion

Quaternion::Quaternion() { }
Quaternion::Quaternion(float x, float y, float z, float angle) : X(x), Y(y), Z(z), W(angle) { }
Quaternion::Quaternion(const Vector3 vector, float angle) : X(vector.X), Y(vector.Y), Z(vector.Z), W(angle) { }

Quaternion& Quaternion::Lerp(const Quaternion &q1, const Quaternion &q2, float c)
{
    Quaternion* result = new Quaternion(
        q1.X + (q2.X - q1.X) * c,
        q1.Y + (q2.Y - q1.Y) * c,
        q1.Z + (q2.Z - q1.Z) * c,
        q1.W + (q2.W - q1.W) * c
    );
    return *result;
}

const Quaternion Quaternion::Identity = Quaternion(Vector3::Backward, 0);