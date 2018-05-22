package section_1_3;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: barn1
*/
import java.io.*;
import java.util.*;

public class barn1 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "barn1";
	
	static class Solver {
		Solver() {
			int M=in.nextInt(), S=in.nextInt(), C=in.nextInt(), minStall=S-1, maxStall=0;
			boolean[] hasCow = new boolean[S];
			for(int i=0; i<C; ++i) {
				int stall=in.nextInt()-1;
				hasCow[stall]=true;
				minStall=Math.min(stall, minStall);
				maxStall=Math.max(stall, maxStall);
			}
			List<Integer> contEmptyStalls = new ArrayList<Integer>();
			int lastStall=-1;
			for(int i=minStall+1; i<=maxStall; ++i) {
				if(hasCow[i]&&lastStall!=-1) {
					contEmptyStalls.add(i-lastStall);
					lastStall=-1;
				} else if(lastStall==-1&&!hasCow[i])
					lastStall=i;
			}
			contEmptyStalls.sort(Collections.reverseOrder());
			int t=maxStall-minStall+1;
			for(int i=0; i<M-1&&i<contEmptyStalls.size(); ++i)
				t-=contEmptyStalls.get(i);
			out.println(t);
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