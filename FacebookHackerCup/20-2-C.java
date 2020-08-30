import java.io.*;
import java.util.*;

public class C {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			out.print("Case #"+_+": ");
			new Solver();
		}
		out.close();
	}
	
	static class Solver {
		static final int M=(int)1e9+7;
		
		int[] ra(int n, int k, int m) {
			int[] x = new int[n];
			for(int i=0; i<k; ++i)
				x[i]=in.nextInt();
			long a=in.nextLong(), b=in.nextLong(), c=in.nextLong();
			for(int i=k; i<n; ++i)
				x[i]=(int)((a*x[i-2]+b*x[i-1]+c)%m);
			return x;
		}
		
		Solver() {
			int n=in.nextInt(), m=in.nextInt(), q=in.nextInt(), k=in.nextInt();
			int[] x=ra(n, k, m), y=ra(n, k, m), qx=ra(q, k, n*m+n), qw=ra(q, k, (int)1e9);
			Multiset[][] s = new Multiset[n][2];
			Multiset s2 = new Multiset(), sm = new Multiset();
			int[] w = new int[n*m+n], t = new int[n*m+n];
			Arrays.fill(w, 1);
			long ts=n*m+n, tsm=0;
			for(int i=0; i<n; ++i) {
				s[i][0] = new Multiset();
				s[i][1] = new Multiset();
				int j=x[i];
				for(; j!=y[i]; j=(j+1)%m)
					s[i][0].add(1);
				s[i][1].add(1);
				t[i*m+j]=1;
				j=(j+1)%m;
				for(; j!=x[i]; j=(j+1)%m) {
					s[i][1].add(1);
					t[i*m+j]=1;
				}
				int a=s[i][0].max()>s[i][1].max()?0:1;
				sm.add(s[i][a^1].max());
				tsm+=Math.max(s[i][0].max(), s[i][1].max());
				s2.add(1);
			}
			long ans=1;
			for(int qi=0; qi<q; ++qi) {
				ts-=w[qx[qi]];
				ts+=qw[qi];
				if(qx[qi]<n*m) {
					int ci=qx[qi]/m, a=s[ci][0].max()>s[ci][1].max()?0:1;
					sm.remove(s[ci][a^1].max());
					tsm-=Math.max(s[ci][0].max(), s[ci][1].max());
					s[ci][t[qx[qi]]].remove(w[qx[qi]]);
					w[qx[qi]]=qw[qi];
					s[ci][t[qx[qi]]].add(qw[qi]);
					a=s[ci][0].max()>s[ci][1].max()?0:1;
					sm.add(s[ci][a^1].max());
					tsm+=Math.max(s[ci][0].max(), s[ci][1].max());
				} else {
					s2.remove(w[qx[qi]]);
					w[qx[qi]]=qw[qi];
					s2.add(qw[qi]);
				}
				ans=Math.min(ts-tsm-s2.max(), ts-tsm-sm.max())%M*ans%M;
			}
			out.println(ans);
		}
		
		class Multiset {
			TreeMap<Integer, Integer> map = new TreeMap<Integer, Integer>();
			long sum;
			void add(int x) {
				sum+=x;
				map.put(x, map.getOrDefault(x, 0)+1);
			}
			void remove(int x) {
				sum-=x;
				map.put(x, map.get(x)-1);
				if(map.get(x)<1)
					map.remove(x);
			}
			int max() {
				return map.isEmpty()?0:map.lastKey();
			}
		}
	}
	
	static class Reader {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		String next() {
			while(st==null||!st.hasMoreTokens()) {
				try {
					st=new StringTokenizer(in.readLine());
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
