import java.io.*;
import java.util.*;

public class Judge {
	static final StdIn in = new StdIn();
	
	public static void main(String[] args) throws Exception {
		String sn = in.next(), tn = in.next();
		TreeMap<Integer, List<Double>> bn = new TreeMap<Integer, List<Double>>(), bp = new TreeMap<Integer, List<Double>>();
		double a=0;
		int b=0;
		long mt=0;
		for(File f : new File("../TestData/"+tn).listFiles()) {
			System.out.println("Running "+f.getName());
			long time=System.currentTimeMillis();
			Process pc = new ProcessBuilder("../Solutions/"+sn).redirectInput(f).redirectOutput(new File("../out.txt")).start();
			pc.waitFor();
			time=System.currentTimeMillis()-time;
			System.out.println("Took "+time+"ms");
			mt=Math.max(time, mt);
			System.out.println("Checking "+f.getName());
			pc = new ProcessBuilder("java", "-cp", "../Checker", "Checker").redirectInput(f).start();
			StdIn po = new StdIn(pc.getInputStream());
			double r=po.nextDouble();
			if(r<0) {
				System.out.println("Checker returned exit code "+po.nextInt());
				break;
			}
			po.close();
			System.out.println("Checker returned score of "+r);
			String[] fd=f.getName().split("_");
			int n=Integer.parseInt(fd[0]), p=Integer.parseInt(fd[1]);
			if(!bn.containsKey(n))
				bn.put(n, new ArrayList<Double>());
			bn.get(n).add(r);
			if(!bp.containsKey(p))
				bp.put(p, new ArrayList<Double>());
			bp.get(p).add(r);
			a+=r;
			++b;
		}
		System.out.println("Averages by n:");
		for(Map.Entry<Integer, List<Double>> e : bn.entrySet()) {
			double s=0;
			for(double d : e.getValue())
				s+=d;
			System.out.println("Average for n="+e.getKey()+": "+s/e.getValue().size());
		}
		System.out.println("Averages by p:");
		for(Map.Entry<Integer, List<Double>> e : bp.entrySet()) {
			double s=0;
			for(double d : e.getValue())
				s+=d;
			System.out.println("Average for p="+e.getKey()+": "+s/e.getValue().size());
		}
		System.out.println("Total average of "+a/b);
		System.out.println("Maximum time per test case: "+mt+"ms");
	}
	
	static class StdIn {
		final private int BUFFER_SIZE = 1 << 16;
		private DataInputStream din;
		private byte[] buffer;
		private int bufferPointer, bytesRead;
		public StdIn() {
			din = new DataInputStream(System.in);
			buffer = new byte[BUFFER_SIZE];
			bufferPointer = bytesRead = 0;
		}
		public StdIn(InputStream in) {
			try{
				din = new DataInputStream(in);
			} catch(Exception e) {
				throw new RuntimeException();
			}
			buffer = new byte[BUFFER_SIZE];
			bufferPointer = bytesRead = 0;
		}
		public String next() {
			int c;
			while((c=read())!=-1&&(c==' '||c=='\n'||c=='\r'));
			StringBuilder s = new StringBuilder();
			while (c != -1)
			{
				if (c == ' ' || c == '\n'||c=='\r')
					break;
				s.append((char)c);
				c=read();
			}
			return s.toString();
		}
		public String nextLine() {
			int c;
			while((c=read())!=-1&&(c==' '||c=='\n'||c=='\r'));
			StringBuilder s = new StringBuilder();
			while (c != -1)
			{
				if (c == '\n'||c=='\r')
					break;
				s.append((char)c);
				c = read();
			}
			return s.toString();
		}
		public int nextInt() {
			int ret = 0;
			byte c = read();
			while (c <= ' ')
				c = read();
			boolean neg = (c == '-');
			if (neg)
				c = read();
			do
				ret = ret * 10 + c - '0';
			while ((c = read()) >= '0' && c <= '9');

			if (neg)
				return -ret;
			return ret;
		}
		public int[] readIntArray(int n, int os) {
			int[] ar = new int[n];
			for(int i=0; i<n; ++i)
				ar[i]=nextInt()+os;
			return ar;
		}
		public long nextLong() {
			long ret = 0;
			byte c = read();
			while (c <= ' ')
				c = read();
			boolean neg = (c == '-');
			if (neg)
				c = read();
			do
				ret = ret * 10 + c - '0';
			while ((c = read()) >= '0' && c <= '9');
			if (neg)
				return -ret;
			return ret;
		}
		public long[] readLongArray(int n, long os) {
			long[] ar = new long[n];
			for(int i=0; i<n; ++i)
				ar[i]=nextLong()+os;
			return ar;
		}
		public double nextDouble() {
			double ret = 0, div = 1;
			byte c = read();
			while (c <= ' ')
				c = read();
			boolean neg = (c == '-');
			if (neg)
				c = read();
			do
				ret = ret * 10 + c - '0';
			while ((c = read()) >= '0' && c <= '9');
			if (c == '.')
				while ((c = read()) >= '0' && c <= '9')
					ret += (c - '0') / (div *= 10);
			if (neg)
				return -ret;
			return ret;
		}
		private void fillBuffer() throws IOException {
			bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
			if (bytesRead == -1)
				buffer[0] = -1;
		}
		private byte read() {
			try{
				if (bufferPointer == bytesRead)
					fillBuffer();
				return buffer[bufferPointer++];
			} catch(IOException e) {
				throw new RuntimeException();
			}
		}
		public void close() throws IOException {
			if (din == null)
				return;
			din.close();
		}
	}
}