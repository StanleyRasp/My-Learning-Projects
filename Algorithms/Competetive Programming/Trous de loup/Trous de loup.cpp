// Built in O(n) time complexity using prefix sums and a monotonic queue to hold the maximum value on a segment.

#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 2e6;

long long arr[MAXN], dech[MAXN];
long long prefix[MAXN];
deque<pair<long long, long long>> deq;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long n, p, d;
    cin >> n >> p >> d;

    for (int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    prefix[0] = arr[0];
    for (int i = 1; i < n; ++i){
        prefix[i] = prefix[i-1] + arr[i];
    }

    dech[d - 1] = prefix[d - 1];
    for (int i = d; i < n; ++i){
        dech[i] = dech[i-1] + arr[i] - arr[i - d];
    }

    int start = 0, end = d - 1, maxSize = d;
    deq.emplace_front(dech[end], d - 1);
    while (start < n && end < n){
        long long sum;
        if (0 < start) sum = prefix[end] - prefix[start - 1] - deq.front().first;
        else sum = prefix[end] - deq.front().first;

        if (sum <= p){
            maxSize = max(end - start + 1, maxSize);
            if (end == n - 1) break;
            end ++;
            while (!deq.empty() && deq.back().first <= dech[end]) deq.pop_back();
            deq.emplace_back(dech[end], end);
        }
        else {
            if (start == n - 1) break;
            start ++;
            while (!deq.empty() && deq.front().second < start + d - 1) deq.pop_front();
        }
    }

    cout << maxSize << endl;

    return 0;
}

