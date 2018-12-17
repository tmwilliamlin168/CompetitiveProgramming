package section_1_2;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: milk2
*/
import java.io.*;
import java.util.*;

public class milk2 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "milk2";
	
	static class Solver {
		Solver() {
			int N=in.nextInt();
			int[] starts = new int[1_000_000];
			for(int i=0; i<N; ++i) {
				int start=in.nextInt(), end=in.nextInt();
				++starts[start];
				if(end!=starts.length)
					--starts[end];
			}
			int active=0, continued=0, longestMilk=0, longestIdle=0;
			boolean lastWasMilk=false;
			for(int i=0; i<starts.length; ++i) {
				active+=starts[i];
				if(!(lastWasMilk&&active>0||!lastWasMilk&&active==0)) {
					if(lastWasMilk)
						longestMilk=Math.max(continued, longestMilk);
					else if(longestMilk!=0)
						longestIdle=Math.max(continued, longestIdle);
					lastWasMilk=!lastWasMilk;
					continued=0;
				}
				++continued;
			}
			if(lastWasMilk)
				longestMilk=Math.max(continued, longestMilk);
			out.println(longestMilk+" "+longestIdle);
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