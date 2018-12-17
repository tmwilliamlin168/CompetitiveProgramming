package section_2_1;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: castle
*/
import java.io.*;
import java.util.*;

public class castle {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "castle";
	
	static class Solver {
		int[][] cellWalls, cellColors, neighbors={{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
		
		Solver() {
			int m=in.nextInt(), n=in.nextInt(), colors=0;
			cellWalls = new int[n][m];
			cellColors = new int[n][m];
			for(int i=0; i<n; ++i)
				for(int j=0; j<m; ++j)
					cellWalls[i][j]=in.nextInt();
			List<Integer> roomSizes = new ArrayList<Integer>();
			for(int i=0; i<n; ++i)
				for(int j=0; j<m; ++j)
					if(cellColors[i][j]==0)
						roomSizes.add(dfs(i, j, ++colors));
			out.println(colors);
			int maxRoom=-1, maxRoomCombine=-1, combineI=-1, combineJ=-1, combineDir=-1;
			for(int room : roomSizes)
				maxRoom=Math.max(room, maxRoom);
			out.println(maxRoom);
			for(int j=0; j<m; ++j) {
				for(int i=n-1; i>=0; --i) {
					if(i>0&&cellColors[i][j]!=cellColors[i-1][j]&&roomSizes.get(cellColors[i][j]-1)+roomSizes.get(cellColors[i-1][j]-1)>maxRoomCombine) {
						maxRoomCombine=roomSizes.get(cellColors[i][j]-1)+roomSizes.get(cellColors[i-1][j]-1);
						combineI=i;
						combineJ=j;
						combineDir=0;
					}
					if(j<m-1&&cellColors[i][j]!=cellColors[i][j+1]&&roomSizes.get(cellColors[i][j]-1)+roomSizes.get(cellColors[i][j+1]-1)>maxRoomCombine) {
						maxRoomCombine=roomSizes.get(cellColors[i][j]-1)+roomSizes.get(cellColors[i][j+1]-1);
						combineI=i;
						combineJ=j;
						combineDir=1;
					}
				}
			}
			out.println(maxRoomCombine);
			out.println((combineI+1)+" "+(combineJ+1)+" "+(combineDir==0?"N":"E"));
		}
		
		int dfs(int i, int j, int color) {
			int t=1;
			cellColors[i][j]=color;
			for(int k=0; k<4; ++k)
				if((cellWalls[i][j]&(1<<k))==0&&cellColors[i+neighbors[k][0]][j+neighbors[k][1]]==0)
					t+=dfs(i+neighbors[k][0], j+neighbors[k][1], color);
			return t;
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