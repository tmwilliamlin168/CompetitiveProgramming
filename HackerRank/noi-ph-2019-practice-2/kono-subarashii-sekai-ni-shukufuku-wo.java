import java.io.*;
import java.util.*;

public class Solution {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(); tests-->0; )
			new Solver();
		out.close();
	}
	
	static class Solver {
		int n, d, s, ans;
		Monster[] ms;
		
		Solver() {
			n=in.nextInt();
			d=in.nextInt();
			s=in.nextInt();
			ms = new Monster[n];
			for(int i=0; i<n; ++i)
				ms[i] = new Monster(in.nextInt(), in.nextInt(), in.nextInt());
			Arrays.sort(ms);
			solve(0, n-1);
			out.println(ans);
		}
		
		void solve(int l2, int r2) {
			if(l2==r2) {
				if(ms[l2].h<=s)
					ans=Math.max(ms[l2].v, ans);
				return;
			}
			int m2=(l2+r2)/2, sv=(m2-l2+1)*40;
			int[][] dp1 = new int[m2-l2+2][], dp2 = new int[r2-m2+1][];
			dp1[0] = dp2[0] = new int[sv+1];
			Arrays.fill(dp1[0], s+1);
			dp1[0][0]=0;
			for(int i=0; m2-i>=l2; ++i) {
				dp1[i+1]=Arrays.copyOf(dp1[i], sv+1);
				for(int j=sv; j>=ms[m2-i].v; --j)
					dp1[i+1][j]=Math.min(dp1[i+1][j-ms[m2-i].v]+ms[m2-i].h, dp1[i+1][j]);
				for(int j=sv-1; j>=0; --j)
					dp1[i+1][j]=Math.min(dp1[i+1][j+1], dp1[i+1][j]);
			}
			for(int i=0; m2+1+i<=r2; ++i) {
				dp2[i+1]=Arrays.copyOf(dp2[i], sv+1);
				for(int j=sv; j>=ms[m2+1+i].v; --j)
					dp2[i+1][j]=Math.min(dp2[i+1][j-ms[m2+1+i].v]+ms[m2+1+i].h, dp2[i+1][j]);
				for(int j=sv-1; j>=0; --j)
					dp2[i+1][j]=Math.min(dp2[i+1][j+1], dp2[i+1][j]);
			}
			int i1=m2+1, i2=m2+1;
			for(; i1-1>=l2&&ms[i2].p-ms[i1-1].p<=d; --i1);
			for(; i1<=m2; ++i1) {
				for(; i2+1<=r2&&ms[i2+1].p-ms[i1].p<=d; ++i2);
				for(int j1=0, j2=sv; j1<=sv&&j2>=0; ++j1) {
					for(; j2>=0&&dp1[m2+1-i1][j1]+dp2[i2-m2][j2]>s; --j2);
					if(j2>=0)
						ans=Math.max(j1+j2, ans);
				}
			}
			solve(l2, m2);
			solve(m2+1, r2);
		}
		
		class Monster implements Comparable<Monster> {
			int p, h, v;
			Monster(int p, int h, int v) {
				this.p=p;
				this.h=h;
				this.v=v;
			}
			public int compareTo(Monster o) {
				return p-o.p;
			}
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
