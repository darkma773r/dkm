/**
 * vector3_test.cpp
 *
 * Unit tests for the Vector 3 specialized template class.
 */

#include "dkm/math/vector3_test.h"

#include <iostream>

#include <gtest/gtest.h>

#include "dkm/math/matrix.h"
#include "dkm/math/math_test_helpers.h"

using namespace dkm;

// common inputs and outputs for testing
const double zeros3d[] = { 0, 0, 0 };
const double base3d[] = { 1.1, 2.2, 3.3 };
const double baseTimesTwo3d[] = { 2.2, 4.4, 6.6 };
const double addend3d[] = { 2.2, 3.3, 4.4 };
const double sum3d[] = { 3.3, 5.5, 7.7 };

const int zeros3i[] = { 0, 0, 0 };
const int base3i[] = { 1, 2, 3 };
const int baseTimesTwo3i[] = { 2, 4, 6 };
const int addend3i[] = { 2, 3, 4 };
const int sum3i[] = { 3, 5, 7 };


// double comparison accuracy
const double DoubleComparisonAccuracy = 0.01;

// size of array comparison
const int ArrayComparisonSize = 3;

// test suite for the specialized vector 3 template class

TEST_F(Vector3Test, xAxis){
    // arrange
    Vector<3, double> v = Vector<3, double>::xAxis();

    // assert
    double expected[] = { 1.0, 0.0, 0.0 };
    ASSERT_ARRAY_EQ(expected, v.data(), 3);
}

TEST_F(Vector3Test, yAxis){
    // arrange
    Vector<3, double> v = Vector<3, double>::yAxis();

    // assert
    double expected[] = { 0.0, 1.0, 0.0 };
    ASSERT_ARRAY_EQ(expected, v.data(), 3);
}

TEST_F(Vector3Test, zAxis){
    // arrange
    const Vector<3, double> v = Vector<3, double>::zAxis();

    // assert
    double expected[] = { 0.0, 0.0, 1.0 };
    ASSERT_ARRAY_EQ(expected, v.data(), 3);
}


