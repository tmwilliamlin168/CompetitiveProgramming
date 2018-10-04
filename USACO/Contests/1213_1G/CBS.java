import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "cbs";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int k=in.nextInt(), n=in.nextInt(), ans=0;
			int[][] ps = new int[n+1][k], last = new int[2*n+2][k];
			Arrays.fill(ps[0], n+1);
			for(int i=0; i<k; ++i) {
				char[] s=in.next().toCharArray();
				for(int j=0; j<n; ++j)
					ps[j+1][i]=ps[j][i]+(s[j]=='('?1:-1);
			}
			Map<List<Integer>, Pair> map = new HashMap<List<Integer>, Pair>();
			for(int i=1; i<=n; ++i) {
				int lower=0;
				List<Integer> l = new ArrayList<Integer>();
				for(int j=0; j<k; ++j) {
					l.add(ps[i][j]);
					lower = Math.max(last[ps[i][j]-1][j], lower);
					last[ps[i][j]][j]=i;
				}
				Pair p=map.get(l);
				if(p!=null&&p.a==lower)
					ans+=p.b++;
				else
					map.put(l, new Pair(lower, 1));
			}
			out.println(ans);
		}
		
		class Pair {
			int a, b;
			Pair(int a, int b) {
				this.a=a;
				this.b=b;
			}
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
