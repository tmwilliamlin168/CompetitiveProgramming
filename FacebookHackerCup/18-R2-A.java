import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(), ti=1; ti<=tests; ++ti) {
			int n=in.nextInt(), k=in.nextInt();
			out.print("Case #"+ti+": ");
			if(n>2&&k>2) {
				int m=Math.min(n-1, k-1), s=-k;
				for(int i=0; i<m; ++i)
					s+=k-1-i;
				out.print(s+"\n"+(m+1)+"\n");
				for(int i=0; i<m; ++i)
					out.println((i+1)+" "+(i==m-1?n:i+2)+" "+(k-1-i));
			} else
				out.print("0\n1\n");
			out.println("1 "+n+" "+k);
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
