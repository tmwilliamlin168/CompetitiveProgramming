package section_2_1;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: sort3
*/
import java.io.*;
import java.util.*;

public class sort3 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "sort3";
	
	static class Solver {
		Solver() {
			int N=in.nextInt(), swaps=0;
			int[] a = new int[N];
			int[] cnt = new int[3];
			for(int i=0; i<N; ++i) {
				a[i]=in.nextInt()-1;
				++cnt[a[i]];
			}
			List<Integer>[][] cntInSecs = new List[3][3];
			for(int i=0; i<3; ++i)
				for(int j=0; j<3; ++j)
					cntInSecs[i][j]=new ArrayList<Integer>();
			for(int i=0, j=0, jEnd=0; i<3; ++i) {
				jEnd+=cnt[i];
				for(; j<jEnd; ++j)
					cntInSecs[i][a[j]].add(j);
			}
			for(int i=0; i<3; ++i) {
				for(int j=i+1; j<3; ++j) {
					while(!cntInSecs[i][j].isEmpty()&&!cntInSecs[j][i].isEmpty()) {
						int i1=cntInSecs[i][j].remove(cntInSecs[i][j].size()-1), i2=cntInSecs[j][i].remove(cntInSecs[j][i].size()-1);
						++swaps;
					}
				}
			}
			out.println(swaps+2*(cntInSecs[0][1].size()+cntInSecs[1][0].size()));
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