#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int M=1e9+7;
int r, c, q;
vector<ll> iv{0, 1};

ll nck(ll n, ll k) {
	k=min(n-k, k);
	while(k>=iv.size())
		iv.push_back(M-M/iv.size()*iv[M%iv.size()]%M);
	ll ans=1;
	for(int i=0; i<k; ++i) {
		ans=ans*(n-i)%M;
		ans=ans*iv[i+1]%M;
	}
	return ans;
}

ar<int, 2> sb(int a, int b) {
	if(a==r-1&&b==0)
		return {1, 1};
	if(r-1<=a+b)
		return {2, 1};
	int co=(r-1-a-b-1)/(2*c-2), r2=r-co*(2*c-2), em=2*co, sl;
	if(r2-1<=a+2*c-2-b) {
		++em;
		sl=(a+2*c-2-b-(r2-1))/2;
	} else {
		em+=2;
		sl=(a+2*c-2-(r2-1-b))/2;
	}
	int t=nck(sl+em, em);
	if(sl>a)
		t=(t+M-nck(sl-a-1+em, em))%M;
	return {em+2, t};
}

vector<vector<int>> sk(int p) {
	vector<vector<int>> a(c, vector<int>(c));
	if(!p) {
		for(int i=0; i<c; ++i)
			a[i][i]=1;
	} else if(p&1) {
		vector<vector<int>> b=sk(p-1);
		for(int i=0; i<c; ++i) {
			for(int j=0; j<c; ++j) {
				if(j)
					a[i][j]+=b[i][j-1];
				if(j+1<c)
					a[i][j]+=b[i][j+1];
				a[i][j]=((ll)a[i][j]+b[i][j])%M;
			}
		}
	} else {
		vector<vector<int>> b=sk(p/2);
		for(int i=0; i<c; ++i)
			for(int k=0; k<c; ++k)
				a[i][0]=(a[i][0]+(ll)b[i][k]*b[k][0])%M;
		for(int j=1; j<c; ++j)
			for(int k=0; k<c; ++k)
				a[0][j]=(a[0][j]+(ll)b[0][k]*b[k][j])%M;
		for(int i=1; i<c; ++i)
			for(int j=1; j<c-i; ++j)
				a[i][j]=(a[i-1][j-1]+a[0][i+j])%M;
		for(int i=0; i<c; ++i)
			for(int j=0; i+j<c-1; ++j)
				a[c-1-i][c-1-j]=a[i][j];
	}
	return a;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> r >> c >> q;
	vector<vector<int>> d=sk(r-1);
	while(q--) {
		char qt;
		int a, b;
		cin >> qt >> a >> b, --a, --b;
		ar<int, 2> ans;
		if(qt=='P') {
			ans=a^b?ar<int, 2>{}:ar<int, 2>{r-1, 1};
		} else if(qt=='R') {
			ans=a^b?ar<int, 2>{2, 2}:ar<int, 2>{1, 1};
		} else if(qt=='Q') {
			if(a>b)
				swap(a, b);
			ans=a==b||a==0&&b==r-1?ar<int, 2>{1, 1}:ar<int, 2>{2, 4+(a==0&&r==c)+(b==r-1)+(a%2==(b+r-1)%2&&(a+b+r-1)/2<c)+(a%2==(b+r-1)%2&&(a+b-r+1)/2>=0)};
		} else if(qt=='B') {
			if(a%2==(b+r-1)%2) {
				ar<int, 2> a1=sb(a, b), a2=sb(c-1-a, c-1-b);
				ans={min(a1[0], a2[0])};
				if(a1[0]==ans[0])
					ans[1]+=a1[1];
				if(a2[0]==ans[0])
					ans[1]+=a2[1];
			} else
				ans={};
		} else if(qt=='K') {
			ans={r-1, d[a][b]};
		}
		cout << ans[0] << " " << ans[1]%M << "\n";
	}
}
