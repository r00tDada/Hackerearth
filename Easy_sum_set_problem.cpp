#include <bits/stdc++.h>
using namespace std;
// ----------------------R00TDADA------------------------------
#define rep(i, a, b) for (__typeof((b)) i = (a); i < (b); i++)
#define nrep(i, a, b) for (__typeof((b)) i = (a); i > (b); i--)
#define all(a) (a).begin(), (a).end()
#define ff first
#define ss second
#define ppi pair<int, int>
#define pppi pair<ppi, int>
#define vi vector<int>
#define vii vector<ppi>
#define viii vector<pppi>
#define vs vector<string>
#define pb push_back
#define mp make_pair
#define sz(x) (int)x.size()
#define M_PI 3.14159265358979323846
#define rootdada ios_base::sync_with_stdio(false)
#define int long long
#define M 1000000007
#define MAX 100005
int A[MAX], tree[4 * MAX];
int power(int x, int p)
{
    if (p == 0)
        return 1;
    int y = power(x, p / 2);
    y *= y;
    y %= M;
    if (p % 2 == 0)
        return y;
    y *= x;
    y %= M;
    return y;
}
void build(int node, int start, int end)
{
    if (start == end)
        //Leaf node will have a single element
        tree[node] = start;
    else
    {
        int mid = (start + end) / 2;
        //Recurse on the left child
        build(2 * node, start, mid);
        //Recurse on the right child
        build(2 * node + 1, mid + 1, end);
        // Internal node will have the sum of both of its children
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}
void update(int node, int start, int end, int idx, int val)
{
    if (start == end)
    {
        //Leaf Node
        A[idx] = val;
        tree[node] += val;
    }
    else
    {
        int mid = (start - end) / 2 + end;
        if (start <= idx && idx <= mid)
        {
            // If idx is in the left child, recurse on the left child
            update(2 * node, start, mid, idx, val);
        }
        else
        {
            // if idx is in the right child, recurse on the right child
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        // Internal node will have the sum of both of its children
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}
int query(int node, int start, int end, int l, int r)
{
    if (r < start || l > end)
    {
        // range represented by a node is completely outside the given range
        return 0;
    }
    if (l <= start && end <= r)
    {
        // range represented by a node is completely inside the given range
        return tree[node];
    }
    // range represented by a node is partially inside and partially outside the given range
    int mid = (start + end) / 2;
    int p1 = query(2 * node, start, mid, l, r);
    int p2 = query(2 * node + 1, mid + 1, end, l, r);
    return p1 + p2;
}

signed main()
{
#ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
#endif
    rootdada;
    int n;
    cin >> n;
    vi a, b, c;
    rep(i, 0, n)
    {
        int x;
        cin >> x;
        a.pb(x);
    }
    int m;
    cin >> m;
    rep(i, 0, m)
    {
        int x;
        cin >> x;
        c.pb(x);
        // cout << x << endl;
    }

    rep(i, 0, n)
    {
        rep(j, 0, m)
        {
            int x;
            x = c[j] - a[i];
            b.pb(x);
        }
    }
    sort(b.begin(), b.end());
    set<int> e;
    rep(i, 0, b.size())
    {
        e.insert(b[i]);
    }
    vi f;
    for (auto it = e.begin(); it != e.end(); it++)
        f.pb(*it);
    vi g;
    rep(j, 0, n)
    {
        rep(i, 0, f.size())
        {
            if (binary_search(c.begin(), c.end(), a[j] + f[i]) && f[i] != INT_MIN)
            {
                g.pb(f[i]);
            }
            else
            {
                rep(k, 0, g.size())
                {
                    if (g[k] == f[i])
                    {
                        g[k] = INT_MIN;
                    }
                }

                f[i] = INT_MIN;
            }
        }
    }
    set<int> ans;
    rep(i, 0, f.size())
    {
        if (f[i] > 0)
            ans.insert(f[i]);
    }
    for (auto it = ans.begin(); it != ans.end(); it++)
        cout << *it << " ";
}