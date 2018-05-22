package section_2_2;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: subset
*/
import java.io.*;
import java.util.*;

public class subset {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "subset";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), mid=1000;
			int[] cntA = new int[2001], cntB = new int[2001];
			int[] dp1 = new int[1<<(n/2)], dp2 = new int[1<<(n-n/2)];
			dp1[0]=-n/2*(n/2+1)/2;
			++cntA[dp1[0]+mid];
			for(int i=1; i<1<<(n/2); ++i) {
				for(int j=0; j<n/2; ++j) {
					if((i&(1<<j))!=0) {
						dp1[i]=dp1[i^(1<<j)]+2*(j+1);
						++cntA[dp1[i]+mid];
						break;
					}
				}
			}
			dp2[0]=-n*(n+1)/2-dp1[0];
			++cntB[dp2[0]+mid];
			for(int i=1; i<1<<(n-n/2); ++i) {
				for(int j=0; j<n-n/2; ++j) {
					if((i&(1<<j))!=0) {
						dp2[i]=dp2[i^(1<<j)]+2*(j+1+n/2);
						++cntB[dp2[i]+mid];
						break;
					}
				}
			}
			long t=0;
			for(int i=-1000; i<=1000; ++i) {
				t+=(long)cntA[i+mid]*cntB[mid-i];
			}
			out.println(t/2);
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