import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		for(int tests=in.nextInt(); tests>0; --tests)
			new Solver();
		out.close();
	}
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), m=in.nextInt();
			int[] d = new int[n];
			boolean aa=true, aw=true;
			for(int i=0; i<n; ++i) {
				d[i]=in.nextInt();
				aa&=d[i]==1;
				aw&=d[i]==0;
			}
			int[][] a = new int[n][m];
			for(int i=0; i<n; ++i)
				for(int j=0; j<m; ++j)
					a[i][j]=in.nextInt();
			for(int i=0; i<n; ++i)
				for(int j=0; j<m; ++j)
					if(in.nextInt()==0)
						a[i][j]=Integer.MAX_VALUE;
			if(aa) {
				out.println("YES");
				out.println("1 0");
				out.println();
				return;
			}
			List<Pair> p = new ArrayList<Pair>();
			for(int i=0; i<m; ++i) {
				int rt=1;
				for(int j=0; j<n; ++j)
					if(d[j]==1)
						rt=Math.max(a[j][i], rt);
				p.add(new Pair(rt, i));
			}
			Collections.sort(p);
			int[] mt = new int[n];
			for(int i=0; i<m; ++i) {
				int pi=p.get(i).b, rt=p.get(i).a;
				boolean ok=true;
				for(int j=0; j<n; ++j) {
					if(d[j]==1)
						continue;
					mt[j]=Math.max(a[j][pi], mt[j]);
					ok&=mt[j]>rt;
				}
				if(ok&&rt<Integer.MAX_VALUE) {
					out.println("YES");
					out.println(rt+" "+(i+1));
					for(int j=0; j<=i; ++j)
						out.print((p.get(j).b+1)+" ");
					out.println();
					return;
				}
			}
			out.println("NO");
		}
		
		class Pair implements Comparable<Pair> {
			int a, b;
			Pair(int a, int b) {
				this.a=a;
				this.b=b;
			}
			public int compareTo(Pair o) {
				return a==o.a?b-o.b:a-o.a;
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
