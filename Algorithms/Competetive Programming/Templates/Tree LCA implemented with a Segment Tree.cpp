#include <bits/stdc++.h>
using namespace std;

// misc variables
const int MAXN = 1e5;
const int INF = 0x3f3f3f;

// misc functions
void swap(int &a, int &b){
    int tmp = b;
    b = a;
    a = tmp;
}

// graph variables
int moment = 0;
int eulerTour[2 * MAXN - 1];
int eulerDepth[2 * MAXN - 1];
int depth[MAXN];
int last[MAXN];
bool visited[MAXN];
vector<int> adj[MAXN];

// graph functions
void addEdge(int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void populate(int v){
    eulerTour[moment] = v;
    eulerDepth[moment] = depth[v];
    last[v] = moment;
    moment ++;
}

void dfs(int v = 0){
    visited[v] = true;
    populate(v);
    for (int child : adj[v]){
        if (!visited[child]) {
            depth[child] = depth[v] + 1;
            dfs(child);
            populate(v);
        }
    }
}

// segment tree variables
const int base = 1 << 18;
pair<int, int> st[2 * base];

// segment tree functions
void build(int arr[], int n){
    for (int i = 0; i < n; ++i){
        st[base + i] = {eulerDepth[i], i}; // should use reference to arr not hardcoded eulerTour
    }

    for (int i = base - 1; i > 0; --i){
        st[i] = min(st[i<<1], st[(i<<1) + 1]);
    }
}

pair<int, int> indexOfSmallestAtRange(int p, int k, int v = 1, int a = 0, int b = base - 1){
    if (b < p || k < a) return {INF, INF};
    else if (p <= a && b <= k) return st[v];
    else {
        int l = v << 1, r = (v << 1) + 1, mid = (a + b) / 2;
        return min(indexOfSmallestAtRange(p, k, l, a, mid), indexOfSmallestAtRange(p, k, r, mid + 1, b));
    }
}

// lca functions
void setup(){
    depth[0] = 0;
    moment = 0;
    fill_n(visited, MAXN, false);
    dfs();

    fill_n(st, 2 * base, make_pair(INF, INF));
    build(eulerDepth, 2 * MAXN - 1);
}

int lca(int u, int v){
    if (v < u) swap(u, v);
    pair<int, int> valueIndexPair = indexOfSmallestAtRange(last[u], last[v]);
    return eulerTour[valueIndexPair.second];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    addEdge(0, 1);
    addEdge(1, 3);
    addEdge(0, 2);
    addEdge(2, 4);
    addEdge(4, 6);
    addEdge(2, 5);

    setup();
    cout << lca(4, 1);
    return 0;
}
