package section_1_2;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: transform
*/
import java.io.*;
import java.util.*;

public class transform {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "transform";
	
	static class Solver {
		Solver() {
			int N=in.nextInt();
			char[][] before = new char[N][], after = new char[N][];
			for(int i=0; i<N; ++i)
				before[i]=in.next().toCharArray();
			for(int i=0; i<N; ++i)
				after[i]=in.next().toCharArray();
			if(Arrays.deepEquals(rotate(before), after)) {
				out.println(1);
				return;
			}
			if(Arrays.deepEquals(rotate(rotate(before)), after)) {
				out.println(2);
				return;
			}
			if(Arrays.deepEquals(rotate(rotate(rotate(before))), after)) {
				out.println(3);
				return;
			}
			if(Arrays.deepEquals(reflect(before), after)) {
				out.println(4);
				return;
			}
			if(Arrays.deepEquals(reflect(rotate(before)), after)
					||Arrays.deepEquals(reflect(rotate(rotate(before))), after)
					||Arrays.deepEquals(reflect(rotate(rotate(rotate(before)))), after)) {
				out.println(5);
				return;
			}
			if(Arrays.deepEquals(before, after)) {
				out.println(6);
			}
			out.println(7);
		}
		
		static char[][] rotate(char[][] mat) {
			char[][] res = new char[mat.length][mat.length];
			for(int i=0; i<mat.length; ++i)
				for(int j=0; j<mat.length; ++j)
					res[i][j] = mat[mat.length-1-j][i];
			return res;
		}
		
		static char[][] reflect(char[][] mat) {
			char[][] res = new char[mat.length][mat.length];
			for(int i=0; i<mat.length; ++i)
				for(int j=0; j<mat.length; ++j)
					res[i][j] = mat[i][mat.length-1-j];
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