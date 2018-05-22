package section_1_3;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: crypt1
*/
import java.io.*;
import java.util.*;

public class crypt1 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "crypt1";
	
	static int[] digits;
	static int t;
	
	static class Solver {
		Solver() {
			int N=in.nextInt();
			digits = new int[N];
			for(int i=0; i<N; ++i)
				digits[i]=in.nextInt();
			recur(new int[5], 0);
			out.println(t);
		}
		void recur(int[] ar, int i) {
			if(i==ar.length) {
				int a=ar[0]*100+ar[1]*10+ar[2], b=a*ar[3], c=a*ar[4];
				if(b>=1000||c>=1000||!check(b)||!check(c)||!check(b+10*c))
					return;
				++t;
			} else {
				for(int j=0; j<digits.length; ++j) {
					ar[i]=digits[j];
					recur(ar, i+1);
				}
			}
		}
		boolean check(int n) {
			while(n>0) {
				int d=n%10;
				boolean validDigit=false;
				for(int i=0; i<digits.length; ++i) {
					if(digits[i]==d) {
						validDigit=true;
						break;
					}
				}
				if(!validDigit)
					return false;
				n/=10;
			}
			return true;
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