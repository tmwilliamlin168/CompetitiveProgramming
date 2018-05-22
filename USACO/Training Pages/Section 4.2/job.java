package section_4_2;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: job
*/
import java.io.*;
import java.util.*;

public class job {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "job";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), m1=in.nextInt(), m2=in.nextInt();
			int[] a = new int[m1], b = new int[m2];
			for(int i=0; i<m1; ++i)
				a[i]=in.nextInt();
			for(int i=0; i<m2; ++i)
				b[i]=in.nextInt();
			int[] restA = new int[m1], restB = new int[m2], jobDoneA = new int[n], jobDoneB = new int[n];
			int t=0, nLeft=n;
			for(; nLeft>0; ++t) {
				for(int i=0; i<m1; ++i) {
					if(restA[i]>=a[i]) {
						restA[i]=0;
						jobDoneA[n-nLeft]=t;
						--nLeft;
						if(nLeft<=0)
							break;
					}
					++restA[i];
				}
			}
			out.print(t-1+" ");
			t=0;
			nLeft=n;
			for(; nLeft>0; ++t) {
				for(int i=0; i<m2; ++i) {
					if(restB[i]>=b[i]){
						restB[i]=0;
						jobDoneB[n-nLeft]=t;
						--nLeft;
						if(nLeft<=0)
							break;
					}
					++restB[i];
				}
			}
			int max=0;
			for(int i=0; i<n; ++i)
				max=Math.max(jobDoneA[i]+jobDoneB[n-i-1], max);
			out.println(max);
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