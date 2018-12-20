import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final long M=(long)1e9+7;
	
	public static void main(String[] args) {
		int n=in.nextInt(), k=in.nextInt(), m=in.nextInt();
		boolean[] a = new boolean[n];
		List<Integer> b = new ArrayList<Integer>();
		b.add(-1);
		for(int i=0; i<n; ++i) {
			a[i]=in.nextInt()>=m;
			if(!a[i])
				b.add(i);
		}
		b.add(n);
		long[][] c = new long[n+3][k+3];
		c[0][0]=1;
		for(int i=1; i<n+3; ++i) {
			c[i]=Arrays.copyOf(c[i-1], k+3);
			for(int j=1; j<k+3; ++j)
				c[i][j]=(c[i][j]+c[i-1][j-1])%M;
		}
		long a1=0;
		for(int i=1; i<b.size(); ++i) {
			a1+=c[b.get(i)-b.get(i-1)+1][k+2];
			for(int j=i; j<b.size()-1; ++j) {
				int n1=j-i+1, l1=b.get(j)-b.get(i)+1-n1, l2=b.get(j+1)-b.get(i-1)-1-n1, d=Math.min(b.get(j+1)-b.get(j), b.get(i)-b.get(i-1));
				for(int l=0; l<=Math.min(n1, k/2); ++l)
					a1+=(c[l2+2][k-l+2]-c[l2-d+2][k-l+2]-c[l1+d][k-l+2]+c[l1][k-l+2]+2*M)*c[n1][l]%M;
			}
		}
		System.out.println(a1%M);
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
