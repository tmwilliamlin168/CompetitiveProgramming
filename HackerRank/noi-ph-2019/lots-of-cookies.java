import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		int q=in.nextInt();
		long a=in.nextLong(), b=in.nextLong();
		long[] c = new long[1000001];
		for(int i=1; i<=1000000; ++i)
			for(int j=1; i*j<=1000000; ++j) {
				long x=a*j*j^b*j;
				c[Math.min(1000000, i*(j+1)-1)]+=x;
				c[i*j-1]-=x;
			}
		for(int i=1000000; i>1; --i)
			c[i-1]+=c[i];
		while(q-->0) {
			int d=in.nextInt();
			out.println(c[d]);
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
		long nextLong() {
			return Long.parseLong(next());
		}
	}
}
