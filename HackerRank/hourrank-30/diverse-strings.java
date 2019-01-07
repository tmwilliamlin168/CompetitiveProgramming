import java.io.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		List<Integer>[] ls = new List[26];
		ls[0]=Arrays.asList(0);
		for(int i=1; i<26; ++i) {
			ls[i] = new ArrayList<Integer>(Arrays.asList(0, 0));
			for(int a : ls[i-1]) {
				ls[i].add(a+1);
				if(a==0)
					ls[i].add(0);
			}
			ls[i].add(0);
		}
		for(int tests=in.nextInt(); tests>0; --tests) {
			int n=in.nextInt(), k=in.nextInt();
			if(ls[k-1].size()>n) {
				out.println("NONE");
				continue;
			}
			for(int i=0; i<n-ls[k-1].size(); ++i)
				out.print('a');
			for(int i=0; i<ls[k-1].size(); ++i)
				out.print((char)('a'+ls[k-1].get(i)));
			out.println();
		}
		out.close();
	}
	
	static class Reader {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
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
