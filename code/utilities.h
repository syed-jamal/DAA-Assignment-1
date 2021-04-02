#ifndef UTILITIES_H
#define UTILITIES_H

#include "classes.h"

/**
 *  Overloaded == operator.
 *  Used to test equlity of 2 intervals.
 *  @param[in] a first interval.
 *  @param[in] b second interval.
 *  @return boolean value of (a==b) which in turn is defined by sequential comparison of their members.
 */
bool operator==(const Interval &a, const Interval &b);

#endif