package section_3_3;
/*
ID: tmwilliamlin168
LANG: JAVA
TASK: shopping
*/
import java.io.*;
import java.util.*;

public class shopping {
	static boolean stdin = true;
	static Reader in;
	static PrintWriter out;
	static String filename = "shopping";
	
	static class Solver {
		int minPrice=Integer.MAX_VALUE, b;
		List<int[]> usefulOffers;
		
		Solver() {
			int s=in.nextInt();
			Offer[] offers = new Offer[s];
			for(int i=0; i<s; ++i) {
				offers[i] = new Offer();
				int n=in.nextInt();
				for(int j=0; j<n; ++j)
					offers[i].pairs.add(new Pair(in.nextInt(), in.nextInt()));
				offers[i].p=in.nextInt();
			}
			b=in.nextInt();
			if(b==0) {
				out.println(0);
				return;
			}
			usefulOffers = new ArrayList<int[]>();
			int[] products = new int[5], amounts = new int[5];
			for(int i=0; i<b; ++i) {
				products[i]=in.nextInt();
				amounts[i]=in.nextInt();
				int[] noffer = new int[6];
				noffer[i]=1;
				noffer[5]=in.nextInt();
				usefulOffers.add(noffer);
			}
			for(int i=0; i<s; ++i) {
				int[] noffer = new int[6];
				noffer[5]=offers[i].p;
				boolean useful1=true;
				for(Pair p : offers[i].pairs) {
					boolean useful2=false;
					for(int j=0; j<b; ++j) {
						if(p.a==products[j]) {
							noffer[j]=p.b;
							useful2=true;
							break;
						}
					}
					if(!useful2) {
						useful1=false;
						break;
					}
				}
				if(useful1)
					usefulOffers.add(noffer);
			}
			int[][][][][] dp = new int[6][6][6][6][6];
			for(int i1=0; i1<=5; ++i1) for(int i2=0; i2<=5; ++i2) for(int i3=0; i3<=5; ++i3)
				for(int i4=0; i4<=5; ++i4) for(int i5=0; i5<=5; ++i5)
					dp[i1][i2][i3][i4][i5]=(int)1e9;
			dp[0][0][0][0][0]=0;
			for(int i1=0; i1<=5; ++i1) for(int i2=0; i2<=5; ++i2) for(int i3=0; i3<=5; ++i3)
				for(int i4=0; i4<=5; ++i4) for(int i5=0; i5<=5; ++i5) for(int[] offer : usefulOffers)
					if(i1+offer[0]<=5&&i2+offer[1]<=5&&i3+offer[2]<=5&&i4+offer[3]<=5&&i5+offer[4]<=5)
						dp[i1+offer[0]][i2+offer[1]][i3+offer[2]][i4+offer[3]][i5+offer[4]]=
								Math.min(dp[i1][i2][i3][i4][i5]+offer[5], 
								dp[i1+offer[0]][i2+offer[1]][i3+offer[2]][i4+offer[3]][i5+offer[4]]);
			out.println(dp[amounts[0]][amounts[1]][amounts[2]][amounts[3]][amounts[4]]);
		}
		
		class Offer {
			List<Pair> pairs = new ArrayList<Pair>();
			int p;
		}
		
		class Pair {
			int a, b;
			Pair(int a, int b) {
				this.a=a;
				this.b=b;
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
	}
}