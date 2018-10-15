import java.io.*;
import java.util.*;
 
public class Main {
	static final Reader in = new Reader();
	
	public static void main(String[] args) {
		int n=in.nextInt(), m=in.nextInt();
		char[] s=in.next().toCharArray(), t=in.next().toCharArray();
		int g=gcd(n, m);
		for(int i1=0, i2=0; i1<s.length; i1+=n/g, i2+=m/g) {
			if(s[i1]!=t[i2]) {
				System.out.println(-1);
				return;
			}
		}
		System.out.println((long)n*m/g);
	}
	
	static int gcd(int a, int b) {
		while((a%=b)>0&&(b%=a)>0);
		return a^b;
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
