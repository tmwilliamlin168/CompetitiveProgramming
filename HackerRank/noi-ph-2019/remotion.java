import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final int mxN=(int)1e6, M=(int)1e9, MG[]={0, mxN, mxN, 109545, 664, 136};
	
	static void tr(long[][] a, int i, int s) {
		a[i]=Arrays.copyOf(a[i-1], a[0].length);
		for(int j=0; j+s<a[0].length; ++j)
			a[i][j+s]=(a[i][j+s]+a[i][j])%M;
	}
	
	public static void main(String[] args) {
		int t=in.nextInt();
		long[][] a = new long[6][mxN], b = new long[3][mxN], c = new long[3][mxN];
		a[0][0]=1;
		for(int i=1; i<6; ++i)
			tr(a, i, i);
		b[0]=a[2];
		for(int i=1; i<3; ++i)
			tr(b, i, 2*i);
		c[0]=a[3];
		for(int i=1; i<3; ++i)
			tr(c, i, i);
		long[][] d = new long[4][mxN], e = new long[4][mxN], f = new long[4][mxN];
		d[0][0]=e[0][0]=f[0][0]=1;
		for(int i=1; i<4; ++i)
			tr(d, i, i+1);
		for(int i=1; i<4; ++i)
			tr(e, i, i<2?1:i+1);
		for(int i=1; i<4; ++i)
			tr(f, i, i>2?4:i);
		long[] g = new long[mxN], h = new long[mxN];
		for(int i=5; i<mxN; ++i) {
			g[i]=g[i-1];
			h[i]=h[i-1];
			//3 same
			g[i]=(g[i]+(i-5)/3+(i%4==1?0:1))%M;
			//2 groups of 2
			if(i%2==1)
				g[i]=(g[i]+(i-3)/4)%M;
			//3 groups
			if(i>9)
				g[i]=(g[i]+2*d[3][i-10])%M;
			if(i>8)
				g[i]=(g[i]+2*e[3][i-9])%M;
			if(i>7)
				g[i]=(g[i]+2*f[3][i-8])%M;
			//4 groups
			if(i>10)
				g[i]=(g[i]+a[4][i-11]*3)%M;
			//all same
			if(i%4==1)
				h[i]=(h[i]+1)%M;
			//2 groups of 2
			if(i%2==1)
				h[i]=(h[i]+(i-3)/4)%M;
		}
		long[] j = new long[mxN], l = new long[mxN];
		for(int i=6; i<mxN; ++i) {
			//asymmetric 212
			j[i]=(j[i-1]+g[i-2])%M;
			l[i]=(l[i-1]+j[i])%M;
			//symmetric 212
			if(i>6)
				l[i]=(l[i]+b[2][i-7])%M;
			//23
			l[i]=(l[i]+c[2][i-6])%M;
		}
		while(t-->0) {
			int n=in.nextInt(), k=in.nextInt();
			long ans;
			if(k==1)
				ans=n>1?0:1;
			else if(k==2)
				ans=n>1?1:0;
			else if(k==3)
				ans=n<4?0:a[3][n-4];
			else if(k==4)
				ans=n<5?0:(a[4][n-5]+g[n-1]+h[n-1])%M;
			else
				ans=n<6?0:(a[5][n-6]+l[n-1])%M;
			if(n>MG[k])
				out.println((ans+M+"").substring(1));
			else
				out.println(ans);
		}
		out.close();
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
