/*
	- There can only be at most O(sqrt(n))~31 jugglers with the same number of red saws
	- If there are x jugglers with y red saws, then there must be <=x jugglers with y+1 red saws
	- Use these 2 properties and the generous 25 second time limit to search all possible ways
*/

import java.io.*;
import java.util.*;

public class Solution {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static int[][] ans = new int[501][501];
	
	public static void main(String[] args) {
		recur(0, 0, 0, 0, 31);
		for(int i=0; i<=500; ++i)
			for(int j=0; j<500; ++j)
				ans[i][j+1]=Math.max(ans[i][j], ans[i][j+1]);
		for(int i=0; i<500; ++i)
			for(int j=0; j<=500; ++j)
				ans[i+1][j]=Math.max(ans[i][j], ans[i+1][j]);
		int tt=in.nextInt();
		for(int ti=1; ti<=tt; ++ti)
			out.println("Case #"+ti+": "+(ans[in.nextInt()][in.nextInt()]-1));
		out.close();
	}
	
	static void recur(int i, int u1, int u2, int ac, int m1) {
		ans[u1][u2]=Math.max(ac, ans[u1][u2]);
		for(int j=0; j<=m1; ++j) {
			u1+=i;
			u2+=j;
			++ac;
			if(u1>500||u2>500)
				break;
			recur(i+1, u1, u2, ac, j);
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
