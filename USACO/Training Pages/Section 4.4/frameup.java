package section_4_4;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: frameup
*/
import java.io.*;
import java.util.*;

public class frameup {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "frameup";
	
	static class Solver {
		int h=in.nextInt(), w=in.nextInt();
		char[][] mat = new char[h][];
		List<String> ans = new ArrayList<String>();
		int[] minI, maxI, minJ, maxJ, charToId = new int[256];
		char[] idToChar = new char[26];
		boolean[][] above = new boolean[26][26];
		
		Solver() {
			for(int i=0; i<h; ++i)
				mat[i]=in.next().toCharArray();
			Arrays.fill(charToId, -1);
			int frameI=0;
			for(int i=0; i<h; ++i) {
				for(int j=0; j<w; ++j) {
					if(mat[i][j]!='.'&&charToId[mat[i][j]]==-1) {
						idToChar[frameI]=mat[i][j];
						charToId[mat[i][j]]=frameI++;
					}
				}
			}
			minI = new int[frameI]; 
			maxI = new int[frameI];
			minJ = new int[frameI];
			maxJ = new int[frameI];
			Arrays.fill(minI, h-1);
			Arrays.fill(minJ, w-1);
			for(int i=0; i<h; ++i) {
				for(int j=0; j<w; ++j) {
					if(mat[i][j]=='.')
						continue;
					minI[charToId[mat[i][j]]]=Math.min(i, minI[charToId[mat[i][j]]]);
					maxI[charToId[mat[i][j]]]=Math.max(i, maxI[charToId[mat[i][j]]]);
					minJ[charToId[mat[i][j]]]=Math.min(j, minJ[charToId[mat[i][j]]]);
					maxJ[charToId[mat[i][j]]]=Math.max(j, maxJ[charToId[mat[i][j]]]);
				}
			}
			for(int i=0; i<frameI; ++i) {
				for(int j=minI[i]; j<=maxI[i]; ++j) {
					if(mat[j][minJ[i]]!=idToChar[i])
						above[charToId[mat[j][minJ[i]]]][i]=true;
					if(mat[j][maxJ[i]]!=idToChar[i])
						above[charToId[mat[j][maxJ[i]]]][i]=true;
				}
				for(int j=minJ[i]+1; j<=maxJ[i]-1; ++j) {
					if(mat[minI[i]][j]!=idToChar[i])
						above[charToId[mat[minI[i]][j]]][i]=true;
					if(mat[maxI[i]][j]!=idToChar[i])
						above[charToId[mat[maxI[i]][j]]][i]=true;
				}
			}
			permute(new int[frameI], 0);
			//permute(new int[]{4, 3, 0, 1, 2}, 5);
			Collections.sort(ans);
			for(String s : ans)
				out.println(s);
		}
		void permute(int[] perm, int i) {
			if(i>=perm.length) {
				char[][] mat2 = new char[h][w];
				for(int j=0; j<h; ++j)
					Arrays.fill(mat2[j], '.');
				for(int j=0; j<perm.length; ++j) {
					for(int k=minI[perm[j]]; k<=maxI[perm[j]]; ++k)
						mat2[k][minJ[perm[j]]]=mat2[k][maxJ[perm[j]]]=idToChar[perm[j]];
					for(int k=minJ[perm[j]]+1; k<=maxJ[perm[j]]-1; ++k)
						mat2[minI[perm[j]]][k]=mat2[maxI[perm[j]]][k]=idToChar[perm[j]];
				}
				if(Arrays.deepEquals(mat, mat2)) {
					char[] s = new char[perm.length];
					for(int j=0; j<s.length; ++j)
						s[j]=idToChar[perm[j]];
					ans.add(new String(s));
				}
			} else {
				boolean[] used = new boolean[perm.length];
				for(int j=0; j<i; ++j)
					used[perm[j]]=true;
				for(int j=0; j<perm.length; ++j) {
					if(used[j])
						continue;
					boolean ok=true;
					for(int k=0; k<perm.length; ++k) {
						if(above[j][k]&&!used[k]) {
							ok=false;
						}
					}
					if(!ok)
						continue;
					perm[i]=j;
					permute(perm, i+1);
				}
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