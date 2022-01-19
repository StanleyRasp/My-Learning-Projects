#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;
const int INF = 0x3f3f3f;
const int MOD = 1e9 + 7;

void printVec(vector<int> vec, int from = 0, int upto = INF, bool indexify = false){
    int l = vec.size();
    int lim = min(l, upto);

    for (int i = from; i < lim; ++i){
        if (indexify) cout << i << ": ";
        cout << vec[i] << " ";
        if (indexify) cout << ' ';
    }
    cout << '\n';
}

class SegTree{
public:
    int base, len, changeNum = 0;
    vector<pair<int, int>>  st;

    SegTree(int arr[], int l){
        len = l;
        st.resize(MAXN * 2);

        for (int val = 1; val < MAXN * 3; val *= 2){
            if (val >= l){
                base = val;
                break;
            }
        }

        for (int i = 0; i < l; ++i){
            st[base + i] = make_pair(arr[i], changeNum);
        }

        for (int i = base - 1; i > 0; --i){
            st[i] = make_pair(st[2 * i].first + st[2 * i + 1].first, changeNum);
        }
    }

    int readAtPos(int pos){
        pos += base;
        int res = st[pos].first, biggest = st[pos].second;
        while (pos > 1){
            pos /= 2;
            if (st[pos].second > biggest) {
                biggest = st[pos].second;
                res = st[pos].first;
            }
        }
        return res;
    }

    void changeSegment(int s, int e, int val){
        s = s - 1 + base;
        e = e + 1 + base;
        while (s / 2 != e / 2){
            if (s % 2 == 0) {
                changeNum = (changeNum + 1) % MOD;
                st[s + 1] = {val, changeNum};
            }
            if (e % 2 == 1) {
                changeNum = (changeNum + 1) % MOD;
                st[e - 1] = {val, changeNum};
            }
            s /= 2;
            e /= 2;
        }
    }
};

int main()
{

    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    SegTree segTree(arr, n);

    int mode = 3, a, b, c;
    while(mode != -1){
        cin >> mode;
        if (mode == 0){
            cin >> a;
            cout << segTree.readAtPos(a) << endl;
        } else if (mode == 1){
            cin >> a >> b >> c;
            segTree.changeSegment(a, b, c);
        } else {
            cout << "Mode not found!\n";
        }
    }

    return 0;
}
