package section_2_4;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: cowtour
*/
import java.io.*;
import java.util.*;

public class cowtour {
	static boolean stdin=true;
	static Reader in;
	static PrintWriter out;
	static String fileName = "cowtour";
	
	static class Solver {
		static double INF = 1e9;
		
		Solver() {
			int n=in.nextInt();
			int[] x = new int[n], y = new int[n];
			for(int i=0; i<n; ++i) {
				x[i]=in.nextInt();
				y[i]=in.nextInt();
			}
			boolean[][] adj = new boolean[n][n];
			for(int i=0; i<n; ++i) {
				String s = in.next();
				for(int j=0; j<n; ++j)
					adj[i][j]=s.charAt(j)=='1'||i==j;
			}
			double[][] minDist = new double[n][n];
			for(int i=0; i<n; ++i) {
				for(int j=0; j<n; ++j) {
					if(adj[i][j])
						minDist[i][j]=Math.hypot(x[i]-x[j], y[i]-y[j]);
					else
						minDist[i][j]=INF;
				}
			}
			for(int k=0; k<n; ++k)
				for(int i=0; i<n; ++i)
					for(int j=0; j<n; ++j)
						minDist[i][j]=Math.min(minDist[i][k]+minDist[j][k], minDist[i][j]);
			double[] maxDist = new double[n];
			for(int i=0; i<n; ++i)
				for(int j=0; j<n; ++j)
					if(minDist[i][j]!=INF)
						maxDist[i]=Math.max(minDist[i][j], maxDist[i]);
			double[] diam = new double[n];
			Arrays.fill(diam, -1);
			for(int i=0; i<n; ++i) {
				for(int j=0; j<n; ++j) {
					if(diam[j]!=-1) {
						diam[i]=diam[j];
						break;
					}
					diam[i]=Math.max(maxDist[j], diam[i]);
				}
			}
			double min=INF;
			for(int i=0; i<n; ++i)
				for(int j=0; j<n; ++j)
					if(!(i==j||minDist[i][j]!=INF))
						min=Math.min(Math.max(maxDist[i]+maxDist[j]+Math.hypot(x[i]-x[j], y[i]-y[j]), Math.max(diam[i], diam[j])), min);
			out.printf("%.6f", min);
			out.println();
		}
	}
	
	static void preprocess() {
		
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(fileName+".in");
			out = new PrintWriter(fileName+".out");
		}
		preprocess();
		for(int testCases=1; testCases>0; --testCases)
			new Solver();
		out.close();
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			br = new BufferedReader(new InputStreamReader(System.in));
		}
		Reader(String fileName) throws Exception {
			br = new BufferedReader(new FileReader(fileName));
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
