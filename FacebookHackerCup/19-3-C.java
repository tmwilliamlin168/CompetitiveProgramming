import java.io.*;
import java.util.*;

public class C {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final int M=(int)1e9+7;

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			out.print("Case #"+_+": ");
			new Solver();
		}
		out.close();
	}
	
	static class Solver {
		List<Integer>[] adj;
		long[] iv;
		int[] d;
		
		long exp(long b, int p) {
			long r=1;
			while(p>0) {
				if(p%2==1)
					r=r*b%M;
				b=b*b%M;
				p/=2;
			}
			return r;
		}
		
		Solver() {
			int n=in.nextInt(), k=in.nextInt(), a=in.nextInt()-1, b=in.nextInt()-1;
			adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			int[] p = new int[n];
			d = new int[n];
			for(int i=1; i<n; ++i) {
				p[i]=in.nextInt()-1;
				adj[p[i]].add(i);
			}
			iv = new long[n];
			iv[1]=1;
			for(int i=2; i<n; ++i)
				iv[i]=M-M/i*iv[M%i]%M;
			dfs(0);
			int a2=a, b2=b, c=-1;
			long ans=0;
			while(a2>0||b2>0) {
				if(d[a2]>d[b2]) {
					ans+=exp((n-1-(d[a]-d[a2]))*iv[n-1]%M, k);
					a2=p[a2];
				} else {
					ans+=exp((n-1-(d[b]-d[b2]))*iv[n-1]%M, k);
					b2=p[b2];
				}
				if(c<0&&a2==b2)
					c=a2;
			}
			int c2=c;
			while(c2>0) {
				ans-=2*exp((n-1-(d[a]-d[c])-(d[b]-d[c])-(d[c]-d[c2]))*iv[n-1]%M, k);
				c2=p[c2];
			}
			out.println((ans%M+M)%M);
		}
		
		void dfs(int u) {
			for(int v : adj[u]) {
				d[v]=d[u]+1;
				dfs(v);
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
