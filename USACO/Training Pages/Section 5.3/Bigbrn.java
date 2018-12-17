/*
ID: tmwilliamlin168
LANG: JAVA
TASK: bigbrn
*/
import java.io.*;
import java.util.*;

public class bigbrn {
	static final boolean stdin = false;
	static final String filename = "bigbrn";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), t=in.nextInt(), ans=0;
			int[][] h = new int[n+1][n];
			for(int i=0; i<n; ++i)
				Arrays.fill(h[i], n);
			while(t-->0)
				h[in.nextInt()-1][in.nextInt()-1]=0;
			int[] l = new int[n], r = new int[n];
			for(int i=n-1; i>=0; --i) {
				for(int j=0; j<n; ++j) {
					h[i][j]=Math.min(h[i+1][j]+1, h[i][j]);
					l[j]=j-1;
					while(l[j]>=0&&h[i][l[j]]>=h[i][j])
						l[j]=l[l[j]];
				}
				for(int j=n-1; j>=0; --j) {
					r[j]=j+1;
					while(r[j]<n&&h[i][r[j]]>=h[i][j])
						r[j]=r[r[j]];
					ans=Math.max(Math.min(r[j]-l[j]-1, h[i][j]), ans);
				}
			}
			out.println(ans);
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