import java.util.*;

public class EllysTeleport {
	public int getMax(int n, int h0, int a, int b, int p, int q, int m) {
		long[] h = new long[n];
		h[0]=h0;
		Pair[] c = new Pair[n];
		c[0] = new Pair(h0, 0);
		for(int i=1; i<n; ++i) {
			h[i]=(h[i-1]*a+b)%m;
			c[i] = new Pair(h[i], i);
		}
		Arrays.sort(c);
		int[] f = new int[n];
		for(int i=0; i<n; ++i) {
			int lb=-1, rb=n-1;
			long nh=(h[i]*p+q)%m;
			while(lb<rb) {
				int mb=(lb+rb+1)/2;
				if(c[mb].a>nh)
					rb=mb-1;
				else
					lb=mb;
			}
			f[i]=lb==-1?-1:c[lb].b;
		}
		int ans=0;
		boolean[] vis = new boolean[n];
		for(int i=0; i<n; ++i) {
			Arrays.fill(vis, false);
			int j=i, ca=0;
			while(j!=-1&&!vis[j]) {
				vis[j]=true;
				++ca;
				j=f[j];
			}
			ans=Math.max(ca, ans);
		}
		return ans;
	}
	
	class Pair implements Comparable<Pair> {
		long a;
		int b;
		Pair(long a, int b) {
			this.a=a;
			this.b=b;
		}
		public int compareTo(Pair o) {
			return a==o.a?b-o.b:Long.compare(a, o.a);
		}
	}
}
