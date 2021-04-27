#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#pragma GCC optimize ("O2")
#pragma GCC target ("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
//#include <ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, string> pis;
typedef pair<int, char> pic;
typedef pair<pii, int> piii;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ull, ull> pull;
//#define max(n, m) ((n>m)?n:m)
//#define min(n, m) ((n<m)?n:m)
#define f first
#define s second

int n, q, mod = 998244353;
pll nums[500010], tree[2000010];
// updates value at upIdx to val.
void update(int l, int r, int curIdx, int upIdx, pll val)
{
    if(l == r)
    {
        tree[curIdx] = val;
        nums[upIdx] = val;
        return;
    }
    int mid = (l + r) / 2;
    if(upIdx >= l && upIdx <= mid)
        update(l, mid, curIdx * 2 + 1, upIdx, val);
    else
        update(mid + 1, r, curIdx * 2 + 2, upIdx, val);
    tree[curIdx] = { (tree[curIdx*2+1].f * tree[curIdx*2+2].f) % mod, (tree[curIdx*2+2].f * tree[curIdx*2+1].s + tree[curIdx*2+2].s) % mod };
}
// get the min from lq to rq in the array
pll minQ(int l, int r, int lq, int rq, int curIdx)
{
    if(lq == rq)
        return nums[lq];
    if(r < lq || l > rq)
        return {1, 0};
    if(lq <= l && rq >= r)
        return tree[curIdx];
    int mid = (l + r) / 2;
    pll p1 = minQ(l, mid, lq, rq, curIdx*2+1), p2 = minQ(mid+1, r, lq, rq, curIdx*2+2);
    return { (p1.f * p2.f) % mod, (p2.f * p1.s + p2.s) % mod };
}
// recursive function useful for making segment tree
pll makeTree(int l, int r, int curIdx)
{
    if(l == r)
    {
        tree[curIdx] = nums[l];
        return tree[curIdx];
    }
    int mid = (l + r) / 2;
    pll p1 = makeTree(l, mid, curIdx*2+1), p2 = makeTree(mid+1, r, curIdx*2+2);
    tree[curIdx] = { (p1.f * p2.f) % mod, (p2.f * p1.s + p2.s) % mod };
    return tree[curIdx];
}
int main()
{
    ll a, b, c, d;
    cin >> n >> q;
    for(int i = 0; i < n; i ++)
        cin >> nums[i].f >> nums[i].s;
    makeTree(0, n-1, 0);
    while(q--)
    {
        cin >> a >> b >> c >> d;
        if(a == 0)
            update(0, n-1, 0, b, {c, d});
        else
        {
            pll tmp = minQ(0, n-1, b, c-1, 0);
            cout << (tmp.f * d + tmp.s) % mod << "\n";
        }
    }
}
