#include <bits/stdc++.h>
using namespace std;

int N;
long long K;
vector<long long> A;

struct triple { 
    int a,b,c; 
    long long sum() const { return A[a]+A[b]+A[c]; }
};

set<triple> candidates;

bool operator<(const triple &X, const triple &Y) {
    long long xs = X.sum(), ys = Y.sum();
    if (xs != ys) return xs < ys;
    return make_tuple(X.a,X.b,X.c) < make_tuple(Y.a,Y.b,Y.c);
}

int main() {
    cin >> N >> K;
    A.resize(N);
    for (int n=0; n<N; ++n) cin >> A[n];

    candidates.insert( {0,1,2} );
    while (true) {
        triple curr = *candidates.begin();
        candidates.erase( candidates.begin() );
        --K;
        if (K == 0) { cout << curr.sum() << endl; break; }
        if (curr.a+1 < curr.b) candidates.insert( {curr.a+1,curr.b,curr.c} );
        if (curr.b+1 < curr.c) candidates.insert( {curr.a,curr.b+1,curr.c} );
        if (curr.c+1 < N     ) candidates.insert( {curr.a,curr.b,curr.c+1} );
    }
}
