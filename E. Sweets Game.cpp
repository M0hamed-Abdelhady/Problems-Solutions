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

class calculateTime {
    inline static chrono::high_resolution_clock::time_point Start, End;
public:
    static void start() {
        Start = chrono::high_resolution_clock::now();
    }

    static double finish() {
        End = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = End - Start;
        return duration.count();
    }
};

//-----------------------------------------------------`|||`-----------------------------------------------------\\
\\-----------------------------------------------------`\|/`-----------------------------------------------------//
const int N = 1 << 19, F = 1e7 + 3, mod = 1e9 + 7,
        dx[] = {1, -1, 0, 0},
        dy[] = {0, 0, 1, -1},
        dx8[] = {1, -1, 0, 0, 1, -1, 1, -1},
        dy8[] = {0, 0, 1, -1, 1, -1, -1, 1};

enum STATE {
    UNVISITED = -1, EXPLORED, VISITED
};
int dp[N + 1][2];

int input() {
    string s, bin;
    for (int i = 0; i < 5; ++i) {
        getline(cin, s);
        for (const auto &j: s)
            if (j == '.')bin.push_back('0');
            else if (j == 'O')bin.push_back('1');
    }
    int x = 0, value = 1;
    for (auto i = bin.rbegin(); i != bin.rend(); ++i) {
        if (*i == '1')x += value;
        value <<= 1;
    }
    return x;
}

int value(int player) {
    if (player)return 1;
    else return -1;
}

vi validMasks;

void findValidMasks(int grid) {
    vi masks[15] = {{1,  2,  3},
                    {4,  5,  6,  7},
                    {8,  9,  10, 11, 12},
                    {13, 14, 15, 16},
                    {12, 16, 19},
                    {1,  4,  8},
                    {2,  5,  9,  13},
                    {3,  6,  10, 14, 17},
                    {7,  11, 15, 18},
                    {17, 18, 19},
                    {3,  7,  12},
                    {2,  6,  11, 16},
                    {1,  5,  10, 15, 19},
                    {4,  9,  14, 18},
                    {8,  13, 17},};
    for (const auto &arr: masks) {
        for (int i = 0; i < arr.size(); ++i) {
            int mask = 0;
            for (int j = i; j < arr.size(); ++j) mask |= 1 << (arr[j] - 1), validMasks.push_back(mask);
        }
    }
}

int minmax(int grid, int player) {
    if (grid == 0)return value(player);
    if (dp[grid][player])return dp[grid][player];
    if (!player) {
        int ans = -1;
        for (const auto &mask: validMasks) {
            if ((grid & mask) == mask) {
                ans = minmax(grid & ~mask, 1 - player);
            }
            if (ans == 1)break;
        }
        return dp[grid][player] = ans;
    } else {
        int ans = 1;
        for (const auto &mask: validMasks) {
            if ((grid & mask) == mask) {
                ans = minmax(grid & ~mask, 1 - player);
            }
            if (ans == -1)break;
        }
        return dp[grid][player] = ans;
    }
}


int main() {
    DarkNess::Fast();
    DarkNess::Files();
//-----------------------------------------------------`main`-----------------------------------------------------//
    int grid = input();
    findValidMasks(grid);
    if (minmax(grid, 0) > 0)cout << "Karlsson\n";
    else cout << "Lillebror\n";
    return 0;
}