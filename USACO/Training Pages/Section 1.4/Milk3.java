package section_1_4;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: milk3
*/
import java.io.*;
import java.util.*;

public class milk3 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "milk3";
	
	static class Solver {
		boolean[][][] visited;
		boolean[] possible;
		int A, B, C;
		
		Solver() {
			A=in.nextInt();
			B=in.nextInt();
			C=in.nextInt();
			visited = new boolean[A+1][B+1][C+1];
			possible = new boolean[C+1];
			recur(0, 0, C);
			List<Integer> amounts = new ArrayList<Integer>();
			for(int i=0; i<=C; ++i)
				if(possible[i])
					amounts.add(i);
			for(int i=0; i<amounts.size(); ++i)
				out.print((i==0?"":" ")+amounts.get(i));
			out.println();
		}
		void recur(int a, int b, int c) {
			if(visited[a][b][c])
				return;
			visited[a][b][c]=true;
			if(a==0)
				possible[c]=true;
			recur(a-Math.min(a, B-b), b+Math.min(a, B-b), c);
			recur(a-Math.min(a, C-c), b, c+Math.min(a, C-c));
			recur(a+Math.min(b, A-a), b-Math.min(b, A-a), c);
			recur(a, b-Math.min(b, C-c), c+Math.min(b, C-c));
			recur(a+Math.min(c, A-a), b, c-Math.min(c, A-a));
			recur(a, b+Math.min(c, B-b), c-Math.min(c, B-b));
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