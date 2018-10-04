import java.io.*;
import java.util.*;

public class Main {
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			char[][] grid = new char[9][];
			for(int i=0; i<9; ++i)
				grid[i]=in.next().toCharArray();
			int[][][] min1 = new int[3][8][8];
			int[][] min2 = new int[3][512];
			for(int i=0; i<3; ++i) {
				for(int j=0; j<3; ++j) {
					for(int k=0; k<8; ++k)
						Arrays.fill(min1[j][k], 69);
					for(int a=0; a<512; ++a) {
						if(Integer.bitCount(a)%2!=0)
							continue;
						int c=0, rm=0, cm=0;
						for(int k=0; k<3; ++k) {
							for(int l=0; l<3; ++l) {
								c+=((a>>(3*k+l))&1)^(grid[i*3+k][j*3+l]-'0');
								if(((a>>(3*k+l))&1)==1) {
									rm^=1<<k;
									cm^=1<<l;
								}
							}
						}
						min1[j][rm][cm]=Math.min(c, min1[j][rm][cm]);
					}
				}
				Arrays.fill(min2[i], 69);
				for(int j=0; j<64; ++j)
					for(int k=0; k<64; ++k)
						for(int l=0; l<64; ++l)
							if(((j>>3)^(k>>3)^(l>>3))==0)
								min2[i][(j&7)<<6|(k&7)<<3|(l&7)]=Math.min(min1[0][j>>3][j&7]+min1[1][k>>3][k&7]+min1[2][l>>3][l&7], 
										min2[i][(j&7)<<6|(k&7)<<3|(l&7)]);
			}
			int[] min3 = new int[512];
			Arrays.fill(min3, 69);
			for(int i=0; i<512; ++i)
				for(int j=0; j<512; ++j)
					min3[i^j]=Math.min(min2[0][i]+min2[1][j], min3[i^j]);
			int ans=6969;
			for(int i=0; i<512; ++i)
				ans=Math.min(min3[i]+min2[2][i], ans);
			out.println(ans);
		}
	}
	
	public static void main(String[] args) throws Exception {
		in = new Reader();
		out = new PrintWriter(System.out);
		new Solver();
		out.close();
	}
	
	static class Reader {
		BufferedReader br;
		StringTokenizer st;
		Reader() {
			br = new BufferedReader(new InputStreamReader(System.in));
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
