#ifndef STRIPE_CONTOUR_H
#define STRIPE_CONTOUR_H

#include "stripe.h"
#include <vector>
#include "classes_contour.h"

/**
 *  Function used to get the free segments of and edge with respect to the rectangles in the stripe covering it.
 *  @param[in] h a horizontal edge.
 *  @param[out] leaves an array of leaves of a binary search tree ordered by inorder traversal.
 *  @param[out] res set of free line segments of h.
 *  @return void.
 */
void get_free_segments(Edge h, std::vector<double> &leaves, std::set<Line_Segment, cmp_line_segment> &res);

/**
 *  Inorder traversal and retrieval of leaves.
 *  @param[in] root root of the binary search tree.
 *  @param[out] leaves an array to capture the leaves inorder.
 *  @return void.
 */
void get_leaves(std::shared_ptr<Ctree> root, std::vector<double> &leaves);

/**
 *  Function to get the set of horizontal line segments in the contour.
 *  @param[in] H multiset of horizontal edges of the set of rectangles.
 *  @param[in] S set of stripes defined by the horizontal edges.
 *  @return a set of line segments
 */
std::set<Line_Segment, cmp_line_segment> horizontal_contour(std::multiset<Edge, cmp_edge> H, std::set<Stripe, cmp_stripe> S);

#endif