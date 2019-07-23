/*
	- http://blog.brucemerry.org.za/2012/09/ioi-2012-day-1-analysis.html
*/

#include "grader.h"

const int mxN=1e6;
int n, m, anc[mxN][20], s[mxN], p[mxN+1];
char c[mxN];

void Init() {
	p[0]=-1;
}

void TypeLetter(char l) {
	c[m]=l;
	anc[m][0]=p[n];
	for(int i=1; i<20; ++i)
		anc[m][i]=~anc[m][i-1]?anc[anc[m][i-1]][i-1]:-1;
	s[m]=~p[n]?s[p[n]]+1:1;
	p[++n]=m++;
}

void UndoCommands(int u) {
	p[n+1]=p[n-u];
	++n;
}

char GetLetter(int x) {
	int u=p[n];
	for(int i=19; ~i; --i)
		if(~anc[u][i]&&s[anc[u][i]]>x)
			u=anc[u][i];
	return c[u];
}
