package section_1_5;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: sprime
*/
import java.io.*;
import java.util.*;

public class sprime {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "sprime";
	
	static class Solver {
		int N;
		Solver() {
			N=in.nextInt();
			recur(0, 0);
		}
		void recur(int x, int i) {
			if(i==N)
				out.println(x);
			else {
				for(int j=i==0?2:0; j<10; ++j) {
					int a=x*10+j;
					boolean isComposite=false;
					for(int k=2; k*k<=a; ++k) {
						if(a%k==0) {
							isComposite=true;
							break;
						}
					}
					if(!isComposite)
						recur(a, i+1);
				}
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