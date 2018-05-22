package section_3_2;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: spin
*/
import java.io.*;
import java.util.*;

public class spin {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "spin";
	
	static class Solver {
		Solver() {
			int[] speeds = new int[5];
			List<Pair>[] wedges = new List[5];
			for(int i=0; i<5; ++i) {
				speeds[i]=in.nextInt();
				wedges[i] = new ArrayList<Pair>();
				for(int j=in.nextInt(); j>0; --j)
					wedges[i].add(new Pair(in.nextInt(), in.nextInt()));
			}
			for(int i=0; i<360; ++i) {
				BitSet possible = new BitSet(360);
				Arrays.fill(possible.a, ~0L);
				for(int j=0; j<5; ++j) {
					BitSet cur = new BitSet(360);
					for(Pair wedge : wedges[j]) {
						for(int k=0; k<=wedge.b; ++k)
							cur.set((wedge.a+k)%360);
					}
					possible=possible.and(cur);
				}
				for(int j=0; j<possible.a.length; ++j) {
					if(possible.a[j]!=0) {
						out.println(i);
						return;
					}
				}
				for(int j=0; j<5; ++j)
					for(Pair wedge : wedges[j])
						wedge.a=(wedge.a+speeds[j])%360;
			}
			out.println("none");
		}
		class Pair {
			int a, b;
			Pair(int a, int b) {
				this.a=a;
				this.b=b;
			}
		}
		class BitSet {
			long[] a;
			BitSet(int n) {
				a = new long[((n-1)>>6)+1];
			}
			void set(int i) {
				a[i>>6]|=1L<<(i&63);
			}
			boolean get(int i) {
				return (a[i>>6]&(1L<<(i&63)))!=0;
			}
			BitSet and(BitSet b) {
				BitSet res = new BitSet(1);
				res.a=Arrays.copyOf(a, a.length);
				for(int i=0; i<a.length; ++i)
					res.a[i]&=b.a[i];
				return res;
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