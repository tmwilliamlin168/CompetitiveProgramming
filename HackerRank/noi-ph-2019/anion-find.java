import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		int n=in.nextInt(), m=in.nextInt();
		List<Pair>[] l = new List[200001];
		for(int i=1; i<=200000; ++i)
			l[i] = new ArrayList<Pair>();
		for(int i=0; i<n; ++i)
			for(int j=0; j<m; ++j) {
				int a=in.nextInt();
				if(a<0)
					l[-a].add(new Pair(i, j));
			}
		for(int i=1; i<=200000; ++i)
			Collections.reverse(l[i]);
		int q=in.nextInt();
		while(q-->0) {
			int a=in.nextInt();
			Pair p=l[a].get(l[a].size()-1);
			out.println(p.a+" "+p.b);
			l[a].remove(l[a].size()-1);
		}
		out.close();
	}

	static class Pair {
		int a, b;
		Pair(int a, int b) {
			this.a=a;
			this.b=b;
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
