package section_1_3;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: wormhole
*/
import java.io.*;
import java.util.*;

public class wormhole {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "wormhole";
	
	static class Solver {
		int N, t;
		int[] to;
		
		Solver() {
			N=in.nextInt();
			Triple[] triples = new Triple[N];
			to = new int[N];
			Arrays.fill(to, -1);
			Map<Integer, List<Triple>> triplesByY = new HashMap<Integer, List<Triple>>();
			for(int i=0; i<N; ++i) {
				triples[i] = new Triple(i, in.nextInt(), in.nextInt());
				if(!triplesByY.containsKey(triples[i].y))
					triplesByY.put(triples[i].y, new ArrayList<Triple>());
				triplesByY.get(triples[i].y).add(triples[i]);
			}
			for(Map.Entry<Integer, List<Triple>> entry : triplesByY.entrySet()) {
				List<Triple> list = entry.getValue();
				list.sort(new Comparator<Triple>() {
					public int compare(Triple a, Triple b) {
						return a.x-b.x;
					}
				});
				for(int i=0; i<list.size()-1; ++i)
					to[list.get(i).i]=list.get(i+1).i;
			}
			recur(new int[N/2], new int[N/2], 0);
			out.println(t);
		}
		void recur(int[] a, int[] b, int i) {
			if(i==a.length) {
				int[] to2 = new int[N];
				for(int j=0; j<a.length; ++j)
					to2[a[j]]=b[j];
				for(int j=0; j<a.length; ++j)
					to2[b[j]]=a[j];
				for(int start=0; start<N; ++start) {
					int next1=start;
					do {
						next1=to[to2[next1]];
					} while(next1!=start&&next1!=-1);
					if(next1!=-1) {
						++t;
						return;
					}
				}
			} else {
				boolean[] used = new boolean[N];
				for(int j=0; j<i; ++j) {
					used[a[j]]=true;
					used[b[j]]=true;
				}
				int min=0;
				for(; min<N; ++min)
					if(!used[min])
						break;
				a[i]=min++;
				for(; min<N; ++min) {
					if(used[min])
						continue;
					b[i]=min;
					recur(a, b, i+1);
				}
			}
		}
		
		class Triple {
			int i, x, y;
			Triple(int i, int x, int y) {
				this.i=i;
				this.x=x;
				this.y=y;
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