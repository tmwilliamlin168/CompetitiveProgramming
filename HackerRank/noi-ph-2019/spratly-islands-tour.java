import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(); tests>0; --tests)
			new Solver();
		out.close();
	}
	
	static class Solver {
		int n;
		List<Integer>[] adj;
		List<Integer> ans = new ArrayList<Integer>();
		int[] p, d;
		boolean[] a, v;
		
		void dfs(int u) {
			while(adj[u].size()>0) {
				int e=adj[u].remove(adj[u].size()-1);
				if(a[e])
					continue;
				a[e]=true;
				dfs(u^(e%(n-2)+1)^p[e]);
			}
			ans.add(u);
			v[u]=true;
		}
		
		Solver() {
			n=in.nextInt();
			adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			p = new int[2*(n-2)];
			a = new boolean[2*(n-2)];
			for(int i=0; i<2*(n-2); ++i) {
				p[i]=in.nextInt()-1;
				adj[i%(n-2)+1].add(i);
				adj[p[i]].add(i);
			}
			d = new int[n-1];
			int d0=0;
			for(int i=n-3; i>=0; --i) {
				if(adj[i+1].size()%2!=d[i+1]&&(p[i]>0||adj[0].size()-d0>1)) {
					a[i]=true;
					d[p[i]]^=1;
					if(p[i]==0)
						++d0;
				}
			}
			v = new boolean[n];
			dfs(0);
			boolean ok=true;
			for(int i=0; i<n&&ok; ++i)
				ok=v[i];
			if(!ok) {
				out.println("NO");
				return;
			}
			out.println("YES\n"+(ans.size()-1));
			for(int ai : ans)
				out.print((ai+1)+" ");
			out.println();
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
