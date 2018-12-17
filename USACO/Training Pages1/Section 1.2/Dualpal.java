package section_1_2;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: dualpal
*/
import java.io.*;
import java.util.*;

public class dualpal {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "dualpal";
	
	static class Solver {
		Solver() {
			int N=in.nextInt(), S=in.nextInt()+1, found=0;
			while(found<N) {
				int bases=0;
				for(int b=2; b<=10; ++b) {
					String str=str(S, b);
					boolean isPalin=true;
					for(int i=0; i<str.length()/2; ++i) {
						if(str.charAt(i)!=str.charAt(str.length()-1-i)) {
							isPalin=false;
							break;
						}
					}
					if(isPalin)
						++bases;
					if(bases>=2)
						break;
				}
				if(bases>=2) {
					++found;
					out.println(S);
				}
				++S;
			}
		}

		static String str(int n, int b) {
			String res="";
			while(n>0) {
				res=n%b+res;
				n/=b;
			}
			return res;
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