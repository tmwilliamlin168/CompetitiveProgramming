import java.io.*;
import java.util.*;
 
public class Main {
	static final Reader in = new Reader();
	
	public static void main(String[] args) {
		int n=in.nextInt();
		Pair[] p = new Pair[2*n];
		long[] a = new long[2];
		for(int i=0; i<2*n; ++i) {
			p[i] = new Pair(in.nextInt(), i);
			a[i&1]+=p[i].a;
		}
		a[0]=Math.min(a[1], a[0]);
		a[1]=0;
		Arrays.sort(p, new Comparator<Pair>() {
			public int compare(Pair a, Pair b) {
				return a.a==b.a?a.b-b.b:a.a-b.a;
			}
		});
		int[] q = new int[2*n];
		for(int i=0; i<n; ++i)
			a[1]+=p[i].a;
		for(int i=0; i<2*n; ++i)
			q[p[i].b]=i;
		for(int i=0; i<n; ++i) {
			long c=a[1];
			int j=n;
			while(j-(q[2*i]<j?1:0)-(q[2*i+1]<j?1:0)<n)
				c+=p[j++].a;
			for(int k=2*i; k<2*i+2; ++k)
				if(q[k]<j)
					c-=p[q[k]].a;
			a[0]=Math.min(c, a[0]);
		}
		System.out.println(a[0]);
	}
	
	static class Pair {
		int a, b;
		Pair(int a, int b) {
			this.a=a;
			this.b=b;
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
