/*
	- The strings for B that could cause Ethan's algorithm to go wrong are both pref(A)+A and A+suf(A)
	- Test all possible prefixes of A
*/

import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(), ti=1; ti<=tests; ++ti) {
			String s = in.next();
			int n=s.length();
			String a1="Impossible";
			for(int i=1; i<n; ++i) {
				String a2=s.substring(0, i)+s;
				if(!a2.startsWith(s)) {
					a1=a2;
					break;
				}
			}
			out.println("Case #"+ti+": "+a1);
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
