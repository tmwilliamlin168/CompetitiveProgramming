/*
	- The pattern can be divided into at most 4 quadrants, where each quadrant has the same color
	- Brute force the O(rc) quadrant centers and 2^4 color combinations
	- For each configuration, find the largest connected component in O(rc)
	- O((rc)^2) total
*/

import java.io.*;
import java.util.*;

public class Solution {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static int r, c;
	static char[][] g = new char[20][];
	static boolean[][] vis = new boolean[20][20];
	
	public static void main(String[] args) {
		int tt=in.nextInt();
		for(int ti=1; ti<=tt; ++ti) {
			int ans=0;
			r=in.nextInt();
			c=in.nextInt();
			if(r==1||c==1) {
				if(c==1) {
					c=r;
					g[0] = new char[c];
					for(int i=0; i<c; ++i)
						g[0][i]=in.next().charAt(0);
				} else
					g[0]=in.next().toCharArray();
				for(int i=0, i2=0; i<c; ++i, ans=Math.max(i-i2, ans))
					if(g[0][i]!='B')
						i2=i+1;
				for(int i=0, i2=0; i<c; ++i, ans=Math.max(i-i2, ans))
					if(g[0][i]!='W')
						i2=i+1;
				if(new String(g[0]).indexOf("BW")!=-1) {
					for(int i=0; i<c-1; ++i) {
						int a2=0;
						for(int j=i; j>=0&&g[0][j]=='B'; --j, ++a2);
						for(int j=i+1; j<c&&g[0][j]=='W'; ++j, ++a2);
						ans=Math.max(a2, ans);
					}
				}
				if(new String(g[0]).indexOf("WB")!=-1) {
					for(int i=0; i<c-1; ++i) {
						int a2=0;
						for(int j=i; j>=0&&g[0][j]=='W'; --j, ++a2);
						for(int j=i+1; j<c&&g[0][j]=='B'; ++j, ++a2);
						ans=Math.max(a2, ans);
					}
				}
			} else {
				for(int i=0; i<r; ++i)
					g[i]=in.next().toCharArray();
				for(int m=0; m<16; ++m) {
					boolean ok=false;
					for(int i=0; i<r-1&&!ok; ++i)
						for(int j=0; j<c-1&&!ok; ++j)
							ok=(m%2==1)==(g[i][j]=='B')&&
									(m/2%2==1)==(g[i][j+1]=='B')&&
									(m/4%2==1)==(g[i+1][j]=='B')&&
									(m/8%2==1)==(g[i+1][j+1]=='B');
					if(!ok)
						continue;
					for(int ci=0; ci<=r; ++ci) {
						for(int cj=0; cj<=c; ++cj) {
							for(int i=0; i<r; ++i) {
								Arrays.fill(vis[i], false);
								for(int j=0; j<c; ++j)
									vis[i][j]=(m/(i<ci?1:4)/(j<cj?1:2)%2==1)!=(g[i][j]=='B');
							}
							for(int i=0; i<r; ++i)
								for(int j=0; j<c; ++j)
									if(!vis[i][j])
										ans=Math.max(dfs(i, j), ans);
						}
					}
				}
			}
			out.println("Case #"+ti+": "+ans);
		}
		out.close();
	}
	
	static int dfs(int i, int j) {
		if(vis[i][j])
			return 0;
		int s=1;
		vis[i][j]=true;
		if(i-1>=0)
			s+=dfs(i-1, j);
		if(i+1<r)
			s+=dfs(i+1, j);
		if(j-1>=0)
			s+=dfs(i, j-1);
		if(j+1<c)
			s+=dfs(i, j+1);
		return s;
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
