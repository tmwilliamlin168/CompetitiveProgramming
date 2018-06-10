/*
	- The balls at columns 1 and c fall straight down (since there can't be ramps there)
		- If B_1==0 or B_c==0, then it is impossible
	- Pair the source and targets so that there are no inversions
*/

import java.io.*;
import java.util.*;

public class Solution {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		int tt=in.nextInt();
		for(int ti=1; ti<=tt; ++ti) {
			out.print("Case #"+ti+": ");
			int c=in.nextInt();
			int[] b = new int[c];
			for(int i=0; i<c; ++i)
			    b[i]=in.nextInt();
			if(b[0]<=0||b[c-1]<=0) {
				out.println("IMPOSSIBLE");
				continue;
			}
			--b[0];
			--b[c-1];
			char[][] grid = new char[c-1][c];
			for(int i=0; i<c-1; ++i)
				Arrays.fill(grid[i], '.');
			int mr=c-2;
			for(int i1=1, i2=0; i1<c-1; ++i1) {
				while(b[i2]<=0)
					++i2;
				for(int x=i1, y=c-2; x!=i2; --y) {
					if(x<i2) {
						grid[y][x]='\\';
						++x;
					} else {
						grid[y][x]='/';
						--x;
					}
					mr=Math.min(y-1, mr);
				}
				--b[i2];
			}
			out.println(c-1-mr);
			for(int i=c-2; i>=mr; --i)
				out.println(grid[i]);
		}
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
