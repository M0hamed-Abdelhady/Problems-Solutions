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
#define de deque<int>
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
const int N = 103, F = 3e3 + 3, mod = 1e9 + 7,
        dx[] = {1, -1, 0, 0},
        dy[] = {0, 0, 1, -1},
        dx8[] = {1, -1, 0, 0, 1, -1, 1, -1},
        dy8[] = {0, 0, 1, -1, 1, -1, -1, 1};

enum STATE {
    UNVISITED = 0, EXPLORED = 1, VISITED
};
int n;

void MCM(vector<vi > &dp, vector<vi > &newColor) {
//  search for Matrix Chain Multiplication (MCM)
    for (int i = 1; i < n; ++i) {
//      i for range difference => from j to j + i
        for (int j = 0; j + i < n; ++j) {
//          j for the index
            vi ans, col;
            for (int k = j; k < j + i; ++k) {
//              k for the range pairs
//              (ex: r1({1, k = 1} => {k + 1 = 2, 4}), r2({1, k = 2} => {k + 1 = 3, 4}...))
                int res1 = newColor[j][k], res2 = newColor[k + 1][j + i];
                ans.push_back(dp[j][k] + dp[k + 1][j + i] + (res1 * res2));
                col.push_back((res1 + res2) % 100);
            }
            int ind = min_element(all(ans)) - ans.begin();
            dp[j][j + i] = ans[ind];
            newColor[j][j + i] = col[ind];
        }
    }
}



int main() {
    DarkNess::Fast();
    DarkNess::Files();
//-----------------------------------------------------`main`-----------------------------------------------------//
    ll T = 1;
//    cin >> T;
    while (cin >> n) {
        vi mixtures(n);
        vector<vi > dp(n, vi(n)), newColor(n, vi(n));
        for (int i = 0; i < n; ++i) cin >> mixtures[i], newColor[i][i] = mixtures[i];
        MCM(dp, newColor);
        cout << dp[0][n - 1] nl;
    };
    return 0;
}
