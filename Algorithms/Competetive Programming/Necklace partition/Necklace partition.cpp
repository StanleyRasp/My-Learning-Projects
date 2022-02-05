// Suboptimal solution in worst case O(n^2) but usually closer to O(n)

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6;
const int INF = 0x3f3f3f;
int arr[MAXN], last[MAXN+1], first[MAXN+1];
bool singleCuts[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;


    fill_n(first, MAXN+1, -1);
    for (int i = 0; i < n; ++i){
        cin >> arr[i];
        last[arr[i]] = i;
        if (first[arr[i]] == -1) first[arr[i]] = i;
    }

    int ways = 0, minDiff = INF, iterLast;
    for (int i = 0; i < n; ++i){
        iterLast = last[arr[i]];
        for (int j = i; j < n; ++j){
            if (j - i + 1 == n) break;
            if (first[arr[j]] < i) break;
            iterLast = max(iterLast, last[arr[j]]);
            if (j == iterLast) {
                if ((i == 0 and singleCuts[j]) or (j == n - 1 and singleCuts[i-1])) continue;
                if (i == 0) singleCuts[j] = true;
                if (j == n - 1) singleCuts[i-1] = true;
                ways++;
                minDiff = min(minDiff, abs(2 * (j - i + 1) - n));
            }
        }
    }

    cout << ways << " " << minDiff << endl;

    return 0;
}
