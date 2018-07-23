import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(), ti=1; ti<=tests; ++ti) {
			int n=in.nextInt(), m=in.nextInt();
			long[] h = new long[n];
			h[0]=in.nextInt();
			h[1]=in.nextInt();
			long w=in.nextInt(), x=in.nextInt(), y=in.nextInt(), z=in.nextInt();
			for(int i=2; i<n; ++i)
				h[i]=(w*h[i-2]+x*h[i-1]+y)%z;
			for(int i=0; i<n; ++i)
				h[i]*=2;
			long[] l = new long[n-1], r = new long[n-1];
			Arrays.fill(l, -2*z);
			Arrays.fill(r, 2*z);
			while(m-->0) {
				int a=in.nextInt()-1, b=in.nextInt()-1, u=2*in.nextInt(), d=2*in.nextInt();
				if(a>b) {
					u^=d^(d=u);
					a^=b^(b=a);
				}
				for(int i=a; i<b; ++i) {
					l[i]=Math.max(-d, l[i]);
					r[i]=Math.min(u, r[i]);
				}
			}
			long lb=0, rb=z;
			while(lb<=rb) {
				long mb=(lb+rb)/2, a=h[0]-mb, b=h[0]+mb;
				boolean ok=true;
				for(int i=1; i<n&&ok; ++i) {
					a=Math.max(h[i]-mb, a+l[i-1]);
					b=Math.min(h[i]+mb, b+r[i-1]);
					ok=a<=b;
				}
				if(ok)
					rb=mb-1;
				else
					lb=mb+1;
			}
			out.println("Case #"+ti+": "+lb/2.0);
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
