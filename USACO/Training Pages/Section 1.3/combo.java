package section_1_3;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: combo
*/
import java.io.*;
import java.util.*;

public class combo {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "combo";
	
	static class Solver {
		Solver() {
			int N=in.nextInt();
			int a1=in.nextInt()-1, a2=in.nextInt()-1, a3=in.nextInt()-1;
			int b1=in.nextInt()-1, b2=in.nextInt()-1, b3=in.nextInt()-1;
			boolean[][][] works = new boolean[100][100][100];
			for(int i=a1-2; i<=a1+2; ++i)
				for(int j=a2-2; j<=a2+2; ++j)
					for(int k=a3-2; k<=a3+2; ++k)
						works[(i+N)%N][(j+N)%N][(k+N)%N]=true;
			for(int i=b1-2; i<=b1+2; ++i)
				for(int j=b2-2; j<=b2+2; ++j)
					for(int k=b3-2; k<=b3+2; ++k)
						works[(i+N)%N][(j+N)%N][(k+N)%N]=true;
			int t=0;
			for(int i=0; i<100; ++i)
				for(int j=0; j<100; ++j)
					for(int k=0; k<100; ++k)
						if(works[i][j][k])
							++t;
			out.println(t);
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