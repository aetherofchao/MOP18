#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;                  cin >> N;
    long long K;            cin >> K;
    vector<long long> A(N); for (int n=0; n<N; ++n) cin >> A[n];
    
    long long lo = A[0]+A[1]+A[2]-1, hi = A[N-1]+A[N-2]+A[N-3];
    // invariant: je primálo trojíc so súčtom <= lo, je dosť trojíc so súčtom <= hi
    while (hi - lo > 1) {
        long long med = (lo+hi) / 2;
        // ideme vypočítať, koľko trojíc má súčet <= med
        long long cnt = 0;
        for (int p=2; p<N; ++p) {
            int max_r = 0;
            for (int q=1; q<p; ++q) {
                // upravíme hodnotu max_r: najväčšie r také, že A[p]+A[q]+A[r] <= med
                if (A[p] + A[q] + A[q-1] <= med) {
                    max_r = q-1;
                } else {
                    while (max_r >= 0 && A[p] + A[q] + A[max_r] > med) --max_r;
                }
                cnt += (max_r + 1);
            }
        }
        // podľa výsledku zmenšíme na polovicu interval v ktorom hľadáme odpoveď
        if (cnt >= K) hi = med; else lo = med;
    }
    cout << hi << endl;
}
