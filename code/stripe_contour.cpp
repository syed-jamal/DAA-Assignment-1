#include "stripe_contour.h"
#include "macros.h"
#include "utilities.h"
#include <algorithm>

extern double frame_left;
extern double frame_right;

void get_free_segments(Edge h, std::vector<double> &leaves, std::set<Line_Segment, cmp_line_segment> &res)
{
    int i1 = 0;
    int i2 = 1;

    while (i1 < leaves.size() && i2 < leaves.size() && leaves[i1] < h.interval.top)
    {
        if (leaves[i2] >= h.interval.top && leaves[i1] <= h.interval.bottom)
        {

            Line_Segment l;
            l.coord = h.coord;
            l.interval.bottom = h.interval.bottom;
            l.interval.top = h.interval.top;
            if (l.interval.bottom != l.interval.top)
            {
                res.insert(l);
                break;
            }
        }
        else if (leaves[i2] >= h.interval.top && leaves[i1] > h.interval.bottom)
        {
            Line_Segment l;
            l.coord = h.coord;
            l.interval.bottom = leaves[i1];
            l.interval.top = h.interval.top;
            if (l.interval.bottom != l.interval.top)
            {
                res.insert(l);
                break;
            }
        }

        else if (leaves[i2] > h.interval.bottom && leaves[i1] <= h.interval.bottom)
        {
            Line_Segment l;
            l.coord = h.coord;
            l.interval.bottom = h.interval.bottom;
            l.interval.top = leaves[i2];
            if (l.interval.bottom != l.interval.top)
                res.insert(l);
        }
        else if (leaves[i2] <= h.interval.top && leaves[i1] >= h.interval.bottom)
        {
            Line_Segment l;
            l.coord = h.coord;
            l.interval.bottom = leaves[i1];
            l.interval.top = leaves[i2];
            if (l.interval.bottom != l.interval.top)
                res.insert(l);
        }

        i1 += 2;
        i2 += 2;
    }
}
void get_leaves(std::shared_ptr<Ctree> root, std::vector<double> &leaves)
{
    if (root == NULL)
        return;

    get_leaves(root->lson, leaves);
    if (!(root->lson) && !(root->rson))
        leaves.push_back(root->x);
    get_leaves(root->rson, leaves);
}

std::set<Line_Segment, cmp_line_segment> horizontal_contour(std::multiset<Edge, cmp_edge> H, std::set<Stripe, cmp_stripe> S)
{
    std::set<Line_Segment, cmp_line_segment> res;

   // int was_bottom = 0;
    for (auto h : H)
    {

        if (h.side == BOTTOM_EDGE)
        {
            std::set<Stripe, cmp_stripe>::iterator it = S.begin();
            for (; it != S.end(); ++it)
            {
                if ((it->y_interval).top == h.coord)
                    break;
            }

            std::vector<double> leaves;
            leaves.push_back(frame_left);
            get_leaves(it->tree, leaves);
            leaves.push_back(frame_right);

            get_free_segments(h, leaves, res);
        }

        else
        {
            std::set<Stripe, cmp_stripe>::iterator it = S.begin();
            for (; it != S.end(); ++it)
            {
                if ((it->y_interval).bottom == h.coord)
                    break;
            }

            std::vector<double> leaves;
            leaves.push_back(frame_left);
            get_leaves(it->tree, leaves);
            leaves.push_back(frame_right);

            get_free_segments(h, leaves, res);
        }
    }

    return res;
}

std::set<Interval, cmp_interval> partition(std::set<double> P)
{
    std::set<Interval, cmp_interval> part;

    auto it1 = P.begin();
    auto it2 = P.begin();
    it2++;

    while (it2 != P.end())
    {
        Interval i;
        i.bottom = *it1;
        i.top = *it2;

        part.insert(i);

        it1++;
        it2++;
    }

    return part;
}

