#ifndef CLASSES_MEASURE_H
#define CLASSES_MEASURE_H

#include "classes.h"

/**
 *  A stripe class. Used to store a stripe.
 */
struct Stripe
{
    Interval x_interval;///< x-interval of the stripe.
    Interval y_interval;///< y-interval of the stripe.
    double x_measure;///< total length covered by rectangles along the x-interval.
};

#endif