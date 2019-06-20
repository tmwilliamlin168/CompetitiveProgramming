public class HungryCowsEasy {
	public int[] findFood(int[] a, int[] b) {
		int n=a.length;
		int[] c = new int[n];
		for(int i=0; i<n; ++i) {
			for(int j=1; j<b.length; ++j) {
				int d=Math.abs(b[j]-a[i]), e=Math.abs(b[c[i]]-a[i]);
				if(d<e||d==e&&b[j]<b[c[i]])
					c[i]=j;
			}
		}
		return c;
	}
}