TEST_F(Vector3Test, defaultConstructor){
    // act
    Vector<3, double> v;

    // assert
    ASSERT_ARRAY_EQ(zeros3d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, arrayParamConstructor){
    // act
    Vector<3, double> v(base3d);

    // assert
    ASSERT_TRUE(base3d != v.data());
    ASSERT_ARRAY_EQ(base3d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, valueParamConstructor){
    // act
    Vector<3, int> v(3, 4, 5);

    // assert
    ASSERT_EQ(3, v.x);
    ASSERT_EQ(4, v.y);
    ASSERT_EQ(5, v.z);
}

TEST_F(Vector3Test, implicitArrayConstruction){
    // act
    Vector<3, double> v = base3d;

    // assert
    ASSERT_TRUE(base3d != v.data());
    ASSERT_ARRAY_EQ(base3d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, copyConstructor){
    // arrange
    Vector<3, double> orig(base3d);

    // act
    Vector<3, double> clone(orig);

    // assert
    ASSERT_TRUE(orig.data() != clone.data());
    ASSERT_ARRAY_EQ(base3d, clone.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, assignmentOperator){
    // arrange
    Vector<3, double> orig(base3d);
    Vector<3, double> clone(zeros3d);

    // act
    Vector<3, double> chained = (clone = orig);

    // assert
    ASSERT_TRUE(orig.data() != clone.data());
    ASSERT_ARRAY_EQ(base3d, clone.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base3d, chained.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, selfAssignment){
    // arrange
    Vector<3, double> v(base3d);

    // act
    v = v;

    // assert
    ASSERT_ARRAY_EQ(base3d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, standardGetters){
    // arrange
    Vector<3, double> v;

    // act/assert
    ASSERT_EQ(3, v.size());
}

TEST_F(Vector3Test, copyTo){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0 };
    Vector<3, double> v(base3d);

    // act
    v.copyTo(dest);

    // assert
    ASSERT_ARRAY_EQ(base3d, dest, ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base3d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, copyFrom){
    // arrange
    double dest[] = { 0.1, 0.2, 0.3 };
    Vector<3, double> v(base3d);

    // act
    v.copyFrom(dest);

    // assert
    ASSERT_ARRAY_EQ(dest, v.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, subscriptOperator){
    // arrange
    Vector<3, int> v(zeros3i);

    // act/assert
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
}

TEST_F(Vector3Test, subscriptOperator_const){
    // arrange
    const Vector<3, int> v(base3i);

    // act/assert
    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
}

TEST_F(Vector3Test, namedElementReferences){
    // arrange
    Vector<3, int> v(zeros3i);

    // act/assert
    v.x = 1;
    v.y = 2;
    v.z = 3;

    ASSERT_EQ(1, v.x);
    ASSERT_EQ(2, v.y);
    ASSERT_EQ(3, v.z);

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
}

TEST_F(Vector3Test, namedElementReferences_copyConstructor){
    // arrange
    Vector<3, int> orig(zeros3i);
    Vector<3, int> v(orig);

    // act/assert
    v.x = 1;
    v.y = 2;
    v.z = 3;

    ASSERT_EQ(1, v.x);
    ASSERT_EQ(2, v.y);
    ASSERT_EQ(3, v.z);

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
}

TEST_F(Vector3Test, add){
    // arrange
    Vector<3, double> a(base3d);
    Vector<3, double> b(addend3d);

    // act
    Vector<3, double> x = a.add(b);

    // assert
    ASSERT_ARRAY_NEAR(sum3d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(base3d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(addend3d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, addOperator){
    // arrange
    Vector<3, double> a(base3d);
    Vector<3, double> b(addend3d);

    // act
    Vector<3, double> x = a + b;

    // assert
    ASSERT_ARRAY_NEAR(sum3d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(base3d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(addend3d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, addAssign){
    // arrange
    Vector<3, double> a(base3d);
    Vector<3, double> b(addend3d);

    // act
    a.addAssign(b);

    // assert
    ASSERT_ARRAY_NEAR(sum3d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(addend3d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, addAssignOperator){
    // arrange
    Vector<3, double> a(base3d);
    Vector<3, double> b(addend3d);

    // act
    Vector<3, double> x = a += b;

    // assert
    ASSERT_ARRAY_NEAR(sum3d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(sum3d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(addend3d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, subtract){
    // arrange
    Vector<3, int> a(sum3i);
    Vector<3, int> b(addend3i);

    // act
    Vector<3, int> x = a.subtract(b);

    // assert
    ASSERT_ARRAY_EQ(base3i, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(sum3i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(addend3i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, subtractOperator){
    // arrange
    Vector<3, int> a(sum3i);
    Vector<3, int> b(addend3i);

    // act
    Vector<3, int> x = a - b;

    // assert
    ASSERT_ARRAY_EQ(base3i, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(sum3i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(addend3i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, subtractAssign){
    // arrange
    Vector<3, int> a(sum3i);
    Vector<3, int> b(addend3i);

    // act
    a.subtractAssign(b);

    // assert
    ASSERT_ARRAY_EQ(base3i, a.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(addend3i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, subtractAssignOperator){
    // arrange
    Vector<3, int> a(sum3i);
    Vector<3, int> b(addend3i);

    // act
    Vector<3, int> x = a -= b;

    // assert
    ASSERT_ARRAY_EQ(base3i, x.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base3i, a.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(addend3i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, scalarMultiply){
    // arrange
    Vector<3, double> a(base3d);

    // act
    Vector<3, double> x = a.scalarMultiply(2.0);

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo3d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base3d, a.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, scalarMultiplyOperator){
    // arrange
    Vector<3, double> a(base3d);

    // act
    Vector<3, double> x = a * 2.0;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo3d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base3d, a.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, ScalarMultiplyOperator_ScalarFirst){
    // arrange
    Vector<3, double> a(base3d);

    // act
    Vector<3, double> x = 2.0 * a;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo3d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base3d, a.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, scalarMultiplyAssign){
    // arrange
    Vector<3, double> a(base3d);

    // act
    a.scalarMultiplyAssign(2.0);

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo3d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, scalarMultiplyAssignOperator){
    // arrange
    Vector<3, double> a(base3d);

    // act
    Vector<3, double> x = a *= 2.0;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo3d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(baseTimesTwo3d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, magnitude){
    // arrange
    Vector<3, int> a(base3i);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(3.7417, mag, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, magnitude_zeroVector){
    // arrange
    Vector<3, int> a(zeros3i);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(0.0, mag, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, magnitude_negativeValues){
    // arrange
    int negArr[] = { -1, -2, -3 };
    Vector<3, int> a(negArr);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(3.7417, mag, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, normalize){
    // arrange
    // magnitude = 6.0249
    Vector<3, double> a(base3d);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(true, result);

    double normalized[] = { 0.2673, 0.5345, 0.8018 };
    ASSERT_ARRAY_NEAR(normalized, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, normalize_zeroArray){
    // arrange
    Vector<3, double> a(zeros3d);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(false, result);
    ASSERT_ARRAY_NEAR(zeros3d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, normalize_integerVector){
    // arrange
    Vector<3, int> a(base3i);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(true, result);

    // since every value will be less than one, the array ends up consisting
    // entirely of zeros. This is something the caller will need to be aware of.
    ASSERT_ARRAY_EQ(zeros3i, a.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, isNormalized_default){
    // arrange
    float normalizedArr[] = { 0.0, 0.7071067811, 0.7071067811 };
    float notNormalizedArr[] = { 0.0, 1.0, 1.0 };

    Vector<3, float> a(normalizedArr);
    Vector<3, float> b(notNormalizedArr);

    // act/assert
    ASSERT_EQ(true, a.isNormalized());
    ASSERT_EQ(false, b.isNormalized());
}

TEST_F(Vector3Test, isNormalized_epsilon){
    // arrange
    float arr[] = { 0.0, 0.8, 0.8 };

    Vector<3, float> a(arr);

    // act/assert
    ASSERT_EQ(true, a.isNormalized(0.5));
    ASSERT_EQ(false, a.isNormalized(0.01));
}

TEST_F(Vector3Test, dotProduct){
    // arrange
    Vector<3, int> a(base3i);
    Vector<3, int> b(base3i);

    // act
    double dotproduct = a.dot(b);

    // assert
    ASSERT_NEAR(14.0, dotproduct, DoubleComparisonAccuracy);
    ASSERT_ARRAY_EQ(base3i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base3i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector3Test, toString){
    // arrange
    Vector<3, double> v;
    v[0] = 0.012;
    v[1] = 1.0;
    v[2] = 2.0;

    // act
    std::string expected("[ 0.01, 1.00, 2.00 ]");
    std::string str = v.toString();

    // assert
    ASSERT_EQ(expected, str);
}


// the Vector3 specialization also has the CrossProduct method defined
TEST_F(Vector3Test, crossProduct){
    // arrange
    double aArr[] = { 0.0, 1.0, 1.0 };
    double bArr[] = { 1.0, -1.0, 3.0 };

    Vector<3, double> a(aArr);
    Vector<3, double> b(bArr);

    // act
    Vector<3, double> c = a.cross(b);

    // assert
    double expected[] = { 4.0, 1.0, -1.0 };
    ASSERT_ARRAY_NEAR(expected, c.data(), 3, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(aArr, a.data(), 3, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(bArr, b.data(), 3, DoubleComparisonAccuracy);
}

TEST_F(Vector3Test, crossProduct_OppositeOrder){
    // arrange
    double aArr[] = { 0.0, 1.0, 1.0 };
    double bArr[] = { 1.0, -1.0, 3.0 };

    Vector<3, double> a(aArr);
    Vector<3, double> b(bArr);

    // act
    Vector<3, double> c = b.cross(a);

    // assert
    double expected[] = { -4.0, -1.0, 1.0 };
    ASSERT_ARRAY_NEAR(expected, c.data(), 3, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(aArr, a.data(), 3, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(bArr, b.data(), 3, DoubleComparisonAccuracy);
}

