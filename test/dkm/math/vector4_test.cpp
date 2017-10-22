
/**
 * vector4_test.cpp
 *
 * Unit tests for the Vector 4 specialized template class.
 */

#include "dkm/math/vector4_test.h"

#include <iostream>

#include <gtest/gtest.h>

#include "dkm/math/matrix.h"
#include "dkm/math/math_test_helpers.h"

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

// test suite for the specialized vector 4 template class

TEST_F(Vector4Test, xAxis){
    // arrange
    Vector<4, double> v = Vector<4, double>::xAxis();

    // assert
    double expected[] = { 1.0, 0.0, 0.0, 0.0 };
    ASSERT_ARRAY_EQ(expected, v.data(), 4);
}

TEST_F(Vector4Test, yAxis){
    // arrange
    Vector<4, double> v = Vector<4, double>::yAxis();

    // assert
    double expected[] = { 0.0, 1.0, 0.0, 0.0 };
    ASSERT_ARRAY_EQ(expected, v.data(), 4);
}

TEST_F(Vector4Test, zAxis){
    // arrange
    const Vector<4, double> v = Vector<4, double>::zAxis();

    // assert
    double expected[] = { 0.0, 0.0, 1.0, 0.0 };
    ASSERT_ARRAY_EQ(expected, v.data(), 4);
}

TEST_F(Vector4Test, wAxis){
    // arrange
    const Vector<4, double> v = Vector<4, double>::wAxis();

    // assert
    double expected[] = { 0.0, 0.0, 0.0, 1.0 };
    ASSERT_ARRAY_EQ(expected, v.data(), 4);
}

