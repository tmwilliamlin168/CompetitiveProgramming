import java.io.*;
import java.util.*;

public class A {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			int h=in.nextInt(), n=in.nextInt();
			List<Pair> a = new ArrayList<Pair>();
			for(int i=0; i<n; ++i)
				a.add(new Pair(in.nextInt(), in.nextInt()-1));
			Collections.sort(a);
			int[] dp = new int[n+1];
			for(int i=1; i<=n; ++i) {
				int[] c = new int[2];
				for(int j=i-1, d=0; j>=0; --j) {
					d=Math.max(++c[a.get(j).b], d);
					dp[i]=Math.max(dp[i], dp[j]+d*(d-1)/2);
				}
			}
			out.println("Case #"+_+": "+dp[n]);
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
			return a-o.a;
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
