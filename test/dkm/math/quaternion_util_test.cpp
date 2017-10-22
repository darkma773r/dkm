/**
 * quaternion_util_test.cpp
 *
 * Unit tests for the QuaternionUtil namespace helper functions.
 */

#include "dkm/math/quaternion_util_test.h"

#include <iostream>

#include <gtest/gtest.h>

#include "dkm/math/quaternion.h"
#include "dkm/math/math_test_helpers.h"

using namespace dkm;

// add some macros for degree to radian conversion
#define PI 3.14159265
#define DEG_TO_RAD( x ) ( x * ( PI / 180 ))

// double comparison accuracy
const double DoubleComparisonAccuracy = 0.01;

// size of array comparison
const int ArrayComparisonSize = 4;

TEST_F(QuaternionUtilTest, rotationToQuaternion_NoRotation){
    // arrange
    double vec3[] = { 1.0, 0.0, 0.0 };
    double rotation = 0.0;
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::rotationToQuaternion(vec3, rotation, dest);

    // assert
    ASSERT_EQ(4, written);

    double expected[] = { 0.0, 0.0, 0.0, 1.0 };
    ASSERT_ARRAY_NEAR(expected, dest, ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, rotationToQuaternion_90DegreesAroundXAxis){
    // arrange
    double vec3[] = { 1.0, 0.0, 0.0 };
    double rotation = DEG_TO_RAD(90.0);
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::rotationToQuaternion(vec3, rotation, dest);

    // assert
    ASSERT_EQ(4, written);

    double expected[] = { 0.7071, 0.0, 0.0, 0.7071 };
    ASSERT_ARRAY_NEAR(expected, dest, ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, rotationToQuaternion_90DegreesAroundYAxis){
    // arrange
    double vec3[] = { 0.0, 1.0, 0.0 };
    double rotation = DEG_TO_RAD(90.0);
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::rotationToQuaternion(vec3, rotation, dest);

    // assert
    ASSERT_EQ(4, written);

    double expected[] = { 0.0, 0.7071, 0.0, 0.7071 };
    ASSERT_ARRAY_NEAR(expected, dest, ArrayComparisonSize, DoubleComparisonAccuracy);
}


TEST_F(QuaternionUtilTest, rotationToQuaternion_Minus90DegreesAroundZAxis){
    // arrange
    double vec3[] = { 0.0, 0.0, 1.0 };
    double rotation = DEG_TO_RAD(-90.0);
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::rotationToQuaternion(vec3, rotation, dest);

    // assert
    ASSERT_EQ(4, written);

    double expected[] = { 0.0, 0.0, -0.7071, 0.7071 };
    ASSERT_ARRAY_NEAR(expected, dest, ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, multiply){
    // arrange
    double q[] = { 0.0, 1.0, 0.0, 1.0 };
    double r[] = { 0.5, 0.5, 0.75, 1.0 };
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::multiply(q, r, dest);

    // assert
    ASSERT_EQ(4, written);

    double expected[] = { 1.25, 1.5, 0.25, 0.5 };
    ASSERT_ARRAY_NEAR(expected, dest, ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, ApplyRotation){
    // arrange
    double q[] = { 0.0, 1.0, 0.0, 1.0 };
    double r[] = { 0.5, 0.5, 0.75, 1.0 };
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::multiply(q, r, dest);

    // assert
    ASSERT_EQ(4, written);

    double expected[] = { 1.25, 1.5, 0.25, 0.5 };
    ASSERT_ARRAY_NEAR(expected, dest, ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, applyQuaternionRotation){
    // arrange
    double q[] = { 0.5, 0.5, 0.75, 1.0 };
    double r[] = { 0.0, 1.0, 0.0, 1.0 };
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::applyQuaternionRotation(q, r, dest);

    // assert
    ASSERT_EQ(4, written);

    double expected[] = { 1.25, 1.5, 0.25, 0.5 };
    ASSERT_ARRAY_NEAR(expected, dest, ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, applyQuaternionRotation_AxisRotations){
    // arrange
    double xAxis[] = { 0.7071, 0.0, 0.0, 0.7071 }; // 90 degrees around x axis
    double yAxis[] = { 0.0, 0.7071, 0.0, 0.7071 }; // 90 degrees around y axis
    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::applyQuaternionRotation(xAxis, yAxis, dest);

    // assert
    ASSERT_EQ(4, written);


    double expected[] = { 0.5, 0.5, -0.5, 0.5 };
    ASSERT_ARRAY_NEAR(expected, dest, ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, applyVectorRotation){
    // arrange
    double xAxis[] = { 0.7071, 0.0, 0.0, 0.7071 }; // 90 degrees around x axis

    double yAxis[] = { 0.0, 1.0, 0.0 };
    double yRotation = DEG_TO_RAD(-90); // -90 degrees around y axis

    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::applyVectorRotation(xAxis, yAxis, yRotation, dest);

    // assert
    ASSERT_EQ(4, written);

    double expected[] = { 0.5, -0.5, 0.5, 0.5 };
    ASSERT_ARRAY_NEAR(expected, dest, ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, applyVectorRotation_MultipleRotations){
    // arrange
    double start[] = { 0.0, 0.0, 0.0, 1.0 }; // no rotations

    double xAxis[] = { 1.0, 0.0, 0.0 };
    double xRotation = DEG_TO_RAD(90);

    double yAxis[] = { 0.0, 1.0, 0.0 };
    double yRotation = DEG_TO_RAD(90);

    double dest[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    int written1 = QuaternionUtil::applyVectorRotation(start, xAxis, xRotation, dest);
    int written2 = QuaternionUtil::applyVectorRotation(dest, yAxis, yRotation, dest);

    // assert
    ASSERT_EQ(4, written1);
    ASSERT_EQ(4, written2);

    double expected[] = { 0.5, 0.5, -0.5, 0.5 };
    ASSERT_ARRAY_NEAR(expected, dest, ArrayComparisonSize, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, toRotationMatrix3x3){
    // arrange
    float start[] = { 0.0, 0.7071, 0.0, 0.7071 }; // 90 degrees around y axis
    float dest[] = { 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::toRotationMatrix3x3(start, dest);

    // assert
    ASSERT_EQ(9, written);

    float expected[] = { 0.0, 0.0, 1.0,
                        0.0, 1.0, 0.0,
                        -1.0, 0.0, 0.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 9, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, toRotationMatrix3x3_NonNormalizedQuaternion){
    // arrange
    float start[] = { 0.0, 1.4142, 0.0, 1.4142 }; // non-normalized 90 degrees around y axis
    float dest[] = { 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::toRotationMatrix3x3(start, dest);

    // assert
    ASSERT_EQ(9, written);

    float expected[] = { 0.0, 0.0, 1.0,
                        0.0, 1.0, 0.0,
                        -1.0, 0.0, 0.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 9, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, toRotationMatrix4x4){
    // arrange
    float start[] = { 0.0, 0.7071, 0.0, 0.7071 }; // 90 degrees around y axis
    float dest[] = { 0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::toRotationMatrix4x4(start, dest);

    // assert
    ASSERT_EQ(16, written);

    float expected[] = { 0.0, 0.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        -1.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 1.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 16, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, toRotationMatrix4x4_NonNormalizedQuaternion){
    // arrange
float start[] = { 0.0, 1.4142, 0.0, 1.4142 }; // non-normalized 90 degrees around y axis
    float dest[] = { 0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0 };

    // act
    int written = QuaternionUtil::toRotationMatrix4x4(start, dest);

    // assert
    ASSERT_EQ(16, written);

    float expected[] = { 0.0, 0.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        -1.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 1.0 };
    ASSERT_ARRAY_NEAR(expected, dest, 16, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, testRotations3x3){
    // arrange
    float quat[] = { 0.0, 0.0, 0.0, 1.0 }; // no rotations

    float xAxis[] = { 1.0, 0.0, 0.0 };
    float xRadians = DEG_TO_RAD(90.0);

    float yAxis[] = { 0.0, 1.0, 0.0 };
    float yRadians = DEG_TO_RAD(90.0);

    float zAxis[] = { 0.0, 0.0, 1.0 };
    float zRadians = DEG_TO_RAD(45.0);

    float transformMatrix[] = { 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0 };

    float vec3[] = { 0.0, 1.0, 0.0 };
    float result3[] = { 0.0, 0.0, 0.0 };

    // act
    QuaternionUtil::applyVectorRotation(quat, xAxis, xRadians, quat);
    QuaternionUtil::applyVectorRotation(quat, yAxis, yRadians, quat);
    QuaternionUtil::applyVectorRotation(quat, zAxis, zRadians, quat);
    QuaternionUtil::toRotationMatrix3x3(quat, transformMatrix);

    MatrixUtil::matrixMultiply(transformMatrix, 3, 3, vec3, 1, result3);

    // assert
    float expected[] = { 0.7071, 0.7071, 0.0 };
    ASSERT_ARRAY_NEAR(expected, result3, 3, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, testRotations3x3_NonAxisRotations){
    // arrange
    float quat[] = { 0.0, 0.0, 0.0, 1.0 }; // no rotations

    float rotationVector1[] = { 2.0, 2.0, 0.0 };
    float rotationRadians1 = DEG_TO_RAD(90.0);

    float transformMatrix[] = { 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0 };

    float vec3[] = { 0.0, 1.0, 0.0, 1.0 };
    float result3[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    QuaternionUtil::applyVectorRotation(quat, rotationVector1, rotationRadians1, quat);
    QuaternionUtil::toRotationMatrix3x3(quat, transformMatrix);

    MatrixUtil::matrixMultiply(transformMatrix, 3, 3, vec3, 1, result3);

    // assert
    float expected[] = { 0.5, 0.5, 0.7071 };
    ASSERT_ARRAY_NEAR(expected, result3, 3, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, testRotations4x4){
    // arrange
    float quat[] = { 0.0, 0.0, 0.0, 1.0 }; // no rotations

    float xAxis[] = { 1.0, 0.0, 0.0 };
    float xRadians = DEG_TO_RAD(90.0);

    float yAxis[] = { 0.0, 1.0, 0.0 };
    float yRadians = DEG_TO_RAD(90.0);

    float zAxis[] = { 0.0, 0.0, 1.0 };
    float zRadians = DEG_TO_RAD(45.0);

    float transformMatrix[] = { 0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0 };

    float vec4[] = { 0.0, 1.0, 0.0, 1.0 };
    float result4[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    QuaternionUtil::applyVectorRotation(quat, xAxis, xRadians, quat);
    QuaternionUtil::applyVectorRotation(quat, yAxis, yRadians, quat);
    QuaternionUtil::applyVectorRotation(quat, zAxis, zRadians, quat);
    QuaternionUtil::toRotationMatrix4x4(quat, transformMatrix);

    MatrixUtil::matrixMultiply(transformMatrix, 4, 4, vec4, 1, result4);

    // assert
    float expected[] = { 0.7071, 0.7071, 0.0, 1.0 };
    ASSERT_ARRAY_NEAR(expected, result4, 4, DoubleComparisonAccuracy);
}

TEST_F(QuaternionUtilTest, testRotations4x4_NonAxisRotations){
    // arrange
    float quat[] = { 0.0, 0.0, 0.0, 1.0 }; // no rotations

    float rotationVector1[] = { 2.0, 2.0, 0.0 };
    float rotationRadians1 = DEG_TO_RAD(90.0);

    float transformMatrix[] = { 0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0 };

    float vec4[] = { 0.0, 1.0, 0.0, 1.0 };
    float result4[] = { 0.0, 0.0, 0.0, 0.0 };

    // act
    QuaternionUtil::applyVectorRotation(quat, rotationVector1, rotationRadians1, quat);
    QuaternionUtil::toRotationMatrix4x4(quat, transformMatrix);

    MatrixUtil::matrixMultiply(transformMatrix, 4, 4, vec4, 1, result4);

    // assert
    float expected[] = { 0.5, 0.5, 0.7071, 1.0 };
    ASSERT_ARRAY_NEAR(expected, result4, 4, DoubleComparisonAccuracy);
}