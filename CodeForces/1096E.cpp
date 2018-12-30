#include <bits/stdc++.h>
using namespace std;

#define ll long long
int p, s, r, M=998244353;
ll iv[5100], f1[5100], f2[5100], ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	iv[1]=f1[0]=f1[1]=f2[0]=f2[1]=1;
	for(int i=2; i<5100; ++i) {
		iv[i]=(M-M/i)*iv[M%i]%M;
		f1[i]=f1[i-1]*i%M;
		f2[i]=f2[i-1]*iv[i]%M;
	}
	cin >> p >> s >> r;
	for(int i=1; i<=p&&s-r*i>=0; ++i)
		ans+=(i&1?1:-1)*f1[s-r*i+p-1]*f2[s-r*i]%M*f2[i]%M*f2[p-i]%M;
	ans=(ans%M+M)*f1[p-1]%M*f1[s-r]%M*f2[s-r+p-1]%M;
	cout << ans;
}
