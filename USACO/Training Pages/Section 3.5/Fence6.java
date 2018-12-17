package section_4_1;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: fence6
*/
import java.io.*;
import java.util.*;

public class fence6 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "fence6";
	
	static class Solver {
		int n=in.nextInt(), INF=(int)1e5;
		
		Solver() {
			Segment[] segments = new Segment[n];
			for(int i=0; i<n; ++i) {
				int id=in.nextInt()-1, len=in.nextInt(), leftConns=in.nextInt(), rightConns=in.nextInt();
				segments[id] = new Segment(len);
				for(int j=0; j<leftConns; ++j)
					segments[id].connectLeft(in.nextInt()-1);
				for(int j=0; j<rightConns; ++j)
					segments[id].connectRight(in.nextInt()-1);
			}
			int node=0;
			for(int i=0; i<n; ++i) {
				if(segments[i].leftNode==-1)
					segments[i].leftNode=node++;
				if(segments[i].rightNode==-1)
					segments[i].rightNode=node++;
				for(int j=0; j<n; ++j) {
					if(!segments[i].leftConnected[j])
						continue;
					if(segments[j].leftConnected[i])
						segments[j].leftNode=segments[i].leftNode;
					else
						segments[j].rightNode=segments[i].leftNode;
				}
				for(int j=0; j<n; ++j) {
					if(!segments[i].rightConnected[j])
						continue;
					if(segments[j].leftConnected[i])
						segments[j].leftNode=segments[i].rightNode;
					else
						segments[j].rightNode=segments[i].rightNode;
				}
			}
			int[][] dist1 = new int[node][node], dist2 = new int[node][node];
			for(int i=0; i<node; ++i) {
				Arrays.fill(dist1[i], INF);
				Arrays.fill(dist2[i], INF);
			}
			for(int i=0; i<n; ++i) {
				dist1[segments[i].leftNode][segments[i].rightNode]=
						dist2[segments[i].leftNode][segments[i].rightNode]=segments[i].len;
				dist1[segments[i].rightNode][segments[i].leftNode]=
						dist2[segments[i].rightNode][segments[i].leftNode]=segments[i].len;
			}
			int min=INF;
			for(int k=0; k<node; ++k) {
				for(int i=0; i<node; ++i)
					for(int j=i+1; j<node; ++j)
						min=Math.min(dist2[i][j]+dist1[j][k]+dist1[k][i], min);
				for(int i=0; i<node; ++i)
					for(int j=0; j<node; ++j)
						dist2[i][j]=Math.min(dist2[i][k]+dist2[k][j], dist2[i][j]);
			}
			out.println(min);
		}
		
		class Segment {
			boolean[] leftConnected = new boolean[n], rightConnected = new boolean[n];
			int len, leftNode=-1, rightNode=-1;
			Segment(int len) {
				this.len=len;
			}
			void connectLeft(int seg) {
				leftConnected[seg]=true;
			}
			void connectRight(int seg) {
				rightConnected[seg]=true;
			}
		}
	}
	
	static void preprocess() {
		
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
		preprocess();
		for(int testCases=1; testCases>0; --testCases)
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