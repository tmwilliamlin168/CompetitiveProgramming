import java.io.*;
import java.util.*;

public class B {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final int M=(int)1e9+7;

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			int n=in.nextInt(), k=in.nextInt();
			char[] s=in.next().toCharArray();
			int[] q = new int[n+1];
			q[0]=1;
			for(int i=0; i<n; ++i)
				q[i+1]=q[i]*2%M;
			int ans=0;
			for(int i=n, mx=-n; i>0; --i) {
				if(s[i-1]=='A')
					continue;
				mx=Math.max(-i, mx);
				if((mx+2)-(-(i-1))<=k)
					mx+=2;
				else
					ans=(ans+q[i])%M;
			}
			out.println("Case #"+_+": "+ans);
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
