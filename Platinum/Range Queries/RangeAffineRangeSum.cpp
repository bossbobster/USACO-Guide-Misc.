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
typedef pair<ld, ld> pld;
typedef complex<double> cd;
//#define max(n, m) ((n>m)?n:m)
//#define min(n, m) ((n<m)?n:m)
#define f first
#define s second
#define input() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

ll n, q;
const ll mod = 998244353;
ll seg[4000010];
pll lazy[4000010];
ll arr[500010];
void updateRec(ll node, ll l, ll r, ll lq, ll rq, ll b, ll c)
{
    if(lazy[node].s || lazy[node].f > 1)
    {
        seg[node] = ((seg[node] * lazy[node].f) % mod + lazy[node].s * (r-l+1)) % mod;
        if(l != r)
        {
            lazy[node*2+1].s = (lazy[node*2+1].s*lazy[node].f+lazy[node].s)%mod;
            lazy[node*2+1].f = (lazy[node*2+1].f*lazy[node].f)%mod;
            lazy[node*2+2].s = (lazy[node*2+2].s*lazy[node].f+lazy[node].s)%mod;
            lazy[node*2+2].f = (lazy[node*2+2].f*lazy[node].f)%mod;
        }
        lazy[node] = {1, 0};
    }
    if(l > rq || r < lq || l > r) return;
    if(l >= lq && r <= rq)
    {
        seg[node] = ((seg[node] * b) % mod + c * (r-l+1)) % mod;
        if(l != r)
        {
            lazy[node*2+1].s = (lazy[node*2+1].s*b+c)%mod;
            lazy[node*2+1].f = (lazy[node*2+1].f*b)%mod;
            lazy[node*2+2].s = (lazy[node*2+2].s*b+c)%mod;
            lazy[node*2+2].f = (lazy[node*2+2].f*b)%mod;
        }
        return;
    }
    ll mid = (l + r) / 2;
    updateRec(node * 2 + 1, l, mid, lq, rq, b, c);
    updateRec(node * 2 + 2, mid + 1, r, lq, rq, b, c);
    seg[node] = (seg[node * 2 + 1] + seg[node * 2 + 2]) % mod;
}
void update(ll lq, ll rq, ll b, ll c) { updateRec(0, 0, n-1, lq, rq, b, c); }
ll sumRec(ll node, ll l, ll r, ll lq, ll rq)
{
    if(lazy[node].s || lazy[node].f > 1)
    {
        seg[node] = ((seg[node] * lazy[node].f) % mod + lazy[node].s * (r-l+1)) % mod;
        if(l != r)
        {
            lazy[node*2+1].s = (lazy[node*2+1].s*lazy[node].f+lazy[node].s)%mod;
            lazy[node*2+1].f = (lazy[node*2+1].f*lazy[node].f)%mod;
            lazy[node*2+2].s = (lazy[node*2+2].s*lazy[node].f+lazy[node].s)%mod;
            lazy[node*2+2].f = (lazy[node*2+2].f*lazy[node].f)%mod;
        }
        lazy[node] = {1, 0};
    }
    if(l > rq || r < lq || l > r) return 0;
    if(l >= lq && r <= rq)
        return seg[node];
    ll mid = (l + r) / 2;
    return (sumRec(node * 2 + 1, l, mid, lq, rq) + sumRec(node * 2 + 2, mid + 1, r, lq, rq)) % mod;
}
ll sum(ll lq, ll rq) { return sumRec(0, 0, n-1, lq, rq); }
void makeRec(ll node, ll l, ll r)
{
    if(l > r) return;
    if(l == r) { seg[node] = arr[l]; return; }
    ll mid = (l + r) / 2;
    makeRec(node * 2 + 1, l, mid);
    makeRec(node * 2 + 2, mid + 1, r);
    seg[node] = (seg[node * 2 + 1] + seg[node * 2 + 2]) % mod;
}
void make() { makeRec(0, 0, n-1); for(int i = 0; i < 4000010; i ++) lazy[i] = {1, 0}; }
int main()
{
    input();
    ll type, l, r, b, c;
    cin >> n >> q;
    for(int i = 0; i < n; i ++)
        cin >> arr[i];
    make();
    while(q--)
    {
        cin >> type;
        if(type == 0)
        {
            cin >> l >> r >> b >> c; r--;
            update(l, r, b, c);
        }
        else
        {
            cin >> l >> r; r--;
            cout << sum(l, r)%mod << '\n';
        }
    }
}
