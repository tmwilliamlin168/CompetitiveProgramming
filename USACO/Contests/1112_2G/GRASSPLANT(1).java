import java.io.*;
import java.util.*;

public class Main {
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		int dt;
		int[] st, en, dep;
		int[][] depT;
		List<Integer>[] adj;
		
		Solver() {
			int n=in.nextInt(), m=in.nextInt();
			adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			for(int i=0; i<n-1; ++i) {
				int u=in.nextInt()-1, v=in.nextInt()-1;
				adj[u].add(v);
				adj[v].add(u);
			}
			st = new int[n];
			en = new int[n];
			dep = new int[n];
			depT = new int[31-Integer.numberOfLeadingZeros(2*n-1)+1][2*n-1];
			dfs1(0, -1);
			for(int k=1; k<depT.length; ++k)
				for(int i=0; i+(1<<k)<=2*n-1; ++i)
					depT[k][i]=dep[depT[k-1][i]]<dep[depT[k-1][i+(1<<(k-1))]]?depT[k-1][i]:depT[k-1][i+(1<<(k-1))];
			FenTree ft = new FenTree(2*n-1);
			while(m-->0) {
				char qt=in.next().charAt(0);
				int u=in.nextInt()-1, v=in.nextInt()-1;
				if(st[u]<st[v]) {
					u^=v;
					v^=u;
					u^=v;
				}
				if(qt=='P') {
					ft.upd(st[u], 1);
					ft.upd(st[v], 1);
					int k=31-Integer.numberOfLeadingZeros(st[u]-st[v]+1);
					ft.upd(st[dep[depT[k][st[v]]]<dep[depT[k][st[u]-(1<<k)+1]]?depT[k][st[v]]:depT[k][st[u]-(1<<k)+1]], -2);
				} else
					out.println(ft.qry(en[u])-ft.qry(st[u]));
			}
		}
		
		void dfs1(int u, int p) {
			dep[u]=p==-1?0:dep[p]+1;
			depT[0][st[u]=dt++]=u;
			for(int v : adj[u]) {
				if(v==p)
					continue;
				dfs1(v, u);
				depT[0][dt++]=u;
			}
			en[u]=dt;
		}
		
		class FenTree {
			int[] a;
			FenTree(int n) {
				a = new int[n+1];
			}
			void upd(int i, int x) {
				for(++i; i<a.length; i+=i&-i)
					a[i]+=x;
			}
			int qry(int i) {
				int r=0;
				for(; i>0; i-=i&-i)
					r+=a[i];
				return r;
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		in = new Reader();
		out = new PrintWriter(System.out);
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
