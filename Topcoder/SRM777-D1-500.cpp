#include <bits/stdc++.h>
using namespace std;

#define ar array

class StringTransformation {
public:
	vector<ar<int, 2>> g(string s) {
		vector<ar<int, 2>> r;
		for(int i=0, j=0; i<s.size(); i=j) {
			for(; j<s.size()&&s[j]==s[i]; ++j);
			if((j-i)&1)
				r.push_back({i, j-i});
		}
		return r;
	}
	vector<int> f(string s, int os) {
		vector<int> r;
		for(int i=0, j=0; i<s.size(); i=j) {
			for(; j<s.size()&&s[j]==s[i]; ++j);
			r.push_back(i+os);
		}
		r.push_back(s.size()+os);
		return r;
	}
	bool dp[1500][1500][3];
	string getResult(string s, string t) {
		vector<ar<int, 2>> a=g(s), b=g(t);
		if(a.size()!=b.size())
			return "NO";
		for(int i=0; i<a.size(); ++i)
			if(a[i][1]<b[i][1]||s[a[i][0]]^t[b[i][0]])
				return "NO";
		if(a.size()==1&&a[0][1]==s.size()&&a!=b)
			return "NO";
		a.push_back({(int)s.size()});
		b.push_back({(int)t.size()});
		int si=0, ti=0;
		for(int i=0; i<a.size(); ++i) {
			vector<int> v1=f(s.substr(si, a[i][0]-si), si), v2=f(t.substr(ti, b[i][0]-ti), ti);
			for(int j1=0; j1<v1.size(); ++j1)
				for(int j2=0; j2<v2.size(); ++j2)
			   		for(int k=0; k<3; ++k)
						dp[j1][j2][k]=0;
			dp[0][0][0]=1;
			for(int j1=0; j1+1<v1.size(); ++j1) {
				for(int j2=0; j2<v2.size(); ++j2) {
					dp[j1+1][j2][2]|=dp[j1][j2][2];
					if((j2||i)&&s[v1[j1]]^(j2?t[v2[j2-1]]:s[si-1])&&(j2<v2.size()-1||i<a.size()-1)&&s[v1[j1]]^(j2<v2.size()-1?t[v2[j2]]:s[a[i][0]]))
						dp[j1+1][j2][2]|=dp[j1][j2][0]|dp[j1][j2][1];
					else
						dp[j1+1][j2][1]|=dp[j1][j2][0]|dp[j1][j2][1];
					if(j2+1<v2.size()&&s[v1[j1]]==t[v2[j2]]&&v1[j1+1]-v1[j1]>=v2[j2+1]-v2[j2])
						dp[j1+1][j2+1][0]|=dp[j1][j2][0]|dp[j1][j2][2];
				}
			}
			if(!dp[v1.size()-1][v2.size()-1][0]&&!dp[v1.size()-1][v2.size()-1][2])
				return "NO";
			si=a[i][0]+a[i][1];
			ti=b[i][0]+b[i][1];
		}
		return "YES";
	}
};
