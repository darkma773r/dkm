#include <gtest/gtest.h>

#include "dkm/math/matrix.h"

class Vector2Test : public ::testing::Test {

protected:

    // You can do set-up work for each test here.
    Vector2Test(){}

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~Vector2Test(){}

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp(){}

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown(){}
};