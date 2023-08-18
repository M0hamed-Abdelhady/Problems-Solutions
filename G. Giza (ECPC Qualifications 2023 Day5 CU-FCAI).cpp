#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vll vector<ll>
#define vd vector<double>
#define vp vector<pll>
#define sll set<ll>
#define msll multiset<ll>
#define pq priority_queue<ll>
#define rpq priority_queue<ll, vi, greater<int>>
#define f(i, u, x) for (int i = u; i < x; i++)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define nl <<'\n'
#define sp <<' '
#ifndef ONLINE_JUDGE

#include "DEBUG.cpp"

#define debug(x) cerr << #x <<" "; let(x); cerr << endl;
#else
#define debug(x)
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
const int N = 51, F = 1e7 + 3, mod = 1e9 + 7,
        dx[] = {1, -1, 0, 0},
        dy[] = {0, 0, 1, -1},
        dx8[] = {1, -1, 0, 0, 1, -1, 1, -1},
        dy8[] = {0, 0, 1, -1, 1, -1, -1, 1};

enum STATE {
    UNVISITED = -1, EXPLORED, VISITED
};

int v[N + 1];
int primeFactorsMasks[N + 1];

void sieve() {
    int prime = 0;
    for (int i = 2; i <= N; i++) {
        if (!v[i]) {
            ++prime;
            for (int j = i; j <= N; j += i)
                primeFactorsMasks[j] |= 1 << (prime - 1), v[j] = 1;
        }
    }
}


int DP(int mask, int sum, vector<vi > &dp) {
    if (sum == 0)return 1;
    else if (sum < 0)return 0;
    if (dp[sum][mask])return dp[sum][mask];
    int ans = 0;
    for (int j = 1; j <= sum; ++j) {
        int msk = primeFactorsMasks[j];
        if (!(msk & mask)) {
            ans += DP(mask | msk, sum - j, dp);
        }
    }
    return dp[sum][mask] = ans;
}


int main() {
    DarkNess::Fast();
    DarkNess::Files();
//-----------------------------------------------------`main`-----------------------------------------------------//
    int T = 1;
    sieve();
    vll res(51);
    for (int i = 1; i <= 50; ++i) {
        vector<vi > dp(51, vi(1 << 15));
        res[i] = DP(0, i, dp);
    }
    for (int i = 1; i < 51; ++i) res[i] += res[i - 1];
    cin >> T;
    while (T--) {
        int l, r;
        cin >> l >> r;
        cout << res[r] - res[l - 1] nl;
    }
    return 0;
}