std::set<Stripe, cmp_stripe> concat(std::set<Stripe, cmp_stripe> S1,
                                    std::set<Stripe, cmp_stripe> S2,
                                    std::set<double> P,
                                    Interval x_int)
{

    std::set<Stripe, cmp_stripe>::iterator it1 = S1.begin();
    std::set<Stripe, cmp_stripe>::iterator it2 = S2.begin();

    std::set<Interval, cmp_interval> part = partition(P);
    std::set<Stripe, cmp_stripe> S;

    for (auto p : part)
    {
        Stripe s;
        s.x_interval = x_int;
        s.y_interval = p;

        if ((*it1).tree != nullptr && (*it2).tree != nullptr)
        {
            s.tree = std::make_shared<Ctree>();
            (s.tree)->x = (*it1).x_interval.top;
            (s.tree)->side = UNDEF;
            (s.tree)->lson = (*it1).tree;
            (s.tree)->rson = (*it2).tree;
        }
        else if ((*it1).tree != nullptr && (*it2).tree == nullptr)
        {
            s.tree = (*it1).tree;
        }
        else if ((*it1).tree == nullptr && (*it2).tree != nullptr)
        {
            s.tree = (*it2).tree;
        }
        else if ((*it1).tree == nullptr && (*it2).tree == nullptr)
        {
            s.tree = nullptr;
        }

        it1++;
        it2++;

        S.insert(s);
    }

    return S;
}

std::set<Stripe, cmp_stripe> blacken(std::set<Stripe, cmp_stripe> S, std::set<Interval, cmp_interval> J)
{
    std::set<Stripe, cmp_stripe> S1;
    std::set<Interval, cmp_interval>::iterator it = J.begin();
    if (J.empty())
    {
        return S;
    }

    for (auto s : S)
    {

        Stripe s1;
        s1.x_interval = s.x_interval;
        s1.y_interval = s.y_interval;
        s1.tree = s.tree;

        while (it != J.end() && s1.y_interval.bottom >= (*it).top)
        {
            it++;
        }

        if (it != J.end())
        {
            if (s1.y_interval.bottom >= (*it).bottom && s1.y_interval.top <= (*it).top)
            {
                s1.tree = nullptr;
            }
        }

        S1.insert(s1);
    }

    return S1;
}

std::set<Stripe, cmp_stripe> copy(std::set<Stripe, cmp_stripe> S, std::set<double> P, Interval x_int)
{

    std::set<Interval, cmp_interval> part = partition(P);
    std::set<Stripe, cmp_stripe> S1;
    std::set<Stripe, cmp_stripe>::iterator it = S.begin();

    for (auto p : part)
    {
        Stripe s1;
        s1.x_interval = x_int;
        s1.y_interval = p;
        s1.tree = nullptr;

        if (p.bottom >= ((*it).y_interval.top))
        {
            it++;
        }

        s1.tree = (*it).tree;
        S1.insert(s1);
    }

    return S1;
}

