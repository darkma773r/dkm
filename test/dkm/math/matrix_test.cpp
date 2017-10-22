/**
 * matrix_test.cpp
 *
 * Unit tests for the Matrix template class.
 */

#include "dkm/math/matrix_test.h"

#include <iostream>

#include <gtest/gtest.h>

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

// Tests for the Matrix template class.

TEST_F(MatrixTest, defaultConstructor){
    // act
    Matrix<2, 2, double> m;

    // assert
    ASSERT_ARRAY_EQ(zeros4d, m.data(), 4);
}

TEST_F(MatrixTest, paramConstructor){
    // act
    Matrix<2, 2, double> m(base4d);

    // assert
    ASSERT_TRUE(m.data() != base4d);
    ASSERT_ARRAY_EQ(base4d, m.data(), 4);
}

TEST_F(MatrixTest, implicitArrayConstruction){
    // act
    Matrix<2, 2, double> m = base4d;

    // assert
    ASSERT_TRUE(m.data() != base4d);
    ASSERT_ARRAY_EQ(base4d, m.data(), 4);
}

TEST_F(MatrixTest, copyConstructor){
    // arrange
    Matrix<2, 2, double> m(base4d);

    // act
    Matrix<2, 2, double> x(m);

    // assert
    ASSERT_TRUE(x.data() != NULL);
    ASSERT_TRUE(x.data() != m.data());
    ASSERT_ARRAY_EQ(m.data(), x.data(), 4);
}

TEST_F(MatrixTest, identity_squareMatrix){
    // act
    Matrix<4, 4, int> identity = Matrix<4, 4, int>::identity();

    // assert
    int expected[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    ASSERT_ARRAY_EQ(expected, identity.data(), 16);
}

TEST_F(MatrixTest, identity_nonSquareMatrix){
    // act
    Matrix<3, 3, int> identity = Matrix<1, 3, int>::identity();

    // assert
    int expected[] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    };
    ASSERT_ARRAY_EQ(expected, identity.data(), 9);
}

TEST_F(MatrixTest, identity_multiplication){
    // arrange
    int arr[] = {
        3, 4, 5,
        6, 7, 8
    };
    Matrix<2, 3, int> x(arr);
    Matrix<3, 3, int> identity = Matrix<1, 3, int>::identity();

    // act
    Matrix<2, 3, int> result = (x * identity) * identity;

    // assert
    ASSERT_ARRAY_EQ(arr, result.data(), 6);
}

TEST_F(MatrixTest, standardGetters){
    // arrange
    Matrix<3, 2, double> m;

    // act/assert
    ASSERT_EQ(6, m.size());
    ASSERT_EQ(3, m.rows());
    ASSERT_EQ(2, m.cols());
}

TEST_F(MatrixTest, copyFrom){
    // arrange
    Matrix<4, 1, int> m;

    // act
    m.copyFrom(base4i);

    // assert
    ASSERT_ARRAY_EQ(base4i, m.data(), 2);
}

TEST_F(MatrixTest, copyTo){
    // arrange
    int arr[] = { 1, 2 };
    Matrix<2, 1, int> m;
    m[0][0] = 3;
    m[1][0] = 4;

    // act
    m.copyTo(arr);

    // assert
    ASSERT_ARRAY_EQ(m.data(), arr, 2);
}

TEST_F(MatrixTest, assignmentOperator){
    // arrange
    Matrix<2, 2, double> m(base4d);
    Matrix<2, 2, double> x;
    Matrix<2, 2, double> y;

    // act
    y= (x = m);

    // assert
    ASSERT_TRUE(x.data() != m.data());
    ASSERT_ARRAY_EQ(base4d, x.data(), 4);

    ASSERT_TRUE(y.data() != m.data());
    ASSERT_ARRAY_EQ(base4d, y.data(), 4);
}

TEST_F(MatrixTest,  assignmentOperator_selfAssignment){
    // arrange
    Matrix<2, 2, int> m(base4i);
    int * initialArr = m.data();

    // act
    m = m;

    // assert
    // make sure the element array didn't change
    ASSERT_TRUE(initialArr == m.data());
    ASSERT_ARRAY_EQ(base4i, m.data(), 4);
}

