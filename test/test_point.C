#include <cmath>
#include <gtest/gtest.h>
#include <iostream>

#include "Logo.h"
#include "Point.h"
#include "Ray.h"

using namespace sauron;

TEST(PointAddition, add_two_point) {
  Point p1 = {1, 3, 5};
  Point p2 = {1, 3, -2};

  Point p_true = {2, 6, 3};
  Point p3 = p1 + p2;

  EXPECT_EQ(true, p_true == p3);
}


TEST(PointAddition, add_scalar) {
  Point p1 = {1, 3, 5};
  double t = 10;

  Point p_true = {11, 13, 15};
  Point p3 = p1 + t;
  EXPECT_EQ(true, p_true == p3);
}

TEST(PointSubstraction, substract_two_point) {
  Point p1 = {1, 3, 5};
  Point p2 = {1, 3, -2};

  Point p_true = {0, 0, 7};
  Point p3 = p1 - p2;

  EXPECT_EQ(true, p_true == p3);
}

TEST(PointSubstraction, substract_scalar) {
    Point p1 = {1, 3, 5};
    double t = -10;

    Point p_true = {11, 13, 15};
    Point p3 = p1  - t;
    EXPECT_EQ(true, p_true == p3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}