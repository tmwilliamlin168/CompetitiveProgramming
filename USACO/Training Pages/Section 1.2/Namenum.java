package section_1_2;

/*
ID: tmwilliamlin168
LANG: JAVA
TASK: namenum
*/
import java.io.*;
import java.util.*;

public class namenum {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "namenum";
	
	static char[][] letters = {{}, {}, 
			{'A', 'B', 'C'}, 
			{'D', 'E', 'F'}, 
			{'G', 'H', 'I'}, 
			{'J', 'K', 'L'}, 
			{'M', 'N', 'O'}, 
			{'P', 'R', 'S'}, 
			{'T', 'U', 'V'}, 
			{'W', 'X', 'Y'}};
	static Set<String> names = new HashSet<String>();
	static String serial;
	static boolean hasName=false;
	
	static class Solver {
		Solver() {
			serial = in.next();
			recur("");
			if(!hasName)
				out.println("NONE");
		}
	}
	
	static void recur(String prev) {
		if(prev.length()==serial.length()) {
			if(names.contains(prev)) {
				out.println(prev);
				hasName=true;
			}
		} else {
			for(char letter : letters[serial.charAt(prev.length())-'0'])
				recur(prev+letter);
		}
	}
	
	static void preprocess() throws Exception {
		Reader dict = new Reader(stdin?"C:\\Users\\20113766\\Desktop\\dict.txt":"dict.txt");
		for(int i=0; i<4617; ++i)
			names.add(dict.next());
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