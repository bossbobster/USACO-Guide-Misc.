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
#define input(x) ios_base::sync_with_stdio(x); cin.tie(x);

struct st
{
    pii l, b;
    bool can;
};
int n, m;
pii nums[200010];
st seg[1000010];
void update(int l, int r, int curIdx, int upIdx, pii val)
{
    if(l == r)
    {
        seg[curIdx].b = {val.f, val.f}; seg[curIdx].l = {val.s, val.s}; seg[curIdx].can = true;
        nums[upIdx] = val;
        return;
    }
    int mid = (l + r) / 2;
    if(upIdx >= l && upIdx <= mid)
        update(l, mid, curIdx * 2 + 1, upIdx, val);
    else
        update(mid + 1, r, curIdx * 2 + 2, upIdx, val);
    int ln = curIdx*2+1, rn = curIdx*2+2;
    if(!seg[ln].can || !seg[rn].can) { seg[curIdx] = {{0, 0}, {0, 0}, false}; return; }
    if(seg[ln].l.s <= seg[rn].l.f) seg[curIdx].l = {seg[ln].l.f, seg[rn].l.s};
    else if(seg[ln].l.s <= seg[rn].b.f) seg[curIdx].l = {seg[ln].l.f, seg[rn].b.s};
    else seg[curIdx].l = {-2000000000, 2000000000};
    if(seg[ln].b.s <= seg[rn].l.f) seg[curIdx].b = {seg[ln].b.f, seg[rn].l.s};
    else if(seg[ln].b.s <= seg[rn].b.f) seg[curIdx].b = {seg[ln].b.f, seg[rn].b.s};
    else seg[curIdx].b = {-2000000000, 2000000000};
    if(seg[curIdx].l.f == -2000000000 && seg[curIdx].l.s == 2000000000 && seg[curIdx].b.f == -2000000000 && seg[curIdx].b.s == 2000000000)
        seg[curIdx].can = false;
    else
        seg[curIdx].can = true;
}
void makeTree(int l, int r, int curIdx)
{
    if(l == r) { seg[curIdx].b = {nums[l].f, nums[l].f}; seg[curIdx].l = {nums[l].s, nums[l].s}; seg[curIdx].can = true; return; }
    int mid = (l + r) / 2;
    makeTree(l, mid, curIdx * 2 + 1); makeTree(mid + 1, r, curIdx * 2 + 2);
    int ln = curIdx*2+1, rn = curIdx*2+2;
    if(!seg[ln].can || !seg[rn].can) { seg[curIdx] = {{0, 0}, {0, 0}, false}; return; }
    if(seg[ln].l.s <= seg[rn].l.f) seg[curIdx].l = {seg[ln].l.f, seg[rn].l.s};
    else if(seg[ln].l.s <= seg[rn].b.f) seg[curIdx].l = {seg[ln].l.f, seg[rn].b.s};
    else seg[curIdx].l = {-2000000000, 2000000000};
    if(seg[ln].b.s <= seg[rn].l.f) seg[curIdx].b = {seg[ln].b.f, seg[rn].l.s};
    else if(seg[ln].b.s <= seg[rn].b.f) seg[curIdx].b = {seg[ln].b.f, seg[rn].b.s};
    else seg[curIdx].b = {-2000000000, 2000000000};
    if(seg[curIdx].l.f == -2000000000 && seg[curIdx].l.s == 2000000000 && seg[curIdx].b.f == -2000000000 && seg[curIdx].b.s == 2000000000)
        seg[curIdx].can = false;
    else
        seg[curIdx].can = true;
}
int main()
{
    input(0);
    int a, b;
    pii p1, p2;
    cin >> n;
    for(int i = 0; i < n; i ++)
    {
        cin >> nums[i].f >> nums[i].s;
        if(nums[i].f < nums[i].s) swap(nums[i].f, nums[i].s);
    }
    cin >> m;
    makeTree(0, n-1, 0);
    while(m--)
    {
        cin >> a >> b; a--; b--;
        p1 = nums[a]; p2 = nums[b];
        update(0, n-1, 0, a, p2); update(0, n-1, 0, b, p1);
        cout << ((seg[0].can)?"TAK\n":"NIE\n");
    }
}
