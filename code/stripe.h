#ifndef STRIPE_H
#define STRIPE_H

#include <set>
#include "classes.h"

/**
 *  Partition function.
 *  Used to find the partition of a set of ordered points.
 *  @param[in] P set of points.
 *  @return a set of intervals defined by the partition.
 */
std::set<Interval, cmp_interval> partition(std::set<double> P);

/**
 *  Concatination function.
 *  Used to concatinate 2 sets of stripes.
 *  @param[in] S1 first set of stripes.
 *  @param[in] S2 second set of stripes.
 *  @param[in] P set of points.
 *  @param[in] x_int combined x-interval of the stripes of S1 and S2.
 *  @return a set of stripes, a concatination of S1 and S2.
 */
std::set<Stripe, cmp_stripe> concat(std::set<Stripe, cmp_stripe> S1,
                                    std::set<Stripe, cmp_stripe> S2,
                                    std::set<double> P,
                                    Interval x_int);

/**
 *  Measure extension function.
 *  Used to extend the measure defined by an edge inside the stripe towards an extreme.
 *  @param[in] S set of stripes.
 *  @param[in] J set of intervals.
 *  @return a set of stripes, the result of blackening the stripes.
 */
std::set<Stripe, cmp_stripe> blacken(std::set<Stripe, cmp_stripe> S, std::set<Interval, cmp_interval> J);

/**
 *  Stripes refinement function.
 *  Used to refine the stripes according to P(a set of points).
 *  @param[in] S set of stripes.
 *  @param[in] P set of points.
 *  @param[in] x_int x-interval of the stripes in S.
 *  @return a set of stripes, which are a refinement of stripes in S.
 */
std::set<Stripe, cmp_stripe> copy(std::set<Stripe, cmp_stripe> S, std::set<double> P, Interval x_int);

/**
 *  Function used to calculate the set of stripes.
 *  @param[in] V multiset of vertical edges.
 *  @param[in] x_ext width of the frame.
 *  @param[out] L set of intervals corresponding to unpaired left edges in V.
 *  @param[out] R set of intervals corresponding to unpaired right edges in V.
 *  @param[out] P set of points defined by end-points of edges in V. 
 *  @return void.
 */
void stripes(std::multiset<Edge, cmp_edge> V,
             Interval x_ext,
             std::set<Interval, cmp_interval> &L,
             std::set<Interval, cmp_interval> &R,
             std::set<double> &P,
             std::set<Stripe, cmp_stripe> &S);

/**
 *  Setup and initialization function.
 *  @param[in] RECT set of rectangles.
 *  @param[out] S set of stripes.
 *  @return void.
 */
void rectangle_dac(std::set<Rectangle, cmp_rectangle> RECT, std::set<Stripe, cmp_stripe> &S);


#endif