#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, mxM=2e5;
int n;
string s;

struct autoac {
    int sl[mxN+1], ol[mxN+1], sz=1, c[mxN+1][256], qu[mxN+1];
    vector<int> oc[mxN];
    vector<array<int, 2>> no[mxN+1];
    void add(string s, int i) {
        int u=0;
        for(char a : s) {
            if(!c[u][a])
                c[u][a]=sz++;
            u=c[u][a];
        }
        ol[u]=u;
        no[u].push_back({i, s.size()});
    }
    void ac() {
        sl[0]=-1;
        int qt=0;
        qu[qt++]=0;
        for(int qh=0; qh<qt; ++qh) {
            int u=qu[qh];
            for(int a=0; a<256; ++a) {
                int v=c[u][a], w=sl[u];
                if(!v)
                    continue;
                while(w!=-1&&!c[w][a])
                    w=sl[w];
                if(w!=-1) {
                    sl[v]=c[w][a];
                    if(!ol[v])
                        ol[v]=ol[sl[v]];
                }
                qu[qt++]=v;
            }
        }
    }
    int feed(int u, char a, int i) {
        while(u&&!c[u][a])
            u=sl[u];
        u=c[u][a];
        int v=ol[u];
        while(v) {
            for(array<int, 2> b : no[v])
                oc[b[0]].push_back(i-b[1]+1);
            v=ol[sl[v]];
        }
        return u;
    }
} ac;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    while(cin >> n) {
        getline(cin, s);
        for(int i=0; i<n; ++i) {
            getline(cin, s);
            ac.add(s, i);
        }
        ac.ac();
        getline(cin, s);
        int u=0;
        for(int i=0; i<s.size(); ++i)
            u=ac.feed(u, s[i], i);
        for(int i=0; i<n; ++i) {
            for(int j : ac.oc[i])
                cout << j << " ";
            cout << "\n";
            ac.oc[i].clear();
        }
        memset(ac.sl, 0, 4*ac.sz);
        memset(ac.ol, 0, 4*ac.sz);
        memset(ac.c, 0, sizeof(ac.c[0])*ac.sz);
        for(int i=0; i<ac.sz; ++i)
            ac.no[i].clear();
        ac.sz=1;
    }
}
