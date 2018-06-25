/*
	- Circle is basically like modulo
	- Answer is the number of 1<=i<n such that gcd(i, n) equals 1
*/

#include <bits/stdc++.h>
using namespace std;

inline int gcd(int a, int b) {
    while((a%=b)&&(b%=a));
    return a^b;
}

int n, a;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;
    ++n;
    for(int i=1; i<n; ++i)
        if(gcd(i, n)==1)
            ++a;
    cout << a;
}
