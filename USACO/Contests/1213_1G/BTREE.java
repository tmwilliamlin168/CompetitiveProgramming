import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "btree";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		List<Integer>[] adj;
		int[] s, mnps, mxps;
		int ans;
		
		Solver() {
			int n=in.nextInt();
			adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			for(int i=1; i<n; ++i)
				adj[in.nextInt()-1].add(i);
			s = new int[n];
			for(int i=0; i<n; ++i)
				s[i]=in.next().charAt(0)=='('?1:-1;
			mnps = new int[n];
			mxps = new int[n];
			dfs1(0);
			dfs2(0, 0, 0);
			out.println(ans);
		}
		
		void dfs1(int u) {
			for(int v : adj[u]) {
				dfs1(v);
				mnps[u]=Math.max(mnps[v], mnps[u]);
				mxps[u]=Math.max(mxps[v], mxps[u]);
			}
			mnps[u]-=s[u];
			mxps[u]+=s[u];
		}
		
		void dfs2(int u, int mnpps, int mxpps) {
			A a1 = new A(), a2 = new A();
			a1.upd(-1, mnpps);
			a2.upd(-1, mxpps);
			for(int i=0; i<adj[u].size(); ++i) {
				a1.upd(i, mnps[adj[u].get(i)]);
				a2.upd(i, mxps[adj[u].get(i)]);
			}
			for(int i=0; i<adj[u].size(); ++i) {
				int mncps=a1.qry(i)-s[u], mxcps=a2.qry(i)+s[u];
				ans=Math.max(Math.max(Math.min(mxcps, mnps[adj[u].get(i)]), Math.min(mncps, mxps[adj[u].get(i)])), ans);
				dfs2(adj[u].get(i), mncps, mxcps);
			}
		}
		
		class A {
			int[] a = {-1, 0}, b = {-1, 0};
			void upd(int i, int x) {
				for(int j=0; j<2; ++j) {
					if(x>b[j]) {
						a[j]^=i^(i=a[j]);
						b[j]^=x^(x=b[j]);
					}
				}
			}
			int qry(int i) {
				return i==a[0]?b[1]:b[0];
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
