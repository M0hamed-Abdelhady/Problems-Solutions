#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define pi pair<int, int>
#define pii pair<ll, ll>
#define vi vector<int>
#define vii vector<ll>
#define vp vector<pii>
#define si set<ll>
#define msi multiset<ll>
#define de deque<ll>
#define mii map<ll, ll>
#define f(x, i, u) for (int i = u; i < x; i++)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define nl <<'\n'
#define sp <<' '
#ifndef ONLINE_JUDGE

#include "DEBUG.cpp"

#define debug(x) cerr << #x <<" "; let(x); cerr << endl;
#define debugArray(x, y) cerr << #x <<" "; let_array(x, y); cerr << endl;
#else
#define debug(x)
#define debugArray(x, y)
#endif

class DarkNess {
public:
    static void Files() {
#ifndef ONLINE_JUDGE
        freopen("INPUT.txt", "r", stdin);
        freopen("OUTPUT.txt", "w", stdout);
        freopen("BacKDooR.txt", "w", stderr);
#endif
    }

    static void Fast() {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    }
};


//-----------------------------------------------------`|||`-----------------------------------------------------\\
\\-----------------------------------------------------`\|/`-----------------------------------------------------//
const int N = 2e2 + 3, F = 1e5 + 1, mod = 1e9 + 7,
        dx[] = {1, -1, 0, 0},
        dy[] = {0, 0, 1, -1},
        dx8[] = {1, -1, 0, 0, 1, -1, 1, -1},
        dy8[] = {0, 0, 1, -1, 1, -1, -1, 1};

enum STATE {
    UNVISITED = 0, EXPLORED = 1, VISITED
};
ll dp[101][F];
vector<pair<ll, ll>> items(N);
ll n, w;


ll knapsack(ll i, ll value) {
    if (i == n || value == 0)return value ? INT_MAX : 0;
    if (dp[i][value])return dp[i][value];
    ll ans = 0;
    if (items[i].second <= value)
//      get minimum wight for the aim value
        ans = min(knapsack(i + 1, value - items[i].second) + items[i].first, knapsack(i + 1, value));
    else ans = knapsack(i + 1, value);
    return dp[i][value] = ans;
}


void solve() {
    cin >> n >> w;
    int sum = 0;
    for (int i = 0; i < n; ++i) cin >> items[i].first >> items[i].second, sum += items[i].second;
    for (int i = sum; i >= 0; --i) {
//      search for the first (largest) obtainable value that will fit in W
        if (knapsack(0, i) <= w)return void(cout << i nl);
    }
}


int main() {
    DarkNess::Fast();
    DarkNess::Files();
    //-----------------------------------------------------`main`-----------------------------------------------------//
    ll T = 1;
//    cin >> T;
    while (T--)solve();
}
