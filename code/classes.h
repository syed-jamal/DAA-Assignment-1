#ifndef CLASSES_H
#define CLASSES_H

/**
 *  A point class. Used to store 2d points.
 */
struct Point
{
    double x; ///< x-coordinate of the point.
    double y; ///< y-coordinate of the point.
};

/**
 *  An interval class. Used to store an interval.
 */
struct Interval
{
    double bottom; ///< coordinate of the bottom point of the interval(x-coordinate for vertical and y-coordinate for horizontal).
    double top;    ///< coordinate of the top point of the interval(x-coordinate for vertical and y-coordinate for horizontal).
};

/**
 *  A rectangle class. Used to store a rectangle.
 */
struct Rectangle
{
    double x_left;   ///< x-coordinate of the left edge.
    double x_right;  ///< x-coordinate of the right edge.
    double y_bottom; ///< y-coordinate of the bottom edge.
    double y_top;    ///< y-coordinate of the top edge.
};

/**
 *  An edge class. Used to store an edge.
 */
struct Edge
{
    Interval interval; ///< interval describing the edge.
    double coord;      ///< coordinate of the edge(x-coordinate for vertical and y-coordinate for horizontal).
    int side;          ///< 0,1,2,3 standing for left, right, bottom, top edges respectively.
};

/**
 *  Auxiliary class used for comparing 2 rectangles.
 */
struct cmp_rectangle
{
    /**
    *  Overloaded () operator.
    *  Used where rectangles can be passed as arguments.
    *  @param[in] a first rectangle.
    *  @param[in] b second rectangle.
    *  @return boolean value of (a<b) which in turn is defined by sequential comparison of their members.
    */
    bool operator()(Rectangle a, Rectangle b) const;
};

/**
 *  Auxiliary class used for comparing 2 edges.
 */
struct cmp_edge
{   
    /**
    *  Overloaded () operator.
    *  Used where edges can be passed as arguments.
    *  @param[in] a first edge.
    *  @param[in] b second edge.
    *  @return boolean value of (a<b) which in turn is defined by sequential comparison of their members.
    */
    bool operator()(Edge a, Edge b) const;
};

/**
 *  Auxiliary class used for comparing 2 intervals.
 */
struct cmp_interval
{   
    /**
    *  Overloaded () operator.
    *  Used where intervals can be passed as arguments.
    *  @param[in] a first interval.
    *  @param[in] b second interval.
    *  @return boolean value of (a<b) which in turn is defined by sequential comparison of their members.
    */
    bool operator()(Interval a, Interval b) const;
};

struct Stripe;

/**
 *  Auxiliary class used for comparing 2 stripes.
 */
struct cmp_stripe
{   
    /**
    *  Overloaded () operator.
    *  Used where stripes can be passed as arguments.
    *  @param[in] a first stripe.
    *  @param[in] b second stripe.
    *  @return boolean value of (a<b) which in turn is defined by sequential comparison of their members.
    */
    bool operator()(Stripe a, Stripe b) const;
};

#endif