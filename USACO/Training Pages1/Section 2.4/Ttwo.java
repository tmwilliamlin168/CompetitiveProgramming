package section_2_4;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: ttwo
*/
import java.io.*;
import java.util.*;

public class ttwo {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "ttwo";
	
	static class Solver {
		static int[][] dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
		
		Solver() {
			boolean[][] mat = new boolean[10][10];
			int fR=-1, fC=-1, fDir=0, cR=-1, cC=-1, cDir=0, t=1;
			for(int i=0; i<10; ++i) {
				String s=in.next();
				for(int j=0; j<10; ++j) {
					if(s.charAt(j)=='F') {
						fR=i;
						fC=j;
					} else if(s.charAt(j)=='C') {
						cR=i;
						cC=j;
					} else if(s.charAt(j)=='*')
						mat[i][j]=true;
				}
			}
			boolean[] visited = new boolean[160000];
			visited[fR+fC*10+fDir*100+cR*400+cC*4000+cDir*40000]=true;
			while(true) {
				int nR, nC;
				nR=fR+dirs[fDir][0];
				nC=fC+dirs[fDir][1];
				if(nR<0||nR>=10||nC<0||nC>=10||mat[nR][nC])
					fDir=(fDir+1)%4;
				else {
					fR=nR;
					fC=nC;
				}
				nR=cR+dirs[cDir][0];
				nC=cC+dirs[cDir][1];
				if(nR<0||nR>=10||nC<0||nC>=10||mat[nR][nC])
					cDir=(cDir+1)%4;
				else {
					cR=nR;
					cC=nC;
				}
				if(fR==cR&&fC==cC) {
					out.println(t);
					return;
				}
				if(visited[fR+fC*10+fDir*100+cR*400+cC*4000+cDir*40000]) {
					out.println(0);
					return;
				}
				visited[fR+fC*10+fDir*100+cR*400+cC*4000+cDir*40000]=true;
				++t;
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