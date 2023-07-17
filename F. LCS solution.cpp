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
const int N = 50 + 3, F = 3e3 + 3, mod = 1e9 + 7,
        dx[] = {1, -1, 0, 0},
        dy[] = {0, 0, 1, -1},
        dx8[] = {1, -1, 0, 0, 1, -1, 1, -1},
        dy8[] = {0, 0, 1, -1, 1, -1, -1, 1};

enum STATE {
    UNVISITED = 0, EXPLORED = 1, VISITED
};

string a, b;
int dp[F][F];

int LCS(int i, int j) {
    if (i == a.size() || j == b.size()) return 0;
    if (~dp[i][j])return dp[i][j];
    if (a[i] == b[j]) dp[i][j] = LCS(i + 1, j + 1) + 1;
    else return dp[i][j] = max(LCS(i + 1, j), LCS(i, j + 1));
    return dp[i][j];
}


void solve() {
    cin >> a >> b;
//  find LCS(a, b) => The Longest Common Subsequence of the string a and b
    memset(dp, -1, sizeof dp);
    int mxLen = LCS(0, 0);
    int i = 0, j = 0;
    string c;
    while (mxLen) {
        if (a[i] == b[j])c.push_back(a[i]), ++i, ++j, --mxLen;
        else {
            if (dp[i + 1][j] >= dp[i][j + 1])++i;
            else ++j;
        }
    }
    cout << c nl;
}


int main() {
    DarkNess::Fast();
    DarkNess::Files();
//-----------------------------------------------------`main`-----------------------------------------------------//
    ll T = 1;
//    cin >> T;
    while (T--)solve();
    return 0;
}