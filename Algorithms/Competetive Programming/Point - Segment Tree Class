#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

const int MAXN = 1e6 + 10;
const int INF = 0x3f3f3f;

void printVec(vi vec, int from = 0, int upto = INF, bool indexify = false){
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
    int base, len;
    vi st;

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
            st[base + i] = arr[i];
        }

        for (int i = base - 1; i > 0; --i){
            st[i] = st[2 * i] + st[2 * i + 1];
        }
    }

    void changeST(int pos, int value){
        pos += base;
        st[pos] = value;
        while (pos > 1){
            pos /= 2;
            st[pos] = st[2 * pos] + st[2 * pos + 1];
        }
    }

    int sumInSegment(int a, int b){
        int res = 0;
        a = a - 1 + base;
        b = b + 1 + base;
        while (a / 2 != b / 2){
            if (a % 2 == 0) res += st[a + 1];
            if (b % 2 == 1) res += st[b - 1];
            a /= 2;
            b /= 2;
        }
        return res;
    }

    void printArr(){
        printVec(st, base, base + len);
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

    int mode = 3, a, b;
    while(mode != -1){
        cin >> mode;
        if (mode == 0){
            segTree.printArr();
        }
        else if (mode == 1){
            cin >> a >> b;
            segTree.changeST(a, b);
        }
        else if (mode == 2){
            cin >> a >> b;
            cout << segTree.sumInSegment(a, b) << endl;
        } else {
            cout << "Mode not found!\n";
        }
    }

    return 0;
}
