import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "triangles";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			long[] x = new long[n], y = new long[n];
			for(int i=0; i<n; ++i) {
				x[i]=in.nextInt();
				y[i]=in.nextInt();
			}
			int[][] below = new int[n][n];
			for(int i=0; i<n; ++i)
				for(int j=0; j<n; ++j)
					for(int k=0; k<n; ++k)
						if(x[i]<=x[k]&&x[k]<x[j]&&(y[k]-y[i])*(x[j]-x[i])<(y[j]-y[i])*(x[k]-x[i]))
							++below[i][j];
			int[] cnt = new int[n-2];
			for(int i=0; i<n; ++i) {
				for(int k=0; k<n; ++k) {
					if(i==k||x[i]>x[k]||x[i]==x[k]&&y[k]>y[i])
						continue;
					for(int j=0; j<n; ++j) {
						if(x[j]>x[k]) {
							if((y[k]-y[i])*(x[j]-x[i])<(y[j]-y[i])*(x[k]-x[i]))
								++cnt[below[i][j]-below[i][k]-below[k][j]-1];
							else
								++cnt[below[i][k]+below[k][j]-below[i][j]];
						} else if(i!=j&&j!=k&&x[j]==x[k]&&y[j]>y[k])
							++cnt[below[i][j]-below[i][k]];
					}
				}
			}
			for(int i=0; i<n-2; ++i)
				out.println(cnt[i]);
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
