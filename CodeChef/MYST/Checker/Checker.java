import java.io.*;
import java.util.*;

public class Checker {
	static final StdIn in = new StdIn();
	static StdIn po;

	public static void main(String[] args) throws Exception {
		po = new StdIn(new FileInputStream(new File("../out.txt")));
		int t=in.nextInt();
		double score=0;
		for(int i=0; i<t; ++i)
			score+=chk();
		System.out.println(score/t);
	}

	static double chk() {
		int n=in.nextInt();
		int[][] ba = new int[n][n], tba = new int[n][n];
		for(int i=0; i<n; ++i) {
			int bi=in.nextInt();
			for(int j=0; j<bi; ++j)
				++ba[in.nextInt()-1][i];
			for(int j=0; j<bi; ++j)
				++tba[in.nextInt()-1][i];
		}
		int l=po.nextInt(), ca=0;
		if(l<0)
			fk(0);
		for(int i=0; i<l; ++i) {
			int a=po.nextInt()-1, b=po.nextInt()-1;
			if(b>=0) {
				if(ba[ca][b]<=0)
					fk(1);
				--ba[ca][b];
			}
			if(ba[ca][a]<=0)
				fk(2);
			ca=a;
			if(b>=0)
				++ba[ca][b];
		}
		if(!Arrays.deepEquals(ba, tba))
			fk(3);
		return (double)l/n;
	}

	static void fk(int ec) {
		System.out.println("-1 "+ec);
		System.exit(0);
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