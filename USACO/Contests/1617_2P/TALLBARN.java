import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "tallbarn";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			long k=in.nextLong(), used;
			k-=n;
			long[] a = new long[n];
			for(int i=0; i<n; ++i)
				a[i]=in.nextLong();
			double l=0, h=2e12, m, ans=0;
			while(h-l>1e-9) {
				m=(l+h)/2;
				used=0;
				for(int i=0; i<n; ++i)
					used+=(long)(Math.sqrt(1+4*a[i]/m)-1)/2;
				if(used>=k)
					l=m;
				else
					h=m;
			}
			used=0;
			for(int i=0; i<n; ++i) {
				long b=(long)(Math.sqrt(1+4*a[i]/l)-1)/2;
				ans+=a[i]/(b+1.0);
				used+=b;
			}
			out.println((int)(ans+(used-k)*l+0.5));
		}
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
		new Solver();
		out.close();
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			br = new BufferedReader(new InputStreamReader(System.in));
		}
		Reader(String filename) throws Exception {
			br = new BufferedReader(new FileReader(filename));
		}
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
