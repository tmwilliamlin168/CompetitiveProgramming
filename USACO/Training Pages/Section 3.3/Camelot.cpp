/*
ID: tmwilliamlin168
LANG: C++
TASK: camelot
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double

ifstream fin ("camelot.in");
ofstream fout ("camelot.out");

struct Pos {
	int i, j;
	Pos() {}
	Pos(int i, int j) {
		this->i=i;
		this->j=j;
	}
};

struct PosDist {
	Pos p;
	int dist;
	PosDist() {}
	PosDist(Pos p, int dist) {
		this->p=p;
		this->dist=dist;
	}
	bool operator<(const PosDist& b) const {
		return dist>b.dist;
	}
};

const int INF=(int)1e6;
const int knightNeighbors[8][2] = {{-2, -1}, {-1, -2}, {2, -1}, {-1, 2}, {-2, 1}, {1, -2}, {2, 1}, {1, 2}};

int main(){
	ios_base::sync_with_stdio(false);
	fin.tie(NULL);
	int r, c, kingI, kingJ, knights=0;
	fin >> r >> c;
	string tempS;
	fin >> tempS;
	kingJ=tempS[0]-'A';
	fin >> kingI;
	--kingI;
	bool hasKnight[30][26]={};
	while(fin >> tempS) {
		if(tempS=="-")
			break;
		int i;
		fin >> i;
		--i;
		hasKnight[i][tempS[0]-'A']=true;
		++knights;
	}
	if(knights==0) {
		fout << "0\n";
		return 0;
	}
	int dist1[30][26][30][26], dist2[30][26][30][26];
	for(int i=0; i<r; ++i) {
		for(int j=0; j<c; ++j) {
			for(int k=0; k<r; ++k) {
				for(int l=0; l<c; ++l) {
					dist1[i][j][k][l]=INF;
					dist2[i][j][k][l]=INF;
				}
			}
		}
	}

	Pos qu[780];
	int qt, qh;
	priority_queue<PosDist> pq;
	for(int i=0; i<r; ++i) {
		for(int j=0; j<c; ++j) {
			qt=0;
			qh=0;
			Pos start(i, j);
			qu[qt++]=start;
			dist1[i][j][i][j]=0;
			while(qh<qt) {
				Pos p=qu[qh++];
				for(int nI=0; nI<8; ++nI) {
					int newI=p.i+knightNeighbors[nI][0], newJ=p.j+knightNeighbors[nI][1];
					if(newI>=0&&newI<r&&newJ>=0&&newJ<c&&dist1[i][j][newI][newJ]>=INF) {
						qu[qt++]=Pos(newI, newJ);
						dist1[i][j][newI][newJ]=dist1[i][j][p.i][p.j]+1;
					}
				}
			}
			for(int k=0; k<r; ++k)
				for(int l=0; l<c; ++l)
					if(dist1[i][j][k][l]<INF)
						pq.push(PosDist(Pos(k, l), dist1[i][j][k][l]+max(abs(k-kingI), abs(l-kingJ))));
			while(!pq.empty()) {
				PosDist pd = pq.top();
				pq.pop();
				if(dist2[i][j][pd.p.i][pd.p.j]<INF)
					continue;
				dist2[i][j][pd.p.i][pd.p.j]=pd.dist;
				for(int nI=0; nI<8; ++nI) {
					int newI=pd.p.i+knightNeighbors[nI][0], newJ=pd.p.j+knightNeighbors[nI][1];
					if(newI>=0&&newI<r&&newJ>=0&&newJ<c&&dist2[i][j][newI][newJ]>=INF)
						pq.push(PosDist(Pos(newI, newJ), dist2[i][j][pd.p.i][pd.p.j]+1));
				}
			}
		}
	}
	int sumDist[30][26];
	for(int i=0; i<r; ++i) {
		for(int j=0; j<c; ++j) {
			if(!hasKnight[i][j])
				continue;
			for(int k=0; k<r; ++k)
				for(int l=0; l<c; ++l)
					sumDist[k][l]+=dist1[i][j][k][l];
		}
	}
	int minMoves=INF;
	for(int i=0; i<r; ++i) {
		for(int j=0; j<c; ++j) {
			if(!hasKnight[i][j])
				continue;
			for(int k=0; k<r; ++k)
				for(int l=0; l<c; ++l)
					minMoves=min(sumDist[k][l]-dist1[i][j][k][l]+dist2[i][j][k][l], minMoves);
		}
	}
	fout << minMoves << '\n';
}
