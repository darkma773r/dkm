/**
 * quaternion.h
 *
 * Contains a template class for working with quaternions. All
 * quaternions are represented as arrays with the components
 * x, y, z, and w occuring in that order.
 */

#ifndef _DKM_QUATERNION_H_
#define _DKM_QUATERNION_H_

#include <cmath>

#include "matrix.h"

// darkma773r namespace
namespace dkm {

// Namespace containing array-based version of  quaternion operations.
// Unless otherwise noted, all functions in this namespace operate
// at an element level, meaning that any size parameter refers to
// the number of elements and not the number of bytes used to
// represent those elements. For consistency with MatrixUtil, any function that
// writes data to an external array returns the number of elements
// written to that array.
namespace QuaternionUtil {

// Converts a rotation (in radians) around a vector into a quaternion, storing the
// result in dest. vec3 must contain 3 elements and dest must be large
// enough to store a quaternion (4 elements). Returns the number of
// elements written to dest, which is 4.
template<typename T>
size_t rotationToQuaternion(const T* vec3, double rotationRadians, T* dest) {
    // normalize the input vector
    T temp[3];
    MatrixUtil::vectorNormalize(vec3, 3, temp);

    double halfAngle = rotationRadians/2.0;
    double sinHalfAngle = sin(halfAngle);

    dest[0] = temp[0] * sinHalfAngle;
    dest[1] = temp[1] * sinHalfAngle;
    dest[2] = temp[2] * sinHalfAngle;

    dest[3] = cos(halfAngle);

    return 4;
}

// Multiplies two quaternions and stores the result in dest
// (dest = quatA * quatB). All arrays must contain at least 4 elements.
// Returns the number of elements written to dest, which will
// always be 4.
template<typename T>
size_t multiply(const T* quatA, const T* quatB, T* dest) {
    T x1 = quatA[0];
    T y1 = quatA[1];
    T z1 = quatA[2];
    T w1 = quatA[3];

    T x2 = quatB[0];
    T y2 = quatB[1];
    T z2 = quatB[2];
    T w2 = quatB[3];

    // x
    dest[0] = w1 * x2
              + x1 * w2
              + y1 * z2
              - z1 * y2;

    // y
    dest[1] = w1 * y2
              - x1 * z2
              + y1 * w2
              + z1 * x2;

    // z
    dest[2] = w1 * z2
              + x1 * y2
              - y1 * x2
              + z1 * w2;

    // w
    dest[3] = w1 * w2
              - x1 * x2
              - y1 * y2
              - z1 * z2;

    return 4;
}

// Applies the rotation indicated by quatB to quatA, using quaternion
// multiplication with quatB multiplied by quatA (dest = quatB * quatA).
// The result is written to dest and the number of elements written is
// returned, which will always be 4.
template<typename T>
size_t applyQuaternionRotation(const T* quatStart, const T* quatRotation, T* dest) {
    return multiply(quatRotation, quatStart, dest);
}

// Applies the vector rotation indicated by vec3 and rotationRadians to the
// quaternion quatStart. The result is written to dest. The number of elements
// written in returned, which will always be 4.
template<typename T>
size_t applyVectorRotation(const T* quatStart, const T* vec3, double rotationRadians, T* dest) {
    T temp[4];
    rotationToQuaternion(vec3, rotationRadians, temp);
    return applyQuaternionRotation(quatStart, temp, dest);
}

// Internal implementation of the quaternion to rotation matrix algorithm with the option
// to create 3x3 or 4x4 matrices.
template<typename T>
size_t _ToRotationMatrixInternal(const T* quat, T* destMatrix, bool build4x4Matrix) {
    // algorithm taken from http://www.flipcode.com/documents/matrfaq.html#Q54
    double mag = MatrixUtil::vectorMagnitude(quat, 4);

    T x = quat[0]/mag;
    T y = quat[1]/mag;
    T z = quat[2]/mag;
    T w = quat[3]/mag;

    T xx = x * x;
    T xy = x * y;
    T xz = x * z;
    T xw = x * w;

    T yy = y * y;
    T yz = y * z;
    T yw = y * w;

    T zz = z * z;
    T zw = z * w;

    int i = 0;

    destMatrix[i++] = 1 - 2.0 * (yy + zz);
    destMatrix[i++] =     2.0 * (xy - zw);
    destMatrix[i++] =     2.0 * (xz + yw);

    if (build4x4Matrix) {
        destMatrix[i++] = 0.0;
    }

    destMatrix[i++] =     2.0 * (xy + zw);
    destMatrix[i++] = 1 - 2.0 * (xx + zz);
    destMatrix[i++] =     2.0 * (yz - xw);

    if (build4x4Matrix) {
        destMatrix[i++] = 0.0;
    }

    destMatrix[i++] =     2.0 * (xz - yw);
    destMatrix[i++] =     2.0 * (yz + xw);
    destMatrix[i++] = 1 - 2.0 * (xx + yy);

    if (build4x4Matrix) {
        destMatrix[i++] = 0.0;

        destMatrix[i++] = 0.0;
        destMatrix[i++] = 0.0;
        destMatrix[i++] = 0.0;
        destMatrix[i++] = 1.0;
    }

    return i;
}

// Converts the given quaternion into a 3x3 rotation matrix. The caller is
// responsible for ensuring that the destination matrix is large enough
// to contain 9 elements. Returns the total number of elements written,
// which will always be 9.
template<typename T>
size_t toRotationMatrix3x3(const T* quat, T* destMatrix) {
    return _ToRotationMatrixInternal(quat, destMatrix, false);
}

// Converts the given quaternion into a 4x4 rotation matrix. The caller is
// responsible for ensuring that the destination matrix is large enough
// to contain 16 elements. Returns the total number of elements written,
// which will always be 16.
template<typename T>
size_t toRotationMatrix4x4(const T* quat, T* destMatrix) {
    return _ToRotationMatrixInternal(quat, destMatrix, true);
}


} // end QuaternionUtil namespace

template<typename T=double>
class Quaternion : public _VectorBase<4, T, Quaternion<T> > {

