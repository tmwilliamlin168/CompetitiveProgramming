/*
	- Without the restriction on k, the problem can be solved with something like Prim
	- Use the Aliens trick by increasing the costs of the fountains
*/

import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static int n;
	static int[] f;
	static int[][] c;
	static long[] ca;
	static boolean[] uf, ad;
	
	public static void main(String[] args) {
		int tests=in.nextInt();
		while(tests-->0) {
			n=in.nextInt();
			int k=in.nextInt();
			f = new int[n];
			for(int i=0; i<n; ++i)
			    f[i]=in.nextInt();
			c = new int[n][n];
			for(int i=0; i<n; ++i)
    			for(int j=0; j<n; ++j)
    			    c[i][j]=in.nextInt();
			ca = new long[n];
			uf = new boolean[n];
			ad = new boolean[n];
			long[] r=c(0);
			if(r[1]<=k) {
				out.println(r[0]);
				continue;
			}
			long ans=0, lb=1, rb=(long)1e9;
			while(lb<=rb) {
				long mb=(lb+rb)/2;
				r=c(mb);
				if(r[1]<=k) {
					ans=r[0];
					rb=mb-1;
				} else
					lb=mb+1;
			}
			out.println(ans-lb*k);
		}
		out.close();
	}
	
	static long[] c(long mb) {
		int af=0;
		long a2=0;
		for(int i=0; i<n; ++i)
			ca[i]=f[i]+mb;
		Arrays.fill(uf, true);
		Arrays.fill(ad, false);
		for(int it=0; it<n; ++it) {
			int mi=-1;
			for(int i=0; i<n; ++i)
				if(!ad[i]&&(mi==-1||ca[i]<ca[mi]))
					mi=i;
			ad[mi]=true;
			if(uf[mi])
				++af;
			a2+=ca[mi];
			for(int i=0; i<n; ++i) {
				if(ca[i]+(uf[i]?1:0)>c[mi][i]) {
					ca[i]=c[mi][i];
					uf[i]=false;
				}
			}
		}
		return new long[]{a2, af};
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
