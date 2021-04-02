#ifndef CLASSES_CONTOUR_H
#define CLASSES_CONTOUR_H

#include "classes.h"
#include <memory>


/**
 *  A line segment class. Used to store a line segment.
 */
struct Line_Segment
{
    Interval interval;///< interval describing the line segment.
    double coord;///< coordinate of the line segment(x in case of vertical segment and y in case of horizontal).
};

/**
 *  A node class used to store node data of binary search tree.
 */
struct Ctree
{
    double x;///< a real number.
    int side;///< side value to guide tree traversal.
    std::shared_ptr<Ctree> lson;///< pointer to left child node.
    std::shared_ptr<Ctree> rson;///< pointer to right child node.
};

/**
 *  A stripe class. Used to store a stripe.
 */
struct Stripe
{
    Interval x_interval;///< x-interval describing the stripe.
    Interval y_interval;///< y-interval describing the stripe.
    std::shared_ptr<Ctree> tree;///< pointer to Ctree node.
};

/**
 *  Auxiliary class used for comparing 2 line segments.
 */
struct cmp_line_segment
{   
    /**
    *  Overloaded () operator.
    *  Used where line segments can be passed as arguments.
    *  @param[in] a first line segment.
    *  @param[in] b second line segment.
    *  @return boolean value of (a<b) which in turn is defined by sequential comparison of their members.
    */
    bool operator()(Line_Segment a, Line_Segment b) const;
};

#endif