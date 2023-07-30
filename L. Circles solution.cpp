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
#define si set<int>
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
const int N = 2e5 + 3, F = 1e6 + 3, mod = 1e9 + 7,
        dx[] = {1, -1, 0, 0},
        dy[] = {0, 0, 1, -1},
        dx8[] = {1, -1, 0, 0, 1, -1, 1, -1},
        dy8[] = {0, 0, 1, -1, 1, -1, -1, 1};

enum STATE {
    UNVISITED = -1, EXPLORED, VISITED
};


struct circle {
    ///    x^2 + y^2 + 2xa + 2yb + c = 0
    double a, b, c;
};


bool valid(circle &s, pii x) {
    double eps = 1e-6;
    double ans = abs(pow(x.first, 2) + pow(x.second, 2) + (2 * s.a * x.first) + (2 * s.b * x.second) + s.c);
    return ans <= eps;
}


double determinant(vector<vector<double>> matrix) {
    ///     evaluate the determinant of the matrix
    double ans;
    ans = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2])
          - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
          + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    return ans;
}


circle findSolution(vector<vector<double>> full) {
///     solve equation by cramer's rule
    vector<vector<double>> d(3, vector<double>(3)), d1(3, vector<double>(3)),
            d2(3, vector<double>(3)), d3(3, vector<double>(3));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            d[i][j] = full[i][j];
        }
    }
    for (int i = 0; i < 3; ++i) {
        d1[i][0] = full[i][3];
        for (int j = 1; j < 3; ++j) {
            d1[i][j] = full[i][j];
        }
    }
    for (int i = 0; i < 3; ++i) {
        d2[i][1] = full[i][3];
        for (int j = 0; j < 3; ++j) {
            if (j == 1)continue;
            d2[i][j] = full[i][j];
        }
    }
    for (int i = 0; i < 3; ++i) {
        d3[i][2] = full[i][3];
        for (int j = 0; j < 3; ++j) {
            if (j == 2)continue;
            d3[i][j] = full[i][j];
        }
    }


    double D = determinant(d);
    double D1 = determinant(d1);
    double D2 = determinant(d2);
    double D3 = determinant(d3);

    if (D != 0) {
        double x = D1 / D;
        double y = D2 / D;
        double z = D3 / D;
        if (z == -0)z = 0;
        return {x, y, z};
    } else {
        return {NAN, NAN, NAN};
    }
}


vector<vector<double>> change(pair<double, double> a, pair<double, double> b, pair<double, double> c) {
///     put variables coefficients on a matrix
    vector<vector<double>> ans(3, vector<double>(4));
    ans = {{2 * a.first, 2 * a.second, 1, -(a.first * a.first) - (a.second * a.second)},
           {2 * b.first, 2 * b.second, 1, -(b.first * b.first) - (b.second * b.second)},
           {2 * c.first, 2 * c.second, 1, -(c.first * c.first) - (c.second * c.second)}};
    return ans;
}


void solve() {
    int n;
    cin >> n;
    vector<pair<double, double>> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i].first >> x[i].second;
    }
    if (n < 4)return void(cout << n nl);
    int q, mx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
///             each three coordinates that aren't on the same line can make exactly one circle
///             so for each three coordinates iterate for all pairs to find more coordinates on that circle
                circle s = findSolution(change(x[i], x[j], x[k]));
                q = 3;
                for (int l = 0; l < n; ++l) {
                    if (l == i || l == j || l == k)continue;
                    if (valid(s, x[l]))++q;
                }
                mx = max(mx, q);
            }
        }
    }
    cout << mx nl;
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
