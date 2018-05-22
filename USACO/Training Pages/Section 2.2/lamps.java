package section_2_2;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: lamps
*/
import java.io.*;
import java.util.*;

public class lamps {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "lamps";
	
	static class Solver {
		List<boolean[]> answers = new ArrayList<boolean[]>();
		int n=in.nextInt(), c=in.nextInt();
		boolean[] set;
		boolean[] isOn;
		
		Solver() {
			set = new boolean[n];
			isOn = new boolean[n];
			int lamp;
			while((lamp=in.nextInt()-1)!=-2) {
				set[lamp]=true;
				isOn[lamp]=true;
			}
			while((lamp=in.nextInt()-1)!=-2)
				set[lamp]=true;
			recur(0);
			answers.sort(new Comparator<boolean[]>() {
				public int compare(boolean[] a, boolean[] b) {
					for(int i=0; i<n; ++i)
						if(a[i]&&!b[i])
							return 1;
						else if(b[i]&&!a[i])
							return -1;
					return 0;
				}
			});
			if(answers.size()==0)
				out.println("IMPOSSIBLE");
			else {
				for(boolean[] ans : answers) {
					for(boolean b : ans)
						out.print(b?"1":0);
					out.println();
				}
			}
		}
		
		void recur(int state) {
			boolean[] lamps = new boolean[n];
			if((state&1)==0)
				Arrays.fill(lamps, true);
			if((state&2)!=0)
				for(int i=0; i<n; i+=2)
					lamps[i]=!lamps[i];
			if((state&4)!=0)
				for(int i=1; i<n; i+=2)
					lamps[i]=!lamps[i];
			if((state&8)!=0)
				for(int i=0; i<n; i+=3)
					lamps[i]=!lamps[i];
			int switches=Integer.bitCount(state);
			if(switches==c||switches<c-1) {
				boolean works=true;
				for(int i=0; i<n; ++i) {
					if(set[i]&&lamps[i]!=isOn[i]) {
						works=false;
						break;
					}
				}
				if(works) {
					for(boolean[] ans : answers) {
						boolean dif=false;
						for(int i=0; i<n; ++i) {
							if(ans[i]!=lamps[i]) {
								dif=true;
								break;
							}
						}
						if(dif==false) {
							works=false;
							break;
						}
					}
				}
				if(works)
					answers.add(lamps);
			}
			if(switches==c)
				return;
			if((state&1)==0&&(state&6)!=6)
				recur(state|1);
			if((state&2)==0&&(state&5)!=5)
				recur(state|2);
			if((state&4)==0&&(state&3)!=3)
				recur(state|4);
			if((state&8)==0)
				recur(state|8);
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