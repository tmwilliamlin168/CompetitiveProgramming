public class EllysSki {
	public int getMax(int[] h) {
		int n=h.length, ans=1;
		for(int i=0; i<n; ++i) {
			for(int j=i-1; j>=0&&h[j]<=h[j+1]; --j)
				ans=Math.max(i-j+1, ans);
			for(int j=i+1; j<n&&h[j]<=h[j-1]; ++j)
				ans=Math.max(j-i+1, ans);
		}
		return ans;
	}
}
