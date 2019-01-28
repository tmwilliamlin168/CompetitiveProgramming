import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final int[] dx={0, 1, 0, -1}, dy={1, 0, -1, 0};
	
	public static void main(String[] args) {
		int n=in.nextInt(), m=in.nextInt();
		int[][] e = new int[n][m];
		int[][][] d = new int[n][m][3];
		for(int i=0; i<n; ++i) {
			for(int j=0; j<m; ++j) {
				e[i][j]=in.nextInt();
				Arrays.fill(d[i][j], (int)1e9);
			}
		}
		d[0][0][0]=0;
		PriorityQueue<Quad> pq = new PriorityQueue<Quad>();
		pq.add(new Quad(0, 0, 0, 0));
		while(!pq.isEmpty()) {
			Quad q=pq.poll();
			if(d[q.a][q.b][q.c]<q.d)
				continue;
			for(int k=0; k<4; ++k) {
				int ni=q.a+dx[k], nj=q.b+dy[k], nk=(q.c+1)%3;
				if(ni<0||ni>=n||nj<0||nj>=m||e[ni][nj]%3==nk)
					continue;
				if(d[ni][nj][nk]>q.d+e[ni][nj]) {
					d[ni][nj][nk]=q.d+e[ni][nj];
					pq.add(new Quad(ni, nj, nk, d[ni][nj][nk]));
				}
			}
		}
		System.out.println(Math.min(Math.min(d[n-1][m-1][0], d[n-1][m-1][1]), d[n-1][m-1][2]));
	}

	static class Quad implements Comparable<Quad> {
		int a, b, c, d;
		Quad(int a, int b, int c, int d) {
			this.a=a;
			this.b=b;
			this.c=c;
			this.d=d;
		}
		public int compareTo(Quad o) {
			return d-o.d;
		}
	}
	
	static class Reader {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		String next() {
			while(st==null||!st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch(Exception e) {}
			}
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
	}
}
