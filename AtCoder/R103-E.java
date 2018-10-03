import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		char[] s=in.next().toCharArray();
		int n=s.length;
		if(s[0]=='0'||s[n-1]=='1')
			fk();
		for(int i=0; i<n-2-i; ++i)
			if(s[i]!=s[n-2-i])
				fk();
		for(int i=1, l=0; i<n; ++i) {
			if(s[i]=='0')
				continue;
			for(int j=i; j>l; --j)
				out.println(j+" "+(i+1));
			l=i;
		}
		out.println(n+" "+(n-1));
		out.close();
	}
	
	static void fk() {
		System.out.println(-1);
		System.exit(0);
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
