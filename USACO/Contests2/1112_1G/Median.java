import java.io.*;
import java.util.*;

public class Main {
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), x=in.nextInt(), rs=n;
			int[] a = new int[n];
			for(int i=0; i<n; ++i)
				a[i]=in.nextInt()>=x?1:-1;
			long ans=0;
			FenTree ft = new FenTree(2*n+1);
			ft.add(rs, 1);
			for(int i=0; i<n; ++i) {
				rs+=a[i];
				ans+=ft.sum(rs+1);
				ft.add(rs, 1);
			}
			out.println(ans);
		}
		
		class FenTree {
			int[] a;
			FenTree(int n) {
				a = new int[n+1];
			}
			void add(int i, int x) {
				for(++i; i<a.length; i+=i&-i)
					a[i]+=x;
			}
			int sum(int i) {
				int r=0;
				for(; i>0; i-=i&-i)
					r+=a[i];
				return r;
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		in = new Reader();
		out = new PrintWriter(System.out);
		new Solver();
		out.close();
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			br = new BufferedReader(new InputStreamReader(System.in));
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
