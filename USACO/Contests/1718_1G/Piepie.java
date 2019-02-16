import java.io.*;
import java.util.*;

public class Main {
	static boolean stdio=false;
	static Reader in = new Reader();
	static PrintWriter out;
	
	public static void main(String[] args) {
		if(stdio)
			out = new PrintWriter(System.out);
		else {
			try {
				out = new PrintWriter("piepie.out");
			} catch (Exception e) {}
		}
		final int INF=(int)1e9;
		int n=in.nextInt(), d=in.nextInt(), qh=0, qt=0;
		int[] a = new int[2*n], b = new int[2*n], dist = new int[2*n], qu = new int[2*n];
		List<Integer> sources = new ArrayList<Integer>();
		TreeSet<Pair> unvisited1 = new TreeSet<Pair>(), unvisited2 = new TreeSet<Pair>();
		for(int i=0; i<2*n; ++i) {
			a[i]=in.nextInt();
			b[i]=in.nextInt();
			if(b[i]==0&&i<n||a[i]==0&&i>=n)
				sources.add(i);
			else if(i<n)
				unvisited1.add(new Pair(b[i], i));
			else
				unvisited2.add(new Pair(a[i], i));
		}
		Arrays.fill(dist, INF);
		for(int source : sources) {
			dist[source]=1;
			qu[qt++]=source;
		}
		while(qt>qh) {
			int u=qu[qh++];
			if(u<n) {
				Pair upper=new Pair(a[u], INF);
				Pair p=unvisited2.lower(upper);
				while(p!=null&&a[u]-p.a<=d) {
					dist[p.b]=dist[u]+1;
					qu[qt++]=p.b;
					unvisited2.remove(p);
					p=unvisited2.lower(upper);
				}
			} else {
				Pair upper=new Pair(b[u], INF);
				Pair p=unvisited1.lower(upper);
				while(p!=null&&b[u]-p.a<=d) {
					dist[p.b]=dist[u]+1;
					qu[qt++]=p.b;
					unvisited1.remove(p);
					p=unvisited1.lower(upper);
				}
			}
		}
		for(int i=0; i<n; ++i)
			out.println(dist[i]>=INF?-1:dist[i]);
		out.close();
	}
	
	static class Pair implements Comparable<Pair> {
		int a, b;
		Pair(int a, int b) {
			this.a=a;
			this.b=b;
		}
		public int compareTo(Pair o) {
			return a==o.a?b-o.b:a-o.a;
		}
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			if(stdio)
				br = new BufferedReader(new InputStreamReader(System.in));
			else {
				try {
					br = new BufferedReader(new FileReader("piepie.in"));
				} catch (Exception e) {}
			}
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
