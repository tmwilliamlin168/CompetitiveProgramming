/*
	- Use square root decomposition, split ponies into blocks
	- For each block, precalculate for each t from 1 to 10^5, how much mana will be present t seconds after a reset
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, bs=300;
int n, q, s[mxN], m[mxN], r[mxN], g[(mxN-1)/bs+1][mxN+3], lt1[(mxN-1)/bs+1], lt2[mxN], ti, li, ri;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> s[i] >> m[i] >> r[i];
		if(!r[i])
			continue;
		g[i/bs][1]+=r[i];
		g[i/bs][m[i]/r[i]+1]+=m[i]%r[i]-r[i];
		g[i/bs][m[i]/r[i]+2]-=m[i]%r[i];
	}
	for(int i=0; i<=(n-1)/bs; ++i) {
		lt1[i]=-1;
		for(int j=2; j<=mxN; ++j)
			g[i][j]+=g[i][j-1];
		for(int j=2; j<=mxN; ++j)
			g[i][j]+=g[i][j-1];
	}
	cin >> q;
	while(q--) {
		cin >> ti >> li >> ri, --li, --ri;
		long long ans=0;
		auto psh=[&](int i) {
			if(lt1[i]==-1)
				return;
			for(int j=i*bs; j<min((i+1)*bs, n); ++j)
				lt2[j]=lt1[i];
			lt1[i]=-1;
		};
		psh(li/bs);
		psh(ri/bs);
		auto ue=[&](int i) {
			ans+=min(s[i]+1ll*(ti-lt2[i])*r[i], 1ll*m[i]);
			s[i]=0;
			lt2[i]=ti;
		};
		for(; li%bs&&li<=ri; ++li)
			ue(li);
		for(; li+bs<=ri; li+=bs) {
			if(lt1[li/bs]==-1)
				for(int j=li; j<li+bs; ++j)
					ue(j);
			else
				ans+=g[li/bs][min(ti-lt1[li/bs], mxN)];
			lt1[li/bs]=ti;
		}
		for(; li<=ri; ++li)
			ue(li);
		cout << ans << "\n";
	}
}
