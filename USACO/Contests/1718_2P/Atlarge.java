import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "atlarge";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		int n, bs, bc, dt;
		int[] st, en, iot, dd, d1, lz, ans;
		int[][] ps;
		List<Integer>[] graph;
		
		Solver() {
			n=in.nextInt();
			bs=(int)Math.sqrt(n);
			bc=(n-1)/bs+1;
			st = new int[n];
			en = new int[n];
			iot = new int[n];
			dd = new int[n];
			d1 = new int[n];
			lz = new int[bc];
			ans = new int[n];
			ps = new int[bc][2*n];
			graph = new List[n];
			for(int i=0; i<n; ++i)
				graph[i] = new ArrayList<Integer>();
			for(int i=0; i<n-1; ++i) {
				int u=in.nextInt()-1, v=in.nextInt()-1;
				graph[u].add(v);
				graph[v].add(u);
			}
			dfs1(0, -1);
			int[] qu = new int[n], d2 = new int[n];
			Arrays.fill(d2, n);
			int qh=0, qt=0;
			for(int i=0; i<n; ++i) {
				if(graph[i].size()==1) {
					qu[qt++]=i;
					d2[i]=0;
				}
			}
			while(qh<qt) {
				int u=qu[qh++];
				for(int v : graph[u]) {
					if(d2[v]>=n) {
						qu[qt++]=v;
						d2[v]=d2[u]+1;
					}
				}
			}
			for(int i=0; i<n; ++i)
				ps[i/bs][(dd[i]=d1[iot[i]]-d2[iot[i]])+n]+=2-graph[iot[i]].size();
			for(int i=0; i<bc; ++i)
				for(int j=ps[i].length-2; j>=0; --j)
					ps[i][j]+=ps[i][j+1];
			dfs2(0, -1);
			for(int i=0; i<n; ++i)
				out.println(graph[i].size()>1?ans[i]:1);
		}
		
		void dfs1(int u, int p) {
			iot[st[u]=dt++]=u;
			d1[u]=p==-1?0:d1[p]+1;
			for(int v : graph[u])
				if(v!=p)
					dfs1(v, u);
			en[u]=dt;
		}
		
		void dfs2(int u, int p) {
			for(int i=0; i<bc; ++i)
				ans[u]+=ps[i][n-lz[i]];
			addRange(0, n, 1);
			for(int v : graph[u]) {
				if(v==p)
					continue;
				addRange(st[v], en[v], -2);
				dfs2(v, u);
				addRange(st[v], en[v], 2);
			}
			addRange(0, n, -1);
		}
		
		void addRange(int l, int r, int x) {
			if(l%bs>0) {
				for(; l%bs>0&&l<r; ++l) {
					if(x>0)
						for(int i=0; i<x; ++i)
							ps[l/bs][++dd[l]+n]+=2-graph[iot[l]].size();
					else
						for(int i=0; i<-x; ++i)
							ps[l/bs][dd[l]--+n]-=2-graph[iot[l]].size();
				}
			}
			for(; l+bs<=r; l+=bs)
				lz[l/bs]+=x;
			if(r%bs>0) {
				if(r<n||l%bs>0) {
					for(; l<r; ++l) {
						if(x>0)
							for(int i=0; i<x; ++i)
								ps[l/bs][++dd[l]+n]+=2-graph[iot[l]].size();
						else
							for(int i=0; i<-x; ++i)
								ps[l/bs][dd[l]--+n]-=2-graph[iot[l]].size();
					}
				} else
					lz[r/bs]+=x;
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
