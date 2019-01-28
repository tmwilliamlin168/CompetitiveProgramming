import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static int[][] a;
	static int[] b, c;
	
	static void s(int i, int j) {
		++a[i][b[i]^j];
		b[i]^=1;
	}
	
	static void t(int d1, int d2, int e1, int e2) {
		if(e1!=-1)
			s(d1, e1);
		if(e2!=-1)
			s(d2, e2);
		++c[d1+1];
		--c[d2];
	}
	
	static void fk() {
		System.out.println("LOVE IS ALL WE NEED FOR CHRISTMAS");
		System.exit(0);
	}
	
	public static void main(String[] args) {
		int n=in.nextInt(), m=in.nextInt();
		a = new int[n][2];
		b = new int[n];
		c = new int[n+1];
		while(m-->0) {
			char c1=in.next().charAt(0);
			int d1=in.nextInt()-1;
			char c2=in.next().charAt(0);
			int d2=in.nextInt()-1;
			if(d1>d2||c2=='L'||c2=='R') {
				d1^=d2^(d2=d1);
				c1^=c2^(c2=c1);
			}
			if(c1=='T'||c1=='B') {
				if(d1==d2&&c2==c1)
					fk();
				if(d1==d2)
					t(d1-1, d1+1, -1, -1);
				else
					t(d1, d2, c1=='T'?0:1, c2=='T'?1:0);
			} else {
				if(c1==c2)
					fk();
				if(c1=='R'&&c2!='L')
					t(d2, n, c2=='T'?0:1, -1);
				else if(c1=='L'&&c2!='R')
					t(-1, d2, -1, c2=='T'?1:0);
				else
					++c[0];
			}
		}
		for(int i=0; i<n; ++i)
			c[i+1]+=c[i];
		char[] s = new char[n];
		for(int i=0; i<n; ++i) {
			int f=(a[i][0]>0?1:0)+(a[i][1]>0?1:0)+(c[i]>0?1:0);
			if(f>1)
				fk();
			if(a[i][0]>0)
				s[i]='\\';
			else if(a[i][1]>0)
				s[i]='/';
			else
				s[i]='.';
		}
		System.out.println(s);
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