void stripes(std::multiset<Edge, cmp_edge> V,
             Interval x_ext,
             std::set<Interval, cmp_interval> &L,
             std::set<Interval, cmp_interval> &R,
             std::set<double> &P,
             std::set<Stripe, cmp_stripe> &S)
{
    if (V.size() == 1)
    {
        Edge v;
        v = *(V.begin());
        if (v.side == LEFT_EDGE)
        {
            L.insert(v.interval);
        }
        else
        {
            R.insert(v.interval);
        }

        P.insert(FRAME_BOTTOM);
        P.insert(v.interval.bottom);
        P.insert(v.interval.top);
        P.insert(FRAME_TOP);

        std::set<Interval, cmp_interval> part = partition(P);

        for (auto p : part)
        {

            Stripe s;
            s.x_interval = x_ext;
            s.y_interval = p;
            s.tree = nullptr;

            if (s.y_interval == v.interval)
            {
                s.tree = std::make_shared<Ctree>();
                if (v.side == LEFT_EDGE)
                {
                    (s.tree)->x = v.coord;
                    (s.tree)->side = LEFT_EDGE;
                    (s.tree)->lson = nullptr;
                    (s.tree)->rson = nullptr;
                }
                else
                {
                    (s.tree)->x = v.coord;
                    (s.tree)->side = RIGHT_EDGE;
                    (s.tree)->lson = nullptr;
                    (s.tree)->rson = nullptr;
                }
            }

            S.insert(s);
        }

        return;
    }

    std::multiset<Edge, cmp_edge>::iterator it1 = V.begin();
    std::advance(it1, V.size() / 2);

    std::multiset<Edge, cmp_edge> V1;
    std::multiset<Edge, cmp_edge> V2;

    std::multiset<Edge, cmp_edge>::iterator it2;
    for (it2 = V.begin(); it2 != it1; ++it2)
    {
        V1.insert(*it2);
    }

    for (; it2 != V.end(); ++it2)
    {
        V2.insert(*it2);
    }

    std::set<Interval, cmp_interval> L1;
    std::set<Interval, cmp_interval> R1;
    std::set<double> P1;
    std::set<Stripe, cmp_stripe> S1;

    std::set<Interval, cmp_interval> L2;
    std::set<Interval, cmp_interval> R2;
    std::set<double> P2;
    std::set<Stripe, cmp_stripe> S2;

    double xm = (*(V1.rbegin())).coord + ((*(V2.begin())).coord - (*(V1.rbegin())).coord) / 2;
    Interval x_ext1;
    x_ext1.bottom = x_ext.bottom;
    x_ext1.top = xm;

    Interval x_ext2;
    x_ext2.bottom = xm;
    x_ext2.top = x_ext.top;

    stripes(V1, x_ext1, L1, R1, P1, S1);
    stripes(V2, x_ext2, L2, R2, P2, S2);

    std::set<Interval, cmp_interval> LR;

    std::set_intersection(L1.begin(), L1.end(), R2.begin(), R2.end(), std::inserter(LR, LR.begin()), cmp_interval());

    std::set<Interval, cmp_interval> temp1;
    std::set_difference(L1.begin(), L1.end(), LR.begin(), LR.end(), std::inserter(temp1, temp1.begin()), cmp_interval());

    std::set_union(temp1.begin(), temp1.end(), L2.begin(), L2.end(), std::inserter(L, L.begin()), cmp_interval());

    std::set<Interval, cmp_interval> temp2;
    std::set_difference(R2.begin(), R2.end(), LR.begin(), LR.end(), std::inserter(temp2, temp2.begin()), cmp_interval());

    std::set_union(R1.begin(), R1.end(), temp2.begin(), temp2.end(), std::inserter(R, R.begin()), cmp_interval());

    std::set_union(P1.begin(), P1.end(), P2.begin(), P2.end(), std::inserter(P, P.begin()));

    std::set<Stripe, cmp_stripe> S_left = copy(S1, P, x_ext1);
    std::set<Stripe, cmp_stripe> S_right = copy(S2, P, x_ext2);

    std::set<Stripe, cmp_stripe> S_left_b = blacken(S_left, temp2);
    std::set<Stripe, cmp_stripe> S_right_b = blacken(S_right, temp1);

    S = concat(S_left_b, S_right_b, P, x_ext);

    return;
}

void rectangle_dac(std::set<Rectangle, cmp_rectangle> RECT, std::set<Stripe, cmp_stripe> &S)
{

    std::multiset<Edge, cmp_edge> VRX;

    for (auto r : RECT)
    {
        Edge left;
        left.coord = r.x_left;
        left.side = LEFT_EDGE;
        left.interval.bottom = r.y_bottom;
        left.interval.top = r.y_top;

        Edge right;
        right.coord = r.x_right;
        right.side = RIGHT_EDGE;
        right.interval.bottom = r.y_bottom;
        right.interval.top = r.y_top;

        VRX.insert(left);
        VRX.insert(right);
    }

    Interval x_ext;
    x_ext.bottom = (*(VRX.begin())).coord;
    x_ext.top = (*(VRX.rbegin())).coord;

    frame_left = x_ext.bottom;
    frame_right = x_ext.top;

    std::set<Interval, cmp_interval> LEFT;
    std::set<Interval, cmp_interval> RIGHT;
    std::set<double> POINTS;

    stripes(VRX, x_ext, LEFT, RIGHT, POINTS, S);
}