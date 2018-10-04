import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "promote";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		List<Integer>[] children;
		int[] st, en;
		int dt;
		
		Solver() {
			int n=in.nextInt();
			Pair[] p = new Pair[n];
			children = new List[n];
			for(int i=0; i<n; ++i)
				p[i] = new Pair(i, in.nextInt());
			for(int i=0; i<n; ++i) {
				children[i] = new ArrayList<Integer>();
				if(i>0)
					children[in.nextInt()-1].add(i);
			}
			st = new int[n];
			en = new int[n];
			dfs(0);
			Arrays.sort(p, new Comparator<Pair>() {
				public int compare(Pair a, Pair b) {
					return -(a.b-b.b);
				}
			});
			int[] ans = new int[n];
			FTree ft = new FTree(n);
			for(Pair pi : p) {
				ans[pi.a]=ft.sum(en[pi.a])-ft.sum(st[pi.a]);
				ft.add(st[pi.a], 1);
			}
			for(int i=0; i<n; ++i)
				out.println(ans[i]);
		}
		
		void dfs(int u) {
			st[u]=dt++;
			for(int v : children[u])
				dfs(v);
			en[u]=dt;
		}
		
		class Pair {
			int a, b;
			Pair(int a, int b) {
				this.a=a;
				this.b=b;
			}
		}
		
		class FTree {
			int[] a;
			FTree(int n) {
				a = new int[n+1];
			}
			void add(int i, int x) {
				for(++i; i<a.length; i+=i&-i)
					a[i]+=x;
			}
			int sum(int i) {
				int r=0;
				for(; i>0; i-=i&-i)
					r+=a[i];
				return r;
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
