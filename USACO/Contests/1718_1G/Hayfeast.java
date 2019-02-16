import java.io.*;
import java.util.*;

public class Main {
	static boolean stdio=false;
	static Reader in = new Reader();
	static PrintWriter out;
	
	public static void main(String[] args) {
		if(stdio)
			out = new PrintWriter(System.out);
		else {
			try {
				out = new PrintWriter("hayfeast.out");
			} catch (Exception e) {}
		}
		int n=in.nextInt(), qh=0, qt=0;
		long m=in.nextLong(), min=Long.MAX_VALUE;
		int[] f = new int[n], s = new int[n], qu = new int[n];
		for(int i=0; i<n; ++i) {
			f[i]=in.nextInt();
			s[i]=in.nextInt();
		}
		int i1=0, i2=0;
		long sum=0;
		while(true) {
			while(i2<n&&sum<m) {
				while(qt>qh&&s[qu[qt-1]]<=s[i2])
					--qt;
				qu[qt++]=i2;
				sum+=f[i2];
				++i2;
			}
			if(sum<m&&i2>=n)
				break;
			min=Math.min(s[qu[qh]], min);
			sum-=f[i1];
			if(qu[qh]==i1)
				++qh;
			++i1;
		}
		out.println(min);
		out.close();
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			if(stdio)
				br = new BufferedReader(new InputStreamReader(System.in));
			else {
				try {
					br = new BufferedReader(new FileReader("hayfeast.in"));
				} catch (Exception e) {}
			}
		}
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
