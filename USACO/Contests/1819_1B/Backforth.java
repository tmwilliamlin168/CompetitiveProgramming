import java.io.*;
import java.util.*;

public class Backforth {
	static final boolean stdin = false;
	static final String filename = "backforth";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		boolean[] possible = new boolean[2001];
		
		Solver() {
			//input
			List<Integer> a = new ArrayList<Integer>(), b = new ArrayList<Integer>();
			for(int i=0; i<10; ++i)
				a.add(in.nextInt());
			for(int i=0; i<10; ++i)
				b.add(in.nextInt());
			//do recursion
			recur(0, 1000, a, 1000, b);
			//count number of answers
			int ans=0;
			for(int i=0; i<=2000; ++i)
				ans+=possible[i]?1:0;
			out.println(ans);
		}
		
		void recur(int day, int ga, List<Integer> a, int gb, List<Integer> b) {
			if(day>=4) {
				//the end, mark possible
				possible[ga]=true;
				return;
			}
			if(day%2==1) {
				//tuesday or thursday
				for(int i=0; i<b.size(); ++i) {
					List<Integer> newa = new ArrayList<Integer>(), newb = new ArrayList<Integer>();
					newa.addAll(a);
					newa.add(b.get(i));
					newb.addAll(b);
					newb.remove(i);
					recur(day+1, ga+b.get(i), newa, gb-b.get(i), newb);
				}
			} else {
				//monday or wednesday
				for(int i=0; i<a.size(); ++i) {
					List<Integer> newa = new ArrayList<Integer>(), newb = new ArrayList<Integer>();
					newa.addAll(a);
					newa.remove(i);
					newb.addAll(b);
					newb.add(a.get(i));
					recur(day+1, ga-a.get(i), newa, gb+a.get(i), newb);
				}
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		if(stdin) {
			in = new Reader();
			out = new PrintWriter(System.out);
		} else {
			in = new Reader(filename+".in");
			out = new PrintWriter(filename+".out");
		}
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