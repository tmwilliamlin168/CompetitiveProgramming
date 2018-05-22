package section_3_2;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: ratios
*/
import java.io.*;
import java.util.*;

public class ratios {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "ratios";
	
	static class Solver {
		Solver() {
			int[] goal = new int[3];
			for(int i=0; i<3; ++i)
				goal[i]=in.nextInt();
			int[][] mixtures = new int[3][3];
			for(int i=0; i<3; ++i)
				for(int j=0; j<3; ++j)
					mixtures[i][j]=in.nextInt();
			int minA=-1, minB=-1, minC=-1, minR=-1;
			int[] k = new int[3];
			for(k[0]=0; k[0]<100; ++k[0]) {
				for(k[1]=0; k[1]<100; ++k[1]) {
					for(k[2]=0; k[2]<100; ++k[2]) {
						if(k[0]==0&&k[1]==0&&k[2]==0)
							continue;
						int[] t = new int[3];
						for(int i=0; i<3; ++i)
							for(int j=0; j<3; ++j)
								t[j]+=k[i]*mixtures[i][j];
						int r=-1;
						boolean works=true;
						for(int i=0; i<3; ++i) {
							if(goal[i]==0) {
								if(t[i]!=0) {
									works=false;
									break;
								}
							} else if(t[i]%goal[i]!=0) {
								works=false;
								break;
							} else {
								if(r==-1)
									r=t[i]/goal[i];
								else if(r!=t[i]/goal[i]) {
									works=false;
									break;
								}
							}
						}
						if(!works)
							continue;
						if(minA==-1||minA+minB+minC>k[0]+k[1]+k[2]) {
							minA=k[0];
							minB=k[1];
							minC=k[2];
							minR=Math.max(r, 0);
						}
					}
				}
			}
			if(minA==-1) {
				out.println("NONE");
			} else {
				out.println(minA+" "+minB+" "+minC+" "+minR);
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