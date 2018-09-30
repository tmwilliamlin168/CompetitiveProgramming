import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(); tests>0; --tests)
			new Solver();
		out.close();
	}
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), vs=0;
			int[] v = new int[n];
			Pair[] pv = new Pair[n];
			for(int i=0; i<n; ++i) {
				v[i]=in.nextInt();
				pv[i]=new Pair(v[i], i);
				vs+=pv[i].a;
			}
			Arrays.sort(pv);
			boolean[][] dp = new boolean[n][(n-1)*500+1];
			dp[0][0]=true;
			for(int i=0; i<n-1; ++i) {
				for(int j=0; j<=i*500; ++j) {
					dp[i+1][j]|=dp[i][j];
					dp[i+1][j+pv[i].a]|=dp[i][j];
				}
			}
			List<Integer> p1 = new ArrayList<Integer>(), p2 = new ArrayList<Integer>();
			for(int i=(n-1)*500; i>=0; --i) {
				if(i>vs-pv[n-1].a-i||!dp[n-1][i])
					continue;
				for(int j=n-2; j>=0; --j) {
					if(!dp[j][i]) {
						p1.add(pv[j].b);
						i-=pv[j].a;
					} else
						p2.add(pv[j].b);
				}
				break;
			}
			p1.add(pv[n-1].b);
			int s1=0, s2=0;
			while(!p1.isEmpty()||!p2.isEmpty()) {
				if(s1<=s2) {
					s1+=v[p1.get(0)];
					out.print((p1.remove(0)+1)+" ");
				} else {
					s2+=v[p2.get(0)];
					out.print((p2.remove(0)+1)+" ");
				}
			}
			out.println();
		}
		
		class Pair implements Comparable<Pair> {
			int a, b;
			Pair(int a, int b) {
				this.a=a;
				this.b=b;
			}
			public int compareTo(Pair o) {
				return a==o.a?b-o.b:a-o.a;
			}
		}
	}
	
	static class Reader {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
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
