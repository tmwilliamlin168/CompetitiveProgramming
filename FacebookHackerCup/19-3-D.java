import java.io.*;
import java.util.*;

public class D {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final int M=(int)1e9+7;

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			out.print("Case #"+_+": ");
			new Solver();
		}
		out.close();
	}
	
	static class Solver {
		List<Integer>[] adj;
		int dt;
		int[] ds, de;
		int[][] anc;
		
		Solver() {
			int n=in.nextInt(), rt=0;
			adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			for(int i=0; i<n; ++i) {
				int c=in.nextInt()-1;
				if(c>=0)
					adj[c].add(i);
				else
					rt=i;
			}
			ds = new int[n];
			de = new int[n];
			anc = new int[n][20];
			anc[rt][0]=-1;
			dfs(rt);
			boolean[] act = new boolean[n];
			SegTree st = new SegTree();
			FenwickTree ft = new FenwickTree(n);
			long ans=1;
			for(int i=0; i<n; ++i) {
				st.upd1(ds[i], 1, 0, n-1);
				if(i>0&&ft.qry(de[i])-ft.qry(ds[i])<=0) {
					int w=i;
					for(int j=19; j>=0; --j)
						if(anc[w][j]>=0&&ft.qry(de[anc[w][j]])-ft.qry(ds[anc[w][j]])<=0)
							w=anc[w][j];
					w=anc[w][0];
					if(!act[w]) {
						st.upd2(ds[w], de[w]-1, 1, 0, n-1);
						ft.upd(ds[w], 1);
						act[w]=true;
					}
				}
				if(!act[i]) {
					st.upd2(ds[i], de[i]-1, 1, 0, n-1);
					ft.upd(ds[i], 1);
					act[i]=true;
				}
				ans=ans*st.a[1]%M;
			}
			out.println(ans);
		}
		
		void dfs(int u) {
			for(int i=1; i<20; ++i)
				anc[u][i]=anc[u][i-1]<0?-1:anc[anc[u][i-1]][i-1];
			ds[u]=dt++;
			for(int v : adj[u]) {
				anc[v][0]=u;
				dfs(v);
			}
			de[u]=dt;
		}
		
		class SegTree {
			static final int STS=1<<21;
			long[] a = new long[STS], b = new long[STS], lz = new long[STS];
			void app(int i, long x) {
				a[i]=(a[i]+b[i]*x)%M;
				lz[i]+=x;
			}
			void psh(int i) {
				app(2*i, lz[i]);
				app(2*i+1, lz[i]);
				lz[i]=0;
			}
			void upd1(int l1, int i, int l2, int r2) {
				if(l2==r2) {
					a[i]=(a[i]+lz[i])%M;
					++b[i];
					return;
				}
				int m2=(l2+r2)/2;
				psh(i);
				if(l1<=m2)
					upd1(l1, 2*i, l2, m2);
				else
					upd1(l1, 2*i+1, m2+1, r2);
				a[i]=(a[2*i]+a[2*i+1])%M;
				b[i]=b[2*i]+b[2*i+1];
			}
			void upd2(int l1, int r1, int i, int l2, int r2) {
				if(l1<=l2&&r2<=r1) {
					app(i, 1);
					return;
				}
				int m2=(l2+r2)/2;
				psh(i);
				if(l1<=m2)
					upd2(l1, r1, 2*i, l2, m2);
				if(m2<r1)
					upd2(l1, r1, 2*i+1, m2+1, r2);
				a[i]=(a[2*i]+a[2*i+1])%M;
				b[i]=b[2*i]+b[2*i+1];
			}
		}
		
		class FenwickTree {
			int[] a;
			FenwickTree(int n) {
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
