import java.io.*;
import java.util.*;

public class Main {
	static final StdIn in = new StdIn();
	static int n, k, v;
	static boolean src, fr, fc;
	static int[][] ans;
	
	public static void main(String[] args) {
		n=in.nextInt();
		k=in.nextInt();
		v=in.nextInt();
		ans = new int[n][n];
		if(n==1) {
			qry(0, 0);
			System.out.println("2 -1 -1");
			return;
		}
		boolean[] ir = new boolean[n], ic = new boolean[n];
		for(int i=0; i<n; i+=2) {
			if(i+1>=n)
				--i;
			int a=qry(i, i), b=qry(i, i+1), c=qry(i+1, i), d=qry(i+1, i+1);
			ir[i]=a<b;
			ir[i+1]=c<d;
			ic[i]=a<c;
			ic[i+1]=b<d;
		}
		for(int i=0; i<n-1&&!src; ++i)
			src=ic[i]!=ic[i+1];
		if(src) {
			boolean[] tmp=ir;
			ir=ic;
			ic=tmp;
		}
		fc=!ic[0];
		if(fc) {
			for(int i=0; i<n-1-i; ++i) {
				boolean tmp=ir[i];
				ir[i]=ir[n-1-i];
				ir[n-1-i]=tmp;
			}
		}
		List<Integer> ps = new ArrayList<Integer>();
		for(int i=0; i<n; ++i)
			if(i==0||ir[i]!=ir[i-1])
				ps.add(i);
		ps.add(n);
		boolean a=true;
		for(int i=0; i<n-1&&a; ++i)
			a=ic[i]==ic[i+1];
		if(a) {
			for(int i=ps.size()-2; i>=0; --i) {
				if(qry(ps.get(i), ir[ps.get(i)]?0:n-1)>v)
					continue;
				if(!ir[ps.get(i)])
					fr=true;
				for(int j1=ps.get(i), j2=n-1; j1<ps.get(i+1); ++j1)
					while(j2>=0&&qry(j1, j2)>v)
						--j2;
				break;
			}
		} else {
			fr=!ir[0];
			int cc=-1;
			for(int i=1; i<n&&cc==-1; ++i)
				if(ic[i]!=ic[i-1])
					cc=i;
			if(qry(ps.get(1), cc-1)>v&&qry(ps.get(1)-1, cc)>v) {
				for(int i1=0, i2=cc-1; i1<ps.get(1); ++i1)
					while(i2>=0&&qry(i1, i2)>v)
						--i2;
				for(int i1=ps.get(1), i2=n-1; i1<n; ++i1)
					while(i2>=0&&qry(i1, i2)<v)
						--i2;
			} else {
				for(int i1=0, i2=cc; i1<ps.get(1); ++i1)
					while(i2<n&&qry(i1, i2)<v)
						++i2;
				for(int i1=ps.get(1), i2=0; i1<n; ++i1)
					while(i2<cc&&qry(i1, i2)>v)
						++i2;
			}
		}
		System.out.println("2 -1 -1");
	}
	
	static int qry(int i, int j) {
		if(fr)
			j=n-1-j;
		if(fc)
			i=n-1-i;
		if(src)
			i^=j^(j=i);
		if(ans[i][j]==0) {
			System.out.println("1 "+(i+1)+" "+(j+1));
			System.out.flush();
			ans[i][j]=in.nextInt();
			if(ans[i][j]==v) {
				System.out.println("2 "+(i+1)+" "+(j+1));
				System.exit(0);
			}
		}
		return ans[i][j];
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
