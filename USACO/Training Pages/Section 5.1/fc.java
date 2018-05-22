package section_5_1;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: fc
*/
import java.io.*;
import java.util.*;

public class fc {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "fc";
	
	static class Solver {
		Solver() {
			int n=in.nextInt();
			final Pt[] pts = new Pt[n];
			for(int i=0; i<n; ++i)
				pts[i]=new Pt(in.nextDouble(), in.nextDouble());
			int minI=0;
			for(int i=1; i<n; ++i)
				if(pts[i].y<pts[minI].y||(pts[i].y==pts[minI].y&&pts[i].x<pts[minI].x))
					minI=i;
			Pt a=pts[0];
			pts[0]=pts[minI];
			pts[minI]=a;
			Arrays.sort(pts, 1, n, new Comparator<Pt>() {
				public int compare(Pt pt1, Pt pt2) {
					return Double.compare(crossProductZ(pts[0], pt1, pt2), 0);
				}
			});
			//for(Pt pt : pts)
			//	System.out.println(pt.x+" "+pt.y);
			List<Pt> convexHull = new ArrayList<Pt>();
			convexHull.add(pts[0]);
			for(int i=1; i<n; ++i) {
				while(convexHull.size()>=2&&crossProductZ(convexHull.get(convexHull.size()-2), convexHull.get(convexHull.size()-1), pts[i])>=0)
					convexHull.remove(convexHull.size()-1);
				convexHull.add(pts[i]);
			}
			//System.out.println(convexHull.size());
			double ans=0;
			for(int i=0; i<convexHull.size(); ++i)
				ans+=Math.hypot(convexHull.get(i).x-convexHull.get((i+1)%convexHull.size()).x, convexHull.get(i).y-convexHull.get((i+1)%convexHull.size()).y);
			out.printf("%.2f\n", ans);
		}
		double crossProductZ(Pt p1, Pt p2, Pt p3) {
			return (p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x);
		}
		class Pt {
			double x, y;
			Pt(double x, double y) {
				this.x=x;
				this.y=y;
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
					st = new StringTokenizer(br.readLine());
				} catch(Exception e) {}
			}
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
		double nextDouble() {
			return Double.parseDouble(next());
		}
	}
}