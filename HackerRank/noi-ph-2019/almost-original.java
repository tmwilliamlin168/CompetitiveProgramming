import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final int M=998244353;
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(); tests-->0; ) {
			int n=in.nextInt();
			int[] a = new int[n], v = new int[n], lst = new int[n];
			Map<Integer, Integer> mp = new HashMap<Integer, Integer>();
			for(int i=0; i<n; ++i) {
				a[i]=in.nextInt();
				v[i]=in.nextInt();
				lst[i]=mp.getOrDefault(v[i], -1);
				mp.put(v[i], i);
			}
			long[] dp1 = new long[n+1], dp2 = new long[n+1], b = new long[n], p = new long[n];
			dp2[0]=1;
			for(int i=0; i<n; ++i) {
				b[i]=(dp1[i]-dp1[lst[i]+1]+dp2[lst[i]+1]+M)%M;
				p[i]=pm(2, a[i]);
				dp2[i+1]=b[i]*p[i]%M;
				dp1[i+1]=(b[i]*(p[i]*2-2+M)+dp1[i])%M;
			}
			long ans=0, dp3=1;
			Map<Integer, Long> dp4 = new HashMap<Integer, Long>();
			for(int i=n-1; i>=0; --i) {
				long c=(dp3-dp4.getOrDefault(v[i], 0L)+M)%M, cd=((p[i]-2+M)*c+p[i]*dp3)%M;
				ans=(ans+(((a[i]-2)*p[i]%M+2)*c+p[i]*dp3%M*a[i])%M*v[i]%M*b[i])%M;
				dp3=(dp3+cd-dp4.getOrDefault(v[i], 0L)+M)%M;
				dp4.put(v[i], cd);
			}
			System.out.println(ans);
		}
	}
	
	static long pm(long b, int p) {
		long r=1;
		while(p>0) {
			if(p%2==1)
				r=r*b%M;
			b=b*b%M;
			p/=2;
		}
		return r;
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
