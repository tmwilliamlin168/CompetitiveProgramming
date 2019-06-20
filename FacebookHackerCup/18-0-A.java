/*
	- Notice that we can take v mod n and the answer will be the same
	- Brute force the rest
*/

import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(), ti=1; ti<=tests; ++ti) {
			int n=in.nextInt(), k=in.nextInt(), v=(int)((in.nextLong()-1)%n);
			String[] s = new String[n];
			for(int i=0; i<n; ++i)
				s[i]=in.next();
			Pair[] ps = new Pair[n];
			for(int i=0; i<n; ++i)
				ps[i] = new Pair(i, 0);
			while(v-->0) {
				for(int i=0; i<k; ++i)
					++ps[i].b;
				Arrays.sort(ps);
			}
			out.print("Case #"+ti+":");
			int[] ans = new int[k];
			for(int i=0; i<k; ++i)
				ans[i]=ps[i].a;
			Arrays.sort(ans);
			for(int i=0; i<k; ++i)
				out.print(" "+s[ans[i]]);
			out.println();
		}
		out.close();
	}
	
	static class Pair implements Comparable<Pair> {
		int a, b;
		Pair(int a, int b) {
			this.a=a;
			this.b=b;
		}
		public int compareTo(Pair o) {
			return b==o.b?a-o.a:b-o.b;
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
		long nextLong() {
			return Long.parseLong(next());
		}
	}
}
