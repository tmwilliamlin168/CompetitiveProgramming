/*
	- https://atcoder.jp/img/arc079/editorial.pdf
*/

import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static List<Integer>[] adj;
	static boolean[] vis, act, ic;
	static List<Integer> cyc = new ArrayList<Integer>();
	static int[] a;
	
	public static void main(String[] args) {
		int n=in.nextInt();
		adj = new List[n];
		for(int i=0; i<n; ++i)
			adj[i] = new ArrayList<Integer>();
		for(int i=0; i<n; ++i)
			adj[in.nextInt()-1].add(i);
		vis = new boolean[n];
		act = new boolean[n];
		ic = new boolean[n];
		a = new int[n];
		for(int i=0; i<n; ++i)
			if(!vis[i]&&dfs1(i))
				break;
		cyc.remove(cyc.size()-1);
		Arrays.fill(a, -1);
		a[cyc.get(0)]=n;
		if(dfs2(cyc.get(0))!=a[cyc.get(1)]) {
			System.out.println("POSSIBLE");
			return;
		}
		int a1=a[cyc.get(0)];
		Arrays.fill(a, -1);
		a[cyc.get(0)]=a1;
		if(dfs2(cyc.get(0))==a1)
			System.out.println("POSSIBLE");
		else
			System.out.println("IMPOSSIBLE");
	}
	
	static boolean dfs1(int u) {
		vis[u]=true;
		act[u]=true;
		for(int v : adj[u]) {
			if(act[v]) {
				cyc.add(v);
				ic[v]=true;
				cyc.add(u);
				ic[u]=true;
				return true;
			}
			if(dfs1(v)) {
				if(ic[v]&&v!=cyc.get(0)) {
					cyc.add(u);
					ic[u]=true;
				}
				return true;
			}
		}
		act[u]=false;
		return false;
	}
	
	static int dfs2(int u) {
		List<Integer> b = new ArrayList<Integer>();
		b.add(0);
		b.add(Integer.MAX_VALUE);
		for(int v : adj[u])
			b.add(a[v]==-1?dfs2(v):a[v]);
		Collections.sort(b);
		for(int i=0; ; ++i)
			if(b.get(i+1)>b.get(i)+1)
				return a[u]=b.get(i)+1;
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
