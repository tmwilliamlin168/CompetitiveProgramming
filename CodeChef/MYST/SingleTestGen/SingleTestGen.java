import java.io.*;
import java.util.*;

public class SingleTestGen {
	static final StdIn in = new StdIn();
	static final PrintWriter out = new PrintWriter(System.out);
	static int t, n;
	static double p;
	
	public static void main(String[] args) {
		t=in.nextInt();
		out.println(t);
		n=in.nextInt();
		p=in.nextDouble();
		for(int i=0; i<t; ++i)
			genTest();
		out.close();
	}
	
	static void genTest() {
		//Generate B's
		int[] b = new int[n];
		int bs;
		while(true) {
			bs=0;
			for(int i=0; i<n; ++i) {
				b[i]=gr(30, 1/p)+1;
				bs+=b[i];
			}
			if(bs>=2*n)
				break;
		}
		//Generate initial config
		int[][] bs1 = new int[n][], bs2 = new int[n][];
		List<Integer>[] adj = new List[n];
		for(int i=0; i<n; ++i) {
			adj[i] = new ArrayList<Integer>();
			bs1[i] = new int[b[i]];
			bs2[i] = new int[b[i]];
		}
		int[] cb = new int[n];
		while(true) {
			SCCFinder sccf = new SCCFinder(adj);
			boolean a=false;
			for(List<Integer> scc : sccf.sccs) {
				Collections.shuffle(scc);
				int c=-1;
				for(int i=0; c==-1; ++i)
					if(cb[scc.get(i)]<b[scc.get(i)])
						c=scc.get(i);
				for(int i : scc) {
					while(cb[i]<b[i]-(i==c?2:1)) {
						int d=r(n);
						adj[d].add(i);
						bs1[i][cb[i]++]=d;
						a=true;
					}
				}
			}
			if(a)
				continue;
			if(sccf.sccs.size()<=1)
				break;
			Collections.shuffle(sccf.sccs);
			sccf.sccs.add(sccf.sccs.get(0));
			for(int i=0; i<sccf.sccs.size()-1; ++i) {
				List<Integer> scc = sccf.sccs.get(i);
				int c=-1;
				for(int j=0; c==-1; ++j)
					if(cb[scc.get(j)]<b[scc.get(j)])
						c=scc.get(j);
				int d=sccf.sccs.get(i+1).get(0);
				adj[d].add(c);
				bs1[c][cb[c]++]=d;
			}
		}
		//Generate ideal config
		while(true) {
			for(int i=0; i<n; ++i)
				adj[i].clear();
			int[] d = new int[n];
			int ds=0;
			for(int i=0; i<n&&bs-ds>=2*n; ++i) {
				bs2[i] = new int[bs1[i].length];
				for(int j=0; j<bs2[i].length&&bs-ds>=2*n; ++j) {
					int[] p1 = new int[n];
					for(int k=0; k<n; ++k) {
						p1[k]=k;
						int l=r(k+1);
						p1[k]^=p1[l]^(p1[l]=p1[k]);
					}
					for(int k=0; k<n-1; ++k) {
						bs2[i][j]=p1[k];
						if(d[bs2[i][j]]<2&&bs2[i][j]!=i)
							break;
					}
					adj[bs2[i][j]].add(i);
					if(bs2[i][j]!=i)
						++d[bs2[i][j]];
					if(bs2[i][j]==i||d[bs2[i][j]]>2)
						++ds;
				}
			}
			if(bs-ds<2*n)
				continue;
			SCCFinder sccf = new SCCFinder(adj);
			if(sccf.sccs.size()<=1)
				break;
		}
		//Print everything (with permutation)
		int[] p1 = new int[n], p2 = new int[n];
		for(int i=1; i<n; ++i) {
			int j=r(i+1);
			p1[i]=p1[j];
			p1[j]=i;
		}
		for(int i=0; i<n; ++i)
			p2[p1[i]]=i;
		out.println(n);
		for(int i=0; i<n; ++i) {
			out.print(b[p1[i]]);
			for(int j=0; j<b[p1[i]]; ++j)
				out.print(" "+(p2[bs1[p1[i]][j]]+1));
			for(int j=0; j<b[p1[i]]; ++j)
				out.print(" "+(p2[bs2[p1[i]][j]]+1));
			out.println();
		}
	}
	
	static int r(int n) {
		return (int)(Math.random()*n);
	}
	
	static int gr(int n, double p) {
		for(int i=0; i<n-1; ++i)
			if(Math.random()<p)
				return i;
		return n-1;
	}
	
	static class SCCFinder {
		List<Integer>[] graph;
		List<List<Integer>> sccs = new ArrayList<List<Integer>>();
		int[] tin, low, who;
		Stack<Integer> st = new Stack<Integer>();
		boolean[] inst;
		int n, time=1;
		SCCFinder(List<Integer>[] graph) {
			this.graph=graph;
			n=graph.length;
			tin = new int[n];
			low = new int[n];
			who = new int[n];
			inst = new boolean[n];
			for(int i=0; i<n; ++i)
				if(tin[i]==0)
					dfs(i);
		}
		void dfs(int u) {
			tin[u]=low[u]=time++;
			st.push(u);
			inst[u]=true;
			for(int v : graph[u]) {
				if(tin[v]==0) {
					dfs(v);
					low[u]=Math.min(low[u], low[v]);
				} else if(inst[v])
					low[u]=Math.min(low[u], tin[v]);
			}
			if(tin[u]==low[u]) {
				List<Integer> scc = new ArrayList<Integer>();
				do {
					scc.add(st.peek());
					inst[st.peek()]=false;
					who[st.peek()]=sccs.size();
				} while(st.pop()!=u);
				sccs.add(scc);
			}
		}
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