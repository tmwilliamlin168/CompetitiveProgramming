package section_5_3;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: milk4
*/
import java.io.*;
import java.util.*;

public class milk4 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "milk4";
	static Comparator<List<Integer>> lCmp = new Comparator<List<Integer>>() {
		public int compare(List<Integer> a, List<Integer> b) {
			if(a.size()!=b.size())
				return a.size()-b.size();
			for(int i=0; i<a.size(); ++i)
				if(a.get(i)!=b.get(i))
					return a.get(i)-b.get(i);
			return 0;
		}
	};
	
	static class Solver {
		Solver() {
			int q=in.nextInt(), p=in.nextInt();
			int[] a = new int[p];
			for(int i=0; i<p; ++i)
				a[i]=in.nextInt();
			Arrays.sort(a);
			List<Integer>[][] dp = new List[p+1][q+1];
			List<Integer> dummy = new ArrayList<Integer>();
			for(int i=0; i<p; ++i)
				dummy.add(i);
			Arrays.fill(dp[p], dummy);
			dp[p][0] = new ArrayList<Integer>();
			for(int i=p-1; i>=0; --i) {
				int[] best = new int[a[i]];
				for(int j=0; j<=q; ++j) {
					if(j<a[i]||dp[i+1][j].size()<=dp[i+1][best[j%a[i]]].size())
						dp[i][j]=dp[i+1][j];
					else {
						dp[i][j] = new ArrayList<Integer>();
						dp[i][j].add(i);
						dp[i][j].addAll(dp[i+1][best[j%a[i]]]);
					}
					if(j<a[i]||lCmp.compare(dp[i+1][j], dp[i+1][best[j%a[i]]])<0)
						best[j%a[i]]=j;
				}
			}
			out.print(dp[0][q].size());
			for(int i : dp[0][q])
				out.print(" "+a[i]);
			out.println();
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