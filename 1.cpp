#include <iostream>
#include <vector>
#include <cmath>


struct Point
{
    double x;
    double y;
};

std::vector<Point> terribleTrigonometry(unsigned int n)
{
    std::vector<Point> vec;
    //vec.reserve(n);
    //vec.resize(n);
    double angle = 2 * M_PI / n;
    double current_sin = 0;
    double current_cos = 1;
    double s = std::sin(angle);
    double c = std::cos(angle);
    for(int i = 0; i < n; i ++)
    {
        vec.push_back(Point {current_cos, current_sin});
        current_sin = vec[i].y * c + vec[i].x * s;
        current_cos = vec[i].x * c - vec[i].y * s;
    }
    return vec;
}

int main()
{
    unsigned int n;
    std::cin >> n;
    std::vector<Point> v = terribleTrigonometry(n);
    std::cout<< "{";
    for(int i = 0; i < n; i ++)
    {
        std::cout << "{" << round(v[i].x * 10000) / 10000 << ", " << round(v[i].y * 10000) / 10000 << "}";
        if (i < n - 1) std::cout << ", ";
    }
    std::cout << "}";
}
