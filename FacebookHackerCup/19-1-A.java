import java.io.*;
import java.util.*;

public class A {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			int n=in.nextInt(), m=in.nextInt();
			List<Pair>[] adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Pair>();
			for(int i=0; i<m; ++i) {
				int u=in.nextInt()-1, v=in.nextInt()-1, w=in.nextInt();
				adj[u].add(new Pair(w, v));
				adj[v].add(new Pair(w, u));
			}
			int[][] d = new int[n][n];
			for(int s=0; s<n; ++s) {
				PriorityQueue<Pair> pq = new PriorityQueue<Pair>();
				Arrays.fill(d[s], (int)1e9);
				d[s][s]=0;
				pq.add(new Pair(0, s));
				while(pq.size()>0) {
					Pair u=pq.poll();
					if(u.a>d[s][u.b])
						continue;
					for(Pair v : adj[u.b]) {
						if(u.a+v.a<d[s][v.b]) {
							d[s][v.b]=u.a+v.a;
							pq.add(new Pair(d[s][v.b], v.b));
						}
					}
				}
			}
			out.print("Case #"+_+": ");
			boolean ok=true;
			for(int u=0; u<n; ++u)
				for(Pair v : adj[u])
					ok&=d[u][v.b]==v.a;
			if(ok) {
				out.println(m);
				for(int u=0; u<n; ++u)
					for(Pair v : adj[u])
						if(u<v.b)
							out.println((u+1)+" "+(v.b+1)+" "+(v.a));
			} else
				out.println("Impossible");
		}
		out.close();
	}
	
	static class Pair implements Comparable<Pair> {
		int a, b;
		Pair(int a, int b) {
			this.a=a;
			this.b=b;
		}
		public int compareTo(Pair o) {
			return a-o.a;
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
