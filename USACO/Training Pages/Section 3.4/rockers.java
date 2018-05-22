package section_3_4;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: rockers
*/
import java.io.*;
import java.util.*;

public class rockers {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "rockers";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), t=in.nextInt(), m=in.nextInt(), max=0;
			int[] songs = new int[n];
			for(int i=0; i<n; ++i)
				songs[i]=in.nextInt();
			for(int i=0; i<1<<n; ++i) {
				int disks=0, spaceLeft=t;
				for(int j=0; j<n; ++j) {
					if((i&(1<<j))!=0) {
						if(songs[j]>t) {
							disks=6969;
							break;
						}
						if(spaceLeft>=songs[j])
							spaceLeft-=songs[j];
						else {
							++disks;
							spaceLeft=t-songs[j];
						}
					}
				}
				if(spaceLeft!=t)
					++disks;
				if(disks<=m)
					max=Math.max(Integer.bitCount(i), max);
			}
			out.println(max);
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