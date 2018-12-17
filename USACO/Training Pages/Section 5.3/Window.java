package section_5_3;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: window
*/
import java.io.*;
import java.util.*;

public class window {
	static final boolean stdin = true;
	static final String filename = "window";
	static Reader in;
	static PrintWriter out;
	
	static class Solver {
		Solver() {
			List<Window> windows = new ArrayList<Window>();
			List<Integer> xs = new ArrayList<Integer>(), ys = new ArrayList<Integer>();
			boolean[][] g = new boolean[123][123];
			while(true) {
				char qt=in.next().charAt(0), id=in.next().charAt(0);
				if(qt=='e')
					break;
				if(qt=='s') {
					int si=-1, t=0;
					while(windows.get(++si).id!=id);
					Window sw=windows.get(si);
					for(int i=si; i<windows.size(); ++i) {
						xs.add(windows.get(i).x1);
						ys.add(windows.get(i).y1);
						xs.add(windows.get(i).x2);
						ys.add(windows.get(i).y2);
					}
					Collections.sort(xs);
					Collections.sort(ys);
					int sx1=Collections.binarySearch(xs, sw.x1), sy1=Collections.binarySearch(ys, sw.y1), sx2=Collections.binarySearch(xs, sw.x2), sy2=Collections.binarySearch(ys, sw.y2);
					for(int i=si+1; i<windows.size(); ++i) {
						Window cw=windows.get(i);
						int x1=Collections.binarySearch(xs, cw.x1), y1=Collections.binarySearch(ys, cw.y1), x2=Collections.binarySearch(xs, cw.x2), y2=Collections.binarySearch(ys, cw.y2);
						for(int j=Math.max(x1, sx1); j<Math.min(x2, sx2); ++j)
							for(int k=Math.max(y1, sy1); k<Math.min(y2, sy2); ++k)
								g[j][k]=true;
					}
					for(int i=sx1; i<sx2; ++i)
						for(int j=sy1; j<sy2; ++j)
							if(!g[i][j])
								t+=(xs.get(i+1)-xs.get(i))*(ys.get(j+1)-ys.get(j));
					out.printf("%.3f\n", 100.0*t/(xs.get(sx2)-xs.get(sx1))/(ys.get(sy2)-ys.get(sy1)));
					for(int i=sx1; i<sx2; ++i)
						Arrays.fill(g[i], false);
					xs.clear();
					ys.clear();
				} else if(qt!='w') {
					Window window=null;
					for(int i=0; i<windows.size()&&window==null; ++i)
						if(windows.get(i).id==id)
							window=windows.get(i);
					windows.remove(window);
					if(qt=='t')
						windows.add(window);
					else if(qt=='b')
						windows.add(0, window);
				} else
					windows.add(new Window(id, in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt()));
			}
		}
		
		static class Window {
			char id;
			int x1, y1, x2, y2;
			Window(char id, int x1, int y1, int x2, int y2) {
				this.id=id;
				this.x1=Math.min(x1, x2);
				this.y1=Math.min(y1, y2);
				this.x2=Math.max(x1, x2);
				this.y2=Math.max(y1, y2);
			}
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
					String line=br.readLine();
					if(line==null)
						return "e";
					st = new StringTokenizer(line, "(,)");
				} catch(Exception e) {}
			}
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
	}
}