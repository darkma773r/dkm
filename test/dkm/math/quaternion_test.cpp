
/**
 * quaternion_test.cpp
 *
 * Unit tests for the Quaternion template class.
 */

#include "dkm/math/quaternion_test.h"

#include <iostream>

#include <gtest/gtest.h>

#include "dkm/math/quaternion.h"
#include "dkm/math/math_test_helpers.h"

// add some macros for degree to radian conversion
#define PI 3.14159265
#define DEG_TO_RAD( x ) ( x * ( PI / 180 ))

using namespace dkm;

// common inputs and outputs for testing
const double zeros4d[] = { 0, 0, 0, 0 };
const double base4d[] = { 1.1, 2.2, 3.3, 4.4 };
const double baseTimesTwo4d[] = { 2.2, 4.4, 6.6, 8.8 };
const double addend4d[] = { 2.2, 3.3, 4.4, 5.5 };
const double sum4d[] = { 3.3, 5.5, 7.7, 9.9 };

const int zeros4i[] = { 0, 0, 0, 0 };
const int base4i[] = { 1, 2, 3, 4 };
const int baseTimesTwo4i[] = { 2, 4, 6, 8 };
const int addend4i[] = { 2, 3, 4, 5 };
const int sum4i[] = { 3, 5, 7, 9 };


// double comparison accuracy
const double DoubleComparisonAccuracy = 0.01;

// size of array comparison
const int ArrayComparisonSize = 4;

