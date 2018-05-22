package section_1_1;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: friday
*/
import java.io.*;
import java.util.*;

public class friday {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "friday";
	
	static class Solver {
		Solver() {
			/*
			 * Saturday=0
			 * Sunday=1
			 * Monday=2
			 * Tuesday=3
			 * Wednesday=4
			 * Thursday=5
			 * Friday=6
			 */
			//First 13th is Saturday
			
			int N=in.nextInt(), curDay=-31;
			int[] daysInMonth = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
			int[] cnt = new int[7];
			for(int i=1900; i<1900+N; ++i) {
				for(int j=0; j<12; ++j) {
					curDay=(curDay+daysInMonth[j])%7;
					if(j==2&&(i%400==0||(i%100!=0&&i%4==0)))
						curDay=(++curDay)%7;
					++cnt[curDay];
				}
			}
			for(int i=0; i<7; ++i)
				out.print((i==0?"":" ")+cnt[i]);
			out.println();
		}
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
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