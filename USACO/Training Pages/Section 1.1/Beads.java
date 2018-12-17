package section_1_1;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: beads
*/
import java.io.*;
import java.util.*;

public class beads {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "beads";
	
	static class Solver {
		Solver() {
			int n=in.nextInt(), max=0;
			String necklace = in.next();
			for(int i=0; i<n; ++i) {
				int cI1=i+1, cI2=i;
				char firstC=0;
				while(true) {
					if(firstC==0&&necklace.charAt(cI1%n)!='w')
						firstC=necklace.charAt(cI1%n);
					else if(firstC!=0&&necklace.charAt(cI1%n)!='w'&&firstC!=necklace.charAt(cI1%n))
						break;
					++cI1;
					if(cI1-i>n)
						break;
				}
				firstC=0;
				while(true) {
					if(firstC==0&&necklace.charAt((cI2+n)%n)!='w')
						firstC=necklace.charAt((cI2+n)%n);
					else if(firstC!=0&&necklace.charAt((cI2+n)%n)!='w'&&firstC!=necklace.charAt((cI2+n)%n))
						break;
					--cI2;
					if(i-cI2>=n)
						break;
				}
				//out.println(cI1-cI2-1);
				max=Math.max(cI1-cI2-1, max);
			}
			out.println(Math.min(max, n));
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
