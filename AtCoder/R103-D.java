import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	static final long A=2147483647;
	
	public static void main(String[] args) {
		int n=in.nextInt();
		long[] x = new long[n], y = new long[n];
		for(int i=0; i<n; ++i) {
			x[i]=in.nextInt()+A;
			y[i]=in.nextInt()+A;
			if(i>0&&(x[i]+y[i])%2!=(x[i-1]+y[i-1])%2) {
				System.out.println(-1);
				return;
			}
		}
		boolean al=false;
		if((x[0]+y[0])%2==0) {
			al=true;
			for(int i=0; i<n; ++i)
				++x[i];
		}
		out.println((31+(al?1:0)));
		for(int i=0; i<31; ++i)
			out.print((1L<<i)+" ");
		if(al)
			out.print(1);
		out.println();
		for(int i=0; i<n; ++i) {
			for(int j=0; j<31; ++j) {
				if(x[i]%(1L<<(j+1))==0) {
					y[i]-=1L<<j;
					if(j>29!=(x[i]%(1L<<(j+2))==y[i]%(1L<<(j+2)))) {
						out.print('R');
						x[i]-=1L<<(j+1);
					} else
						out.print('L');
				} else {
					x[i]-=1L<<j;
					if(j>29!=(y[i]%(1L<<(j+2))==x[i]%(1L<<(j+2)))) {
						out.print('U');
						y[i]-=1L<<(j+1);
					} else
						out.print('D');
				}
			}
			if(al)
				out.print('L');
			out.println();
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
