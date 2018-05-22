package section_3_2;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: butter
*/
import java.io.*;
import java.util.*;

public class butter {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "butter";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), p=in.nextInt(), c=in.nextInt();
			int[] cows = new int[n];
			for(int i=0; i<n; ++i)
				cows[i] = in.nextInt()-1;
			List<Pair>[] graph = new List[p];
			for(int i=0; i<p; ++i)
				graph[i]=new ArrayList<Pair>();
			for(int i=0; i<c; ++i) {
				int u=in.nextInt()-1, v=in.nextInt()-1, l=in.nextInt();
				graph[u].add(new Pair(v, l));
				graph[v].add(new Pair(u, l));
			}
			int minCost=Integer.MAX_VALUE;
			int[] dist = new int[p];
			PriorityQueue<Pair> queue = new PriorityQueue<Pair>();
			for(int i=0; i<p; ++i) {
				Arrays.fill(dist, -1);
				queue.add(new Pair(i, 0));
				while(!queue.isEmpty()) {
					Pair pair = queue.poll();
					if(dist[pair.a]!=-1)
						continue;
					dist[pair.a]=pair.b;
					for(Pair neighbor : graph[pair.a])
						if(dist[neighbor.a]==-1)
							queue.add(new Pair(neighbor.a, pair.b+neighbor.b));
				}
				int cost=0;
				for(int j=0; j<n; ++j)
					cost+=dist[cows[j]];
				minCost=Math.min(cost, minCost);
			}
			out.println(minCost);
		}
		
		class Pair implements Comparable<Pair> {
			int a, b;
			Pair(int a, int b)  {
				this.a=a;
				this.b=b;
			}
			public int compareTo(Pair p) {
				return b-p.b;
			}
		}
	}
	
	static void preprocess() {
		
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
		preprocess();
		for(int testCases=1; testCases>0; --testCases)
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