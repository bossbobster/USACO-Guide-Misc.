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
using namespace std;
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef pair<int, int> pii;
typedef pair<int, string> pis;
typedef pair<int, short> pish;
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
typedef pair<pll, ll> plll;
typedef pair<pll, ld> plld;
typedef pair<int, ll> pil;
typedef pair<ull, ull> pull;
typedef pair<ld, ld> pld;
typedef complex<double> cd;
//#define max(n, m) ((n>m)?n:m)
//#define min(n, m) ((n<m)?n:m)
#define f first
#define s second
#define input() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define eps 1e-9
//#define cin fin

vector<pil> adj[200010];
ll n, k, a, b, root;
ll sz[200010];
ll p[200010];
bitset<200010> vis;
ll dfs1(int cur, int par)
{
    sz[cur] = 1;
    for(auto nx : adj[cur])
        if(nx.f != par && !vis[nx.f])
            sz[cur] += dfs1(nx.f, cur);
    return sz[cur];
}
int dfs2(int cur, int par, ll n)
{
    for(auto nx : adj[cur])
        if(nx.f != par && sz[nx.f] > n/2 && !vis[nx.f])
            return dfs2(nx.f, cur, n);
    return cur;
}
ll ans = 2000000000000000;
ll cnt[1000010];
vector<ll> gud;
void dfs3(int cur, int par, ll d, ll num)
{
    if(d > k) return;
    ans = min(ans, num+cnt[k-d]);
    for(auto nx : adj[cur])
        if(nx.f != par && !vis[nx.f])
            dfs3(nx.f, cur, d+nx.s, num+1);
}
void dfs4(int cur, int par, ll d, ll num)
{
    if(d > k) return;
    cnt[d] = min(cnt[d], num);
    gud.push_back(d);
    for(auto nx : adj[cur])
        if(nx.f != par && !vis[nx.f])
            dfs4(nx.f, cur, d+nx.s, num+1);
}
void make(int cur, int par)
{
    int cent = dfs2(cur, par, dfs1(cur, par));
    vis[cent] = 1;
    gud.clear();
    for(auto it : adj[cent])
        if(!vis[it.f])
            dfs3(it.f, cent, it.s, 1), dfs4(it.f, cent, it.s, 1);
    if(cnt[k])
        ans = min(ans, cnt[k]);
    for(auto it : gud)
        cnt[it] = 1000000000;
    for(auto it : adj[cent])
        if(!vis[it.f])
            make(it.f, cent);
}
int best_path(int N, int K, int H[][2], int L[])
{
    for(int i = 0; i < n-1; i ++)
        adj[H[i][0]].push_back({H[i][1], L[i]}), adj[H[i][1]].push_back({H[i][0], L[i]});
    k = K; n = N;
    for(int i = 0; i < 1000010; i ++)
        cnt[i] = 1000000000;
    make(0, -1);
    return ((ans>=1000000000)?-1:(int)ans);
}
int edges[200010][2], lll[200010];
int main()
{
    input();
    cin >> n >> k;
    for(int i = 0; i < n-1; i ++)
        cin >> edges[i][0] >> edges[i][1] >> lll[i];
    cout << best_path(n, k, edges, lll) << '\n';
}
