import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(); tests>0; --tests) {
			int n=in.nextInt(), k=in.nextInt(), qh=0, qt=0;
			int[] qu = new int[n];
			long[] a = new long[n];
			for(int i=0; i<n; ++i)
				a[i]=in.nextInt();
			long ans=0, r=0;
			for(int i=0; i<n; ++i) {
				a[i]-=in.nextInt();
				ans+=a[i];
			}
			for(int i=0; i<n; ++i) {
				a[i]+=r;
				while(qh<qt&&a[qu[qt-1]]>a[i])
					--qt;
				qu[qt++]=i;
				if(i<k-1)
					continue;
				r=a[qu[qh]];
				if(qu[qh]<i-k+2)
					++qh;
			}
			System.out.println(ans-r*k);
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
