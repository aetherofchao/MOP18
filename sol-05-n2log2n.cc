#include <bits/stdc++.h>
using namespace std;

long long count_leq(const vector<long long> &A, long long val) {
    int lo = -1, hi = A.size();
    while (hi - lo > 1) {
        int med = (lo+hi) / 2;
        if (A[med] > val) hi = med; else lo = med;
    }
    return hi;
}

int main() {
    int N;
    cin >> N;
    long long K;
    cin >> K;
    vector<long long> A(N);
    for (int n=0; n<N; ++n) cin >> A[n];
    sort( A.begin(), A.end() );
    
    long long lo = A[0]+A[1]+A[2]-1, hi = A[N-1]+A[N-2]+A[N-3];
    while (hi - lo > 1) {
        long long med = (lo+hi) / 2;
        long long cnt = 0;
        for (int c=2; c<N; ++c) {
            for (int b=1; b<c; ++b) {
                if (A[c] + A[b] + A[0] > med) break;
                cnt += min( (long long)b, count_leq( A, med-A[c]-A[b] ) );
            }
        }
        if (cnt >= K) hi = med; else lo = med;
    }
    cout << hi << endl;
}
