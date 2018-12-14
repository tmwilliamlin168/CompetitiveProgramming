import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "lifeguards";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), k=in.nextInt();
			Pair[] ps1 = new Pair[n];
			for(int i=0; i<n; ++i)
				ps1[i]=new Pair(in.nextInt(), in.nextInt()-1);
			Arrays.sort(ps1, new Comparator<Pair>() {
				public int compare(Pair a, Pair b) {
					return a.a-b.a;
				}
			});
			List<Pair> ps2 = new ArrayList<Pair>();
			for(int i=0; i<n; ++i) {
				if(i>0&&ps1[i].b<=ps2.get(ps2.size()-1).b)
					--k;
				else
					ps2.add(ps1[i]);
			}
			k=Math.max(k, 0);
			int[][] dp1 = new int[ps2.size()+1][k+1];
			Arrays.fill(dp1[0], (int)-1e9);
			dp1[0][0]=0;
			int[] dp2 = Arrays.copyOf(dp1[0], k+1);
			for(int i1=1, i2=0; i1<=ps2.size(); ++i1) {
				while(i2+1<i1&&ps2.get(i2).b<ps2.get(i1-1).a) {
					++i2;
					for(int j=0; j<=k; ++j)
						dp2[j]=Math.max(dp1[i2][j], dp2[j]);
				}
				for(int j=k; j>=0; --j) {
					dp1[i1][j]=Math.max(j>=k?(int)-1e9:dp1[i1][j+1], j>0?dp1[i1-1][j-1]:(int)-1e9);
					dp1[i1][j]=Math.max(dp2[Math.max(j-(i1-i2-1), 0)]+ps2.get(i1-1).b-ps2.get(i1-1).a+1, dp1[i1][j]);
					if(i2+1<i1)
						dp1[i1][j]=Math.max(dp1[i2+1][Math.max(j-(i1-i2-2), 0)]+ps2.get(i1-1).b-ps2.get(i2).b, dp1[i1][j]);
				}
			}
			out.println(dp1[ps2.size()][k]);
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
