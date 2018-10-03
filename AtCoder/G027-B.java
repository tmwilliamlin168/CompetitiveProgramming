import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	
	public static void main(String[] args) {
		int n=in.nextInt();
		long x=in.nextInt(), ans=Long.MAX_VALUE;
		long[] ps = new long[n+1];
		for(int i=0; i<n; ++i)
			ps[i+1]=ps[i]+in.nextInt();
		for(int i=1; i<=n; ++i) {
			long ca=2*(ps[n]-ps[n-i])+i*x;
			for(int j=0; n-i*j>0; ++j) {
				long b=(2*j+3)*(ps[n-i*j]-ps[Math.max(n-i*(j+1), 0)]);
				if(Long.MAX_VALUE-b<ca) {
					ca=Long.MAX_VALUE;
					break;
				}
			}
			ans=Math.min(ca, ans);
		}
		System.out.println(ans+n*x);
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
