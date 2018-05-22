package section_3_2;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: kimbits
*/
import java.io.*;
import java.util.*;

public class kimbits {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "kimbits";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), l=in.nextInt();
			long k=in.nextLong();
			out.println(solve(n, l, k-1));
		}
		String solve(int n, int l, long k) {
			if(n==0)
				return "";
			if(k==0) {
				String s="";
				for(int i=0; i<n; ++i)
					s+="0";
				return s;
			}
			--k;
			int cN=0;
			long[] nCk = new long[l];
			nCk[0]=1;
			long nCkS=1;
			while(nCkS<=k) {
				k-=nCkS;
				++cN;
				nCkS=0;
				for(int i=0; i<Math.min(l, cN); ++i) {
					nCk[i]*=cN;
					nCk[i]/=cN-i;
					nCkS+=nCk[i];
				}
				if(cN<l) {
					nCk[cN]=1;
					++nCkS;
				}
			}
			
			String s="1"+solve(cN, l-1, k);
			while(s.length()<n)
				s="0"+s;
			return s;
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
		long nextLong() {
			return Long.parseLong(next());
		}
	}
}