package section_3_1;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: humble
*/
import java.io.*;
import java.util.*;

public class humble {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "humble";
	
	static class Solver {
		Solver() {
			int k=in.nextInt(), n=in.nextInt();
			int[] primes = new int[k];
			for(int i=0; i<k; ++i)
				primes[i]=in.nextInt();
			int[] hum = new int[n+1], prev = new int[k];
			hum[0]=1;
			for(int i=1; i<=n; ++i) {
				int min=Integer.MAX_VALUE;
				for(int j=0; j<k; ++j) {
					while(primes[j]*hum[prev[j]]<=hum[i-1])
						++prev[j];
					min=Math.min(primes[j]*hum[prev[j]], min);
				}
				hum[i]=min;
			}
			out.println(hum[n]);
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