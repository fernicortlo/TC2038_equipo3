#include <cstdio>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>
#include <sstream>

struct Point{
    double x, y;
};

double find_minimum(std::vector<Point> points);
std::vector<Point> sort_points_x(std::vector<Point> list);