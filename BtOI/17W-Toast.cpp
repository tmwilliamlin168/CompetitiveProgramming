/*
	- Basically finding the radius when the angle and chord length are known
		- Law of Cosines
	- A few other edge cases to watch out for
*/

#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897

int main() {
	int n, d, t;
	cin >> n >> d >> t;
	if(t%n) {
		cout << "0 " << d;
		return 0;
	}
	t/=n;
	double th1=2*PI/n*t, th2=2*PI/n*(t+1);
	cout << fixed << setprecision(9) << (2*(t+1)>n?0:d*sqrt(2/(1-cos(th2)))) << " " << d*sqrt(2/(1-cos(th1)));
}
