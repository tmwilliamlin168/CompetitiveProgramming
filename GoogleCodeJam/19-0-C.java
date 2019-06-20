import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Solution {
	static final Reader in = new Reader();
	
	public static void main(String[] args) {
		int t=in.nextInt();
		for(int ti=1; ti<=t; ++ti) {
			in.next();
			int n=in.nextInt();
			BigInteger[] a = new BigInteger[n];
			BII[] b = new BII[n+1];
			for(int i=0; i<n; ++i)
				a[i] = new BigInteger(in.next());
			for(int i=1; i<n; ++i) {
				if(a[i].compareTo(a[i-1])==0)
					continue;
				b[i] = new BII(a[i].gcd(a[i-1]), i);
				for(int j=i-1; j>=0; --j)
					b[j] = new BII(a[j].divide(b[j+1].a), j);
				for(int j=i+1; j<=n; ++j)
					b[j] = new BII(a[j-1].divide(b[j-1].a), j);
				break;
			}
			Arrays.sort(b, new Comparator<BII>() {
				public int compare(BII a, BII b) {
					return a.a.compareTo(b.a);
				}
			});
			char[] ans = new char[n+1];
			for(int i=0, j=0; i<=n; ++i) {
				if(i>0&&b[i].a.compareTo(b[i-1].a)>0)
					++j;
				ans[b[i].b]=(char)('A'+j);
			}
			System.out.println("Case #"+ti+": "+new String(ans));
		}
	}
	
	static class BII {
		BigInteger a;
		int b;
		BII(BigInteger a, int b) {
			this.a=a;
			this.b=b;
		}
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
