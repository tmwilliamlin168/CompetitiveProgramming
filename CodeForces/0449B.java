import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	
	public static void main(String[] args) {
		int n=in.nextInt(), m=in.nextInt(), k=in.nextInt(), ans=0;
		List<Pair>[] adj = new List[n];
		for(int i=0; i<n; ++i)
			adj[i] = new ArrayList<Pair>();
		while(m-->0) {
			int u=in.nextInt()-1, v=in.nextInt()-1, w=in.nextInt();
			adj[u].add(new Pair(w, v));
			adj[v].add(new Pair(w, u));
		}
		boolean[] a = new boolean[n];
		long[] d = new long[n];
		Arrays.fill(d, (long)1e18);
		PriorityQueue<Pair> pq = new PriorityQueue<Pair>();
		d[0]=0;
		pq.add(new Pair(0, 0));
		while(k-->0) {
			int s=in.nextInt()-1, y=in.nextInt();
			if(a[s])
				++ans;
			if(y<d[s]) {
				d[s]=y;
				pq.add(new Pair(y, s));
				a[s]=true;
			}
		}
		while(pq.size()>0) {
			Pair u=pq.poll();
			if(u.a>d[u.b])
				continue;
			for(Pair v : adj[u.b]) {
				if(u.a+v.a<=d[v.b]&&a[v.b]) {
					a[v.b]=false;
					++ans;
				}
				if(u.a+v.a<d[v.b]) {
					d[v.b]=u.a+v.a;
					pq.add(new Pair(d[v.b], v.b));
				}
			}
		}
		System.out.println(ans);
	}
	
	static class Pair implements Comparable<Pair> {
		long a;
		int b;
		Pair(long a, int b) {
			this.a=a;
			this.b=b;
		}
		public int compareTo(Pair o) {
			return Long.compare(a, o.a);
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
