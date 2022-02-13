// Solution using a segment-segment segment tree data structure in O(mlogn)

#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 3e5;
const long long base = 1 << 19;
long long tree[base * 2];
pair<long long, long long> lazy[base * 2];
long long receivers[MAXN + 1][2];

void propagate(long long l, long long r, long long v, long long a, long long b){
    long long mid = (a + b)/2, ls = lazy[v].first, rs = lazy[v].first + lazy[v].second * (mid - a + 1);
    lazy[l].first += ls;
    lazy[l].second += lazy[v].second;
    lazy[r].first += rs;
    lazy[r].second += lazy[v].second;
    tree[l] += (long long)(((double)(2 * ls + (mid - a) * lazy[v].second) / 2) * (double)(mid - a + 1));
    tree[r] += (long long)(((double)(2 * rs + (mid - a) * lazy[v].second) / 2) * (double)(mid - a + 1));
    lazy[v] = {0, 0};
    if (l > base - 1) lazy[l] = {0, 0};
    if (r > base - 1) lazy[r] = {0, 0};
}

void addArithmaticSeries(long long p, long long k, long long s, long long rest, long long v = 1, long long a = 0, long long b = base - 1){
    if (b < p || k < a) return;
    else if (p <= a && b <= k)
    {
        long long newS = s + (a - p) * rest, newR = rest;
        lazy[v].first += newS;
        lazy[v].second += newR;
        tree[v] += (long long)(((double) (2 * newS + (b - a) * newR) / 2) * (double)(b - a + 1));
        if (v > base - 1) lazy[v] = {0, 0};
    }
    else{
        long long l = v << 1, r = (v << 1) + 1, mid = (a + b) / 2;

        propagate(l, r, v, a, b);

        addArithmaticSeries(p, k, s, rest, l, a, mid);
        addArithmaticSeries(p, k, s, rest, r, mid + 1, b);

        tree[v] = tree[l] + tree[r];
    }
}

long long sumAtSegment(long long p, long long k, long long v = 1, long long a = 0, long long b = base - 1){
    if (b < p || k < a) return 0;
    else if (p <= a && b <= k) return tree[v];
    else{
        long long l = v << 1, r = (v << 1) + 1, mid = (a + b) / 2;

        propagate(l, r, v, a, b);

        return sumAtSegment(p, k, l, a, mid) + sumAtSegment(p, k, r, mid + 1, b);
    }
}

void placeReceiver(long long x, long long s, long long r){
    auto length = (long long) ceil((double)s / (double)r);
    addArithmaticSeries(x, min(base * 2 - 1, x + length - 1), s, -1 * r);
    long long firstVal = s - min(x, length - 1) * r;
    addArithmaticSeries(max((long long)0, x - length + 1), x - 1, firstVal, r);
}

void deleteReceiver(long long x){
    placeReceiver(x, -1 * receivers[x][0], -1 * receivers[x][1]);
}

void averageSignalAtSegment(long long p, long long k){
    cout << sumAtSegment(p, k) / (k - p + 1) << endl;
}

void printSegmentTreeArray(){
    for(long long i = 0; i < base; ++i){
        long long sum = sumAtSegment(i, i), tmpSum = sum, zeros = 1;
        while (tmpSum / 10 >= 1){
            zeros ++;
            tmpSum /= 10;
        }

        cout << sum << " ";
        for (long long j = 0; j < 2 - zeros; ++j){
            cout << " ";
        }
    }
    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    for(long long q = 0; q < m; ++q){
        char mode;
        cin >> mode;

        if (mode == 'P'){
            long long x, s, r;
            cin >> x >> s >> r;
            placeReceiver(x - 1, s, r);
            receivers[x - 1][0] = s;
            receivers[x - 1][1] = r;
        }
        if (mode == 'U'){
            long long x;
            cin >> x;
            deleteReceiver(x - 1);
        }
        if (mode == 'Z'){
            long long p, k;
            cin >> p >> k;
            averageSignalAtSegment(p - 1, k - 1);
        }
        if (mode == 'D'){
            printSegmentTreeArray();
        }
    }

    return 0;
}
