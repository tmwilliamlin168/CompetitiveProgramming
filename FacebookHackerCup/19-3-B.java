import java.io.*;
import java.util.*;

public class B {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);

	public static void main(String[] args) {
		int t=in.nextInt();
		for(int _=1; _<=t; ++_) {
			int n=in.nextInt();
			long ans=1, g=0;
			Map<Integer, Integer> low = new HashMap<Integer, Integer>(), up = new HashMap<Integer, Integer>();
			for(int i=0; i<n; ++i) {
				char o=in.next().charAt(0);
				int vi=in.nextInt(), ri=in.nextInt();
				Map<Integer, Integer> v=factorize(vi), r=factorize(ri);
				if(ans<0)
					continue;
				if(o=='G') {
					for(Map.Entry<Integer, Integer> e : r.entrySet())
						if(e.getValue()>v.getOrDefault(e.getKey(), 0))
							ans=-1;
					for(Map.Entry<Integer, Integer> e : v.entrySet()) {
						int p=e.getKey(), a=e.getValue(), b=r.getOrDefault(p, 0);
						low.put(p, Math.max(low.getOrDefault(p, 0), b));
						if(a>b)
							up.put(p, Math.min(up.getOrDefault(p, 99), b));
						if(low.get(p)>up.getOrDefault(p, 99))
							ans=-1;
					}
				} else {
					g=gcd(g, ri);
					for(Map.Entry<Integer, Integer> e : v.entrySet())
						if(e.getValue()>r.getOrDefault(e.getKey(), 0))
							ans=-1;
					for(Map.Entry<Integer, Integer> e : r.entrySet()) {
						int p=e.getKey(), a=v.getOrDefault(p, 0), b=e.getValue();
						if(a<b)
							low.put(p, Math.max(low.getOrDefault(p, 0), b));
						if(low.getOrDefault(p, 0)>up.getOrDefault(p, 99))
							ans=-1;
					}
				}
			}
			for(Map.Entry<Integer, Integer> e : low.entrySet()) {
				if(ans<0)
					continue;
				int i=e.getValue();
				while(ans<=1e9&&i-->0)
					ans=ans*e.getKey();
				if(ans>1e9)
					ans=-1;
			}
			if(ans>0&&g%ans>0)
				ans=-1;
			out.println("Case #"+_+": "+ans);
		}
		out.close();
	}
	
	static long gcd(long a, long b) {
		return a==0?b:gcd(b%a, a);
	}
	
	static Map<Integer, Integer> factorize(int x) {
		Map<Integer, Integer> a = new HashMap<Integer, Integer>();
		for(int i=2; i*i<=x; ++i) {
			while(x%i==0) {
				a.put(i, a.getOrDefault(i, 0)+1);
				x/=i;
			}
		}
		if(x>1)
			a.put(x, 1);
		return a;
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
