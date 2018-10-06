#include <bits/stdc++.h>
using namespace std;

const int mxN=100;
int n, x[mxN], y[mxN], h[mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> x[i] >> y[i] >> h[i];
	//Find a given point that has a positive h
	int a=-1;
	while(++a<n&&!h[a]);
	if(a>=n) {
		//No given points have positive h
		//Find any point not given in the input
		for(int cx=0; cx<=mxN; ++cx) {
			for(int cy=0; cy<=mxN; ++cy) {
				//Make sure the center doesn't coincide with any given points
				bool ok=1;
				for(int i=0; i<n&&ok; ++i)
					ok=cx!=x[i]||cy!=y[i];
				if(ok) {
					cout << cx << " " << cy << " 1";
					return 0;
				}
			}
		}
	}
	//Iterate through all possible O(n^2) center coordinates
	for(int cx=0; cx<=mxN; ++cx) {
		for(int cy=0; cy<=mxN; ++cy) {
			//Find the height
			int ch=h[a]+abs(cx-x[a])+abs(cy-y[a]);
			//Iterate through all points to make sure the information isn't contradicting
			bool ok=1;
			for(int i=0; i<n&&ok; ++i)
				ok=h[i]==max(ch-abs(cx-x[i])-abs(cy-y[i]), 0);
			if(ok) {
				cout << cx << " " << cy << " " << ch;
				return 0;
			}
		}
	}
}
