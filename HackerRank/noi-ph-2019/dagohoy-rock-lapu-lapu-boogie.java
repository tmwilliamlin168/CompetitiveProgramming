import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final int M=(int)1e9+7;
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(); tests>0; --tests) {
			long n=in.nextLong(), ans=0;
			int m=in.nextInt(), l=(int)Math.min(n, 4);
			char[][] s = new char[m][];
			for(int i=0; i<m; ++i) {
				in.nextInt();
				s[i]=in.next().toCharArray();
			}
			long[] v = new long[1<<l];
			for(int i=0; i<1<<l; ++i) {
				v[i]=1;
				for(int j=0; j<m&&v[i]>0; ++j) {
					for(int k=0; k<=l-s[j].length&&v[i]>0; ++k) {
						v[i]=0;
						for(int o=0; o<s[j].length&&v[i]<1; ++o)
							v[i]=((i>>o+k)%2==0)==(s[j][o]=='D')?0:1;
					}
				}
			}
			long[][] b = new long[1<<l][1<<l];
			for(int i=0; i<1<<l; ++i) {
				for(int j=i/2; j<1<<l; j+=1<<l-1) {
					b[j][i]=1;
					for(int k=0; k<m&&b[j][i]>0; ++k) {
						b[j][i]=0;
						for(int o=0; o<s[k].length&&b[j][i]<1; ++o)
							b[j][i]=((j>>l-s[k].length+o)%2==0)==(s[k][o]=='D')?0:1;
					}
				}
			}
			n-=l;
			while(n>0) {
				if(n%2==1) {
					long[] nv = new long[1<<l];
					for(int i=0; i<1<<l; ++i)
						for(int j=0; j<1<<l; ++j)
							nv[i]=(nv[i]+b[i][j]*v[j])%M;
					v=nv;
				}
				long[][] nb = new long[1<<l][1<<l];
				for(int i=0; i<1<<l; ++i)
					for(int k=0; k<1<<l; ++k)
						for(int j=0; j<1<<l; ++j)
							nb[i][j]=(nb[i][j]+b[i][k]*b[k][j])%M;
				b=nb;
				n/=2;
			}
			for(int i=0; i<1<<l; ++i)
				ans+=v[i];
			System.out.println(ans%M);
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
		long nextLong() {
			return Long.parseLong(next());
		}
	}
}
