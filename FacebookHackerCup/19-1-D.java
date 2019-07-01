import java.io.*;
import java.util.*;

public class D {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			out.print("Case #"+_+": ");
			int n=in.nextInt(), h=in.nextInt(), v=in.nextInt();
			int[] x = re(n), y=re(n), a = new int[n], b = new int[n+1];
			if(h+v<n) {
				out.println(-1);
				continue;
			}
			Pair[] p = new Pair[n], q = new Pair[n];
			for(int i=0; i<n; ++i)
				p[i] = new Pair(x[i], y[i]);
			Arrays.sort(p);
			for(int i=0; i<n; ++i)
				q[i] = new Pair(p[i].b, i);
			Arrays.sort(q);
			for(int i=0; i<n; ++i)
				a[q[i].b]=i;
			for(int i=n-1; i>=0; --i)
				b[i]=Math.max(p[i].b, b[i+1]);
			int ans=(int)2e9;
			if(v>=n)
				ans=b[0];
			FenwickTree ft = new FenwickTree(n);
			for(int i=0; i<n; ++i) {
				ft.upd(a[i]);
				if(n-1-i<=v)
					ans=Math.min(p[i].a+Math.max(b[i+1], h>i?0:q[ft.gk(i-h)].a), ans);
			}
			out.println(ans);
		}
		out.close();
	}
	
	static int[] re(int n) {
		int[] x = new int[n];
		x[0]=in.nextInt();
		x[1]=in.nextInt();
		long a=in.nextInt(), b=in.nextInt(), c=in.nextInt(), d=in.nextInt();
		for(int i=2; i<n; ++i)
			x[i]=(int)((a*x[i-2]+b*x[i-1]+c)%d+1);
		return x;
	}
	
	static class Pair implements Comparable<Pair> {
		int a, b;
		Pair(int a, int b) {
			this.a=a;
			this.b=b;
		}
		public int compareTo(Pair o) {
			return a-o.a;
		}
	}
	
	static class FenwickTree {
		int n;
		int[] ft;
		FenwickTree(int n) {
			this.n=n;
			ft = new int[n+1];
		}
		void upd(int i) {
			for(++i; i<=n; i+=i&-i)
				++ft[i];
		}
		int gk(int x) {
			int k=0;
			for(int i=19; i>=0; --i) {
				if(k+(1<<i)<=n&&ft[k+(1<<i)]<=x) {
					k+=1<<i;
					x-=ft[k];
				}
			}
			return k;
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
