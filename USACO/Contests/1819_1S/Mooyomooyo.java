import java.io.*;
import java.util.*;

public class Mooyomooyo {
	static final boolean stdin = false;
	static final String filename = "mooyomooyo";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		int n;
		char[][] g;
		boolean[][] vis;
		
		Solver() {
			//input
			n=in.nextInt();
			int k=in.nextInt();
			g = new char[n][];
			for(int i=0; i<n; ++i)
				g[i]=in.next().toCharArray();
			//simulate the process
			while(true) {
				boolean changed=false;
				//find components to erase
				vis = new boolean[n][10];
				for(int i=0; i<n; ++i) {
					for(int j=0; j<10; ++j) {
						if(g[i][j]!='0'&&!vis[i][j]&&findSize(new int[]{i, j})>=k) {
							erase(new int[]{i, j});
							changed=true;
						}
					}
				}
				if(!changed)
					break;
				//move things down
				for(int j=0; j<10; ++j) {
					//two pointers
					int i1=n-1;
					for(int i2=n-1; i2>=0; --i2)
						if(g[i2][j]!='0')
							g[i1--][j]=g[i2][j];
					for(; i1>=0; --i1)
						g[i1][j]='0';
				}
			}
			//output
			for(int i=0; i<n; ++i)
				out.println(g[i]);
		}
		
		List<int[]> getNeighbors(int[] u) {
			List<int[]> v = new ArrayList<int[]>();
			if(u[0]>0)
				v.add(new int[]{u[0]-1, u[1]});
			if(u[0]<n-1)
				v.add(new int[]{u[0]+1, u[1]});
			if(u[1]>0)
				v.add(new int[]{u[0], u[1]-1});
			if(u[1]<9)
				v.add(new int[]{u[0], u[1]+1});
			return v;
		}
		
		int findSize(int[] u) {
			int s=1;
			vis[u[0]][u[1]]=true;
			for(int[] v : getNeighbors(u))
				if(!vis[v[0]][v[1]]&&g[v[0]][v[1]]==g[u[0]][u[1]])
					s+=findSize(v);
			return s;
		}
		
		void erase(int[] u) {
			char oc=g[u[0]][u[1]];
			g[u[0]][u[1]]='0';
			for(int[] v : getNeighbors(u))
				if(g[v[0]][v[1]]==oc)
					erase(v);
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