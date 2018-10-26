#include <bits/stdc++.h>
using namespace std;

int t, n;
string ss[32];
char ans[16];
bool fa;

int nd(const string &s) {
    unordered_set<char> cs;
    for(char c : s)
        cs.insert(c);
    return cs.size();
}

void ti(int i) {
    if(fa)
        return;
    if(i>=n) {
        fa=1;
        return;
    }
    auto tp=[&](array<int, 4> a) {
        for(int j=0; j<4; ++j)
            if(ans[a[j]]&&ans[a[j]]!=ss[i][j])
                return;
        char o[4];
        for(int j=0; j<4; ++j) {
            o[j]=ans[a[j]];
            ans[a[j]]=ss[i][j];
        }
        ti(i+1);
        for(int j=0; j<4; ++j)
            ans[a[j]]=o[j];
    };
    for(int j=0; j<4; ++j) {
        tp({j*4, j*4+1, j*4+2, j*4+3});
        tp({j*4+3, j*4+2, j*4+1, j*4});
        tp({j, j+4, j+8, j+12});
        tp({j+12, j+8, j+4, j});
    }
}

void solve() {
    cin >> n;
    for(int i=0; i<n; ++i)
        cin >> ss[i];
    memset(ans, 0, sizeof(ans));
    fa=0;
    ti(0);
    if(fa) {
        for(int i=0; i<16; ++i) {
            for(ans[i]='A'; ans[i]<'Z'; ++ans[i]) {
                fa=0;
                ti(0);
                if(fa)
                    break;
            }
        }
        for(int i=0; i<4; ++i) {
            for(int j=0; j<4; ++j)
                cout << ans[i*4+j];
            cout << "\n";
        }
    } else
        cout << "grid\nsnot\nposs\nible\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> t;
    while(t--) {
        solve();
        cout << "\n";
    }
}
