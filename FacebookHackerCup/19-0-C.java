import java.io.*;
import java.util.*;

public class C {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			char[] s=in.next().toCharArray();
			out.println("Case #"+_+": "+(eval(s, 0, s.length, 0)==eval(s, 0, s.length, 1)?0:1));
		}
		out.close();
	}
	
	static int eval(char[] s, int l, int r, int x) {
		if(s[l]=='x')
			return x;
		if(s[l]=='X')
			return x^1;
		if(s[l]!='(')
			return s[l]&1;
		for(int i=l+1, c=0; ; ++i) {
			if(s[i]=='(')
				++c;
			if(s[i]==')')
				--c;
			if(c<1) {
				int a=eval(s, l+1, i+1, x), b=eval(s, i+2, r-1, x);
				return s[i+1]=='&'?a&b:(s[i+1]=='|'?a|b:a^b);
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
