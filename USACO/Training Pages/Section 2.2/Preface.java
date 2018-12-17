package section_2_2;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: preface
*/
import java.io.*;
import java.util.*;

public class preface {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "preface";
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			char[] letters = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
			int[] cnt = new int[7];
			for(int i=1; i<=n; ++i) {
				int a=i%10;
				if(a<=3)
					cnt[0]+=a;
				else if(a==4) {
					++cnt[0];
					++cnt[1];
				} else if(a<=8) {
					cnt[0]+=a-5;
					++cnt[1];
				} else {
					++cnt[0];
					++cnt[2];
				}
				a=i/10%10;
				if(a<=3)
					cnt[2]+=a;
				else if(a==4) {
					++cnt[2];
					++cnt[3];
				} else if(a<=8) {
					cnt[2]+=a-5;
					++cnt[3];
				} else {
					++cnt[2];
					++cnt[4];
				}
				a=i/100%10;
				if(a<=3)
					cnt[4]+=a;
				else if(a==4) {
					++cnt[4];
					++cnt[5];
				} else if(a<=8) {
					cnt[4]+=a-5;
					++cnt[5];
				} else {
					++cnt[4];
					++cnt[6];
				}
				cnt[6]+=i/1000;
			}
			for(int i=0; i<7&&cnt[i]!=0; ++i)
				out.println(letters[i]+" "+cnt[i]);
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