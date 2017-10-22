/**
 * vector_test.cpp
 *
 * Unit tests for the Vector template class.
 */

#include "dkm/math/vector_test.h"

#include <iostream>

#include <gtest/gtest.h>

#include "dkm/math/matrix.h"
#include "dkm/math/math_test_helpers.h"

using namespace dkm;

// common inputs and outputs for testing
const double zeros6d[] = { 0, 0, 0, 0, 0, 0 };
const double base6d[] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 };
const double baseTimesTwo6d[] = { 2.2, 4.4, 6.6, 8.8, 11.0, 13.2 };
const double addend6d[] = { 2.2, 3.3, 4.4, 5.5, 6.6, 7.7 };
const double sum6d[] = { 3.3, 5.5, 7.7, 9.9, 12.1, 14.3 };

const int zeros6i[] = { 0, 0, 0, 0, 0, 0 };
const int base6i[] = { 1, 2, 3, 4, 5, 6 };
const int baseTimesTwo6i[] = { 2, 4, 6, 8, 10, 12 };
const int addend6i[] = { 2, 3, 4, 5, 6, 7 };
const int sum6i[] = { 3, 5, 7, 9, 11, 13 };


// double comparison accuracy
const double DoubleComparisonAccuracy = 0.01;

// size of array comparison
const int ArrayComparisonSize = 4;

