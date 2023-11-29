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

double findNearestServerDistance(const Point& point, const std::vector<Point>& points, std::vector<Point>& closest) {
    double minDistance = std::numeric_limits<double>::max();
    Point closest_point = Point();
    for (const auto& p : points) {
        if (!(p.x == point.x && p.y == point.y)) {  // Ensure it's not the same point
            double distance = euclidean(point, p);
            if (distance < minDistance) {
                minDistance = distance;
                closest_point = p;
            }
        }
    }
    closest.push_back(closest_point);
    return minDistance;
}