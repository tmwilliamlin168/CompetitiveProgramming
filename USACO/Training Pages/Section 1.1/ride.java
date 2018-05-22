package section_1_1;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: ride
*/
import java.io.*;
import java.util.*;

public class ride {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "ride";
	
	static class Solver {
		Solver() {
			String s1=in.next();
			String s2=in.next();
			int prod1=1, prod2=1;
			for(char c : s1.toCharArray())
				prod1=prod1*(c-'A'+1)%47;
			for(char c : s2.toCharArray())
				prod2=prod2*(c-'A'+1)%47;
			if(prod1==prod2)
				out.println("GO");
			else
				out.println("STAY");
		}
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
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