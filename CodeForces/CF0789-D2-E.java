/*
	- http://codeforces.com/blog/entry/51312
*/

import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final int INF=(int)1e9;
	
	public static void main(String[] args) {
		int n=in.nextInt(), k=in.nextInt();
		boolean[] he = new boolean[2001];
		while(k-->0)
			he[n-in.nextInt()+1000]=true;
		int[] qu = new int[2001], dist = new int[2001];
		int qh=0, qt=0;
		qu[qt++]=1000;
		Arrays.fill(dist, INF);
		dist[1000]=0;
		while(qh<qt) {
			int u=qu[qh++];
			for(int i=0; i<=2000; ++i) {
				if(!he[i]||u+i-1000<0||u+i-1000>2000)
					continue;
				if(u+i-1000==1000) {
					System.out.println(dist[u]+1);
					return;
				}
				if(dist[u+i-1000]>=INF) {
					qu[qt++]=u+i-1000;
					dist[u+i-1000]=dist[u]+1;
				}
			}
		}
		System.out.println(-1);
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
