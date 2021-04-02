#include <iostream>
#include <set>
#include <algorithm>
#include <iomanip>
#include <limits.h>
#include <chrono>
#include "classes_measure.h"
#include "utilities.h"
#include "stripe.h"
#include "macros.h"

int main()
{
    std::set<Rectangle, cmp_rectangle> R;
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        Rectangle r;
        double x1;
        double x2;
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

        std::cin >> x1;
        std::cin >> x2;

        if (x1 > x2)
        {
            r.y_bottom = x2;
            r.y_top = x1;
        }
        else
        {
            r.y_bottom = x1;
            r.y_top = x2;
        }

        R.insert(r);
    }

    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    std::set<Stripe, cmp_stripe> S;

    rectangle_dac(R, S);

    double area = 0;
    for (auto s : S)
    {
        area = area + s.x_measure * (s.y_interval.top - s.y_interval.bottom);
    }

    std::cout << "Area: " << std::setprecision(20) << area << std::endl;
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << std::setprecision(5) << ms_double.count() << "ms" << std::endl;

    return 0;
}