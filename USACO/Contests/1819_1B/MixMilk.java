import java.io.*;
import java.util.*;

public class MixMilk {
	static final boolean stdin = false;
	static final String filename = "mixmilk";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			//input
			int[] c = new int[3], m = new int[3];
			for(int i=0; i<3; ++i) {
				c[i]=in.nextInt();
				m[i]=in.nextInt();
			}
			//Do the 100 pours
			for(int it=0; it<100; ++it) {
				int from=it%3, to=(it+1)%3;
				int amount=m[from];
				//Make sure milk doesn't overflow
				amount=Math.min(c[to]-m[to], amount);
				m[from]-=amount;
				m[to]+=amount;
			}
			//output
			for(int i=0; i<3; ++i)
				out.println(m[i]);
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