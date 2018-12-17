package section_1_4;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: ariprog
*/
import java.io.*;
import java.util.*;

public class ariprog {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "ariprog";
	
	static class Solver {
		boolean[] isBisquare = new boolean[2*250*250+1];
		
		Solver() {
			int N=in.nextInt(), M=in.nextInt();
			for(int p=0; p<=M; ++p)
				for(int q=p; q<=M; ++q)
					isBisquare[p*p+q*q]=true;
			boolean noAnswers=true;
			for(int b=1; b<=2*M*M/(N-1); ++b) {
				for(int a=0; a+b*(N-1)<=2*M*M; ++a) {
					boolean works=true;
					for(int i=0; i<N; ++i) {
						if(!isBisquare[a+b*i]) {
							works=false;
							break;
						}
					}
					if(works) {
						noAnswers=false;
						out.println(a+" "+b);
					}
				}
			}
			if(noAnswers)
				out.println("NONE");
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