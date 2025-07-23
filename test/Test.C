#include "Vector.h"
#include "Logo.h"

#include <gtest/gtest.h>
#include <cmath>
#include<iostream>

TEST(Vector3DTest, DotProduct) {
    Vector3D v1(1, 3, 5);
    Vector3D v2(1, 3, -2);
    EXPECT_EQ(v1.dotProduct(v2), 0);
}

TEST(Vector3DTest, Norm) {
    Vector3D v(1, 1, 1);
    EXPECT_DOUBLE_EQ(v._norm, std::sqrt(3));
}

TEST(Vector3DTest, Subtraction) {
    Vector3D v(1, 1, 1);
    v = v - 1.0;
    EXPECT_EQ(v._vector, Vector3D(0, 0, 0)._vector);
}

TEST(Vector3DTest, ScalarAddition) {
    Vector3D v(1, 1, 1);
    v = v + 2.0;
    EXPECT_EQ(v._vector, Vector3D(3, 3, 3)._vector);
}

TEST(Vector3DTest, VectorAddition) {
    Vector3D v1(1, 1, 1);
    Vector3D v2(1, 1, 1);
    auto v3 = addVectors(v1,v2);
    EXPECT_EQ(v3._vector, Vector3D(2, 2, 2)._vector);
}
TEST(Vector3DTest, Multiplication) {
    Vector3D v(1, 1, 1);
    v=v * 2.0;
    EXPECT_EQ(v._vector, Vector3D(2, 2, 2)._vector);
}

TEST(Vector3DTest, Division) {
    Vector3D v(1, 1, 1);
    v=v / 0.5;
    EXPECT_EQ(v._vector, Vector3D(2, 2, 2)._vector);
}

int main(int argc, char **argv) {
    printLogo();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
