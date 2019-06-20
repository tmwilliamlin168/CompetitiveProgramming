import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static long M=(long)1e9+7;
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(), ti=1; ti<=tests; ++ti) {
			int n=in.nextInt(), s=in.nextInt(), e=in.nextInt();
			int[] x = new int[n], y = new int[n], ya;
			List<Integer> p = new ArrayList<Integer>();
			for(int i=0; i<n; ++i) {
				x[i]=in.nextInt();
				y[i]=in.nextInt();
				p.add(i);
			}
			Collections.sort(p, new Comparator<Integer>() {
				public int compare(Integer a, Integer b) {
					return x[a]-x[b];
				}
			});
			ya = Arrays.copyOf(y, n+2);
			ya[n]=s;
			ya[n+1]=e;
			Arrays.sort(ya);
			s=Arrays.binarySearch(ya, s);
			e=Arrays.binarySearch(ya, e);
			for(int i=0; i<n; ++i)
				y[i]=Arrays.binarySearch(ya, y[i]);
			long[][][][][] dp = new long[n+1][n+2-s][s+1][n+2-e][e+1];
			dp[0][0][s][n+1-e][0]=1;
			for(int i=0; i<n; ++i) {
				int pi=p.get(i);
				for(int j1=0; j1<=n+1-s; ++j1) {
					for(int j2=0; j2<=s; ++j2) {
						for(int k1=0; k1<=n+1-e; ++k1) {
							for(int k2=0; k2<=e; ++k2) {
								if(dp[i][j1][j2][k1][k2]==0)
									continue;
								dp[i][j1][j2][k1][k2]%=M;
								//Up
								if(y[pi]>=k2)
									dp[i+1][j1][Math.min(y[pi], j2)][k1][k2]+=dp[i][j1][j2][k1][k2];
								//Down
								if(y[pi]<=k1+e)
									dp[i+1][Math.max(y[pi]-s, j1)][j2][k1][k2]+=dp[i][j1][j2][k1][k2];
								//Left
								if(y[pi]>s?y[pi]>j1+s:y[pi]<j2)
									dp[i+1][j1][j2][k1][k2]+=dp[i][j1][j2][k1][k2];
								//Right
								if(y[pi]>e)
									dp[i+1][j1][j2][Math.min(y[pi]-e, k1)][k2]+=dp[i][j1][j2][k1][k2];
								else
									dp[i+1][j1][j2][k1][Math.max(y[pi], k2)]+=dp[i][j1][j2][k1][k2];
							}
						}
					}
				}
			}
			long a1=1, a2=0;
			for(int i=0; i<n; ++i)
				a1=a1*4%M;
			for(int j1=0; j1<=n+1-s; ++j1)
				for(int j2=0; j2<=s; ++j2)
					for(int k1=0; k1<=n+1-e; ++k1)
						for(int k2=0; k2<=e; ++k2)
							a2+=dp[n][j1][j2][k1][k2];
			out.println("Case #"+ti+": "+(a1-a2%M+M)%M);
		}
		out.close();
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