    typedef Quaternion<T> ThisType;
    typedef _VectorBase<4, T, Quaternion<T> > SuperType;

public:

    Quaternion(const T* elements = NULL) : SuperType(elements) { }

    Quaternion(const Vector<3, T>& vec3, double radians) :
        SuperType() {
        QuaternionUtil::rotationToQuaternion(vec3.data(), radians, this->mData);
    }

    Quaternion(T xValue, T yValue, T zValue, T wValue) :
        SuperType() {
        this->mData[0] = xValue;
        this->mData[1] = yValue;
        this->mData[2] = zValue;
        this->mData[3] = wValue;
    }

    virtual ~Quaternion() { }

    /**
    Setter for the x value
    */
    void x(T value) { 
        this->mData[0] = value;
    }

    /**
    Accessors for the x value.
     */
    T& x() { return this->mData[0]; }
    const T x() const { return this->mData[0]; }

    /**
    Setter for the y value
    */
    void y(T value) { 
        this->mData[1] = value;
    }

    /**
    Accessors for the y value.
     */
    T& y() { return this->mData[1]; }
    const T y() const { return this->mData[1]; }

    /**
    Setter for the z value
    */
    void z(T value) { 
        this->mData[2] = value;
    }

    /**
    Accessors for the z value.
     */
    T& z() { return this->mData[2]; }
    const T z() const { return this->mData[2]; }

    /**
    Setter for the w value
    */
    void w(T value) { 
        this->mData[3] = value;
    }

    /**
    Accessors for the w value.
     */
    T& w() { return this->mData[3]; }
    const T w() const { return this->mData[3]; }

    // Applies the rotation defined by the quaternion argument to this quaternion.
    void rotate(ThisType& other) {
        QuaternionUtil::applyQuaternionRotation(this->mData, other.data(), this->mData);
    }

    // Applies the rotation defined by the vector and rotation radians to this quaternion.
    void rotate(const Vector<3, T>& axisOfRotation, double rotationRadians) {
        QuaternionUtil::applyVectorRotation(this->mData, axisOfRotation.data(), rotationRadians, this->mData);
    }

    // Returns a 3x3 rotation matrix.
    Matrix<3, 3, T> toRotationMatrix3x3() const {
        Matrix<3, 3, T> mat;
        QuaternionUtil::toRotationMatrix3x3(this->mData, mat.data());
        return mat;
    }

    // Returns a 4x4 rotation matrix.
    Matrix<4, 4, T> toRotationMatrix4x4() const {
        Matrix<4, 4, T> mat;
        QuaternionUtil::toRotationMatrix4x4(this->mData, mat.data());
        return mat;
    }

    // We need to override the default assignment operator
    // since we have internal reference elements.
    ThisType& operator=(const ThisType& other) {
        MatrixUtil::copy(other.mData, this->mData, 4);
        return *this;
    }

    // Returns a new Quaternion set to the identity value.
    static Quaternion identity() {
        Quaternion result;
        result.mData[0] = static_cast<T>(0);
        result.mData[1] = static_cast<T>(0);
        result.mData[2] = static_cast<T>(0);
        result.mData[3] = static_cast<T>(1);

        return result;
    }

    // Returns a new Quaternion built by constructing rotating around the X, Y, and Z
    // axes the given amount of radians in that order.
    static Quaternion fromEulerAngles(T xRadians, T yRadians, T zRadians) {
        Quaternion q = Quaternion::identity();
        q.rotate(Vector<3, T>::xAxis(), xRadians);
        q.rotate(Vector<3, T>::yAxis(), yRadians);
        q.rotate(Vector<3, T>::zAxis(), zRadians);
        return q;
    }

};

// Global function allowing scalar Quaternion multiplication to occur when
// the scalar comes before the Quaternion.
template<typename T>
Quaternion<T> operator*(T scalar, const Quaternion<T>& quat) {
    return quat * scalar;
}


// create some useful typedefs
typedef Quaternion<double> Quatd;
typedef Quaternion<float> Quatf;

} // end dkm namespace

#endif
