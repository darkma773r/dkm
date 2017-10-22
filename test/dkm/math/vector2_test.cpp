/**
 * vector2_test.cpp
 *
 * Unit tests for the Vector 2 specialized template class.
 */

#include "dkm/math/vector2_test.h"

#include <iostream>

#include <gtest/gtest.h>

#include "dkm/math/matrix.h"
#include "dkm/math/math_test_helpers.h"

using namespace dkm;

// common inputs and outputs for testing
const double zeros2d[] = { 0, 0 };
const double base2d[] = { 1.1, 2.2 };
const double baseTimesTwo2d[] = { 2.2, 4.4 };
const double addend2d[] = { 2.2, 3.3 };
const double sum2d[] = { 3.3, 5.5 };

const int zeros2i[] = { 0, 0 };
const int base2i[] = { 1, 2 };
const int baseTimesTwo2i[] = { 2, 4 };
const int addend2i[] = { 2, 3 };
const int sum2i[] = { 3, 5 };


// double comparison accuracy
const double DoubleComparisonAccuracy = 0.01;

// size of array comparison
const int ArrayComparisonSize = 2;

TEST_F(Vector2Test, xAxis){
    // arrange
    Vector<2, double> v = Vector<2, double>::xAxis();

    // assert
    double expected[] = { 1.0, 0.0 };
    ASSERT_ARRAY_NEAR_DEF(expected, v.data(), 2);
}

