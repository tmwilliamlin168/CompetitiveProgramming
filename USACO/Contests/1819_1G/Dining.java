import java.io.*;
import java.util.*;

public class Dining {
	static final boolean stdin = false;
	static final String filename = "dining";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		static final int BIG=(int)1e9;
		int n;
		List<PII>[] adj;
		int[] y, d1;
		PII[] d2;
		
		Solver() {
			//input
			n=in.nextInt();
			int m=in.nextInt(), k=in.nextInt();
			adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<PII>();
			while(m-->0) {
				int a=in.nextInt()-1, b=in.nextInt()-1, t=in.nextInt();
				adj[a].add(new PII(t, b));
				adj[b].add(new PII(t, a));
			}
			y = new int[n];
			while(k-->0) {
				int a=in.nextInt()-1, b=in.nextInt();
				y[a]=Math.max(b, y[a]);
			}
			dijkstra1();
			dijkstra2();
			//output
			//if there is a haybale at node n, all answers are 1
			for(int i=0; i<n-1; ++i)
				out.println((d2[i].b<n-1||y[n-1]>0)?1:0);
		}
		
		void dijkstra1() {
			//first dijkstra from n
			PriorityQueue<PII> pq = new PriorityQueue<PII>();
			d1 = new int[n];
			Arrays.fill(d1, Integer.MAX_VALUE);
			d1[n-1]=0;
			pq.add(new PII(0, n-1));
			while(!pq.isEmpty()) {
				PII u=pq.poll();
				if(u.a>d1[u.b])
					continue;
				for(PII v : adj[u.b]) {
					if(d1[v.b]>u.a+v.a) {
						d1[v.b]=u.a+v.a;
						pq.add(new PII(d1[v.b], v.b));
					}
				}
			}
		}
		
		void dijkstra2() {
			//multi-source dijkstra
			//we also keep track of the source
			//sources that are not node n mean that haybales are possible
			//distances are stored as a pair {distance, source}
			PriorityQueue<PPIII> pq = new PriorityQueue<PPIII>();
			d2 = new PII[n];
			Arrays.fill(d2, new PII(Integer.MAX_VALUE, n));
			d2[n-1]=new PII(BIG, n-1);
			pq.add(new PPIII(d2[n-1], n-1));
			//add other nodes with haybales as sources
			for(int i=0; i<n-1; ++i) {
				if(y[i]<=0)
					continue;
				d2[i]=new PII(d1[i]+BIG-y[i], i);
				pq.add(new PPIII(d2[i], i));
			}
			while(!pq.isEmpty()) {
				PPIII u=pq.poll();
				if(u.a.compareTo(d2[u.b])>0)
					continue;
				for(PII v : adj[u.b]) {
					if(d2[v.b].compareTo(new PII(u.a.a+v.a, u.a.b))>0) {
						d2[v.b]=new PII(u.a.a+v.a, u.a.b);
						pq.add(new PPIII(d2[v.b], v.b));
					}
				}
			}
		}
		
		static class PII implements Comparable<PII> {
			int a, b;
			PII(int a, int b) {
				this.a=a;
				this.b=b;
			}
			//Lexicographical comparison
			public int compareTo(PII o) {
				return a==o.a?b-o.b:a-o.a;
			}
		}
		
		static class PPIII implements Comparable<PPIII> {
			PII a;
			int b;
			PPIII(PII a, int b) {
				this.a=a;
				this.b=b;
			}
			//Lexicographical comparison
			public int compareTo(PPIII o) {
				return a.equals(o.a)?b-o.b:a.compareTo(o.a);
			}
		}
	}
	
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
		new Solver();
		out.close();
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			br = new BufferedReader(new InputStreamReader(System.in));
		}
		Reader(String filename) throws Exception {
			br = new BufferedReader(new FileReader(filename));
		}
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