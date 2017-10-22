/**
 * matrix_util_test.cpp
 *
 * Unit tests for the MatrixUtil namespace helper functions.
 */

#include "dkm/math/matrix_util_test.h"

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


const double doubleArr[] = { 1.1, 2.2, 3.3, 4.4 };

// double comparison accuracy
const double DoubleComparisonAccuracy = 0.0001;

TEST_F(MatrixUtilTest, copy){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0 };

    // act

    // only use part of the array to ensure the bounds are correct
    int written =  MatrixUtil::copy(doubleArr, dest, 2);

    // assert
    ASSERT_EQ(2, written);
    double expected[] = { 1.1, 2.2, 0.0 };
    ASSERT_ARRAY_EQ(expected, dest, 3);
}

TEST_F(MatrixUtilTest, copy_noSize){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0 };

    // act
    int written = MatrixUtil::copy(doubleArr, dest, 0);

    // assert
    ASSERT_EQ(0, written);
    double expected[] = { 0.0, 0.0, 0.0 };
    ASSERT_ARRAY_EQ(expected, dest, 3);
}

TEST_F(MatrixUtilTest, set){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0 };

    // act

    // only use part of the array to ensure the bounds are correct
    int written = MatrixUtil::set(dest, 1.0, 2);

    // assert
    ASSERT_EQ(2, written);
    double expected[] = { 1.0, 1.0, 0.0 };
    ASSERT_ARRAY_EQ(expected, dest, 3);
}

TEST_F(MatrixUtilTest, set_noSize){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0 };

    // act
    int written = MatrixUtil::set(dest, 1.0, 0);

    // assert
    ASSERT_EQ(0, written);
    double expected[] = { 0.0, 0.0, 0.0 };
    ASSERT_ARRAY_EQ(expected, dest, 3);
}

