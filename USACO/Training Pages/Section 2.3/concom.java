package section_2_3;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: concom
*/
import java.io.*;
import java.util.*;

public class concom {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "concom";
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			int[][] shares = new int[100][100];
			for(int i=0; i<n; ++i)
				shares[in.nextInt()-1][in.nextInt()-1]=in.nextInt();
			for(int i=0; i<100; ++i) {
				boolean[] owned = new boolean[100];
				owned[i]=true;
				boolean hasChange=true;
				while(hasChange) {
					hasChange=false;
					for(int j=0; j<100; ++j) {
						if(owned[j])
							continue;
						int t=0;
						for(int k=0; k<100; ++k)
							if(owned[k])
								t+=shares[k][j];
						if(t>50) {
							owned[j]=true;
							hasChange=true;
						}
					}
				}
				owned[i]=false;
				for(int j=0; j<100; ++j)
					if(owned[j])
						out.println((i+1)+" "+(j+1));
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