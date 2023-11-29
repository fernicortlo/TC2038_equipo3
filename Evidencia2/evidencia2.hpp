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

// tsp
int minCost(int current_node, const std::vector<std::vector<int>>& matrix, const std::vector<bool>& visited);
void find_path(int node, int length, int currentCost, int &min, const std::vector<std::vector<int>>& matrix, int *path, std::vector<bool> &visited);
int tsp_solve(int size, const std::vector<std::vector<int>>& matrix);

// kruskal
class Edge {
public:
    int source;
    int dest;
    int weight;
};

void kruskal(const std::string& filename);

// geometry
double findNearestServerDistance(const Point& currentPoint, const std::vector<Point>& points, std::vector<Point>& closest);
