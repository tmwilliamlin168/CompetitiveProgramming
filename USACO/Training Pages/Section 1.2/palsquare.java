package section_1_2;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: palsquare
*/
import java.io.*;
import java.util.*;

public class palsquare {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "palsquare";
	
	static class Solver {
		Solver() {
			int B=in.nextInt();
			for(int i=1; i<=300; ++i) {
				String strI=str(i, B), strI2=str(i*i, B);
				boolean isPalindrome=true;
				for(int j=0; j<strI2.length()/2; ++j) {
					if(strI2.charAt(j)!=strI2.charAt(strI2.length()-1-j)) {
						isPalindrome=false;
						break;
					}
				}
				if(isPalindrome)
					out.println(strI+" "+strI2);
			}
		}
		
		static String str(int n, int b) {
			String res="";
			while(n>0) {
				int rem=n%b;
				if(rem<10)
					res=rem+res;
				else
					res=(char)(rem-10+'A')+res;
				n/=b;
			}
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