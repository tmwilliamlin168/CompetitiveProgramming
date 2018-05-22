package section_2_3;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: zerosum
*/
import java.io.*;
import java.util.*;

public class zerosum {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "zerosum";
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			recur(new char[n-1], 0);
		}
		
		void recur(char[] c, int i) {
			if(i==c.length) {
				int t=0, cI=c.length;
				char lastC='+';
				for(int j=0; j<=c.length; ++j) {
					int cur=j+1;
					while(j<c.length&&c[j]==' ') {
						++j;
						cur=cur*10+j+1;
					}
					if(lastC=='+')
						t+=cur;
					else
						t-=cur;
					if(j<c.length)
						lastC=c[j];
				}
				if(t==0) {
					out.print(1);
					for(int j=0; j<c.length; ++j)
						out.print(""+c[j]+(j+2));
					out.println();
				}
			} else {
				c[i]=' ';
				recur(c, i+1);
				c[i]='+';
				recur(c, i+1);
				c[i]='-';
				recur(c, i+1);
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