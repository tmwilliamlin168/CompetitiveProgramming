package section_3_4;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: heritage
*/
import java.io.*;
import java.util.*;

public class heritage {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "heritage";
	
	static class Solver {
		Solver() {
			String inOrd=in.next(), preOrd=in.next();
			recur(inOrd, preOrd);
			out.println();
		}
		void recur(String inOrd, String preOrd) {
			if(preOrd.length()==0)
				return;
			char root=preOrd.charAt(0);
			int i=inOrd.indexOf(root);
			recur(inOrd.substring(0, i), preOrd.substring(1, i+1));
			recur(inOrd.substring(i+1), preOrd.substring(i+1));
			out.print(root);
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