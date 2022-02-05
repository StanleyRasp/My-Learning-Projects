#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6;
const int MOD = 1e9 + 7;
const int p = 29;
int power[MAXN + 1] = {1};
int hashTable[MAXN];

bool compareHash(int p1, int k1, int p2, int k2){
    int hash1 = hashTable[k1];
    if (p1 > 0) hash1 -= hashTable[p1 - 1];

    int hash2 = hashTable[k2];
    if (p2 > 0) hash2 -= hashTable[p2 - 1];

    if ((hash1 * power[p2 - p1]) % MOD == hash2){
        return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 1; i < MAXN + 1; ++i){
        power[i] = (power[i-1] * p) % MOD;
    }
  
  return 0;
}