TEST_F(QuaternionTest, defaultConstructor){
    // act
    Quaternion<double> v;

    // assert
    ASSERT_ARRAY_EQ(zeros4d, v.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, arrayParamConstructor){
    // act
    Quaternion<double> v(base4d);

    // assert
    ASSERT_TRUE(base4d != v.data());
    ASSERT_ARRAY_EQ(base4d, v.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, valueParamConstructor){
    // act
    Quaternion<int> v(3, 4, 5, 6);

    // assert
    ASSERT_EQ(3, v.x());
    ASSERT_EQ(4, v.y());
    ASSERT_EQ(5, v.z());
    ASSERT_EQ(6, v.w());
}

TEST_F(QuaternionTest, implicitArrayConstruction){
    // act
    Quaternion<double> v = base4d;

    // assert
    ASSERT_TRUE(base4d != v.data());
    ASSERT_ARRAY_EQ(base4d, v.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, copyConstructor){
    // arrange
    Quaternion<double> orig(base4d);

    // act
    Quaternion<double> clone(orig);

    // assert
    ASSERT_TRUE(orig.data() != clone.data());
    ASSERT_ARRAY_EQ(base4d, clone.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, assignmentOperator){
    // arrange
    Quaternion<double> orig(base4d);
    Quaternion<double> clone(zeros4d);

    // act
    Quaternion<double> chained = (clone = orig);

    // assert
    ASSERT_TRUE(orig.data() != clone.data());
    ASSERT_ARRAY_EQ(base4d, clone.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base4d, chained.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, selfAssignment){
    // arrange
    Quaternion<double> v(base4d);

    // act
    v = v;

    // assert
    ASSERT_ARRAY_EQ(base4d, v.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, identity){
    // act
    Quaternion<double> q = Quaternion<double>::identity();

    // assert
    ASSERT_EQ(0.0, q.x());
    ASSERT_EQ(0.0, q.y());
    ASSERT_EQ(0.0, q.z());
    ASSERT_EQ(1.0, q.w());
}

TEST_F(QuaternionTest, standardGetters){
    // arrange
    Quaternion<double> v;

    // act/assert
    ASSERT_EQ(4, v.size());
}

TEST_F(QuaternionTest, copyTo){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };
    Quaternion<double> v(base4d);

    // act
    v.copyTo(dest);

    // assert
    ASSERT_ARRAY_EQ(base4d, dest, ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base4d, v.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, copyFrom){
    // arrange
    double dest[] = { 0.1, 0.2, 0.3, 0.4 };
    Quaternion<double> v(base4d);

    // act
    v.copyFrom(dest);

    // assert
    ASSERT_ARRAY_EQ(dest, v.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, subscriptOperator){
    // arrange
    Quaternion<int> v(zeros4i);

    // act/assert
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
}

TEST_F(QuaternionTest, subscriptOperator_const){
    // arrange
    const Quaternion<int> v(base4i);

    // act/assert
    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
}

TEST_F(QuaternionTest, namedAccessors){
    // arrange
    Quaternion<int> v(zeros4i);

    // act/assert
    v.x(1);
    v.y(2);
    v.z(3);
    v.w(4);

    ASSERT_EQ(1, v.x());
    ASSERT_EQ(2, v.y());
    ASSERT_EQ(3, v.z());
    ASSERT_EQ(4, v.w());

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
}

TEST_F(QuaternionTest, namedAccessors_const){
    // arrange
    const Quaternion<int> v(base4i);

    // act/assert
    ASSERT_EQ(1, v.x());
    ASSERT_EQ(2, v.y());
    ASSERT_EQ(3, v.z());
    ASSERT_EQ(4, v.w());

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
}

TEST_F(QuaternionTest, namedAccessors_setByReferences){
    // arrange
    Quaternion<int> v(zeros4i);
    
    // act/assert
    v.x() = 1;
    v.y() = 2;
    v.z() = 3;
    v.w() = 4;

    ASSERT_EQ(1, v.x());
    ASSERT_EQ(2, v.y());
    ASSERT_EQ(3, v.z());
    ASSERT_EQ(4, v.w());

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
}

TEST_F(QuaternionTest, add){
    // arrange
    Quaternion<double> a(base4d);
    Quaternion<double> b(addend4d);

    // act
    Quaternion<double> x = a.add(b);

    // assert
    ASSERT_ARRAY_NEAR(sum4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(base4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(addend4d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, addOperator){
    // arrange
    Quaternion<double> a(base4d);
    Quaternion<double> b(addend4d);

    // act
    Quaternion<double> x = a + b;

    // assert
    ASSERT_ARRAY_NEAR(sum4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(base4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(addend4d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, addAssign){
    // arrange
    Quaternion<double> a(base4d);
    Quaternion<double> b(addend4d);

    // act
    a.addAssign(b);

    // assert
    ASSERT_ARRAY_NEAR(sum4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(addend4d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, addAssignOperator){
    // arrange
    Quaternion<double> a(base4d);
    Quaternion<double> b(addend4d);

    // act
    Quaternion<double> x = a += b;

    // assert
    ASSERT_ARRAY_NEAR(sum4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(sum4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(addend4d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, subtract){
    // arrange
    Quaternion<int> a(sum4i);
    Quaternion<int> b(addend4i);

    // act
    Quaternion<int> x = a.subtract(b);

    // assert
    ASSERT_ARRAY_EQ(base4i, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(sum4i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(addend4i, b.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, subtractOperator){
    // arrange
    Quaternion<int> a(sum4i);
    Quaternion<int> b(addend4i);

    // act
    Quaternion<int> x = a - b;

    // assert
    ASSERT_ARRAY_EQ(base4i, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(sum4i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(addend4i, b.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, subtractAssign){
    // arrange
    Quaternion<int> a(sum4i);
    Quaternion<int> b(addend4i);

    // act
    a.subtractAssign(b);

    // assert
    ASSERT_ARRAY_EQ(base4i, a.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(addend4i, b.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, subtractAssignOperator){
    // arrange
    Quaternion<int> a(sum4i);
    Quaternion<int> b(addend4i);

    // act
    Quaternion<int> x = a -= b;

    // assert
    ASSERT_ARRAY_EQ(base4i, x.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base4i, a.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(addend4i, b.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, scalarMultiply){
    // arrange
    Quaternion<double> a(base4d);

    // act
    Quaternion<double> x = a.scalarMultiply(2.0);

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base4d, a.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, scalarMultiplyOperator){
    // arrange
    Quaternion<double> a(base4d);

    // act
    Quaternion<double> x = a * 2.0;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base4d, a.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, scalarMultiplyOperator_ScalarFirst){
    // arrange
    Quaternion<double> a(base4d);

    // act
    Quaternion<double> x = 2.0 * a;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base4d, a.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, scalarMultiplyAssign){
    // arrange
    Quaternion<double> a(base4d);

    // act
    a.scalarMultiplyAssign(2.0);

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, scalarMultiplyAssignOperator){
    // arrange
    Quaternion<double> a(base4d);

    // act
    Quaternion<double> x = a *= 2.0;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, magnitude){
    // arrange
    Quaternion<int> a(base4i);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(5.4772, mag, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, magnitude_zeroVector){
    // arrange
    Quaternion<int> a(zeros4i);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(0.0, mag, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, magnitude_negativeValues){
    // arrange
    int negArr[] = { -1, -2, -3, -4 };
    Quaternion<int> a(negArr);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(5.4772, mag, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, normalize){
    // arrange
    // magnitude = 6.0249
    Quaternion<double> a(base4d);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(true, result);

    double normalized[] = { 0.1826, 0.3651, 0.5477, 0.7303 };
    ASSERT_ARRAY_NEAR(normalized, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, normalize_zeroArray){
    // arrange
    Quaternion<double> a(zeros4d);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(false, result);
    ASSERT_ARRAY_NEAR(zeros4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, normalize_integerVector){
    // arrange
    Quaternion<int> a(base4i);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(true, result);

    // since every value will be less than one, the array ends up consisting
    // entirely of zeros. This is something the caller will need to be aware of.
    ASSERT_ARRAY_EQ(zeros4i, a.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, isNormalized_default){
    // arrange
    float normalizedArr[] = { 0.0, 0.0, 0.7071067811, 0.7071067811 };
    float notNormalizedArr[] = { 0.0, 0.0, 1.0, 1.0 };

    Quaternion<float> a(normalizedArr);
    Quaternion<float> b(notNormalizedArr);

    // act/assert
    ASSERT_EQ(true, a.isNormalized());
    ASSERT_EQ(false, b.isNormalized());
}

TEST_F(QuaternionTest, isNormalized_epsilon){
    // arrange
    float arr[] = { 0.0, 0.0, 0.8, 0.8 };

    Quaternion<float> a(arr);

    // act/assert
    ASSERT_EQ(true, a.isNormalized(0.5));
    ASSERT_EQ(false, a.isNormalized(0.01));
}

TEST_F(QuaternionTest, dotProduct){
    // arrange
    Quaternion<int> a(base4i);
    Quaternion<int> b(base4i);

    // act
    double dotproduct = a.dot(b);

    // assert
    ASSERT_NEAR(30.0, dotproduct, DoubleComparisonAccuracy);
    ASSERT_ARRAY_EQ(base4i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base4i, b.data(), ArrayComparisonSize);
}

TEST_F(QuaternionTest, toString){
    // arrange
    Quaternion<double> v;
    v[0] = 0.012;
    v[1] = 1.0;
    v[2] = 2.0;
    v[3] = 3.3333;

    // act
    std::string expected("[ 0.01, 1.00, 2.00, 3.33 ]");
    std::string str = v.toString();

    // assert
    ASSERT_EQ(expected, str);
}

TEST_F(QuaternionTest, quaternionRotate){
    // arrange
    Quaternion<double> q( 0.5, 0.5, 0.75, 1.0 );
    Quaternion<double> r( 0.0, 1.0, 0.0, 1.0 );

    // act
    q.rotate(r);

    // assert
    double expected[] = { 1.25, 1.5, 0.25, 0.5 };
    ASSERT_ARRAY_NEAR(expected, q.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, vectorRotate){
    // arrange
    Quaternion<double> q(0.7071, 0.0, 0.0, 0.7071); // 90 degrees around x axis

    Vector<3, double> rotationAxis(0.0, 1.0, 0.0 );
    double rotationRadians = DEG_TO_RAD(-90); // -90 degrees around y axis

    // act
    q.rotate(rotationAxis, rotationRadians);

    // assert
    double expected[] = { 0.5, -0.5, 0.5, 0.5 };
    ASSERT_ARRAY_NEAR(expected, q.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, toRotationMatrix3x3){
    // arrange
    Quaternion<float> q(0.0, 0.7071, 0.0, 0.7071); // 90 degrees around y axis

    // act
    Matrix<3, 3, float> matrix = q.toRotationMatrix3x3();

    // assert
    float expected[] = { 0.0, 0.0, 1.0,
                        0.0, 1.0, 0.0,
                        -1.0, 0.0, 0.0 };
    ASSERT_ARRAY_NEAR(expected, matrix.data(), 9, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, toRotationMatrix3x3_NonNormalizedQuaternion){
    // arrange
    Quaternion<float> q(0.0, 1.4142, 0.0, 1.4142); // non-normalized 90 degrees around y axis

    // act
    Matrix<3, 3, float> matrix = q.toRotationMatrix3x3();

    // assert
    float expected[] = { 0.0, 0.0, 1.0,
                        0.0, 1.0, 0.0,
                        -1.0, 0.0, 0.0 };
    ASSERT_ARRAY_NEAR(expected, matrix.data(), 9, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, toRotationMatrix4x4){
    // arrange
    Quaternion<float> q(0.0, 0.7071, 0.0, 0.7071 ); // 90 degrees around y axis

    // act
    Matrix<4, 4, float> matrix = q.toRotationMatrix4x4();

    // assert
    float expected[] = { 0.0, 0.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        -1.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 1.0 };
    ASSERT_ARRAY_NEAR(expected, matrix.data(), 16, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, toRotationMatrix4x4_NonNormalizedQuaternion){
    // arrange
    Quaternion<float> q(0.0, 1.4142, 0.0, 1.4142); // non-normalized 90 degrees around y axis

    // act
    Matrix<4, 4, float> matrix = q.toRotationMatrix4x4();

    // assert
    float expected[] = { 0.0, 0.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        -1.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 1.0 };
    ASSERT_ARRAY_NEAR(expected, matrix.data(), 16, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, testRotateAndTransform){
    // arrange
    Quaternion<double> q = Quaternion<double>::identity();
    Vector<4, double> v(0.0, 1.0, 0.0, 1.0);

    // act
    q.rotate(Vector<3, double>::xAxis(), DEG_TO_RAD(90));
    q.rotate(Vector<3, double>::yAxis(), DEG_TO_RAD(90));
    q.rotate(Vector<3, double>::zAxis(), DEG_TO_RAD(45));

    Matrix<4, 4, double> matrix = q.toRotationMatrix4x4();
    Vector<4, double> transformed = matrix.transformVector(v);

    // assert
    double expected[] = { 0.7071, 0.7071, 0.0, 1.0 };
    ASSERT_ARRAY_NEAR(expected, transformed.data(), 4, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, fromEulerAngles_xAxis){
    // act
    Quaternion<float> q = Quaternion<float>::fromEulerAngles(DEG_TO_RAD(90), 0.0, 0.0);

    // assert
    double expected[] = { 0.7071, 0.0, 0.0, 0.7071 };
    ASSERT_ARRAY_NEAR(expected, q.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, fromEulerAngles_yAxis){
    // act
    Quaternion<float> q = Quaternion<float>::fromEulerAngles(0.0, DEG_TO_RAD(90), 0.0);

    // assert
    double expected[] = { 0.0, 0.7071, 0.0, 0.7071 };
    ASSERT_ARRAY_NEAR(expected, q.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, fromEulerAngles_zAxis){
    // act
    Quaternion<float> q = Quaternion<float>::fromEulerAngles(0.0, 0.0, DEG_TO_RAD(-90));

    // assert
    double expected[] = { 0.0, 0.0, -0.7071, 0.7071 };
    ASSERT_ARRAY_NEAR(expected, q.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionTest, fromEulerAngles_allAxes){
    // act
    Quaternion<float> q = Quaternion<float>::fromEulerAngles(DEG_TO_RAD(90), DEG_TO_RAD(90), DEG_TO_RAD(45));

    // assert
    double expected[] = { 0.2706, 0.6533, -0.2706, 0.6533 };
    ASSERT_ARRAY_NEAR(expected, q.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

