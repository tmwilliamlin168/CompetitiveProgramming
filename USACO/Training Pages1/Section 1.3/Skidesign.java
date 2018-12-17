package section_1_3;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: skidesign
*/
import java.io.*;
import java.util.*;

public class skidesign {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "skidesign";
	
	static class Solver {
		Solver() {
			int N=in.nextInt(), minCost=Integer.MAX_VALUE;
			int[] hills = new int[N];
			for(int i=0; i<N; ++i)
				hills[i]=in.nextInt();
			for(int i=0; i<=83; ++i) {
				int cCost=0;
				for(int j=0; j<N; ++j) {
					if(hills[j]<i)
						cCost+=(i-hills[j])*(i-hills[j]);
					else if(hills[j]>i+17)
						cCost+=(hills[j]-(i+17))*(hills[j]-(i+17));
				}
				minCost=Math.min(cCost, minCost);
			}
			out.println(minCost);
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