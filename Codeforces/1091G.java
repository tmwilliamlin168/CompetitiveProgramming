import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		BigInteger n = new BigInteger(in.next());
		List<BigInteger> f = new ArrayList<BigInteger>();
		f.add(n);
		for(int it=69; it-->0; ) {
			BigInteger x = new BigInteger(1000, new Random()).mod(n);
			out.println("sqrt "+x.multiply(x).mod(n));
			out.flush();
			x=x.add(new BigInteger(in.next()));
			List<BigInteger> nf = new ArrayList<BigInteger>();
			for(BigInteger fi : f) {
				BigInteger g=x.gcd(fi);
				if(g.compareTo(BigInteger.ONE)>0)
					nf.add(g);
				g=fi.divide(g);
				if(g.compareTo(BigInteger.ONE)>0)
					nf.add(g);
			}
			f=nf;
		}
		out.print("! "+f.size());
		for(BigInteger fi : f)
			out.print(" "+fi);
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
	}
}
