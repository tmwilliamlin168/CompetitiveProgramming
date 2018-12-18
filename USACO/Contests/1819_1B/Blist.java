import java.io.*;
import java.util.*;

public class Blist {
	static final boolean stdin = false;
	static final String filename = "blist";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			//input
			int n=in.nextInt(), ans=0;
			int[] a = new int[1001];
			for(int i=0; i<n; ++i) {
				int si=in.nextInt(), ti=in.nextInt(), bi=in.nextInt();
				//add bi to all moments of time [si, ti]
				for(int j=si; j<=ti; ++j)
					a[j]+=bi;
			}
			//answer is maximum of all moments
			for(int i=1; i<=1000; ++i)
				ans=Math.max(a[i], ans);
			//output
			out.println(ans);
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