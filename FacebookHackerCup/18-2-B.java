import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static List<Integer>[] adj;
	static int[] d;
	static long ans;
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(), ti=1; ti<=tests; ++ti) {
			int n=in.nextInt(), m=in.nextInt();
			long a=in.nextInt(), b=in.nextInt();
			adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			for(int i=1; i<n; ++i)
				adj[in.nextInt()].add(i);
			d = new int[n];
			for(int i=0; i<m; ++i)
				++d[(int)((a*i+b)%n)];
			ans=0;
			dfs(0);
			out.println("Case #"+ti+": "+ans);
		}
		out.close();
	}
	
	static PriorityQueue<Integer> dfs(int u) {
		PriorityQueue<Integer> pq = new PriorityQueue<Integer>(Collections.reverseOrder());
		pq.add(u);
		for(int v : adj[u]) {
			PriorityQueue<Integer> pq2 = dfs(v);
			if(pq2.size()>pq.size()) {
				for(int a : pq)
					pq2.add(a);
				pq=pq2;
			} else
				for(int a : pq2)
					pq.add(a);
		}
		while(d[u]-->0&&!pq.isEmpty())
			ans+=pq.poll();
		return pq;
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
