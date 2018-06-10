/*
	- Binary search by number of steps
	- The set of cells in which a person can walk to given a fixed number of steps forms a square
	- Check that the intersection of the squares is non-empty
		- It's intuitive but hard to prove that if the intersection is non-empty, all the people can actually meet there using the algorithm described in the problem
	- This is actually the same as finding the minimum bounding square, which can be done in O(n) instead
*/

import java.io.*;
import java.util.*;

public class Solution {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		int tt=in.nextInt();
		for(int ti=1; ti<=tt; ++ti) {
			int n=in.nextInt();
			int[] r = new int[n], c = new int[n];
			for(int i=0; i<n; ++i) {
				r[i]=in.nextInt();
				c[i]=in.nextInt();
			}
			int lb=0, rb=(int)5e8;
			while(lb<=rb) {
				int mb=(lb+rb)/2, lr=Integer.MIN_VALUE, rr=Integer.MAX_VALUE, lc=Integer.MIN_VALUE, rc=Integer.MAX_VALUE;
				for(int i=0; i<n; ++i) {
					lr=Math.max(r[i]-mb, lr);
					rr=Math.min(r[i]+mb, rr);
					lc=Math.max(c[i]-mb, lc);
					rc=Math.min(c[i]+mb, rc);
				}
				if(lr<=rr&&lc<=rc)
					rb=mb-1;
				else
					lb=mb+1;
			}
			out.println("Case #"+ti+": "+lb);
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
