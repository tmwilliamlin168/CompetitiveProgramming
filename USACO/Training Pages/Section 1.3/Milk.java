package section_1_3;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: milk
*/
import java.io.*;
import java.util.*;

public class milk {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "milk";
	
	static class Solver {
		Solver() {
			int N=in.nextInt(), M=in.nextInt(), t=0, bought=0;
			Pair[] pairs = new Pair[M];
			for(int i=0; i<M; ++i)
				pairs[i] = new Pair(in.nextInt(), in.nextInt());
			Arrays.sort(pairs);
			for(int i=0; i<M&&bought<N; ++i) {
				int unitsToBuy=Math.min(N-bought, pairs[i].b);
				bought+=unitsToBuy;
				t+=pairs[i].a*unitsToBuy;
			}
			out.println(t);
		}
		
		class Pair implements Comparable<Pair> {
			int a, b;
			Pair(int a, int b) {
				this.a=a;
				this.b=b;
			}
			public int compareTo(Pair p) {
				return a-p.a;
			}
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