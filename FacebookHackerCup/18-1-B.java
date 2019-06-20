import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static int[] a, b, c, d, f;
	static int ci, di;
	static List<Integer>[] adj;
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(), ti=1; ti<=tests; ++ti) {
			int n=in.nextInt(), k=in.nextInt();
			a = new int[n];
			b = new int[n];
			for(int i=0; i<n; ++i) {
				a[i]=in.nextInt()-1;
				b[i]=in.nextInt()-1;
			}
			c = new int[n];
			d = new int[n];
			ci=di=0;
			dfs1(0);
			adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			for(int i=0; i<n; ++i) {
				adj[c[i]].add(d[i]);
				adj[d[i]].add(c[i]);
			}
			int e=0;
			f = new int[n];
			for(int i=0; i<n; ++i)
				if(f[i]==0)
					dfs2(i, (e++)%k+1);
			out.print("Case #"+ti+":");
			if(e>=k) {
				for(int i=0; i<n; ++i)
					out.print(" "+f[i]);
				out.println();
			} else
				out.println(" Impossible");
		}
		out.close();
	}
	
	static void dfs1(int u) {
		c[ci++]=u;
		if(a[u]!=-1)
			dfs1(a[u]);
		if(b[u]!=-1)
			dfs1(b[u]);
		d[di++]=u;
	}
	
	static void dfs2(int u, int e) {
		f[u]=e;
		for(int v : adj[u])
			if(f[v]==0)
				dfs2(v, e);
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
