package section_4_3;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: buylow
*/
import java.io.*;
import java.math.*;
import java.util.*;

public class buylow {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "buylow";
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			int[] a = new int[n];
			for(int i=0; i<n; ++i)
				a[i] = in.nextInt();
			int[] next = new int[n];
			Map<Integer, Integer> seen = new HashMap<Integer, Integer>();
			for(int i=n-1; i>=0; --i) {
				if(!seen.containsKey(a[i]))
					next[i]=n;
				else
					next[i]=seen.get(a[i]);
				seen.put(a[i], i);
			}
			int[] dp1 = new int[n];
			BigInteger[] dp2 = new BigInteger[n];
			dp1[0]=1;
			dp2[0]=BigInteger.ONE;
			for(int i=1; i<n; ++i) {
				int max=0;
				BigInteger nMax=BigInteger.ONE;
				for(int j=i-1; j>=0; --j) {
					if(a[j]<=a[i]||next[j]<i)
						continue;
					if(dp1[j]>max) {
						max=dp1[j];
						nMax=dp2[j];
					} else if(dp1[j]==max)
						nMax=nMax.add(dp2[j]);
				}
				dp1[i]=max+1;
				dp2[i]=nMax;
			}
			int max=0;
			BigInteger nMax=BigInteger.ONE;
			for(int i=n-1; i>=0; --i) {
				if(next[i]<n)
					continue;
				if(dp1[i]>max) {
					max=dp1[i];
					nMax=dp2[i];
				} else if(dp1[i]==max)
					nMax=nMax.add(dp2[i]);
			}
			//System.out.println(Arrays.toString(dp1));
			//System.out.println(Arrays.toString(dp2));
			out.println(max+" "+nMax);
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