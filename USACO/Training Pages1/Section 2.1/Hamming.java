package section_2_1;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: hamming
*/
import java.io.*;
import java.util.*;

public class hamming {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "hamming";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), b=in.nextInt(), d=in.nextInt(), cur=0;
			List<Integer> codewords = new ArrayList<Integer>();
			while(codewords.size()<n) {
				boolean works=true;
				for(int codeword : codewords) {
					if(hamDist(cur, codeword)<d) {
						works=false;
						break;
					}
				}
				if(works)
					codewords.add(cur);
				++cur;
			}
			for(int i=0; i<n; ++i)
				out.print(codewords.get(i)+(i%10==9||i==n-1?"\n":" "));
		}
		int hamDist(int a, int b) {
			int t=0;
			for(int i=0; i<8; ++i)
				if((a&(1<<i))!=(b&(1<<i)))
					++t;
			return t;
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