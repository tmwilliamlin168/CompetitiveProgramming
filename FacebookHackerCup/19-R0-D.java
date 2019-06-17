import java.io.*;
import java.util.*;

public class D {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			out.print("Case #"+_+":");
			new Solver();
		}
		out.close();
	}
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), m=in.nextInt();
			List<Triple> ts = new ArrayList<Triple>();
			for(int i=0; i<m; ++i)
				ts.add(new Triple(in.nextInt()-1, in.nextInt()-1, in.nextInt()-1));
			if(!checkTopo(n, ts)) {
				out.println(" Impossible");
				return;
			}
			boolean[] l = new boolean[n];
			Arrays.fill(l, true);
			for(Triple t : ts)
				l[t.c]=false;
			int[] p = new int[n];
			Arrays.fill(p, -1);
			if(recur(n, ts, l, p))
				for(int i=0; i<n; ++i)
					out.print(" "+(p[i]+1));
			else
				out.print(" Impossible");
			out.println();
		}
		
		boolean recur(int n, List<Triple> ts, boolean[] l, int[] p) {
			if(ts.size()<1) {
				for(int i=0, r=-1; i<n; ++i) {
					if(p[i]<0) {
						p[i]=r;
						r=i;
					}
				}
				return true;
			}
			if(!checkDup(ts))
				return false;
			List<Integer> q = new ArrayList<Integer>();
			for(int i=0; i<n; ++i)
				q.add(i);
			Collections.shuffle(q);
			for(int i=0; i<n; ++i) {
				int u=q.get(i);
				if(l[u])
					continue;
				boolean[] ch = new boolean[n];
				ch[u]=true;
				int np=0, nc=0;
				for(Triple t : ts) {
					if(t.c==u) {
						ch[t.a]=true;
						ch[t.b]=true;
						if(t.a!=u&&t.b!=u)
							++np;
					}
				}
				for(int j=0; j<n&&np>=0; ++j) {
					if(ch[j]&&j!=u) {
						++nc;
						if(!l[j])
							np=-1;
					}
				}
				for(Triple t : ts)
					if(ch[t.a]&&ch[t.b]&&t.c!=u)
						np=-1;
				if(np!=nc*(nc-1)/2)
					continue;
				for(int j=0; j<n; ++j)
					if(ch[j]&&j!=u)
						p[j]=u;
				l[u]=true;
				List<Triple> ts2 = new ArrayList<Triple>();
				for(Triple t : ts) {
					t=new Triple(t);
					if(ch[t.a])
						t.a=u;
					if(ch[t.b])
						t.b=u;
					ts2.add(t);
				}
				int ns=0;
				for(int j=0; j<ts2.size(); ++j)
					if(ts2.get(j).c!=u)
						ts2.set(ns++, ts2.get(j));
				while(ts2.size()>ns)
					ts2.remove(ts2.size()-1);
				if(recur(n, ts2, l, p))
					return true;
				for(int j=0; j<n; ++j)
					if(ch[j])
						p[j]=-1;
				l[u]=false;
				return false;
			}
			for(int i=0; i<n; ++i) {
				int u=q.get(i);
				if(l[u])
					continue;
				boolean[] ch = new boolean[n];
				ch[u]=true;
				boolean ok=true;
				for(Triple t : ts) {
					if(t.c==u) {
						ch[t.a]=true;
						ch[t.b]=true;
					}
				}
				for(int j=0; j<n&&ok; ++j)
					if(ch[j]&&j!=u&&!l[j])
						ok=false;
				for(Triple t : ts)
					if(ch[t.a]&&ch[t.b]&&t.c!=u)
						ok=false;
				if(!ok)
					continue;
				for(int j=0; j<n; ++j)
					if(ch[j]&&j!=u)
						p[j]=u;
				l[u]=true;
				List<Triple> ts2 = new ArrayList<Triple>();
				for(Triple t : ts) {
					t=new Triple(t);
					if(ch[t.a])
						t.a=u;
					if(ch[t.b])
						t.b=u;
					ts2.add(t);
				}
				int ns=0;
				for(int j=0; j<ts2.size(); ++j)
					if(ts2.get(j).c!=u)
						ts2.set(ns++, ts2.get(j));
				while(ts2.size()>ns)
					ts2.remove(ts2.size()-1);
				if(recur(n, ts2, l, p))
					return true;
				for(int j=0; j<n; ++j)
					if(ch[j])
						p[j]=-1;
				l[u]=false;
			}
			return false;
		}
		
		boolean checkDup(List<Triple> ts) {
			for(Triple t : ts)
				if(t.a>t.b)
					t.a^=t.b^(t.b=t.a);
			Collections.sort(ts);
			int fs=0;
			for(int i=0, j=0; i<ts.size(); i=j) {
				for(; j<ts.size()&&ts.get(j).a==ts.get(i).a&&ts.get(j).b==ts.get(i).b; ++j)
					if(ts.get(j).c!=ts.get(i).c)
						return false;
				ts.set(fs++, ts.get(i));
			}
			while(ts.size()>fs)
				ts.remove(ts.size()-1);
			return true;
		}
		
		boolean checkTopo(int n, List<Triple> ts) {
			List<Integer>[] adj = new List[n];
			for(int i=0; i<n; ++i)
				adj[i] = new ArrayList<Integer>();
			int[] d = new int[n];
			for(Triple t : ts) {
				if(t.a!=t.c) {
					adj[t.c].add(t.a);
					++d[t.a];
				}
				if(t.b!=t.c) {
					adj[t.c].add(t.b);
					++d[t.b];
				}
			}
			int[] qu = new int[n];
			int qt=0, qh=0;
			for(int i=0; i<n; ++i)
				if(d[i]<1)
					qu[qt++]=i;
			for(; qh<qt; ) {
				int u=qu[qh++];
				for(int v : adj[u]) {
					--d[v];
					if(d[v]<1)
						qu[qt++]=v;
				}
			}
			return qh>=n;
		}
		
		class Triple implements Comparable<Triple> {
			int a, b, c;
			Triple(int a, int b, int c) {
				this.a=a;
				this.b=b;
				this.c=c;
			}
			Triple(Triple t) {
				this(t.a, t.b, t.c);
			}
			public int compareTo(Triple o) {
				return a==o.a?(b==o.b?c-o.c:b-o.b):a-o.a;
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
