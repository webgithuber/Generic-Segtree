#include <vector>
#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H
#define ll long long int
#define ff first
#define ss second

using namespace std;

template <class T>
class Segtree
{
private:
    vector<T> segment; // this vector works as tree.
    int size = 0;
    T combine(T a, T b); // combine result of left and right subtree.

    T build(int i, int s, int e, vector<T> &vec); // build segtree on top of vec

    T point_update(int node, int l, int r, int a, int b, ll val); // return updated value

    T query(int node, int l, int r, int a, int b); // return queried value from range a,b.

public:
    Segtree(int n, vector<T> &vec); // constructor of segtree

    void update(int l, ll val); // update value at vec[l]=val,0-based indexing

    T query_rng(int l, int r); // query range from l to r ,0-based indexing
};
template <class T>
Segtree<T>::Segtree(int n, vector<T> &vec)
{
    size = n;
    segment.resize(4 * n + 10); // resizing size of tree
    build(1, 0, n - 1, vec);    // building segtree
}
template <class T>
T Segtree<T>::query_rng(int l, int r)
{
    return query(1, 0, size - 1, l, r); // private function , return range query from l to r.
}
template <class T>
void Segtree<T>::update(int l, ll val)
{
    point_update(1, 0, size - 1, l, l, val); // private function , update val.
}
template <class T>
T Segtree<T>::build(int i, int s, int e, vector<T> &vec)
{
    T left, right;

    if (s == e)
    {
        segment[i] = vec[e];
        return segment[i];
    }

    left = build(2 * i, s, (s + e) / 2, vec);
    right = build(1 + 2 * i, 1 + (s + e) / 2, e, vec);

    return segment[i] = combine(left, right);
}
template <class T>
T Segtree<T>::point_update(int node, int l, int r, int a, int b, ll val)
{
    T left, right;

    if (b < l || a > r)
    {
        return segment[node];
    }

    if (a <= l && r <= b)
    {
        segment[node].ff -= val;
        segment[node].ss -= val;
        return segment[node];
    }

    left = point_update(2 * node, l, (l + r) / 2, a, b, val);
    right = point_update(1 + 2 * node, 1 + (l + r) / 2, r, a, b, val);

    return segment[node] = combine(left, right);
}
template <class T>
T Segtree<T>::query(int node, int l, int r, int a, int b)
{
    T left, right, result;

    if (b < l || a > r)
    {
        return result;
    }

    if (a <= l && r <= b)
    {
        return segment[node];
    }

    left = query(2 * node, l, (l + r) / 2, a, b);
    right = query(1 + 2 * node, 1 + (l + r) / 2, r, a, b);

    return combine(left, right);
    ;
}
#endif
