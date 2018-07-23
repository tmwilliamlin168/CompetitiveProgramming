/*
	- https://www.facebook.com/notes/facebook-hacker-cup/hacker-cup-2018-round-1-solutions/2267977239884831/
*/

import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final long M=(long)1e9+7;
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(), ti=1; ti<=tests; ++ti) {
			int n=in.nextInt(), m=in.nextInt();
			int[] a = new int[n-1], b = new int[n-1], h = new int[n];
			for(int i=0; i<n-1; ++i) {
				a[i]=in.nextInt();
				b[i]=in.nextInt();
			}
			while(m-->0) {
				int y=in.nextInt()-1;
				h[y]=Math.max(in.nextInt(), h[y]);
			}
			int[] c = Arrays.copyOf(h, n+2);
			c[n]=1000001;
			Arrays.sort(c);
			m=0;
			for(int i=0; i<=n+1; ++i)
				if(i==0||c[i]!=c[i-1])
					c[m++]=c[i];
			c=Arrays.copyOf(c, m);
			for(int i=0; i<n; ++i)
				h[i]=Arrays.binarySearch(c, h[i]);
			long[][] dp1 = new long[n][m], dp2 = new long[n][m];
			dp1[0][h[0]]=1;
			for(int i=1; i<n; ++i) {
				long d=modI(b[i-1]-a[i-1]+1, M);
				for(int j=1; j<m; ++j) {
					int e=Math.min(Math.max(c[j]-a[i-1]+1, 0), b[i-1]-a[i-1]+1);
					dp1[i][j]=dp1[i-1][j]*(e*d%M)%M;
					dp1[i][0]+=dp1[i-1][j]*(1-e*d%M+M)%M;
				}
				dp1[i][0]%=M;
				for(int j=h[i]-1; j>=0; --j) {
					dp1[i][h[i]]+=dp1[i][j];
					dp1[i][j]=0;
				}
				long f=0;
				for(int j=1; j<m; ++j) {
					int e=Math.max(Math.min(c[j], b[i-1])-Math.max(c[j-1], a[i-1]-1), 0), g=Math.min(Math.max(c[j]-a[i-1]+1, 0), b[i-1]-a[i-1]+1);
					dp2[i][j]=((dp1[i-1][0]+f)*(e*d%M)+dp2[i-1][j]*(g*d%M))%M;
					f+=dp2[i-1][j];
					if(f>=M)
						f-=M;
				}
				for(int j=h[i]; j>0; --j) {
					dp1[i][h[i]]+=dp2[i][j];
					dp2[i][j]=0;
				}
				dp1[i][h[i]]%=M;
			}
			long ans=dp1[n-1][0];
			for(int i=h[n-1]+1; i<m; ++i)
				ans+=dp2[n-1][i];
			out.println("Case #"+ti+": "+ans%M);
		}
		out.close();
	}
	
	static long modI(long a, long m) {
		if((a%=m)<=1)
			return 1;
		return (1-modI(m%a, a)*m)/a+m;
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
