package section_3_3;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: camelot
*/
import java.io.*;
import java.util.*;

public class camelot {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "camelot";
	
	static class Solver {
		static int INF=(int)1e6;
		static int[][] knightNeighbors = {{-2, -1}, {-1, -2}, {2, -1}, {-1, 2}, {-2, 1}, {1, -2}, {2, 1}, {1, 2}};
		
		Solver() {
			int r=in.nextInt(), c=in.nextInt(), kingJ=in.next().charAt(0)-'A', kingI=in.nextInt()-1, knights=0;
			boolean[][] hasKnight = new boolean[r][c];
			while(true) {
				String s = in.next();
				if(s==null||s.charAt(0)=='-')
					break;
				hasKnight[in.nextInt()-1][s.charAt(0)-'A']=true;
				++knights;
			}
			if(knights==0) {
				out.println(0);
				return;
			}
			int[][][][] dist1 = new int[r][c][r][c];
			for(int i=0; i<r; ++i)
				for(int j=0; j<c; ++j)
					for(int k=0; k<r; ++k)
						Arrays.fill(dist1[i][j][k], INF);
			Pos[] qu = new Pos[780];
			int qt, qh;
			for(int i=0; i<r; ++i) {
				for(int j=0; j<c; ++j) {
					qt=0;
					qh=0;
					qu[qt++]=new Pos(i, j);
					dist1[i][j][i][j]=0;
					while(qh<qt) {
						Pos p = qu[qh++];
						for(int[] neighbor : knightNeighbors) {
							int newI=p.i+neighbor[0], newJ=p.j+neighbor[1];
							if(newI>=0&&newI<r&&newJ>=0&&newJ<c&&dist1[i][j][newI][newJ]>=INF) {
								qu[qt++]=new Pos(newI, newJ);
								dist1[i][j][newI][newJ]=dist1[i][j][p.i][p.j]+1;
							}
						}
					}
				}
			}
			int[][] sumDist = new int[r][c];
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
					int c1Moves=0;
					for(int k=0; k<r; ++k)
						for(int l=0; l<c; ++l)
							if(hasKnight[k][l])
								c1Moves+=dist1[i][j][k][l];
					for(int k=0; k<r; ++k) {
						for(int l=0; l<c; ++l) {
							if(!hasKnight[k][l])
								continue;
							int c2Moves=c1Moves-dist1[i][j][k][l];
							for(int m=Math.max(0, kingI-2); m<=Math.min(r-1, kingI+2); ++m)
								for(int n=Math.max(0, kingJ-2); n<=Math.min(c-1, kingJ+2); ++n)
									minMoves=Math.min(c2Moves+dist1[i][j][m][n]+dist1[m][n][k][l]+Math.max(Math.abs(kingI-m), Math.abs(kingJ-n)), minMoves);
						}
					}
				}
			}
			out.println(minMoves);
		}
		
		class Pos {
			int i, j;
			Pos(int i, int j) {
				this.i=i;
				this.j=j;
			}
		}
		
		class PosDist implements Comparable<PosDist> {
			Pos p;
			int dist;
			PosDist(Pos p, int dist) {
				this.p=p;
				this.dist=dist;
			}
			public int compareTo(PosDist o) {
				return dist-o.dist;
			}
		}
	}
	
	static void preprocess() {
		
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
		preprocess();
		for(int testCases=1; testCases>0; --testCases)
			new Solver();
		out.close();
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			br = new BufferedReader(new InputStreamReader(System.in));
		}
		Reader(String filename) throws Exception {
			br = new BufferedReader(new FileReader(filename));
		}
		String next() {
			while(st==null||!st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch(Exception e) {
					return null;
				}
			}
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
	}
}