import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "newbarn";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int q=in.nextInt(), n=0, grps=0;
			Query[] queries = new Query[q];
			int[] grp = new int[q], p = new int[q];
			for(int i=0; i<q; ++i) {
				if(in.next().charAt(0)=='B') {
					queries[i] = new Query(0, n);
					p[n]=in.nextInt()-1;
					grp[n]=p[n]==-2?grps++:grp[p[n]];
					++n;
				} else
					queries[i] = new Query(1, in.nextInt()-1);
			}
			int[] ig = new int[n], gs = new int[grps];
			for(int i=0; i<n; ++i)
				ig[i]=gs[grp[i]]++;
			Graph[] gfs = new Graph[grps];
			for(int i=0; i<grps; ++i)
				gfs[i] = new Graph(gs[i]);
			for(int i=0; i<n; ++i) {
				if(p[i]!=-2) {
					gfs[grp[i]].adj[ig[i]].add(ig[p[i]]);
					gfs[grp[i]].adj[ig[p[i]]].add(ig[i]);
				}
			}
			for(int i=0; i<grps; ++i)
				gfs[i].pp();
			for(int i=0; i<q; ++i) {
				if(queries[i].t==0)
					gfs[grp[queries[i].u]].col(ig[queries[i].u]);
				else
					out.println(gfs[grp[queries[i].u]].md(ig[queries[i].u]));
			}
		}
		
		class Graph {
			int n, dt;
			List<Integer>[] adj, cc;
			int[] st, cp, sz, md2, pci;
			int[][] depT;
			Mex[] md1;
			Graph(int n) {
				this.n=n;
				adj = new List[n];
				for(int i=0; i<n; ++i)
					adj[i] = new ArrayList<Integer>();
			}
			void pp() {
				st = new int[n];
				depT = new int[31-Integer.numberOfLeadingZeros(2*n-1)+1][2*n-1];
				dfs1(0, -1);
				for(int k=1; k<depT.length; ++k)
					for(int i=0; i<2*n-(1<<k); ++i)
						depT[k][i]=Math.min(depT[k-1][i], depT[k-1][i+(1<<(k-1))]);
				cp = new int[n];
				sz = new int[n];
				Arrays.fill(cp, -1);
				cc = new List[n];
				for(int i=0; i<n; ++i)
					cc[i] = new ArrayList<Integer>();
				pci = new int[n];
				dfs2(0, -1);
				cd(0, -2);
				md1 = new Mex[n];
				for(int i=0; i<n; ++i)
					md1[i] = new Mex();
				md2 = new int[n];
			}
			void dfs1(int u, int p) {
				depT[0][st[u]=dt++]=p==-1?0:depT[0][st[p]]+1;
				for(int v : adj[u]) {
					if(v==p)
						continue;
					dfs1(v, u);
					depT[0][dt++]=depT[0][st[u]];
				}
			}
			int dist(int u, int v) {
				if(st[u]>st[v]) {
					u^=v;
					v^=u;
					u^=v;
				}
				int k=31-Integer.numberOfLeadingZeros(st[v]-st[u]);
				return depT[0][st[u]]+depT[0][st[v]]-2*Math.min(depT[k][st[u]], depT[k][st[v]-(1<<k)+1]);
			}
			void cd(int u, int p) {
				int c=dfs3(u, -1, sz[u]);
				dfs2(c, -1);
				cp[c]=p;
				if(p!=-2) {
					pci[c]=cc[p].size();
					cc[p].add(c);
				}
				for(int v : adj[c])
					if(cp[v]==-1)
						cd(v, c);
			}
			void dfs2(int u, int p) {
				sz[u]=1;
				for(int v : adj[u]) {
					if(v==p||cp[v]!=-1)
						continue;
					dfs2(v, u);
					sz[u]+=sz[v];
				}
			}
			int dfs3(int u, int p, int t) {
				for(int v : adj[u])
					if(v!=p&&cp[v]==-1&&sz[v]>t/2)
						return dfs3(v, u, t);
				return u;
			}
			void col(int u) {
				md1[u].upd(cc[u].size(), 0);
				for(int v=u; cp[v]!=-2; md2[cp[v]]=Math.max(dist(u, cp[v]), md2[cp[v]]), v=cp[v])
					md1[cp[v]].upd(pci[v], dist(u, cp[v]));
			}
			int md(int u) {
				int r=md2[u];
				for(int v=u; cp[v]!=-2; v=cp[v])
					r=Math.max(md1[cp[v]].qry(pci[v])+dist(cp[v], u), r);
				return r;
			}
		}
		
		class Query {
			int t, u;
			Query(int t, int u) {
				this.t=t;
				this.u=u;
			}
		}
		
		class Mex {
			int i1=-1, v1=Integer.MIN_VALUE, i2=-2, v2=Integer.MIN_VALUE;
			void upd(int i, int x) {
				if(x>v1) {
					if(i!=i1) {
						i2=i1;
						v2=v1;
					}
					i1=i;
					v1=x;
				} else if(x>v2&&i!=i1) {
					i2=i;
					v2=x;
				}
			}
			int qry(int i) {
				return i1!=i?v1:v2;
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
