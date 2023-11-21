#include "evidencia2.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s %s\n", argv[0], argv[1]);
        return 1;
    }

    std::ifstream file(argv[1]);
    std::vector<Point>  points;
    std::vector<int> matrix;
    int size = 0;

    if (file.is_open()) {
        std::string line;
        int count = 0;
        
        //Read Size of matrix
        file >> size;
        //Read matrix from file
        while (std::getline(file, line) && count < size) {
            std::stringstream linestream(line);
            int num;

            while (linestream >> num) {
                if (num >= 0)
                    matrix.push_back(num);
                else
                    matrix.push_back(INT_MAX);
            }
            count++;
        }

        //Read Points
        Point p;
        while (file >> p.x >> p.y)
            points.push_back(p);
        file.close();
    }

    //Sort the points by its x component
    points = sort_points_x(points);

    int min = find_minimum(points);

    printf("The minimum distance is %d\n", min);

    return 0;
}