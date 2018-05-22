package section_3_2;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: msquare
*/
import java.io.*;
import java.util.*;

public class msquare {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "msquare";
	
	static class Solver {
		int[] finalP = new int[8];
		Map<Integer, String> map = new HashMap<Integer, String>();
		
		Solver() {
			PriorityQueue<PermData> queue = new PriorityQueue();
			queue.add(new PermData(new int[]{0, 1, 2, 3, 4, 5, 6, 7}, ""));
			while(!queue.isEmpty()) {
				PermData pd = queue.poll();
				if(map.containsKey(permToInt(pd.perm)))
					continue;
				map.put(permToInt(pd.perm), pd.ops);
				int[] perm=applyA(pd.perm);
				if(!map.containsKey(permToInt(perm)))
					queue.add(new PermData(perm, pd.ops+"A"));
				perm=applyB(pd.perm);
				if(!map.containsKey(permToInt(perm)))
					queue.add(new PermData(perm, pd.ops+"B"));
				perm=applyC(pd.perm);
				if(!map.containsKey(permToInt(perm)))
					queue.add(new PermData(perm, pd.ops+"C"));
			}
			for(int i=0; i<8; ++i)
				finalP[i]=in.nextInt()-1;
			String s=map.get(permToInt(finalP));
			out.println(s.length());
			if(s.length()==0)
				out.println();
			for(int i=0; i<s.length(); i+=60)
				out.println(s.substring(i, Math.min(s.length(), i+60)));
		}
		int permToInt(int[] perm) {
			int res=perm[0];
			for(int i=1; i<perm.length; ++i)
				res=res*8+perm[i];
			return res;
		}
		int[] applyA(int[] perm) {
			int[] res = new int[8];
			for(int i=0; i<8; ++i)
				res[i]=perm[7-i];
			return res;
		}
		int[] applyB(int[] perm) {
			int[] res = new int[8];
			for(int i=0; i<4; ++i)
				res[(i+1)%4]=perm[i];
			for(int i=0; i<4; ++i)
				res[i+4]=perm[(i+1)%4+4];
			return res;
		}
		int[] applyC(int[] perm) {
			int[] res = new int[8];
			int[] map = {0, 6, 1, 3, 4, 2, 5, 7};
			for(int i=0; i<8; ++i)
				res[i]=perm[map[i]];
			return res;
		}
		
		class PermData implements Comparable<PermData> {
			int[] perm;
			String ops;
			PermData(int[] perm, String ops) {
				this.perm=perm;
				this.ops=ops;
			}
			public int compareTo(PermData o) {
				if(ops.length()==o.ops.length())
					return ops.compareTo(o.ops);
				return ops.length()-o.ops.length();
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