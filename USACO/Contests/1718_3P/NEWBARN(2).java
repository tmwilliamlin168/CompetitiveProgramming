import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "newbarn";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		int q=in.nextInt(), lgq=31-Integer.numberOfLeadingZeros(q), n=0, grps=0;
		int[] dep = new int[q], grp = new int[q], dia1 = new int[q], dia2 = new int[q], dl = new int[q];
		int[][] p = new int[q][lgq+1];
		
		Solver() {
			while(q-->0) {
				char qt=in.next().charAt(0);
				int u=in.nextInt()-1;
				if(qt=='B') {
					dep[n]=u==-2?0:dep[u]+1;
					grp[n]=u==-2?grps++:grp[u];
					p[n][0]=u==-2?-1:u;
					for(int i=1; i<=lgq; ++i)
						p[n][i]=p[n][i-1]!=-1?p[p[n][i-1]][i-1]:-1;
					if(u!=-2) {
						int d1=dist(n, dia1[grp[n]]), d2=dist(n, dia2[grp[n]]);
						if(d1>dl[grp[n]]) {
							dia2[grp[n]]=n;
							dl[grp[n]]=d1;
						} else if(d2>dl[grp[n]]) {
							dia1[grp[n]]=n;
							dl[grp[n]]=d2;
						}
					} else
						dia1[grp[n]]=dia2[grp[n]]=n;
					++n;
				} else
					out.println(Math.max(dist(u, dia1[grp[u]]), dist(u, dia2[grp[u]])));
			}
		}
		
		int dist(int u, int v) {
			int r=dep[u]+dep[v];
			if(dep[u]<dep[v]) {
				u^=v;
				v^=u;
				u^=v;
			}
			for(int k=p[0].length-1; k>=0; --k)
				if(dep[u]-dep[v]>=1<<k)
					u=p[u][k];
			for(int k=p[0].length-1; k>=0; --k) {
				if(p[u][k]!=p[v][k]) {
					u=p[u][k];
					v=p[v][k];
				}
			}
			if(u!=v)
				u=p[u][0];
			return r-2*dep[u];
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
