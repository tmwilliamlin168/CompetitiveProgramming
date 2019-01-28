import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		int n=in.nextInt(), m=in.nextInt();
		TreeSet<Integer> s = new TreeSet<Integer>();
		s.add(0);
		s.add(n+1);
		long ans=(long)n*(n+1)/2;
		while(m-->0) {
			int a=in.nextInt(), b=s.lower(a), c=s.higher(a);
			ans-=(long)(c-a)*(a-b);
			s.add(a);
			out.println(ans);
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
