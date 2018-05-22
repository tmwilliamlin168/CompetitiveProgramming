package section_2_4;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: maze1
*/
import java.io.*;
import java.util.*;

public class maze1 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "maze1";
	
	static class Solver {
		static int[][] dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
		
		Solver() {
			int w=in.nextInt(), h=in.nextInt();
			char[][] maze = new char[2*h+1][2*w+1];
			for(int i=0; i<maze.length; ++i)
				maze[i]=in.nextLine().toCharArray();
			int[][] walls = new int[h][w];
			int exit1i=-1, exit1j=-1, exit2i=-1, exit2j=-1;
			for(int i=0; i<h; ++i) {
				for(int j=0; j<w; ++j) {
					//x=j*2+1, y=i*2+1
					for(int k=0; k<dirs.length; ++k) {
						char mazeCell = maze[i*2+1+dirs[k][0]][j*2+1+dirs[k][1]];
						if(mazeCell=='-'||mazeCell=='|')
							walls[i][j]|=1<<k;
						else {
							int newI=i+dirs[k][0], newJ=j+dirs[k][1];
							if(newI<0||newI>=h||newJ<0||newJ>=w) {
								if(exit1i==-1) {
									exit1i=i;
									exit1j=j;
								} else {
									exit2i=i;
									exit2j=j;
								}
							}
						}
					}
				}
			}
			//double bfs
			int[][] q = new int[h*w*2][];
			int qh=0, qt=0;
			int[][] minReach = new int[h][w];
			for(int i=0; i<h; ++i)
				Arrays.fill(minReach[i], 6969);
			q[qt++]=new int[]{exit1i, exit1j};
			minReach[exit1i][exit1j]=1;
			while(qh<qt) {
				int[] pt = q[qh++];
				for(int k=0; k<dirs.length; ++k) {
					if((walls[pt[0]][pt[1]]&(1<<k))==0) {
						int newI=pt[0]+dirs[k][0], newJ=pt[1]+dirs[k][1];
						if(newI<0||newI>=h||newJ<0||newJ>=w||minReach[newI][newJ]<=minReach[pt[0]][pt[1]]+1)
							continue;
						q[qt++]=new int[]{newI, newJ};
						minReach[newI][newJ]=minReach[pt[0]][pt[1]]+1;
					}
				}
			}
			q[qt++]=new int[]{exit2i, exit2j};
			minReach[exit2i][exit2j]=1;
			while(qh<qt) {
				int[] pt = q[qh++];
				for(int k=0; k<dirs.length; ++k) {
					if((walls[pt[0]][pt[1]]&(1<<k))==0) {
						int newI=pt[0]+dirs[k][0], newJ=pt[1]+dirs[k][1];
						if(newI<0||newI>=h||newJ<0||newJ>=w||minReach[newI][newJ]<=minReach[pt[0]][pt[1]]+1)
							continue;
						q[qt++]=new int[]{newI, newJ};
						minReach[newI][newJ]=minReach[pt[0]][pt[1]]+1;
					}
				}
			}
			int maxReach=0;
			for(int i=0; i<h; ++i)
				for(int j=0; j<w; ++j)
					maxReach=Math.max(minReach[i][j], maxReach);
			out.println(maxReach);
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
		String nextLine() {
			try {
				return br.readLine();
			} catch (Exception e) {
				return "";
			}
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
	}
}