TEST_F(Vector4Test, defaultConstructor){
    // act
    Vector<4, double> v;

    // assert
    ASSERT_ARRAY_EQ(zeros4d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, arrayParamConstructor){
    // act
    Vector<4, double> v(base4d);

    // assert
    ASSERT_TRUE(base4d != v.data());
    ASSERT_ARRAY_EQ(base4d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, valueParamConstructor){
    // act
    Vector<4, int> v(3, 4, 5, 6);

    // assert
    ASSERT_EQ(3, v.x);
    ASSERT_EQ(4, v.y);
    ASSERT_EQ(5, v.z);
    ASSERT_EQ(6, v.w);
}

TEST_F(Vector4Test, implicitArrayConstruction){
    // act
    Vector<4, double> v = base4d;

    // assert
    ASSERT_TRUE(base4d != v.data());
    ASSERT_ARRAY_EQ(base4d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, copyConstructor){
    // arrange
    Vector<4, double> orig(base4d);

    // act
    Vector<4, double> clone(orig);

    // assert
    ASSERT_TRUE(orig.data() != clone.data());
    ASSERT_ARRAY_EQ(base4d, clone.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, assignmentOperator){
    // arrange
    Vector<4, double> orig(base4d);
    Vector<4, double> clone(zeros4d);

    // act
    Vector<4, double> chained = (clone = orig);

    // assert
    ASSERT_TRUE(orig.data() != clone.data());
    ASSERT_ARRAY_EQ(base4d, clone.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base4d, chained.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, selfAssignment){
    // arrange
    Vector<4, double> v(base4d);

    // act
    v = v;

    // assert
    ASSERT_ARRAY_EQ(base4d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, standardGetters){
    // arrange
    Vector<4, double> v;

    // act/assert
    ASSERT_EQ(4, v.size());
}

TEST_F(Vector4Test, copyTo){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };
    Vector<4, double> v(base4d);

    // act
    v.copyTo(dest);

    // assert
    ASSERT_ARRAY_EQ(base4d, dest, ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base4d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, copyFrom){
    // arrange
    double dest[] = { 0.1, 0.2, 0.3, 0.4 };
    Vector<4, double> v(base4d);

    // act
    v.copyFrom(dest);

    // assert
    ASSERT_ARRAY_EQ(dest, v.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, subscriptOperator){
    // arrange
    Vector<4, int> v(zeros4i);

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

TEST_F(Vector4Test, subscriptOperator_const){
    // arrange
    const Vector<4, int> v(base4i);

    // act/assert
    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
}

TEST_F(Vector4Test, NamedElementReferences){
    // arrange
    Vector<4, int> v(zeros4i);

    // act/assert
    v.x = 1;
    v.y = 2;
    v.z = 3;
    v.w = 4;

    ASSERT_EQ(1, v.x);
    ASSERT_EQ(2, v.y);
    ASSERT_EQ(3, v.z);
    ASSERT_EQ(4, v.w);

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
}

TEST_F(Vector4Test, namedElementReferences_copyConstructor){
    // arrange
    Vector<4, int> orig(zeros4i);
    Vector<4, int> v(orig);

    // act/assert
    v.x = 1;
    v.y = 2;
    v.z = 3;
    v.w = 4;

    ASSERT_EQ(1, v.x);
    ASSERT_EQ(2, v.y);
    ASSERT_EQ(3, v.z);
    ASSERT_EQ(4, v.w);

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
}

TEST_F(Vector4Test, add){
    // arrange
    Vector<4, double> a(base4d);
    Vector<4, double> b(addend4d);

    // act
    Vector<4, double> x = a.add(b);

    // assert
    ASSERT_ARRAY_NEAR(sum4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(base4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(addend4d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector4Test, addOperator){
    // arrange
    Vector<4, double> a(base4d);
    Vector<4, double> b(addend4d);

    // act
    Vector<4, double> x = a + b;

    // assert
    ASSERT_ARRAY_NEAR(sum4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(base4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(addend4d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector4Test, addAssign){
    // arrange
    Vector<4, double> a(base4d);
    Vector<4, double> b(addend4d);

    // act
    a.addAssign(b);

    // assert
    ASSERT_ARRAY_NEAR(sum4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(addend4d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector4Test, addAssignOperator){
    // arrange
    Vector<4, double> a(base4d);
    Vector<4, double> b(addend4d);

    // act
    Vector<4, double> x = a += b;

    // assert
    ASSERT_ARRAY_NEAR(sum4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(sum4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(addend4d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector4Test, subtract){
    // arrange
    Vector<4, int> a(sum4i);
    Vector<4, int> b(addend4i);

    // act
    Vector<4, int> x = a.subtract(b);

    // assert
    ASSERT_ARRAY_EQ(base4i, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(sum4i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(addend4i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, subtractOperator){
    // arrange
    Vector<4, int> a(sum4i);
    Vector<4, int> b(addend4i);

    // act
    Vector<4, int> x = a - b;

    // assert
    ASSERT_ARRAY_EQ(base4i, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(sum4i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(addend4i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, subtractAssign){
    // arrange
    Vector<4, int> a(sum4i);
    Vector<4, int> b(addend4i);

    // act
    a.subtractAssign(b);

    // assert
    ASSERT_ARRAY_EQ(base4i, a.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(addend4i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, subtractAssignOperator){
    // arrange
    Vector<4, int> a(sum4i);
    Vector<4, int> b(addend4i);

    // act
    Vector<4, int> x = a -= b;

    // assert
    ASSERT_ARRAY_EQ(base4i, x.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base4i, a.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(addend4i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, scalarMultiply){
    // arrange
    Vector<4, double> a(base4d);

    // act
    Vector<4, double> x = a.scalarMultiply(2.0);

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base4d, a.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, scalarMultiplyOperator){
    // arrange
    Vector<4, double> a(base4d);

    // act
    Vector<4, double> x = a * 2.0;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base4d, a.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, ScalarMultiplyOperator_ScalarFirst){
    // arrange
    Vector<4, double> a(base4d);

    // act
    Vector<4, double> x = 2.0 * a;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base4d, a.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, scalarMultiplyAssign){
    // arrange
    Vector<4, double> a(base4d);

    // act
    a.scalarMultiplyAssign(2.0);

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector4Test, scalarMultiplyAssignOperator){
    // arrange
    Vector<4, double> a(base4d);

    // act
    Vector<4, double> x = a *= 2.0;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector4Test, magnitude){
    // arrange
    Vector<4, int> a(base4i);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(5.4772, mag, DoubleComparisonAccuracy);
}

TEST_F(Vector4Test, magnitude_zeroVector){
    // arrange
    Vector<4, int> a(zeros4i);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(0.0, mag, DoubleComparisonAccuracy);
}

TEST_F(Vector4Test, magnitude_negativeValues){
    // arrange
    int negArr[] = { -1, -2, -3, -4 };
    Vector<4, int> a(negArr);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(5.4772, mag, DoubleComparisonAccuracy);
}

TEST_F(Vector4Test, normalize){
    // arrange
    // magnitude = 6.0249
    Vector<4, double> a(base4d);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(true, result);

    double normalized[] = { 0.1826, 0.3651, 0.5477, 0.7303 };
    ASSERT_ARRAY_NEAR(normalized, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector4Test, normalize_zeroArray){
    // arrange
    Vector<4, double> a(zeros4d);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(false, result);
    ASSERT_ARRAY_NEAR(zeros4d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector4Test, normalize_integerVector){
    // arrange
    Vector<4, int> a(base4i);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(true, result);

    // since every value will be less than one, the array ends up consisting
    // entirely of zeros. This is something the caller will need to be aware of.
    ASSERT_ARRAY_EQ(zeros4i, a.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, isNormalized_default){
    // arrange
    float normalizedArr[] = { 0.0, 0.0, 0.7071067811, 0.7071067811 };
    
    float notNormalizedArr[] = { 0.0, 0.0, 1.0, 1.0 };

    Vector<4, float> a(normalizedArr);
    Vector<4, float> b(notNormalizedArr);

    // act/assert
    ASSERT_EQ(true, a.isNormalized());
    ASSERT_EQ(false, b.isNormalized());
}

TEST_F(Vector4Test, isNormalized_epsilon){
    // arrange
    float arr[] = { 0.0, 0.0, 0.8, 0.8 };

    Vector<4, float> a(arr);

    // act/assert
    ASSERT_EQ(true, a.isNormalized(0.5));
    ASSERT_EQ(false, a.isNormalized(0.01));
}

TEST_F(Vector4Test, dotProduct){
    // arrange
    Vector<4, int> a(base4i);
    Vector<4, int> b(base4i);

    // act
    double dotproduct = a.dot(b);

    // assert
    ASSERT_NEAR(30.0, dotproduct, DoubleComparisonAccuracy);
    ASSERT_ARRAY_EQ(base4i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base4i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector4Test, toString){
    // arrange
    Vector<4, double> v;
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

