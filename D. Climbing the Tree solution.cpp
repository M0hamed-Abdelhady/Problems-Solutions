#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define pll pair<long long , long long >
#define vi vector<int>
#define pq priority_queue<ll>
#define rpq priority_queue<ll, vi, greater<int>>
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


class calculateTime {
    inline static chrono::high_resolution_clock::time_point _s_START_, _e_END_;
public:
    static void start() {
        _s_START_ = chrono::high_resolution_clock::now();
    }

    static double finish() {
        _e_END_ = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = _e_END_ - _s_START_;
        return duration.count();
    }
};


//-----------------------------------------------------`|||`-----------------------------------------------------\\
\\-----------------------------------------------------`\|/`-----------------------------------------------------//
const int N = 2e5 + 3, F = 1e6 + 3, mod = 1e9 + 7,
        dx[] = {1, -1, 0, 0},
        dy[] = {0, 0, 1, -1},
        dx8[] = {1, -1, 0, 0, 1, -1, 1, -1},
        dy8[] = {0, 0, 1, -1, 1, -1, -1, 1};

enum STATE {
    UNVISITED = -1, EXPLORED, VISITED
};


bool intersect(pll &a, pll &b) {
/// Given two ranges a and b, is a and b intersect ?
    return ((b.first >= a.first && b.first <= a.second) || (b.second >= a.first && b.second <= a.second) ||
            (a.first >= b.first && a.second <= b.second));
}

ll solution(ll &a, ll &b, ll &c) {
//    (a - b) * n + a >= c
/// Given a, b and c find smallest n
    if (a >= c)return 1;
    ll x = (c - a), y = a - b, n = x / y;
    return (x % y ? n + 2 : n + 1);
}

void solve() {
    ll q;
    cin >> q;
///    The initial range of the height of the tree
    pll currentHeight = {LLONG_MIN, LLONG_MAX};
    while (q--) {
        ll type, a, b, n;
        cin >> type;
        if (type == 1) {
            cin >> a >> b >> n;
            pll newHeight;
///         The new range of the height of the tree according to the query
            if (n >= 2)newHeight = {(a - b) * (n - 2) + a + 1, (a - b) * (n - 1) + a};
            else newHeight = {1, a};
            if (intersect(currentHeight, newHeight)) {
///          if the new range intersect with the current range update current range else ignore it
                currentHeight = {max(currentHeight.first, newHeight.first), min(currentHeight.second, newHeight.second)};
                cout << "1 ";
            } else cout << "0 ";
        } else {
            cin >> a >> b;
///          find solution for n days that needed to climb equal to the upper boundary of current range or more
            n = solution(a, b, currentHeight.second);
            if (n == 1) {
                cout << n sp;
                continue;
            }
            ll last = (a - b) * (n - 2) + a;
///          check if the solution when find cover all the current range
///          so that we make sure whatever the value of h in this range the solution will be true always
            if (last < currentHeight.first)cout << n sp;
            else cout << "-1 ";
        }
    }
    cout nl;
}


int main() {
    DarkNess::Fast();
    DarkNess::Files();
//-----------------------------------------------------`main`-----------------------------------------------------//
    ll T = 1;
    cin >> T;
    while (T--)solve();
    return 0;
}