import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	
	public static void main(String[] args) {
		int n=in.nextInt(), x=in.nextInt();
		int[] a = new int[n];
		for(int i=0; i<n; ++i)
			a[i]=in.nextInt();
		Arrays.sort(a);
		int ans=0;
		for(int i=0; i<n; ++i) {
			if(a[i]<=x){
				x-=a[i];
				++ans;
			}
		}
		System.out.println(x>0?Math.min(ans, n-1):ans);
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
