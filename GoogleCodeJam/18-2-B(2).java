/*
	- There can only be at most O(sqrt(n)) jugglers with the same number of red saws
	- There are O(sqrt(n)*sqrt(n))=O(n) types of jugglers
	- We can do knapsack with O(n^2) states for a total of O(n^3)
*/

import java.io.*;
import java.util.*;

public class Solution {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static int[][] ans = new int[501][501];
	
	public static void main(String[] args) {
		for(int i1=0; i1<=31; ++i1)
		    for(int j1=0; j1<=31; ++j1)
		        for(int i2=500-i1; i2>=0; --i2)
		            for(int j2=500-j1; j2>=0; --j2)
		                ans[i2+i1][j2+j1]=Math.max(ans[i2][j2]+1, ans[i2+i1][j2+j1]);
		int tt=in.nextInt();
		for(int ti=1; ti<=tt; ++ti)
			out.println("Case #"+ti+": "+(ans[in.nextInt()][in.nextInt()]-1));
		out.close();
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
