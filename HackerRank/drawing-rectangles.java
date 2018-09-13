import java.io.*;
import java.util.*;

public class Solution {
	static final int MC=300000, INF=(int)1e9;
	static List<Integer>[] canMatch = new List[MC+1];
	static boolean[] used = new boolean[MC+1], vis1 = new boolean[MC+1], vis2 = new boolean[MC+1];
	static int[] match = new int[MC+1], dist = new int[MC+1];
	
	public static void main(String[] args) {
		Reader in = new Reader();
		PrintWriter out = new PrintWriter(System.out);
		int n=in.nextInt();
		List<Query>[] queries = new List[MC+2];
		for(int i=0; i<=MC; ++i)
			queries[i] = new ArrayList<Query>();
		for(int i=0; i<n; ++i) {
			int x1=in.nextInt(), y1=in.nextInt(), x2=in.nextInt(), y2=in.nextInt();
			queries[x1].add(new Query(y1, y2, 1));
			queries[x2+1].add(new Query(y1, y2, -1));
		}
		SegTree st = new SegTree();
		for(int i=0; i<=MC; ++i) {
			for(Query q : queries[i])
				st.upd(q.l, q.r, q.x);
			st.gen();
			canMatch[i] = st.ys;
		}
		Arrays.fill(match, -1);
		int[] qu = new int[MC+1];
		int qt;
		while(true) {
			Arrays.fill(dist, INF);
			qt=0;
			for(int i=0; i<=MC; ++i) {
				if(!used[i]) {
					qu[qt++]=i;
					dist[i]=0;
				}
			}
			for(int qh=0; qh<qt; ++qh) {
				int u=qu[qh];
				for(int v1 : canMatch[u]) {
					int v2=match[v1];
					if(v2!=-1&&dist[v2]>=INF) {
						qu[qt++]=v2;
						dist[v2]=dist[u]+1;
					}
				}
			}
			boolean ch=false;
			Arrays.fill(vis1, false);
			for(int i=0; i<=MC; ++i)
				if(!used[i]&&dfs1(i))
					ch=true;
			if(!ch)
				break;
		}
		Arrays.fill(vis1, false);
		for(int i=0; i<=MC; ++i)
			if(!used[i])
				dfs2(i);
		int tc=0, tr=0;
		for(int i=0; i<=MC; ++i) {
			if(!vis1[i])
				++tc;
			if(vis2[i])
				++tr;
		}
		out.println(tc+tr);
		out.println(tc);
		for(int i=0; i<=MC; ++i)
			if(!vis1[i])
				out.print(i+" ");
		out.println("\n"+tr);
		for(int i=0; i<=MC; ++i)
			if(vis2[i])
				out.print(i+" ");
		out.println();
		out.close();
	}
	
	static boolean dfs1(int u) {
		vis1[u]=true;
		for(int v1 : canMatch[u]) {
			int v2=match[v1];
			if(v2==-1||!vis1[v2]&&dist[v2]==dist[u]+1&&dfs1(v2)) {
				match[v1]=u;
				used[u]=true;
				return true;
			}
		}
		return false;
	}
	
	static void dfs2(int u) {
		vis1[u]=true;
		for(int v1 : canMatch[u]) {
			if(!vis2[v1]) {
				vis2[v1]=true;
				dfs2(match[v1]);
			}
		}
	}
	
	static class SegTree {
		int n=MC+1, l, r, x;
		int[] a = new int[1<<20], lz = new int[1<<20];
		List<Integer> ys;
		void push(int i, int l2, int r2) {
			a[i]+=lz[i]*(r2-l2+1);
			if(l2<r2) {
				lz[2*i]+=lz[i];
				lz[2*i+1]+=lz[i];
			}
			lz[i]=0;
		}
		void upd(int l, int r, int x) {
			this.l=l;
			this.r=r;
			this.x=x;
			upd2(1, 0, n-1);
		}
		void upd2(int i, int l2, int r2) {
			if(l<=l2&&r2<=r) {
				lz[i]+=x;
				push(i, l2, r2);
				return;
			}
			int m=(l2+r2)/2;
			push(2*i, l2, m);
			push(2*i+1, m+1, r2);
			if(l<=m)
				upd2(2*i, l2, m);
			if(m<r)
				upd2(2*i+1, m+1, r2);
			a[i]=a[2*i]+a[2*i+1];
		}
		void gen() {
			ys = new ArrayList<Integer>();
			gen2(1, 0, n-1);
		}
		void gen2(int i, int l2, int r2) {
			if(l2==r2) {
				ys.add(l2);
				return;
			}
			int m=(l2+r2)/2;
			push(2*i, l2, m);
			push(2*i+1, m+1, r2);
			if(a[2*i]>0)
				gen2(2*i, l2, m);
			if(a[2*i+1]>0)
				gen2(2*i+1, m+1, r2);
		}
	}
	
	static class Query {
		int l, r, x;
		Query(int l, int r, int x) {
			this.l=l;
			this.r=r;
			this.x=x;
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