TEST_F(MatrixTest, transpose){
    // arrange
    Matrix<2, 2, int> m(base4i);

    // act
    Matrix<2, 2, int> x = m.transpose();

    // assert
    ASSERT_TRUE(x.data() != m.data());

    int expected[] = { 1, 3, 2, 4};
    ASSERT_ARRAY_EQ(expected, x.data(), 4);
}

TEST_F(MatrixTest, subscriptOperator){
    // arrange
    Matrix<2, 2, int> m;

    // act
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    // assert
    ASSERT_ARRAY_EQ(base4i, m.data(), 4);

    ASSERT_EQ(1, m[0][0]);
    ASSERT_EQ(2, m[0][1]);
    ASSERT_EQ(3, m[1][0]);
    ASSERT_EQ(4, m[1][1]);
}

TEST_F(MatrixTest, subscriptOperator_const){
    // arrange
    const Matrix<2, 2, int> m(base4i);

    // act/assert
    ASSERT_EQ(1, m[0][0]);
    ASSERT_EQ(2, m[0][1]);
    ASSERT_EQ(3, m[1][0]);
    ASSERT_EQ(4, m[1][1]);
}

TEST_F(MatrixTest, functorCall){
    // arrange
    Matrix<2, 2, int> m;

    // act
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;

    // assert
    ASSERT_ARRAY_EQ(base4i, m.data(), 4);

    ASSERT_EQ(1, m(0, 0));
    ASSERT_EQ(2, m(0, 1));
    ASSERT_EQ(3, m(1, 0));
    ASSERT_EQ(4, m(1, 1));
}

TEST_F(MatrixTest, functorCall_const){
    // arrange
    const Matrix<2, 2, int> m(base4i);

    // act/assert
    ASSERT_EQ(1, m(0, 0));
    ASSERT_EQ(2, m(0, 1));
    ASSERT_EQ(3, m(1, 0));
    ASSERT_EQ(4, m(1, 1));
}

TEST_F(MatrixTest, add){
    // arrange
    Matrix<2, 2, int> a(base4i);
    Matrix<2, 2, int> b(addend4i);

    // act
    Matrix<2, 2, int> x = a.add(b);

    // assert
    ASSERT_ARRAY_EQ(sum4i, x.data(), 4);

    ASSERT_ARRAY_EQ(base4i, a.data(), 4);
    ASSERT_ARRAY_EQ(addend4i, b.data(), 4);
}

TEST_F(MatrixTest, add_operator){
    // arrange
    Matrix<2, 2, int> a(base4i);
    Matrix<2, 2, int> b(addend4i);

    // act
    Matrix<2, 2, int> x = a + b;

    // assert
    ASSERT_ARRAY_EQ(sum4i, x.data(), 4);

    ASSERT_ARRAY_EQ(base4i, a.data(), 4);
    ASSERT_ARRAY_EQ(addend4i, b.data(), 4);
}

TEST_F(MatrixTest, addAssign){
    // arrange
    Matrix<2, 2, int> a(base4i);
    Matrix<2, 2, int> b(addend4i);

    // act
    a.addAssign(b);

    // assert
    ASSERT_ARRAY_EQ(sum4i, a.data(), 4);

    ASSERT_ARRAY_EQ(addend4i, b.data(), 4);
}

TEST_F(MatrixTest, addAssignOperator){
    // arrange
    Matrix<2, 2, int> a(base4i);

    // act
    Matrix<2, 2, int> x = a += a;

    // assert
    ASSERT_ARRAY_EQ(baseTimesTwo4i, a.data(), 4);
    ASSERT_ARRAY_EQ(baseTimesTwo4i, x.data(), 4);
}

TEST_F(MatrixTest, subtract){
    // arrange
    Matrix<2, 2, int> a(sum4i);
    Matrix<2, 2, int> b(base4i);

    // act
    Matrix<2, 2, int> x = a.subtract(b);

    // assert
    ASSERT_ARRAY_EQ(addend4i, x.data(), 4);

    ASSERT_ARRAY_EQ(sum4i, a.data(), 4);
    ASSERT_ARRAY_EQ(base4i, b.data(), 4);
}

TEST_F(MatrixTest, subtractOperator){
    // arrange
    Matrix<2, 2, int> a(sum4i);
    Matrix<2, 2, int> b(base4i);

    // act
    Matrix<2, 2, int> x = a - b;

    // assert
    ASSERT_ARRAY_EQ(addend4i, x.data(), 4);

    ASSERT_ARRAY_EQ(sum4i, a.data(), 4);
    ASSERT_ARRAY_EQ(base4i, b.data(), 4);
}

