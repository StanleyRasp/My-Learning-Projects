#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;

struct event{
    char type;
    int a, b;
};

typedef pair<long long, int> pli;
pli operator + (pli a, pli b){
    return make_pair(a.first + b.first, a.second + b.second);
}

const int base = 1 << 20;
pli tree[base * 2];
vector<int> baseValues;
map<long long, int> baseIndexes;

void addAtValue(int val){
    int index = baseIndexes[val], treeIndex = base + index;
    tree[treeIndex].second ++;
    tree[treeIndex].first = tree[treeIndex].second * baseValues[index];

    while (treeIndex > 1){
        treeIndex >>= 1;
        tree[treeIndex] = tree[treeIndex << 1] + tree[(treeIndex << 1) + 1];
    }
}

void subtractAtValue(int val){
    int index = baseIndexes[val], treeIndex = base + index;
    tree[treeIndex].second --;
    tree[treeIndex].first = tree[treeIndex].second * baseValues[index];

    while (treeIndex > 1){
        treeIndex >>= 1;
        tree[treeIndex] = tree[treeIndex << 1] + tree[(treeIndex << 1) + 1];
    }
}

long long sumForSetKm(int km, int v = 1, int a = 0, int b = base - 1){
    if (baseValues[b] <= km) return tree[v].first;
    else if (baseValues[a] >= km) return tree[v].second * km;
    else{
        int l = v << 1, r = (v << 1) + 1, mid = (a + b) / 2;
        return sumForSetKm(km, l, a, mid) + sumForSetKm(km, r, mid + 1, b);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    event eventTimeline[m];
    for (int i = 0; i < m; ++i){
        cin >> eventTimeline[i].type >> eventTimeline[i].a >> eventTimeline[i].b;
        if (eventTimeline[i].type == 'U'){
            baseValues.push_back(eventTimeline[i].b);
            eventTimeline[i].a -= 1;
        }
    }

    sort(baseValues.begin(), baseValues.end());

    int baseValueAmt = baseValues.size();
    for (int i = baseValueAmt; i < base; ++i){
        baseValues.push_back(INF);
    }

    for (int i = 0; i < baseValueAmt; ++i){
        baseIndexes[baseValues[i]] = i;
    }

    long long drivers[n];
    fill_n(drivers, n, 0);
    for (event ev : eventTimeline){
        if(ev.type == 'U'){
            if (0 < drivers[ev.a]) subtractAtValue(drivers[ev.a]);
            drivers[ev.a] = ev.b;
            addAtValue(drivers[ev.a]);
        } else {
            long long sum = sumForSetKm(ev.b);
            if (ev.a * ev.b <= sum){
                cout << "TAK" << '\n';
            } else {
                cout << "NIE" << '\n';
            }
        }
    }

    return 0;
}
