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

struct node
{
    node* left = nullptr;
    node* right = nullptr;
    int val;
    bool lazy;
    node(node* left, node* right, int val)
    {
        this->left = left; this->right = right; this->val = val;
    }
};
 
void update(node* cur, int l, int r, int lq, int rq)
{
    int mid = (l + r) / 2;
    if(cur->lazy)
    {
        cur->val = (r - l + 1);
        if(l != r)
        {
            if(cur->left == nullptr)
                cur->left = new node(nullptr, nullptr, 0);
            if(cur->right == nullptr)
                cur->right = new node(nullptr, nullptr, 0);
            cur->left->lazy = true;
            cur->right->lazy = true;
        }
        cur->lazy = false;
    }
    if(l > rq || r < lq || l > r) return;
    if(l >= lq && r <= rq)
    {
        cur->val = (r - l + 1);
        if(l != r)
        {
            if(cur->left == nullptr)
                cur->left = new node(nullptr, nullptr, 0);
            if(cur->right == nullptr)
                cur->right = new node(nullptr, nullptr, 0);
            cur->left->lazy = true;
            cur->right->lazy = true;
        }
        return;
    }
    if(cur->left == nullptr)
        cur->left = new node(nullptr, nullptr, 0);
    update(cur->left, l, mid, lq, rq);
    if(cur->right == nullptr)
        cur->right = new node(nullptr, nullptr, 0);
    update(cur->right, mid+1, r, lq, rq);
    int num = 0;
    if(cur->left != nullptr) num += cur->left->val;
    if(cur->right != nullptr) num += cur->right->val;
    cur->val = num;
}
int sum(node* cur, int l, int r, int lq, int rq)
{
    int mid = (l + r) / 2;
    if(cur->lazy)
    {
        cur->val = (r - l + 1);
        if(l != r)
        {
            if(cur->left == nullptr)
                cur->left = new node(nullptr, nullptr, 0);
            if(cur->right == nullptr)
                cur->right = new node(nullptr, nullptr, 0);
            cur->left->lazy = true;
            cur->right->lazy = true;
        }
        cur->lazy = false;
    }
    if(l > rq || r < lq || l > r) return 0;
    if(l >= lq && r <= rq)
        return cur->val;
    int num = 0;
    if(cur->left != nullptr) num += sum(cur->left, l, mid, lq, rq);
    if(cur->right != nullptr) num += sum(cur->right, mid+1, r, lq, rq);
    return num;
}
int main()
{
    input();
    int m, type, a, b;
    int c = 0;
    cin >> m;
    node* root = new node(nullptr, nullptr, 0);
    while(m--)
    {
        cin >> type >> a >> b; a--; b--; a+=c; b+=c;
        if(type == 1)
        {
            c = sum(root, 0, 1000000000, a, b);
            cout << c << "\n";
        }
        else
            update(root, 0, 1000000000, a, b);
    }
}
