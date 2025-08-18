#include <gtest/gtest.h>
#include <optional>

#include "Solver.h"
#include "Ray.h"
#include "Point.h"

using namespace sauron;

TEST(TriangleSolverTest, ray_hitting_triangle) {
    std::vector<Point> triangle = {
            {0.0, 0.0, 0.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}
    };

    Point starting_point = {0.25, 0.25, 1.0};
    Point direction = {0.0, 0.0, -1};

    Ray ray(starting_point, direction);

    Solver solver;
    auto result = solver.triangleSolver(ray, triangle);

    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(result.value(), 1.0, 1e-9);
}


TEST(TriangleSolverTest, ray_misses_triangle) {
    std::vector<Point> triangle = {
            {0.0, 0.0, 0.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}
    };

    Point starting_point = {0.25, 0.25, 1.0};
    Point direction = {0.0, 0.0, 0.0};

    Ray ray(starting_point, direction);

    Solver solver;
    auto result = solver.triangleSolver(ray, triangle);

    EXPECT_FALSE(result.has_value());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}