/*
ID: tmwilliamlin168
LANG: JAVA
TASK: charrec
*/
import java.io.*;
import java.util.*;

public class charrec {
	static final boolean stdin = false;
	static final String filename = "charrec";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		static final int INF = (int)1e9;
		
		Solver() throws IOException {
			char[][] ft = new char[540][];
			BufferedReader ftbr = new BufferedReader(new FileReader("font.in"));
			ftbr.readLine();
			for(int i=0; i<ft.length; ++i)
				ft[i]=ftbr.readLine().toCharArray();
			int n=in.nextInt();
			char[][] ss = new char[n][];
			int[][] ld = new int[n][540];
			for(int i=0; i<n; ++i) {
				ss[i]=in.next().toCharArray();
				for(int j=0; j<540; ++j)
					for(int k=0; k<20; ++k)
						ld[i][j]+=ss[i][k]!=ft[j][k]?1:0;
			}
			int[] dp = new int[n+1], pvw = new int[n+1];
			char[] pvc = new char[n+1];
			Arrays.fill(dp, INF);
			dp[0]=0;
			for(int i=19; i<=n; ++i) {
				for(int j=0; j<27; ++j) {
					for(int k=0; k<20; ++k) {
						if(dp[i-19]<INF) {
							int td=0;
							for(int l1=0, l2=i-19; l1<20; ++l1)
								if(l1!=k)
									td+=ld[l2++][j*20+l1];
							if(dp[i-19]+td<dp[i]) {
								dp[i]=dp[i-19]+td;
								pvw[i]=19;
								pvc[i]=j==0?' ':(char)(j-1+'a');
							}
						}
						if(i>=21&&dp[i-21]<INF) {
							int td=0;
							for(int l1=0, l2=i-21; l1<20; ++l1) {
								td+=ld[l2++][j*20+l1];
								if(l1==k)
									td+=ld[l2++][j*20+l1];
							}
							if(dp[i-21]+td<dp[i]) {
								dp[i]=dp[i-21]+td;
								pvw[i]=21;
								pvc[i]=j==0?' ':(char)(j-1+'a');
							}
						}
					}
					if(i>=20&&dp[i-20]<INF) {
						int td=0;
						for(int k=0; k<20; ++k)
							td+=ld[i-20+k][j*20+k];
						if(dp[i-20]+td<dp[i]) {
							dp[i]=dp[i-20]+td;
							pvw[i]=20;
							pvc[i]=j==0?' ':(char)(j-1+'a');
						}
					}
				}
			}
			List<Character> cl = new ArrayList<Character>();
			for(int i=n; i>0; i=i-pvw[i])
				cl.add(pvc[i]);
			for(int i=cl.size()-1; i>=0; --i)
				out.print(cl.get(i));
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