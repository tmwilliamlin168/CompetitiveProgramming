import java.io.*;
import java.util.*;

public class Main {
	static final boolean stdin = true;
	static final String filename = "friendcross";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), k=in.nextInt();
			int[] a = new int[n], b = new int[n];
			for(int i=0; i<n; ++i)
				a[in.nextInt()-1]=n-1-i;
			for(int i=0; i<n; ++i)
				b[in.nextInt()-1]=i;
			List<Query>[] queries = new List[n];
			for(int i=0; i<n; ++i)
				queries[i] = new ArrayList<Query>();
			for(int i=0; i<n; ++i)
				queries[i].add(new Query(a[i], b[i], 1, 0));
			for(int i=0; i<n; ++i) {
				if(i-k-1>=0)
					queries[i-k-1].add(new Query(a[i], b[i], 1, 1));
				if(i+k<n-1) {
					queries[i+k].add(new Query(a[i], b[i], -1, 1));
					queries[n-1].add(new Query(a[i], b[i], 1, 1));
				}
			}
			List<Integer>[] ftp1 = new List[n+1];
			for(int i=1; i<=n; ++i)
				ftp1[i] = new ArrayList<Integer>();
			for(int i=0; i<n; ++i) {
				for(Query query : queries[i]) {
					if(query.t==1)
						continue;
					for(int j=query.x+1; j<=n; j+=j&-j)
						ftp1[j].add(query.y);
				}
			}
			int[][] ftp2 = new int[n+1][];
			for(int i=1; i<=n; ++i) {
				ftp2[i] = new int[ftp1[i].size()];
				for(int j=0; j<ftp2[i].length; ++j)
					ftp2[i][j]=ftp1[i].get(j);
				Arrays.sort(ftp2[i]);
			}
			int[][] ft = new int[n+1][];
			for(int i=1; i<=n; ++i)
				ft[i] = new int[ftp2[i].length+1];
			long t=0;
			for(int i=0; i<n; ++i) {
				for(Query query : queries[i]) {
					if(query.t==1) {
						for(int j1=query.x; j1>0; j1-=j1&-j1) {
							int j2=Arrays.binarySearch(ftp2[j1], query.y);
							if(j2<0)
								j2=-j2-1;
							for(; j2>0; j2-=j2&-j2)
								t+=ft[j1][j2]*query.w;
						}
					} else
						for(int j1=query.x+1; j1<=n; j1+=j1&-j1)
							for(int j2=Arrays.binarySearch(ftp2[j1], query.y)+1; j2<ft[j1].length; j2+=j2&-j2)
								ft[j1][j2]+=query.w;
				}
			}
			out.println(t);
		}
		
		class Query {
			int x, y, w, t;
			Query(int x, int y, int w, int t) {
				this.x=x;
				this.y=y;
				this.w=w;
				this.t=t;
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
		new Solver();
		out.close();
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			br = new BufferedReader(new InputStreamReader(System.in));
		}
		Reader(String filename) throws Exception {
			br = new BufferedReader(new FileReader(filename));
		}
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
