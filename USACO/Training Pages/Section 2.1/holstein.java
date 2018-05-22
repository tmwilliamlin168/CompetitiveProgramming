package section_2_1;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: holstein
*/
import java.io.*;
import java.util.*;

public class holstein {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "holstein";
	
	static class Solver {
		Solver() {
			int V=in.nextInt();
			int[] requiredV = new int[V];
			for(int i=0; i<V; ++i)
				requiredV[i] = in.nextInt();
			int G=in.nextInt();
			int[][] feeds = new int[G][V];
			for(int i=0; i<G; ++i)
				for(int j=0; j<V; ++j)
					feeds[i][j]=in.nextInt();
			int minScoops=G+1, minI=-1;
			int[][] dp = new int[1<<G][V];
			for(int i=1; i<(1<<G); ++i) {
				for(int j=0; j<G; ++j) {
					if((i&(1<<j))!=0) {
						for(int k=0; k<V; ++k)
							dp[i][k]=dp[i^(1<<j)][k]+feeds[j][k];
						break;
					}
				}
				int cScoops=Integer.bitCount(i);
				if(cScoops<minScoops) {
					boolean works=true;
					for(int j=0; j<V; ++j) {
						if(dp[i][j]<requiredV[j]) {
							works=false;
							break;
						}
					}
					if(works) {
						minScoops=cScoops;
						minI=i;
					}
				}
			}
			out.print(minScoops);
			for(int i=0; i<G; ++i)
				if((minI&(1<<i))!=0)
					out.print(" "+(i+1));
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
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
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