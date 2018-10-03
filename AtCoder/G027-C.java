import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	
	public static void main(String[] args) {
		int n=in.nextInt(), m=in.nextInt();
		char[] s = in.next().toCharArray();
		for(int i=0; i<n; ++i)
			s[i]-='A';
		List<Integer>[] adj = new List[n];
		for(int i=0; i<n; ++i)
			adj[i]=new ArrayList<Integer>();
		int[][] d = new int[n][2];
		for(int i=0; i<m; ++i) {
			int u=in.nextInt()-1, v=in.nextInt()-1;
			adj[u].add(v);
			adj[v].add(u);
			++d[u][s[v]];
			++d[v][s[u]];
		}
		boolean[] g = new boolean[n];
		int[] qu = new int[n];
		int qt=0;
		for(int i=0; i<n; ++i) {
			if(d[i][0]<=0||d[i][1]<=0) {
				g[i]=true;
				qu[qt++]=i;
			}
		}
		for(int qh=0; qh<n; ++qh) {
			if(qh>=qt) {
				System.out.println("Yes");
				return;
			}
			int u=qu[qh];
			for(int v : adj[u]) {
				if(g[v])
					continue;
				--d[v][s[u]];
				if(d[v][s[u]]<=0) {
					g[v]=true;
					qu[qt++]=v;
				}
			}
		}
		System.out.println("No");
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
