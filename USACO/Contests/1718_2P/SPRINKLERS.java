import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "sprinklers";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		static final long M=(long)1e9+7;
		
		Solver() {
			int n=in.nextInt();
			int[] y = new int[n], l = new int[n], t = new int[n];
			for(int i=0; i<n; ++i)
				y[in.nextInt()]=in.nextInt();
			for(int i=0, j=n; i<n; ++i)
				while(j>y[i])
					l[--j]=i;
			t[n-1]=-1;
			for(int i=n-1; i>0; --i)
				t[i-1]=Math.max(y[i]-1, t[i]);
			long[] p1 = new long[n], p2 = new long[n];
			for(int i=0; i<n-1; ++i) {
				p1[i+1]=(l[i]+p1[i])%M;
				p2[i+1]=((long)(n-i)*l[i]+p2[i])%M;
			}
			long ans=0;
			for(int i=0, j=n; i<n-1; ++i) {
				while(j>y[i])
					--j;
				if(j>t[i])
					continue;
				//add all possible from j to t[i]
				ans=((long)(t[i]-j+2)*(t[i]-j+1)/2*(i+1)+ans)%M;
				//subtract the ones that exceed l
				ans=(-(p2[t[i]+1]-p2[j]+(t[i]-n+1)*(p1[t[i]+1]-p1[j]))+ans)%M;
			}
			out.println((ans+M)%M);
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
	}
}
