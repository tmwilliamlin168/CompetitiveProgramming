import java.io.*;
import java.util.*;

public class Convention2 {
	static final boolean stdin = false;
	static final String filename = "convention2";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			//input
			int n=in.nextInt(), ans=0;
			final int[] a = new int[n], t = new int[n];
			List<Integer> sortedbyA = new ArrayList<Integer>();
			for(int i=0; i<n; ++i) {
				a[i]=in.nextInt();
				t[i]=in.nextInt();
				sortedbyA.add(i);
			}
			Collections.sort(sortedbyA, new Comparator<Integer>() {
				public int compare(Integer i, Integer j) {
					return a[i]-a[j];
				}
			});
			PriorityQueue<Integer> waiting = new PriorityQueue<Integer>();
			//iterate from lowest a
			for(int i=0, time=0; ; ) {
				if(waiting.isEmpty()) {
					if(i>=n)
						break;
					//update time to when next one arrives
					time=a[sortedbyA.get(i)];
					//add next cow to arrive
					waiting.add(sortedbyA.get(i++));
				}
				int next=waiting.poll();
				//update ans according to wait time
				ans=Math.max(time-a[next], ans);
				//update time
				time+=t[next];
				//add the cows that arrived
				while(i<n&&a[sortedbyA.get(i)]<=time)
					waiting.add(sortedbyA.get(i++));
			}
			out.println(ans);
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