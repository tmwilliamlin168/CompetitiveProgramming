import java.io.*;
import java.util.*;

public class Cowpatibility {
	static final boolean stdin = false;
	static final String filename = "cowpatibility";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		static final long base=(long)1e6+3;
		
		Solver() {
			long n=in.nextInt(), ans=0;
			Map<Long, Integer>[] cnt = new Map[6];
			for(int i=1; i<=5; ++i)
				cnt[i] = new HashMap<Long, Integer>();
			for(int i=0; i<n; ++i) {
				int[] b = new int[5];
				for(int j=0; j<5; ++j)
					b[j]=in.nextInt();
				Arrays.sort(b);
				//Iterate over all subsets
				for(int j=1; j<32; ++j) {
					int c=Integer.bitCount(j);
					//Pray to cow gods for no collisions
					long hash=0;
					for(int k=0; k<5; ++k)
						if((j>>k&1)>0)
							hash=hash*base+b[k];
					//add for odd-sized subsets and subtract for even-sized
					ans+=cnt[c].getOrDefault(hash, 0)*(c%2==1?1:-1);
					cnt[c].put(hash, cnt[c].getOrDefault(hash, 0)+1);
				}
			}
			//we found number of compatible, now take the complement
			out.println(n*(n-1)/2-ans);
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