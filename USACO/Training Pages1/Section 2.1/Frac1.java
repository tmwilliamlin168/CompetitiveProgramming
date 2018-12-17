package section_2_1;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: frac1
*/
import java.io.*;
import java.util.*;

public class frac1 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "frac1";
	
	static class Solver {
		Solver() {
			int N=in.nextInt();
			List<Pair> fracs = new ArrayList<Pair>();
			for(int i=1; i<=N; ++i)
				for(int j=0; j<=i; ++j)
					if(gcd(i, j)==1)
						fracs.add(new Pair(j, i));
			Collections.sort(fracs);
			for(Pair p : fracs)
				out.println(p.a+"/"+p.b);
		}
		int gcd(int a, int b) {
			if(b>a) {
				int temp=a;
				a=b;
				b=temp;
			}
			while(b!=0) {
				int newB=a%b;
				a=b;
				b=newB;
			}
			return a;
		}
		class Pair implements Comparable<Pair> {
			int a, b;
			Pair(int a, int b) {
				this.a=a;
				this.b=b;
			}
			public int compareTo(Pair p) {
				return Double.compare((double)a/b, (double)p.a/p.b);
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