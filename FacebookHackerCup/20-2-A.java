import java.io.*;
import java.util.*;

public class A {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			out.print("Case #"+_+": ");
			new Solver();
		}
		out.close();
	}
	
	static class Solver {
		int[] ra(int n, int k) {
			int[] x = new int[n];
			for(int i=0; i<k; ++i)
				x[i]=in.nextInt();
			long a=in.nextLong(), b=in.nextLong(), c=in.nextLong(), d=in.nextLong();
			for(int i=k; i<n; ++i)
				x[i]=(int)((a*x[i-2]+b*x[i-1]+c)%d);
			return x;
		}
		
		Solver() {
			int n=in.nextInt(), k=in.nextInt();
			int[] s=ra(n, k), x=ra(n, k), y=ra(n, k);
			long ss=0, xs=0, ys=0;
			for(int i=0; i<n; ++i) {
				ss+=s[i];
				xs+=x[i];
				ys+=y[i];
			}
			if(ss>=xs&&ss<=xs+ys) {
				long ans1=0, ans2=0;
				for(int i=0; i<n; ++i) {
					ans1+=Math.max(x[i]-s[i], 0);
					ans2+=Math.max(s[i]-x[i]-y[i], 0);
				}
				out.println(Math.max(ans1, ans2));
			} else
				out.println(-1);
		}
	}
	
	static class Reader {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		String next() {
			while(st==null||!st.hasMoreTokens()) {
				try {
					st=new StringTokenizer(in.readLine());
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
