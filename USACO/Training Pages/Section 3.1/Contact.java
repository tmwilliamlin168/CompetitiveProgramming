package section_3_1;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: contact
*/
import java.io.*;
import java.util.*;

public class contact {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "contact";
	
	static class Solver {
		Solver() {
			int a=in.nextInt(), b=in.nextInt(), n=in.nextInt();
			StringBuilder s = new StringBuilder();
			String line;
			while((line=in.next())!=null&&!line.equals("EOF"))
				s.append(line);
			int[] log = new int[1<<(b+1)], cnt = new int[1<<(b+1)], prev = new int[b];
			log[1]=0;
			for(int i=2; i<log.length; ++i)
				log[i]=log[i/2]+1;
			Arrays.fill(prev, -1);
			for(int i=0; i<s.length(); ++i) {
				prev[0]=1;
				for(int j=b-1; j>=0; --j) {
					if(prev[j]==-1)
						continue;
					prev[j]=2*prev[j]+s.charAt(i)-'0';
					++cnt[prev[j]];
					if(j+1<b)
						prev[j+1]=prev[j];
				}
			}
			TreeMap<Integer, List<Integer>> freqMap = new TreeMap<Integer, List<Integer>>();
			for(int i=1<<a; i<cnt.length; ++i) {
				if(freqMap.containsKey(cnt[i]))
					freqMap.get(cnt[i]).add(i);
				else
					freqMap.put(cnt[i], new ArrayList<Integer>(Arrays.asList(i)));
			}
			for(int i=0; i<n; ++i) {
				Map.Entry<Integer, List<Integer>> entry = freqMap.pollLastEntry();
				if(entry==null||entry.getKey()==0)
					break;
				out.println(entry.getKey());
				Collections.sort(entry.getValue());
				for(int j=0; j<entry.getValue().size(); j+=6) {
					for(int k=0; k<6&&j+k<entry.getValue().size(); ++k) {
						if(k!=0)
							out.print(" ");
						int val=entry.getValue().get(j+k);
						for(int l=log[val]-1; l>=0; --l)
							out.print((val>>l)&1);
					}
					out.println();
				}
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
					String line=br.readLine();
					if(line==null)
						return null;
					st = new StringTokenizer(line);
				} catch(Exception e) {}
			}
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
	}
}