package section_4_4;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: shuttle
*/
import java.io.*;
import java.util.*;

public class shuttle {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "shuttle";
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			char[] board = new char[2*n+1];
			for(int i=0; i<n; ++i)
				board[i]='W';
			for(int i=n+1; i<2*n+1; ++i)
				board[i]='B';
			List<Integer> moves = new ArrayList<Integer>();
			int emptyPos=n, printed=0;
			boolean lastMoveWhite=true;
			while(true) {
				//System.out.println(Arrays.toString(board));
				if(!lastMoveWhite) {
					if(emptyPos<2*n&&board[emptyPos+1]=='B'&&(emptyPos>0&&board[emptyPos-1]=='W'||board[0]!='W')) {
						moves.add(emptyPos+2);
						board[emptyPos]='B';
						++emptyPos;
						board[emptyPos]=0;
						lastMoveWhite=false;
						continue;
					}
					if(emptyPos<2*n-1&&board[emptyPos+2]=='B'&&(emptyPos>0&&board[emptyPos-1]=='W'||board[0]!='W')) {
						moves.add(emptyPos+3);
						board[emptyPos]='B';
						emptyPos+=2;
						board[emptyPos]=0;
						lastMoveWhite=false;
						continue;
					}
				}
				if(emptyPos>0&&board[emptyPos-1]=='W'&&(emptyPos<2*n&&board[emptyPos+1]=='B'||board[2*n]!='B')) {
					moves.add(emptyPos);
					board[emptyPos]='W';
					--emptyPos;
					board[emptyPos]=0;
					lastMoveWhite=true;
					continue;
				}
				if(emptyPos>1&&board[emptyPos-2]=='W'&&(emptyPos<2*n&&board[emptyPos+1]=='B'||board[2*n]!='B')) {
					moves.add(emptyPos-1);
					board[emptyPos]='W';
					emptyPos-=2;
					board[emptyPos]=0;
					lastMoveWhite=true;
					continue;
				}
				if(emptyPos<2*n&&board[emptyPos+1]=='B'&&(emptyPos>0&&board[emptyPos-1]=='W'||board[0]!='W')) {
					moves.add(emptyPos+2);
					board[emptyPos]='B';
					++emptyPos;
					board[emptyPos]=0;
					lastMoveWhite=false;
					continue;
				}
				if(emptyPos<2*n-1&&board[emptyPos+2]=='B'&&(emptyPos>0&&board[emptyPos-1]=='W'||board[0]!='W')) {
					moves.add(emptyPos+3);
					board[emptyPos]='B';
					emptyPos+=2;
					board[emptyPos]=0;
					lastMoveWhite=false;
					continue;
				}
				break;
			}
			for(int i=0; i<(moves.size()-1)/20+1; ++i, out.println())
				for(int j=i*20; j<Math.min(moves.size(), (i+1)*20); ++j)
					out.print((j%20==0?"":" ")+moves.get(j));
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