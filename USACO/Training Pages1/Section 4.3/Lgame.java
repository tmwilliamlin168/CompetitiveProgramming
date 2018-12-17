package section_4_3;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: lgame
*/
import java.io.*;
import java.util.*;

public class lgame {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "lgame";
	
	static int[] lVals = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};
	static List<WordData> dict = new ArrayList<WordData>();
	
	static class Solver {
		Solver() {
			String s=in.next();
			int[] cnt = new int[26];
			for(char c : s.toCharArray())
				++cnt[c-'a'];
			int max=0;
			List<WordData> maxWords = new ArrayList<WordData>(), usableDict = new ArrayList<WordData>();
			for(WordData word : dict) {
				boolean usable=true;
				for(int i=0; i<26; ++i) {
					if(word.cnt[i]>cnt[i]) {
						usable=false;
						break;
					}
				}
				if(usable)
					usableDict.add(word);
			}
			System.out.println(usableDict.size());
			for(int i=0; i<usableDict.size(); ++i) {
				WordData word1=usableDict.get(i);
				for(int j=i+1; j<usableDict.size(); ++j) {
					WordData pair = new WordData(word1.s+" "+usableDict.get(j).s);
					boolean usable=true;
					for(int k=0; k<26; ++k) {
						if(pair.cnt[k]>cnt[k]) {
							usable=false;
							break;
						}
					}
					if(usable) {
						if(pair.value>max) {
							max=pair.value;
							maxWords.clear();
						}
						if(pair.value>=max)
							maxWords.add(pair);
					}
				}
				if(word1.value>max) {
					max=word1.value;
					maxWords.clear();
				}
				if(word1.value>=max)
					maxWords.add(word1);
			}
			out.println(max);
			for(WordData word : maxWords)
				out.println(word.s);
		}
	}
	
	static class WordData {
		String s;
		int[] cnt = new int[26];
		int value;
		WordData(String s) {
			this.s=s;
			for(char c : s.toCharArray())
				if(c!=' ')
					++cnt[c-'a'];
			for(int i=0; i<26; ++i)
				value+=cnt[i]*lVals[i];
		}
	}
	
	static void preprocess() throws Exception {
		Reader dictIn = new Reader(stdin?"C:\\Users\\20113766\\Desktop\\lgame.dict":"lgame.dict");
		String word;
		while(!(word=dictIn.next()).equals("."))
			dict.add(new WordData(word));
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