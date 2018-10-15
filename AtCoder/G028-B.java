import java.io.*;
import java.util.*;
 
public class Main {
	static final Reader in = new Reader();
	static final long M=(long)1e9+7;
	
	public static void main(String[] args) {
		int n=in.nextInt();
		long[] ps = new long[n+1];
		long nf=1;
		for(int i=1; i<=n; ++i) {
			ps[i]=(ps[i-1]+in.nextInt())%M;
			nf=nf*i%M;
		}
		long ans=nf*ps[n]%M, s=0;
		for(int i=1; i<=n-1; ++i) {
			s=(s+ps[n-i]-ps[i]+M)%M;
			ans=(ans+nf*modI((long)(i+1)*(i>=n-1?1:i+2), M)%M*2*s+nf*modI(i+1, M)%M*(ps[i]+ps[n]-ps[n-i]+M))%M;
		}
		System.out.println(ans);
	}
	
	static long modI(long a, long m) {
		return (a%=m)<=1?1:(1-modI(m%a, a)*m)/a+m;
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