TEST_F(MatrixTest, subtractAssign){
    // arrange
    Matrix<2, 2, int> a(sum4i);
    Matrix<2, 2, int> b(base4i);

    // act
    a.subtractAssign(b);

    // assert
    ASSERT_ARRAY_EQ(addend4i, a.data(), 4);

    ASSERT_ARRAY_EQ(base4i, b.data(), 4);
}

TEST_F(MatrixTest, subtractAssignOperator){
    // arrange
    Matrix<2, 2, int> a(sum4i);
    Matrix<2, 2, int> b(base4i);

    // act
    Matrix<2, 2, int> x = a -= b;

    // assert
    ASSERT_ARRAY_EQ(addend4i, x.data(), 4);
    ASSERT_ARRAY_EQ(addend4i, a.data(), 4);

    ASSERT_ARRAY_EQ(base4i, b.data(), 4);
}

TEST_F(MatrixTest, scalarMultiply){
    // arrange
    Matrix<2, 2, double> a(base4d);

    // act
    Matrix<2, 2, double> x = a.scalarMultiply(2.0);

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), 4, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(base4d, a.data(), 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixTest, scalarMultiplyOperator){
    // arrange
    Matrix<2, 2, double> a(base4d);

    // act
    Matrix<2, 2, double> x = a * 2.0;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), 4, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(base4d, a.data(), 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixTest, scalarMultiplyOperator_scalarFirst){
    // arrange
    Matrix<2, 2, double> a(base4d);

    // act
    Matrix<2, 2, double> x =  2.0 * a;

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixTest, scalarMultiplyAssign){
    // arrange
    Matrix<2, 2, double> a(base4d);

    // act
    a.scalarMultiplyAssign(2.0);

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, a.data(), 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixTest, scalarMultiplyAssignOperator){
    // arrange
    Matrix<2, 2, double> a(base4d);

    // act
    Matrix<2, 2, double> x = (a *= 2.0);

    // assert
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, a.data(), 4, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(baseTimesTwo4d, x.data(), 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixTest, multiply_squareMatrices){
    // arrange
    double aArr[] = { 1.1, 2.0, 3.0, 4.0 };
    double bArr[] = { 2.0, 4.0, 6.0, 8.2 };

    Matrix<2, 2, double> a(aArr);
    Matrix<2, 2, double> b(bArr);

    // act
    Matrix<2, 2, double> x = a.multiply(b);

    // assert
    double expected[] = { 14.2, 20.8, 30.0, 44.8 };
    ASSERT_ARRAY_NEAR(expected, x.data(), 4, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(aArr, a.data(), 4, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(bArr, b.data(), 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixTest, multiply_diffSizes_largeResult){
    // arrange
    int aArr[] = { 1, 2, 3 };
    int bArr[] = { 2, 4, 6 };

    Matrix<3, 1, int> a(aArr);
    Matrix<1, 3, int> b(bArr);

    // act
    Matrix<3, 3, int> x = a.multiply(b);

    // assert
    int expected[] = { 2, 4, 6, 4, 8, 12, 6, 12, 18 };
    ASSERT_ARRAY_EQ(expected, x.data(), 9);

    ASSERT_ARRAY_EQ(aArr, a.data(), 3);
    ASSERT_ARRAY_EQ(bArr, b.data(), 3);
}

TEST_F(MatrixTest, multiply_diffSizes_smallResult){
    // arrange
    int aArr[] = { 1, 2, 3 };
    int bArr[] = { 2, 4, 6 };

    Matrix<1, 3,int> a(aArr);
    Matrix<3, 1, int> b(bArr);

    // act
    Matrix<1, 1, int> x = a.multiply(b);

    // assert
    int expected[] = { 28 };
    ASSERT_ARRAY_EQ(expected, x.data(), 1);

    ASSERT_ARRAY_EQ(aArr, a.data(), 3);
    ASSERT_ARRAY_EQ(bArr, b.data(), 3);
}

TEST_F(MatrixTest, multiplyOperator_squareMatrices){
    // arrange
    double aArr[] = { 1.1, 2.0, 3.0, 4.0 };
    double bArr[] = { 2.0, 4.0, 6.0, 8.2 };

    Matrix<2, 2, double> a(aArr);
    Matrix<2, 2, double> b(bArr);

    // act
    Matrix<2, 2, double> x = a * b;

    // assert
    double expected[] = { 14.2, 20.8, 30.0, 44.8 };
    ASSERT_ARRAY_NEAR(expected, x.data(), 4, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(aArr, a.data(), 4, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(bArr, b.data(), 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixTest, multiplyOperator_diffSizes_largeResult){
    // arrange
    int aArr[] = { 1, 2, 3 };
    int bArr[] = { 2, 4, 6 };

    Matrix<3, 1, int> a(aArr);
    Matrix<1, 3, int> b(bArr);

    // act
    Matrix<3, 3, int> x = a * b;

    // assert
    int expected[] = { 2, 4, 6, 4, 8, 12, 6, 12, 18 };
    ASSERT_ARRAY_EQ(expected, x.data(), 9);

    ASSERT_ARRAY_EQ(aArr, a.data(), 3);
    ASSERT_ARRAY_EQ(bArr, b.data(), 3);
}

TEST_F(MatrixTest, multiplyOperator_diffSizes_smallResult){
    // arrange
    int aArr[] = { 1, 2, 3 };
    int bArr[] = { 2, 4, 6 };

    Matrix<1, 3,int> a(aArr);
    Matrix<3, 1, int> b(bArr);

    // act
    Matrix<1, 1, int> x = a * b;

    // assert
    int expected[] = { 28 };
    ASSERT_ARRAY_EQ(expected, x.data(), 1);

    ASSERT_ARRAY_EQ(aArr, a.data(), 3);
    ASSERT_ARRAY_EQ(bArr, b.data(), 3);
}

TEST_F(MatrixTest, multiplyAssign){
    // arrange
    double aArr[] = { 1.1, 2.0, 3.0, 4.0 };
    double bArr[] = { 2.0, 4.0, 6.0, 8.2 };

    Matrix<2, 2, double> a(aArr);
    Matrix<2, 2, double> b(bArr);

    // act
    a.multiplyAssign(b);

    // assert
    double expected[] = { 14.2, 20.8, 30.0, 44.8 };
    ASSERT_ARRAY_NEAR(expected, a.data(), 4, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(bArr, b.data(), 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixTest, multiplyAssignOperator){
    // arrange
    double aArr[] = { 1.1, 2.0, 3.0, 4.0 };
    double bArr[] = { 2.0, 4.0, 6.0, 8.2 };

    Matrix<2, 2, double> a(aArr);
    Matrix<2, 2, double> b(bArr);

    // act
    Matrix<2, 2, double> x = a *= b;

    // assert
    double expected[] = { 14.2, 20.8, 30.0, 44.8 };
    ASSERT_ARRAY_NEAR(expected, x.data(), 4, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(expected, a.data(), 4, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(bArr, b.data(), 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixTest, transformVector){
    // arrange
    double mArr[] = { 1.0, 2.0, 3.0, 4.0, };
    double vArr[] = { 2.0, 3.0 };

    Matrix<2, 2, double> m(mArr);
    Vector<2, double> v(vArr);

    // act
    Vector<2, double> x = m.transformVector(v);

    // assert
    double expected[] = { 8.0, 18.0 };
    ASSERT_ARRAY_NEAR(expected, x.data(), 2, DoubleComparisonAccuracy);

    ASSERT_ARRAY_NEAR(mArr, m.data(), 4, DoubleComparisonAccuracy);
    ASSERT_ARRAY_NEAR(vArr, v.data(), 2, DoubleComparisonAccuracy);
}

TEST_F(MatrixTest, toString_double){
    // arrange
    Matrix<2, 2, double> m;
    m[0][0] = 0.012;
    m[0][1] = 1.0;
    m[1][0] = 2.0;
    m[1][1] = 3.3333;

    // act
    std::string expected("[ 0.01, 1.00,\n  2.00, 3.33 ]");
    std::string str = m.toString();

    // assert
    ASSERT_EQ(expected, str);
}

TEST_F(MatrixTest, toString_Int){
    // arrange
    Matrix<2, 2, int> m;
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    // act
    std::string expected("[ 1, 2,\n  3, 4 ]");
    std::string str = m.toString();

    // assert
    ASSERT_EQ(expected, str);
}
