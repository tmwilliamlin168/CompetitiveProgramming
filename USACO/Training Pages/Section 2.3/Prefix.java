package section_2_3;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: prefix
*/
import java.io.*;
import java.util.*;

public class prefix {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "prefix";
	
	static class Solver {
		Solver() {
			List<String> prims = new ArrayList<String>();
			String prim;
			while(!(prim=in.next()).equals("."))
				prims.add(prim);
			StringBuilder S = new StringBuilder();
			String s;
			while((s=in.next())!=null&&!s.equals("x"))
				S.append(s);
			int maxK=0;
			boolean[] dp = new boolean[S.length()+1];
			dp[0]=true;
			for(int i=0; i<=S.length(); ++i) {
				if(dp[i]==true)
					maxK=i;
				else
					continue;
				for(String prim2 : prims) {
					if(i+prim2.length()>S.length()||dp[i+prim2.length()])
						continue;
					boolean works=true;
					for(int j=0; j<prim2.length(); ++j) {
						if(prim2.charAt(j)!=S.charAt(i+j)) {
							works=false;
							break;
						}
					}
					if(works)
						dp[i+prim2.length()]=true;
				}
			}
			out.println(maxK);
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
					String s=br.readLine();
					if(s==null)
						return null;
					st = new StringTokenizer(s);
				} catch(Exception e) {}
			}
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
	}
}