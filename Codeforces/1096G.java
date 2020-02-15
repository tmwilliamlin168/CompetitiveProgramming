import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final int M=998244353;
	
	public static void main(String[] args) {
		int n=in.nextInt(), k=in.nextInt();
		long[] a = new long[1<<20];
		while(k-->0)
			a[in.nextInt()]=1;
		NTT ntt = new NTT(1<<20, M, 3);
		ntt.ac(a);
		long in=pm(1<<20, M-2), ans=0;
		for(int i=0; i<1<<20; ++i)
			a[i]=pm(a[i], n/2)*in%M;
		for(int i=1; i<(1<<20)-i; ++i)
			a[i]^=a[(1<<20)-i]^(a[(1<<20)-i]=a[i]);
		ntt.ac(a);
		for(int i=0; i<1<<20; ++i)
			ans+=a[i]*a[i]%M;
		System.out.println(ans%M);
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
	
	static class NTT {
		int M;
		long[] rt;
		NTT(int n, int M, int G) {
			rt = new long[n];
			rt[n/2]=1;
			rt[n/2+1]=pm(G, (M-1)/n);
			for(int i=n/2+2; i<n; ++i)
				rt[i]=rt[i-1]*rt[n/2+1]%M;
			for(int i=n/2; --i>=1; )
				rt[i]=rt[2*i];
			this.M=M;
		}
		void ac(long[] a) {
			int n=a.length;
			for(int i=0, j=0; i<n; ++i) {
				if(i>j)
					a[i]^=a[j]^(a[j]=a[i]);
				for(int k=n/2; (j^=k)<k; k/=2);
			}
			for(int st=1; 2*st<=n; st*=2) {
				for(int i=0; i<n; i+=2*st) {
					for(int j=i; j<i+st; ++j) {
						long z=rt[j-i+st]*a[j+st]%M;
						a[j+st]=a[j]-z;
						if(a[j+st]<0)
							a[j+st]+=M;
						a[j]+=z;
						if(a[j]>=M)
							a[j]-=M;
					}
				}
			}
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
