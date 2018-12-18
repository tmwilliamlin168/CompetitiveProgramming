import java.io.*;
import java.util.*;

public class Convention {
	static final boolean stdin = false;
	static final String filename = "convention";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			//input
			int n=in.nextInt(), m=in.nextInt(), c=in.nextInt();
			int[] t = new int[n];
			for(int i=0; i<n; ++i)
				t[i]=in.nextInt();
			Arrays.sort(t);
			//do the binary search
			int lb=0, rb=(int)1e9;
			while(lb<rb) {
				int mb=(lb+rb)/2, num=0;
				//greedily group cows
				for(int i=0; i<n; ++i, ++num) {
					int j=i;
					for(; j+1<n&&j-i+2<=c&&t[j+1]-t[i]<=mb; ++j);
					i=j;
				}
				if(num<=m)
					rb=mb;
				else
					lb=mb+1;
			}
			out.println(lb);
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