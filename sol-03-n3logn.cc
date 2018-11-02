#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    long long K;
    cin >> K;
    vector<long long> A(N);
    for (int n=0; n<N; ++n) cin >> A[n];
    vector<long long> sucty;
    for (int c=0; c<N; ++c) for (int b=0; b<c; ++b) for (int a=0; a<b; ++a) sucty.push_back( A[a]+A[b]+A[c] );
    sort( sucty.begin(), sucty.end() );
    cout << sucty[K-1] << endl;
}
