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
const int N = 1e5 + 3, F = 1e7 + 3, mod = 1e9 + 7,
        dx[] = {1, -1, 0, 0},
        dy[] = {0, 0, 1, -1},
        dx8[] = {1, -1, 0, 0, 1, -1, 1, -1},
        dy8[] = {0, 0, 1, -1, 1, -1, -1, 1};

enum STATE {
    UNVISITED = 0, EXPLORED = 1, VISITED
};


void solve() {
    ll n, addOn = 0, mxColor = 0;
    cin >> n;
    vp arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i].first;       // Elements
    for (int i = 0; i < n; ++i) cin >> arr[i].second, mxColor = max(mxColor, arr[i].second);     // Colors
    vector<vii > prefix(mxColor + 1);
    vii globalAdd(mxColor + 1);

    for (int j = 0; j < n; ++j) {
//      make prefix sum on each color
        ll lst = 0;
        if (!prefix[arr[j].second].empty())lst = prefix[arr[j].second].back();
        prefix[arr[j].second].push_back(arr[j].first + lst);
    }

    ll q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        ll type, color, c;
        cin >> type >> color >> c;
        if (type == 1) {
//          all elements will be increased by x except for the elements with this color
//          so we add -x on this element so it cancel the addition of addOn
            globalAdd[color] -= c;
            addOn += c;
        } else {
            ll l = 0, r = prefix[color].size() - 1, mid, ans = -1;
            while (l <= r) {
                mid = (l + r) >> 1;
                ll val = prefix[color][mid] + ((mid + 1) * (addOn + globalAdd[color]));
                if (val <= c)ans = mid, l = mid + 1;
                else r = mid - 1;
            }
            cout << ans + 1 nl;
        }
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