TEST_F(VectorTest, defaultConstructor){
    // act
    Vector<6, double> v;

    // assert
    ASSERT_ARRAY_EQ(zeros6d, v.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, parameterizedConstructor){
    // act
    Vector<6, double> v(base6d);

    // assert
    ASSERT_TRUE(base6d != v.data());
    ASSERT_ARRAY_EQ(base6d, v.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, implicitArrayConstruction){
    // act
    Vector<6, double> v = base6d;

    // assert
    ASSERT_TRUE(base6d != v.data());
    ASSERT_ARRAY_EQ(base6d, v.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, copyConstructor){
    // arrange
    Vector<6, double> orig(base6d);

    // act
    Vector<6, double> clone(orig);

    // assert
    ASSERT_TRUE(orig.data() != clone.data());
    ASSERT_ARRAY_EQ(base6d, clone.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, assignmentOperator){
    // arrange
    Vector<6, double> orig(base6d);
    Vector<6, double> clone(zeros6d);

    // act
    Vector<6, double> chained = (clone = orig);

    // assert
    ASSERT_TRUE(orig.data() != clone.data());
    ASSERT_ARRAY_EQ(base6d, clone.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base6d, chained.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, selfAssignment){
    // arrange
    Vector<6, double> v(base6d);

    // act
    v = v;

    // assert
    ASSERT_ARRAY_EQ(base6d, v.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, standardGetters){
    // arrange
    Vector<6, double> v;

    // act/assert
    ASSERT_EQ(6, v.size());
}

TEST_F(VectorTest, copyTo){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    Vector<6, double> v(base6d);

    // act
    v.copyTo(dest);

    // assert
    ASSERT_ARRAY_EQ(base6d, dest, ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base6d, v.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, copyFrom){
    // arrange
    double dest[] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6 };
    Vector<6, double> v(base6d);

    // act
    v.copyFrom(dest);

    // assert
    ASSERT_ARRAY_EQ(dest, v.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, subscriptOperator){
    // arrange
    Vector<6, int> v(zeros6i);

    // act/assert
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v[4] = 5;
    v[5] = 6;

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
    ASSERT_EQ(5, v[4]);
    ASSERT_EQ(6, v[5]);
}

TEST_F(VectorTest, subscriptOperator_const){
    // arrange
    const Vector<6, int> v(base6i);

    // act/assert
    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
    ASSERT_EQ(5, v[4]);
    ASSERT_EQ(6, v[5]);
}

TEST_F(VectorTest, add){
    // arrange
    Vector<6, double> a(base6d);
    Vector<6, double> b(addend6d);

    // act
    Vector<6, double> x = a.add(b);

    // assert
    ASSERT_ARRAY_NEAR(sum6d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(base6d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(addend6d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(VectorTest, addOperator){
    // arrange
    Vector<6, double> a(base6d);
    Vector<6, double> b(addend6d);

    // act
    Vector<6, double> x = a + b;

    // assert
    ASSERT_ARRAY_NEAR(sum6d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(base6d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(addend6d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(VectorTest, addAssign){
    // arrange
    Vector<6, double> a(base6d);
    Vector<6, double> b(addend6d);

    // act
    a.addAssign(b);

    // assert
    ASSERT_ARRAY_NEAR(sum6d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(addend6d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(VectorTest, addAssignOperator){
    // arrange
    Vector<6, double> a(base6d);
    Vector<6, double> b(addend6d);

    // act
    Vector<6, double> x = a += b;

    // assert
    ASSERT_ARRAY_NEAR(sum6d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(sum6d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(addend6d, b.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(VectorTest, subtract){
    // arrange
    Vector<6, int> a(sum6i);
    Vector<6, int> b(addend6i);

    // act
    Vector<6, int> x = a.subtract(b);

    // assert
    ASSERT_ARRAY_EQ(base6i, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(sum6i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(addend6i, b.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, subtractOperator){
    // arrange
    Vector<6, int> a(sum6i);
    Vector<6, int> b(addend6i);

    // act
    Vector<6, int> x = a - b;

    // assert
    ASSERT_ARRAY_EQ(base6i, x.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(sum6i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(addend6i, b.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, subtractAssign){
    // arrange
    Vector<6, int> a(sum6i);
    Vector<6, int> b(addend6i);

    // act
    a.subtractAssign(b);

    // assert

    ASSERT_ARRAY_EQ(base6i, a.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(addend6i, b.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, subtractAssignOperator){
    // arrange
    Vector<6, int> a(sum6i);
    Vector<6, int> b(addend6i);

    // act
    Vector<6, int> x = a -= b;

    // assert
    ASSERT_ARRAY_EQ(base6i, x.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base6i, a.data(), ArrayComparisonSize);

    ASSERT_ARRAY_EQ(addend6i, b.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, scalarMultiply){
    // arrange
    Vector<6, double> a(base6d);

    // act
    Vector<6, double> x = a.scalarMultiply(2.0);

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo6d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base6d, a.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, scalarMultiplyOperator){
    // arrange
    Vector<6, double> a(base6d);

    // act
    Vector<6, double> x = a * 2.0;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo6d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base6d, a.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, scalarMultiplyOperator_scalarFirst){
    // arrange
    Vector<6, double> a(base6d);

    // act
    Vector<6, double> x = 2.0 * a;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo6d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);

    ASSERT_ARRAY_EQ(base6d, a.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, scalarMultiplyAssign){
    // arrange
    Vector<6, double> a(base6d);

    // act
    a.scalarMultiplyAssign(2.0);

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo6d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(VectorTest, scalarMultiplyAssignOperator){
    // arrange
    Vector<6, double> a(base6d);

    // act
    Vector<6, double> x = a *= 2.0;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo6d, x.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(baseTimesTwo6d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(VectorTest, magnitude){
    // arrange
    Vector<6, int> a(base6i);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(9.53939, mag, DoubleComparisonAccuracy);
}

TEST_F(VectorTest, magnitude_zeroVector){
    // arrange
    Vector<6, int> a(zeros6i);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(0.0, mag, DoubleComparisonAccuracy);
}

TEST_F(VectorTest, magnitude_negativeValues){
    // arrange
    int negArr[] = { -1, -2, -3, -4, -5, -6 };
    Vector<6, int> a(negArr);

    // act
    double mag = a.magnitude();

    // assert
    ASSERT_NEAR(9.53939, mag, DoubleComparisonAccuracy);
}

TEST_F(VectorTest, normalize){
    // arrange
    // magnitude = 10.49333
    Vector<6, double> a(base6d);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(true, result);

    double normalized[] = { 0.1048, 0.2096, 0.3145, 0.4193, 0.52414, 0.62897 };
    ASSERT_ARRAY_NEAR(normalized, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(VectorTest, normalize_zeroArray){
    // arrange
    Vector<6, double> a(zeros6d);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(false, result);
    ASSERT_ARRAY_NEAR(zeros6d, a.data(), ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(VectorTest, normalize_integerVector){
    // arrange
    Vector<6, int> a(base6i);

    // act
    bool result = a.normalize();

    // assert
    ASSERT_EQ(true, result);

    // since every value will be less than one, the array ends up consisting
    // entirely of zeros. This is something the caller will need to be aware of.
    ASSERT_ARRAY_EQ(zeros6i, a.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, isNormalized_default){
    // arrange
    float normalizedArr[] = { 0.0, 0.0, 0.0, 0.0, 0.7071067811865476, 0.7071067811865476 };
    float notNormalizedArr[] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0 };

    Vector<6, float> a(normalizedArr);
    Vector<6, float> b(notNormalizedArr);

    // act/assert
    ASSERT_EQ(true, a.isNormalized());
    ASSERT_EQ(false, b.isNormalized());
}

TEST_F(VectorTest, isNormalized_epsilon){
    // arrange
    float arr[] = { 0.0, 0.0, 0.0, 0.0, 0.8, 0.8 };

    Vector<6, float> a(arr);

    // act/assert
    ASSERT_EQ(true, a.isNormalized(0.5));
    ASSERT_EQ(false, a.isNormalized(0.01));
}

TEST_F(VectorTest, dotProduct){
    // arrange
    Vector<6, int> a(base6i);
    Vector<6, int> b(base6i);

    // act
    double dotproduct = a.dot(b);

    // assert
    ASSERT_NEAR(91.0, dotproduct, DoubleComparisonAccuracy);
    ASSERT_ARRAY_EQ(base6i, a.data(), ArrayComparisonSize);
    ASSERT_ARRAY_EQ(base6i, b.data(), ArrayComparisonSize);
}

TEST_F(VectorTest, toString){
    // arrange
    Vector<6, double> v;
    v[0] = 0.012;
    v[1] = 1.0;
    v[2] = 2.0;
    v[3] = 3.3333;
    v[4] = 4.0;
    v[5] = 5.0;

    // act
    std::string expected("[ 0.01, 1.00, 2.00, 3.33, 4.00, 5.00 ]");
    std::string str = v.toString();

    // assert
    ASSERT_EQ(expected, str);
}

