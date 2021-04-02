#include <iostream>
#include <set>
#include <algorithm>
#include <iomanip>
#include <limits.h>
#include <memory>
#include <vector>
#include <fstream>
#include <chrono>
#include "macros.h"
#include "classes_contour.h"
#include "utilities.h"
#include "stripe_contour.h"

double frame_left;
double frame_right;

int main()
{
    std::set<Rectangle, cmp_rectangle> R;
    std::multiset<Edge, cmp_edge> H;
    int n;
    std::cin >> n;

    std::ofstream file1;
    file1.open("input.txt", std::ios::out);

    for (int i = 0; i < n; i++)
    {
        Rectangle r;
        double x1;
        double x2;
        double y1;
        double y2;
        std::cin >> x1;
        std::cin >> x2;

        if (x1 > x2)
        {
            r.x_left = x2;
            r.x_right = x1;
        }
        else
        {
            r.x_left = x1;
            r.x_right = x2;
        }

        std::cin >> y1;
        std::cin >> y2;

        if (y1 > y2)
        {
            r.y_bottom = y2;
            r.y_top = y1;
        }
        else
        {
            r.y_bottom = y1;
            r.y_top = y2;
        }
        file1 << x1 << " " << x2 << " " << y1 << " " << y2 << std::endl;
        Edge bottom;
        bottom.coord = r.y_bottom;
        bottom.side = BOTTOM_EDGE;
        bottom.interval.bottom = r.x_left;
        bottom.interval.top = r.x_right;

        Edge top;
        top.coord = r.y_top;
        top.side = TOP_EDGE;
        top.interval.bottom = r.x_left;
        top.interval.top = r.x_right;

        H.insert(bottom);
        H.insert(top);
        R.insert(r);
    }
    file1.close();

    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    std::set<Stripe, cmp_stripe> S;

    rectangle_dac(R, S);
    std::set<Line_Segment, cmp_line_segment> HS = horizontal_contour(H, S);

    std::vector<std::vector<double>> contour_points;
    double perimeter = 0;

    for (auto hs : HS)
    {
        perimeter = perimeter + hs.interval.top - hs.interval.bottom;

        contour_points.push_back({hs.interval.bottom, hs.coord});
        contour_points.push_back({hs.interval.top, hs.coord});
    }

    std::sort(contour_points.begin(), contour_points.end(), [](const auto &a, const auto &b) {
        if (a[0] == b[0])
            return a[1] < b[1];
        return a[0] < b[0];
    });

    std::set<Line_Segment, cmp_line_segment> VS;

    int i = 0, j = 1;
    while (j < contour_points.size())
    {
        perimeter = perimeter + contour_points[j][1] - contour_points[i][1];
        Line_Segment l;
        l.coord = contour_points[i][0];
        l.interval.bottom = contour_points[i][1];
        l.interval.top = contour_points[j][1];
        VS.insert(l);
        i += 2;
        j += 2;
    }

    std::cout << std::setprecision(20) << "Perimeter: " << perimeter << std::endl;
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << std::setprecision(5) << ms_double.count() << "ms" << std::endl;

    std::ofstream file;
    file.open("output.txt", std::ios::out);

    for (auto hs : HS)
    {
        file << hs.interval.bottom << " " << hs.interval.top << " " << hs.coord << " " << hs.coord << std::endl;
    }

    for (auto vs : VS)
    {
        file << vs.coord << " " << vs.coord << " " << vs.interval.bottom << " " << vs.interval.top << std::endl;
    }
    file.close();
    return 0;
}