TEST_F(MatrixUtilTest, add){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0 };

    // act

    // only use part of the array to ensure the bounds are correct
    int written = MatrixUtil::add(doubleArr, doubleArr, dest, 2);

    // assert
    ASSERT_EQ(2, written);
    double expected[] = { 2.2, 4.4, 0.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 3, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, add_noSize){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0 };

    // act
    int written = MatrixUtil::add(doubleArr, doubleArr, dest, 0);

    // assert
    ASSERT_EQ(0, written);
    double expected[] = { 0.0, 0.0, 0.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 3, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, sub){
    // arrange
    double dest[] = { 1.0, 1.0, 1.0 };

    // act

    // only use part of the array to ensure the bounds are correct
    int written = MatrixUtil::subtract(doubleArr, doubleArr, dest, 2);

    // assert
    ASSERT_EQ(2, written);
    double expected[] = { 0.0, 0.0, 1.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 3, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, sub_noSize){
    // arrange
    double dest[] = { 1.0, 1.0, 1.0 };

    // act
    int written = MatrixUtil::subtract(doubleArr, doubleArr, dest, 0);

    // assert
    ASSERT_EQ(0, written);
    double expected[] = { 1.0, 1.0, 1.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 3, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, scalarMultiply){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0 };

    // act

    // only use part of the array to ensure the bounds are correct
    int written = MatrixUtil::scalarMultiply(doubleArr, 2.0, dest, 2);

    // assert
    ASSERT_EQ(2, written);
    double expected[] = { 2.2, 4.4, 0.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 3, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, scalarMultiply_noSize){
    // arrange
    double dest[] = { 0.0, 0.0, 0.0 };

    // act
    int written = MatrixUtil::scalarMultiply(doubleArr, 2.0, dest, 0);

    // assert
    ASSERT_EQ(0, written);
    double expected[] = { 0.0, 0.0, 0.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 3, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, transpose){
    // arrange
    double input[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    double dest[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    // act

    // only use part of the array to ensure the bounds are correct
    int written = MatrixUtil::transpose(input, 2, 3, dest);

    // assert
    ASSERT_EQ(6, written);
    double expected[] = { 1.0, 4.0, 2.0, 5.0, 3.0, 6.0, 0.0 };
    ASSERT_ARRAY_EQ(expected, dest, 7);
}

TEST_F(MatrixUtilTest, transpose_NoRows){
    // arrange
    double input[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    double dest[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    // act

    // only use part of the array to ensure the bounds are correct
    int written = MatrixUtil::transpose(input, 0, 3, dest);

    // assert
    ASSERT_EQ(0, written);
    double expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    ASSERT_ARRAY_EQ(expected, dest, 7);
}

TEST_F(MatrixUtilTest, transpose_NoCols){
    // arrange
    double input[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    double dest[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    // act

    // only use part of the array to ensure the bounds are correct
    int written = MatrixUtil::transpose(input, 2, 0, dest);

    // assert
    ASSERT_EQ(0, written);
    double expected[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    ASSERT_ARRAY_EQ(expected, dest, 7);
}

TEST_F(MatrixUtilTest, matrixMultiply){
    // arrange
    int a[] = { 3, 2, 1, 4, -5, 6 }; // 2x3 matrix
    int b[] = { 2, 1, 7, -4, 8, 0 }; // 3x2 matrix
    int dest[] = { 0, 0, 0, 0, 0, 0 };

    // act
    int written = MatrixUtil::matrixMultiply(a, 2, 3, b, 2, dest);

    // assert
    ASSERT_EQ(4, written);

    int expected[] = { 28, -5, 21, 24, 0, 0 };
    ASSERT_ARRAY_EQ(expected, dest, 6);
}

TEST_F(MatrixUtilTest, matrixMultiply_NoInputRows){
    // arrange
    int a[] = { 3, 2, 1, 4, -5, 6 }; // 2x3 matrix
    int b[] = { 2, 1, 7, -4, 8, 0 }; // 3x2 matrix
    int dest[] = { 9, 9, 9, 9, 9, 9 };

    // act
    int written = MatrixUtil::matrixMultiply(a, 0, 3, b, 2, dest);

    // assert
    ASSERT_EQ(0, written);

    int expected[] = { 9, 9, 9, 9, 9, 9 };
    ASSERT_ARRAY_EQ(expected, dest, 6);
}

TEST_F(MatrixUtilTest, matrixMultiply_NoInputCols){
    // arrange
    int a[] = { 3, 2, 1, 4, -5, 6 }; // 2x3 matrix
    int b[] = { 2, 1, 7, -4, 8, 0 }; // 3x2 matrix
    int dest[] = { 9, 9, 9, 9, 9, 9 };

    // act
    int written = MatrixUtil::matrixMultiply(a, 2, 0, b, 2, dest);

    // assert
    ASSERT_EQ(0, written);
    int expected[] = { 9, 9, 9, 9, 9, 9 };
    ASSERT_ARRAY_EQ(expected, dest, 6);
}

TEST_F(MatrixUtilTest, matrixMultiply_NoOutputCols){
    // arrange
    int a[] = { 3, 2, 1, 4, -5, 6 }; // 2x3 matrix
    int b[] = { 2, 1, 7, -4, 8, 0 }; // 3x2 matrix
    int dest[] = { 9, 9, 9, 9, 9, 9 };

    // act
    int written = MatrixUtil::matrixMultiply(a, 2, 3, b, 0, dest);

    // assert
    ASSERT_EQ(0, written);

    int expected[] = { 9, 9, 9, 9, 9, 9 };
    ASSERT_ARRAY_EQ(expected, dest, 6);
}

TEST_F(MatrixUtilTest, identity){
    // arrange

    // add an extra element at the end to make sure that we
    // don't write more than needed
    int out[] = { 
        5, 5, 5, 
        5, 5, 5,
        5, 5, 5, 9 
    };

    // act
    size_t written = MatrixUtil::identity(3, out);

    // assert
    int expected[] = { 
        1, 0, 0,
        0, 1, 0,
        0, 0, 1, 9 
    };	

    ASSERT_ARRAY_EQ(expected, out, 10);
}

TEST_F(MatrixUtilTest, vectorMagnitude){
    // arrange
    int a[] = { 2, 3, 4 };

    // act
    double result = MatrixUtil::vectorMagnitude(a, 3);

    // assert
    ASSERT_NEAR(5.3852, result, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, vectorMagnitude_NoSize){
    // arrange
    int a[] = { 2, 3, 4 };

    // act
    double result = MatrixUtil::vectorMagnitude(a, 0);

    // assert
    ASSERT_NEAR(0.0, result, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, isVectorNormalized_DefaultEpsilon){
    // arrange
    double normalized[] = { 0.70710678, 0.0, 0.70710678 };
    double notNormalized[] = { 1.0, 1.0, 1.0 };

    // act/assert
    ASSERT_EQ(0.000001, MatrixUtil::DEFAULT_NORMALIZED_EPSILON);
    ASSERT_EQ(true, MatrixUtil::isVectorNormalized(normalized, 3));
    ASSERT_EQ(false, MatrixUtil::isVectorNormalized(notNormalized, 3));
}

TEST_F(MatrixUtilTest, isVectorNormalized_ProvidedEpsilon){
    // arrange
    double arr[] = { 0.8, 0.0, 0.8 };

    // act/assert
    ASSERT_EQ(true, MatrixUtil::isVectorNormalized(arr, 3, 0.5));
    ASSERT_EQ(false, MatrixUtil::isVectorNormalized(arr, 0.01));
}

TEST_F(MatrixUtilTest, vectorNormalize){
    // arrange
    double a[] = { 2.0, 3.0, 4.0 };
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = MatrixUtil::vectorNormalize(a, 3, dest);

    // assert
    ASSERT_EQ(3, written);

    double expected[] = { 0.3714, 0.5571, 0.7428, 0.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, vectorNormalize_NoSize){
    // arrange
    double a[] = { 2.0, 3.0, 4.0 };
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = MatrixUtil::vectorNormalize(a, 0, dest);

    // assert
    ASSERT_EQ(0, written);

    double expected[] = { 0.0, 0.0, 0.0, 0.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, vectorDotProduct){
    // arrange
    double a[] = { 2.0, 3.0, 4.0 };
    double b[] = { 3.0, 4.0, 5.0 };

    // act
    double dotproduct = MatrixUtil::vectorDotProduct(a, b, 3);

    // assert
    ASSERT_NEAR(38.0, dotproduct, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, vectorDotProduct_NoSize){
    // arrange
    double a[] = { 2.0, 3.0, 4.0 };
    double b[] = { 3.0, 4.0, 5.0 };

    // act
    double dotproduct = MatrixUtil::vectorDotProduct(a, b, 0);

    // assert
    ASSERT_NEAR(0.0, dotproduct, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, vectorCrossProduct){
    // arrange
    double a[] = { 2.0, 3.0, 4.0 };
    double b[] = { 5.0, 6.0, 7.0 };
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = MatrixUtil::vectorCrossProduct(a, b, dest);

    // assert
    ASSERT_EQ(3, written);
    double expected[] = { -3.0, 6.0, -3.0, 0.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, vectorCrossProduct_OppositeOrder){
    // arrange
    double a[] = { 2.0, 3.0, 4.0 };
    double b[] = { 5.0, 6.0, 7.0 };
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = MatrixUtil::vectorCrossProduct(b, a, dest);

    // assert
    ASSERT_EQ(3, written);
    double expected[] = { 3.0, -6.0, 3.0, 0.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 4, DoubleComparisonAccuracy);
}

TEST_F(MatrixUtilTest, toString){
    // act
    std::string str = MatrixUtil::toString(doubleArr, 4, 1);

    // assert
    std::string expected = "[ 1.10,\n  2.20,\n  3.30,\n  4.40 ]";
    ASSERT_EQ(expected, str);
}

TEST_F(MatrixUtilTest, toString_OneRow){
    // act
    std::string str = MatrixUtil::toString(doubleArr, 1, 4);

    // assert
    std::string expected = "[ 1.10, 2.20, 3.30, 4.40 ]";
    ASSERT_EQ(expected, str);
}

TEST_F(MatrixUtilTest, toString_NoRows){
    // act
    std::string str = MatrixUtil::toString(doubleArr, 0, 4);

    // assert
    std::string expected = "[ ]";
    ASSERT_EQ(expected, str);
}

TEST_F(MatrixUtilTest, toString_NoCols){
    // act
    std::string str = MatrixUtil::toString(doubleArr, 1, 0);

    // assert
    std::string expected = "[ ]";
    ASSERT_EQ(expected, str);
}
