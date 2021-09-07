#include <iostream>
#include <string.h>
#include <random>
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
#include <complex>
#include <valarray>
//#include <ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, string> pis;
typedef pair<string, string> pss;
typedef pair<int, char> pic;
typedef pair<pii, int> piii;
typedef pair<double, double> pdd;
typedef pair<float, float> pff;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ull, ull> pull;
typedef complex<double> cd;
//#define max(n, m) ((n>m)?n:m)
//#define min(n, m) ((n<m)?n:m)
#define f first
#define s second
#define input() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

const double PI = 3.14159265358979323;
vector<double> nums1, nums2;
int c[4];
vector<pll> bad;
ll cp(pll p1, pll p2)
{
    return p1.f * p2.s - p1.s * p2.f;
}
int ccw(pll p1, pll p2, pll p3)
{
    pll p4 = {p2.f - p1.f, p2.s - p1.s};
    pll p5 = {p3.f - p1.f, p3.s - p1.s};
    if(cp(p4, p5) > 0) return 1; // ccw
    if(cp(p4, p5) == 0) return 0;
    return -1; // cw
}
bool inter(pll p1, pll p2, pll p3, pll p4)
{
    c[0] = ccw(p1, p2, p3); c[1] = ccw(p1, p2, p4); c[2] = ccw(p3, p4, p1); c[3] = ccw(p3, p4, p2);
    if(c[0] != c[1] && c[2] != c[3]) return true;
    if(ccw(p1, p2, p3) == 0) //case where segments are both on the same line
        if((!c[0] && p1 <= p3 && p3 <= p2) || (!c[0] && p1 >= p3 && p3 >= p2) || (!c[1] && p1 <= p4 && p4 <= p2) || (!c[1] && p1 >= p4 && p4 >= p2)  || (!c[2] && p3 <= p1 && p1 <= p4) || (!c[2] && p3 >= p1 && p1 >= p4) || (!c[3] && p3 <= p2 && p2 <= p4) || (!c[3] && p3 >= p2 && p2 >= p4))
            return true;
    return false;
}
bool comp(pll p1, pll p2)
{
    if(p1.f == p2.f) return p1.s > p2.s;
    return p1.f < p2.f;
}
int main()
{
    input();
    ll n, r, fjx, fjy, sz, pi, x, y, ogx, ogy, prex, prey, mn1, mx1, mn2, mx2, neg = 0, num = 0, sum = 0;
    bool does;
    double cur;
    cin >> n >> r >> fjx >> fjy;
    nums1.reserve(n*4); nums2.reserve(n*4);
    for(int i = 0; i <= n; i ++)
    {
        cur = atan2(fjy-n, fjx-i);
        nums1.push_back(cur);
        if(cur < 0) neg++, nums2.push_back(cur + 2*PI);
        else nums2.push_back(cur);
    }
    for(int i = n-1; i >= 0; i --)
    {
        cur = atan2(fjy-i, fjx-n);
        nums1.push_back(cur);
        if(cur < 0) neg++, nums2.push_back(cur + 2*PI);
        else nums2.push_back(cur);
    }
    for(int i = n-1; i >= 0; i --)
    {
        cur = atan2(fjy-i, fjx);
        nums1.push_back(cur);
        if(cur < 0) neg++, nums2.push_back(cur + 2*PI);
        else nums2.push_back(cur);
    }
    for(int i = 1; i < n; i ++)
    {
        cur = atan2(fjy, fjx-i);
        nums1.push_back(cur);
        if(cur < 0) neg++, nums2.push_back(cur + 2*PI);
        else nums2.push_back(cur);
    }
    sort(nums1.begin(), nums1.end()); sort(nums2.begin(), nums2.end());
    sz = (int)nums1.size();
    bad.reserve(r*2);
    while(r--)
    {
        cin >> pi; mn1 = mn2 = 2000000000; mx1 = mx2 = -1;
        does = false; prex = -1, prey = -1;
        while(pi--)
        {
            cin >> x >> y;
            if(prex == -1) ogx = x, ogy = y;
            else
                if(inter({fjx, fjy}, {n, fjy+1}, {x, y}, {prex, prey}))
                    does = true;
            cur = atan2(fjy-y, fjx-x);
            mn1 = min(mn1, (ll)(lower_bound(nums1.begin(), nums1.end(), cur)-nums1.begin()));
            mx1 = max(mx1, (ll)(upper_bound(nums1.begin(), nums1.end(), cur)-nums1.begin()));
            if(cur < 0) cur += 2*PI;
            mn2 = min(mn2, (ll)(lower_bound(nums2.begin(), nums2.end(), cur)-nums2.begin()));
            mx2 = max(mx2, (ll)(upper_bound(nums2.begin(), nums2.end(), cur)-nums2.begin()));
            prex = x; prey = y;
        }
        if(inter({fjx, fjy}, {n, fjy+1}, {x, y}, {ogx, ogy}))
            does = true;
        if(!does)
            bad.push_back({mn1, 0}), bad.push_back({mx1, 1});
        else
            bad.push_back({mn2+neg, 0}), bad.push_back({sz, 1}), bad.push_back({0, 0}), bad.push_back({mx2-sz+neg, 1});
    }
    sort(bad.begin(), bad.end(), comp);
    for(int i = 0; i < bad.size(); i ++)
    {
        if(num > 0) sum += bad[i].f - bad[i-1].f;
        if(bad[i].s == 0) num ++;
        else num --;
    }
    cout << sz-sum << '\n';
}
