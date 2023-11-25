#include "evidencia2.hpp"

static double euclidean(Point A, Point B)
{
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

std::vector<Point> sort_points_x(std::vector<Point> list)
{
    std::sort(list.begin(), list.end(), [](Point a, Point b) {
        return a.x < b.x;});
    return list;
}

static std::vector<Point> sort_points_y(std::vector<Point> list)
{
    std::sort(list.begin(), list.end(), [](Point a, Point b) {
        return a.y < b.y;});
    return list;
}

double find_minimum(std::vector<Point> points)
{
    //La distancia si solo hay 1 punto es infinita
    if (points.size() == 1)
        return (INT_MAX);
    //Encontrar la distancia si solo hay 2 puntos
    if (points.size() == 2)
        return (euclidean(points[0], points[1]));

    //Divide in half
    std::size_t const half_size = points.size() / 2;
    std::vector<Point> left(points.begin(), points.begin() + half_size);
    std::vector<Point> right(points.begin() + half_size, points.end());
    double L = find_minimum(left);
    double R = find_minimum(right);

    double d = L < R ? L : R;
    
    double middle = (points[0].x - points.back().x) / 2;

    //Store points closer than d to the middle line
    std::vector<Point> close;
    for (Point p : points)
        if (abs(p.x - middle) < d)
            close.push_back(p);

    if (close.size() > 2)
    {
        //Sort close list
        close = sort_points_y(close);
        //Find smallest distance in close list
        double ds = find_minimum(close);
        return (d < ds ? d : ds);
    }
    return d;
}

double findNearestServerDistance(const Point& point, const std::vector<Point>& points) {
    double minDistance = std::numeric_limits<double>::max();
    for (const auto& p : points) {
        if (!(p.x == point.x && p.y == point.y)) {  // Ensure it's not the same point
            double distance = euclidean(point, p);
            if (distance < minDistance) {
                minDistance = distance;
            }
        }
    }
    return minDistance;
}

/*
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s %s\n", argv[0], argv[1]);
        return 1;
    }

    std::ifstream file(argv[1]);
    std::vector<Point>  points;

    Point p;
    while (file >> p.x >> p.y)
        points.push_back(p);
    file.close();

    //Sort the points by its x component
    points = sort_points_x(points);

    int min = find_minimum(points);

    printf("The minimum distance is %d\n", min);

    return 0;
}
*/