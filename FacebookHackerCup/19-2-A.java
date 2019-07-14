import java.io.*;
import java.util.*;

public class A {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			int n=in.nextInt(), m=in.nextInt(), k=in.nextInt(), a=in.nextInt(), b=in.nextInt();
			int[] r = new int[k], c = new int[k];
			for(int i=0; i<k; ++i) {
				r[i]=in.nextInt();
				c[i]=in.nextInt();
			}
			out.println("Case #"+_+": "+(k>1&&(a+b)%2==(r[0]+c[0])%2&&(a+b)%2==(r[1]+c[1])%2?"Y":"N"));
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
