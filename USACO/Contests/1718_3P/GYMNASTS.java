import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "gymnasts";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		static final long M=(long)1e9+7;
		long n=in.nextLong(), t=0;
		List<Long> pfs = new ArrayList<Long>();
		
		Solver() {
			long n2=n;
			for(long i=2; i*i<=n2; ++i) {
				if(n2%i==0) {
					pfs.add(i);
					while(n2%i==0)
						n2/=i;
				}
			}
			if(n2>1)
				pfs.add(n2);
			for(long i=1; i*i<=n&&n>1; ++i) {
				if(n%i!=0)
					continue;
				calc(i);
				if(i>1&&i*i!=n)
					calc(n/i);
			}
			out.println(((t-n+2)%M+M)%M);
		}
		
		void calc(long i) {
			long j=n/i;
			for(long pf : pfs)
				if(j%pf==0)
					j=j/pf*(pf-1);
			t+=j%M*p(2, i)%M;
		}
		
		long p(long b, long p) {
			long r=1;
			while(p>0) {
				if(p%2==1)
					r=r*b%M;
				b=b*b%M;
				p/=2;
			}
			return r;
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
		long nextLong() {
			return Long.parseLong(next());
		}
	}
}
