public class CheckPolygon {
	long c(long ax, long ay, long bx, long by) {
		return ax*by-ay*bx;
	}
	
	int o(long ax, long ay, long bx, long by, long cx, long cy) {
		long c=c(bx-ax, by-ay, cx-ax, cy-ay);
		return c==0?0:(c>0?1:-1);
	}
	
	boolean a(long ax, long ay, long bx, long by, long cx, long cy) {
		return cx>=Math.min(ax, bx)&&cx<=Math.max(ax, bx)&&cy>=Math.min(ay, by)&&cy<=Math.max(ay, by);
	}
	
	boolean i(long ax, long ay, long bx, long by, long cx, long cy, long dx, long dy) {
		int oa=o(cx, cy, dx, dy, ax, ay), ob=o(cx, cy, dx, dy, bx, by), oc=o(ax, ay, bx, by, cx, cy), od=o(ax, ay, bx, by, dx, dy);
		return oa!=ob&&oc!=od||oa==0&&ob==0&&(a(ax, ay, bx, by, cx, cy)||a(ax, ay, bx, by, dx, dy)||a(cx, cy, dx, dy, ax, ay)||a(cx, cy, dx, dy, bx, by));
	}
	
	public String check(int[] x, int[] y) {
		int n=x.length;
		long a=0;
		for(int i=0; i<n; ++i) {
			if(o(x[i], y[i], x[(i+1)%n], y[(i+1)%n], x[(i+2)%n], y[(i+2)%n])==0)
				return "Not simple";
			for(int j=i+2; j<n-(i==0?1:0); ++j)
				if(i(x[i], y[i], x[(i+1)%n], y[(i+1)%n], x[j], y[j], x[(j+1)%n], y[(j+1)%n]))
					return "Not simple";
			a+=(long)x[i]*y[(i+1)%n]-(long)x[(i+1)%n]*y[i];
		}
		a=Math.abs(a);
		return a/2+"."+(a%2==0?0:5);
	}
}
