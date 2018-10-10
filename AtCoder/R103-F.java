import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		int n=in.nextInt();
		Pair[] d = new Pair[n];
		int[] s1 = new int[n], p = new int[n];
		long[] s2 = new long[n];
		Map<Long, Integer> mp = new HashMap<Long, Integer>();
		for(int i=0; i<n; ++i) {
			d[i] = new Pair(in.nextLong(), i);
			mp.put(d[i].a, i);
			s1[i]=1;
		}
		Arrays.sort(d);
		for(int i=0; i<n-1; ++i) {
			int u=d[i].b;
			p[u]=mp.getOrDefault(d[i].a-n+2*s1[u], -1);
			if(d[i].a-n+2*s1[u]>=d[i].a||p[u]==-1)
				fk();
			s1[p[u]]+=s1[u];
			s2[p[u]]+=s2[u]+s1[u];
		}
		if(s2[d[n-1].b]!=d[n-1].a)
			fk();
		for(int i=0; i<n-1; ++i)
			out.println((d[i].b+1)+" "+(p[d[i].b]+1));
		out.close();
	}
	
	static void fk() {
		System.out.println(-1);
		System.exit(0);
	}
	
	static class Pair implements Comparable<Pair> {
		long a;
		int b;
		Pair(long a, int b) {
			this.a=a;
			this.b=b;
		}
		public int compareTo(Pair o) {
			return -Long.compare(a, o.a);
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
		long nextLong() {
			return Long.parseLong(next());
		}
	}
}
