#include "utilities.h"
#include "classes_contour.h"

bool operator==(const Interval &a, const Interval &b)
{
    if ((a.top == b.top) && (a.bottom == b.bottom))
    {
        return true;
    }
    return false;
}

bool cmp_rectangle::operator()(Rectangle a, Rectangle b) const
{
    if (a.x_left == b.x_left)
    {
        if (a.x_right == b.x_right)
        {
            if (a.y_bottom == b.y_bottom)
            {
                return a.y_top < b.y_top;
            }
            return a.y_bottom < b.y_bottom;
        }
        return a.x_right < b.x_right;
    }
    return a.x_left < b.x_left;
}

bool cmp_edge::operator()(Edge a, Edge b) const
{
    if (a.coord == b.coord)
    {
        if (a.side == b.side)
        {
            if (a.interval.bottom == b.interval.bottom)
            {
                return a.interval.top < b.interval.top;
            }
            return a.interval.bottom < b.interval.bottom;
        }

        return a.side < b.side;
    }

    return a.coord < b.coord;
}

bool cmp_interval::operator()(Interval a, Interval b) const
{
    if (a.bottom == b.bottom)
    {
        return a.top < b.top;
    }
    return a.bottom < b.bottom;
}

bool cmp_stripe::operator()(Stripe a, Stripe b) const
{
    return a.y_interval.bottom < b.y_interval.bottom;
}

bool cmp_line_segment::operator()(Line_Segment a, Line_Segment b) const
{
    if (a.coord == b.coord)
    {
        if (a.interval.bottom == b.interval.bottom)
        {
            return a.interval.top < b.interval.top;
        }
        return a.interval.bottom < b.interval.bottom;
    }
    return a.coord < b.coord;
}