TEST_F(Vector2Test, yAxis){
    // arrange
    Vector<2, double> v = Vector<2, double>::yAxis();

    // assert
    double expected[] = { 0.0, 1.0 };
    ASSERT_ARRAY_NEAR_DEF(expected, v.data(), 2);
}
TEST_F(Vector2Test, defaultConstructor){
    // act
    Vector<2, double> v;

    // assert
    ASSERT_ARRAY_NEAR_DEF(zeros2d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, arrayParamConstructor){
    // act
    Vector<2, double> v(base2d);

    // assert
    ASSERT_TRUE(base2d != v.data());
    ASSERT_ARRAY_NEAR_DEF(base2d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, valueParamConstructor){
    // act
    Vector<2, int> v(3, 4);

    // assert
    ASSERT_EQ(3, v.x);
    ASSERT_EQ(4, v.y);
}

TEST_F(Vector2Test, implicitArrayConstruction){
    // act
    Vector<2, double> v = base2d;

    // assert
    ASSERT_TRUE(base2d != v.data());
    ASSERT_ARRAY_NEAR_DEF(base2d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, copyConstructor){
    // arrange
    Vector<2, double> orig(base2d);

    // act
    Vector<2, double> clone(orig);

    // assert
    ASSERT_TRUE(orig.data() != clone.data());
    ASSERT_ARRAY_NEAR_DEF(base2d, clone.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, assignmentOperator){
    // arrange
    Vector<2, double> orig(base2d);
    Vector<2, double> clone(zeros2d);

    // act
    Vector<2, double> chained = (clone = orig);

    // assert
    ASSERT_TRUE(orig.data() != clone.data());
    ASSERT_ARRAY_NEAR_DEF(base2d, clone.data(), ArrayComparisonSize);
    ASSERT_ARRAY_NEAR_DEF(base2d, chained.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, selfAssignment){
    // arrange
    Vector<2, double> v(base2d);

    // act
    v = v;

    // assert
    ASSERT_ARRAY_NEAR_DEF(base2d, v.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, standardGetters){
    // arrange
    Vector<2, double> v;

    // act/assert
    ASSERT_EQ(2, v.size());
}

TEST_F(Vector2Test, copyTo){
    // arrange
    double dest[] = { 0.0, 0.0 };
    Vector<2, double> v(base2d);

    // act
    v.copyTo(dest);

    // assert
    ASSERT_ARRAY_NEAR(base2d, dest, ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(base2d, v.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, copyFrom){
    // arrange
    double dest[] = { 0.1, 0.2 };
    Vector<2, double> v(base2d);

    // act
    v.copyFrom(dest);

    // assert
    ASSERT_ARRAY_NEAR(dest, v.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, subscriptOperator){
    // arrange
    Vector<2, int> v(zeros2i);

    // act/assert
    v[0] = 1;
    v[1] = 2;

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
}

TEST_F(Vector2Test, subscriptOperator_const){
    // arrange
    const Vector<2, int> v(base2i);

    // act/assert
    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
}

TEST_F(Vector2Test, namedElementReferences){
    // arrange
    Vector<2, int> v(zeros2i);

    // act/assert
    v.x = 1;
    v.y = 2;

    ASSERT_EQ(1, v.x);
    ASSERT_EQ(2, v.y);

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
}

TEST_F(Vector2Test, namedElementReferences_copyConstructor){
    // arrange
    Vector<2, int> orig(zeros2i);
    Vector<2, int> v(orig);

    // act/assert
    v.x = 1;
    v.y = 2;

    ASSERT_EQ(1, v.x);
    ASSERT_EQ(2, v.y);

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
}

TEST_F(Vector2Test, add){
    // arrange
    Vector<2, double> a(base2d);
    Vector<2, double> b(addend2d);

    // act
    Vector<2, double> x = a.add(b);

    // assert
    ASSERT_ARRAY_NEAR(sum2d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(base2d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(addend2d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, addOperator){
    // arrange
    Vector<2, double> a(base2d);
    Vector<2, double> b(addend2d);

    // act
    Vector<2, double> x = a + b;

    // assert
    ASSERT_ARRAY_NEAR(sum2d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(base2d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(addend2d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, addAssign){
    // arrange
    Vector<2, double> a(base2d);
    Vector<2, double> b(addend2d);

    // act
    a.addAssign(b);

    // assert
    ASSERT_ARRAY_NEAR(sum2d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(addend2d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, addAssignOperator){
    // arrange
    Vector<2, double> a(base2d);
    Vector<2, double> b(addend2d);

    // act
    Vector<2, double> x = a += b;

    // assert
    ASSERT_ARRAY_NEAR(sum2d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(sum2d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(addend2d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, subtract){
    // arrange
    Vector<2, int> a(sum2i);
    Vector<2, int> b(addend2i);

    // act
    Vector<2, int> x = a.subtract(b);

    // assert
    ASSERT_ARRAY_NEAR_DEF(base2i, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_NEAR_DEF(sum2i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_NEAR_DEF(addend2i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, subtractOperator){
    // arrange
    Vector<2, int> a(sum2i);
    Vector<2, int> b(addend2i);

    // act
    Vector<2, int> x = a - b;

    // assert
    ASSERT_ARRAY_NEAR_DEF(base2i, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_NEAR_DEF(sum2i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_NEAR_DEF(addend2i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, subtractAssign){
    // arrange
    Vector<2, int> a(sum2i);
    Vector<2, int> b(addend2i);

    // act
    a.subtractAssign(b);

    // assert
    ASSERT_ARRAY_NEAR_DEF(base2i, a.data(), ArrayComparisonSize);

    ASSERT_ARRAY_NEAR_DEF(addend2i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, subtractAssignOperator){
    // arrange
    Vector<2, int> a(sum2i);
    Vector<2, int> b(addend2i);

    // act
    Vector<2, int> x = a -= b;

    // assert
    ASSERT_ARRAY_NEAR_DEF(base2i, x.data(), ArrayComparisonSize);
    ASSERT_ARRAY_NEAR_DEF(base2i, a.data(), ArrayComparisonSize);

    ASSERT_ARRAY_NEAR_DEF(addend2i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, scalarMultiply){
    // arrange
    Vector<2, double> a(base2d);

    // act
    Vector<2, double> x = a.scalarMultiply(2.0);

    // assert
    ASSERT_ARRAY_NEAR_DEF(baseTimesTwo2d, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_NEAR_DEF(base2d, a.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, scalarMultiplyOperator){
    // arrange
    Vector<2, double> a(base2d);

    // act
    Vector<2, double> x = a * 2.0;

    // assert
    ASSERT_ARRAY_NEAR_DEF(baseTimesTwo2d, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_NEAR_DEF(base2d, a.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, scalarMultiplyOperator_scalarFirst){
    // arrange
    Vector<2, double> a(base2d);

    // act
    Vector<2, double> x = 2.0 * a;

    // assert
    ASSERT_ARRAY_NEAR_DEF(baseTimesTwo2d, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_NEAR_DEF(base2d, a.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, scalarMultiplyAssign){
    // arrange
    Vector<2, double> a(base2d);

    // act
    a.scalarMultiplyAssign(2.0);

    // assert
    ASSERT_ARRAY_NEAR_DEF(baseTimesTwo2d, a.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, scalarMultiplyAssignOperator){
    // arrange
    Vector<2, double> a(base2d);

    // act
    Vector<2, double> x = a *= 2.0;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo2d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(baseTimesTwo2d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, magnitude){
    // arrange
    Vector<2, int> a(base2i);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(2.2361, mag, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, magnitude_zeroVector){
    // arrange
    Vector<2, int> a(zeros2i);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(0.0, mag, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, magnitude_negativeValues){
    // arrange
    int negArr[] = { -1, -2 };
    Vector<2, int> a(negArr);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(2.2361, mag, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, normalize){
    // arrange
    // magnitude = 6.0249
    Vector<2, double> a(base2d);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(true, result);

    double normalized[] = { 0.4472, 0.8944 };
    ASSERT_ARRAY_NEAR(normalized, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, normalize_zeroArray){
    // arrange
    Vector<2, double> a(zeros2d);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(false, result);
    ASSERT_ARRAY_NEAR(zeros2d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(Vector2Test, normalize_integerVector){
    // arrange
    Vector<2, int> a(base2i);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(true, result);

    // since every value will be less than one, the array ends up consisting
    // entirely of zeros. This is something the caller will need to be aware of.
    ASSERT_ARRAY_NEAR_DEF(zeros2i, a.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, isNormalized_default){
    // arrange
    float normalizedArr[] = { 0.7071067811, 0.7071067811 };
    float notNormalizedArr[] = { 1.0, 1.0 };

    Vector<2, float> a(normalizedArr);
    Vector<2, float> b(notNormalizedArr);

    // act/assert
    ASSERT_EQ(true, a.isNormalized());
    ASSERT_EQ(false, b.isNormalized());
}

TEST_F(Vector2Test, isNormalized_epsilon){
    // arrange
    float arr[] = { 0.8, 0.8 };

    Vector<2, float> a(arr);

    // act/assert
    ASSERT_EQ(true, a.isNormalized(0.5));
    ASSERT_EQ(false, a.isNormalized(0.01));
}

TEST_F(Vector2Test, dotProduct){
    // arrange
    Vector<2, int> a(base2i);
    Vector<2, int> b(base2i);

    // act
    double dotproduct = a.dot(b);

    // assert
    ASSERT_NEAR(5.0, dotproduct, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR_DEF(base2i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_NEAR_DEF(base2i, b.data(), ArrayComparisonSize);
}

TEST_F(Vector2Test, toString){
    // arrange
    Vector<2, double> v;
    v[0] = 0.012;
    v[1] = 1.0;
    v[2] = 2.0;

    // act
    std::string expected("[ 0.01, 1.00 ]");
    std::string str = v.toString();

    // assert
    ASSERT_EQ(expected, str);
}
