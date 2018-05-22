package section_1_1;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: gift1
*/
import java.io.*;
import java.util.*;

public class gift1 {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "gift1";
	
	static class Solver {
		Solver() {
			int NP=in.nextInt();
			String[] names = new String[NP];
			Map<String, Integer> balances = new HashMap<String, Integer>();
			for(int i=0; i<NP; ++i) {
				names[i]=in.next();
				balances.put(names[i], 0);
			}
			for(int i=0; i<NP; ++i) {
				String giver=in.next();
				int init=in.nextInt(), nPpl=in.nextInt();
				if(nPpl==0)
					continue;
				int moneyPerPerson=init/nPpl;
				for(int j=0; j<nPpl; ++j) {
					String recipient = in.next();
					balances.put(recipient, balances.get(recipient)+moneyPerPerson);
				}
				balances.put(giver, balances.get(giver)-moneyPerPerson*nPpl);
			}
			for(int i=0; i<NP; ++i)
				out.println(names[i]+" "+balances.get(names[i]));
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