/*
	- At first, the program generates graphs of all sizes from 10 to 50
	- To ensure the graph is connected, start with a ring graph
	- Just increase the degree of each node by 2 by adding edges randomly
		- Sometimes it might be stuck where it can't add anymore edges without creating parallel edges, but some nodes don't have a degree of 4
		- Just maintain a counter and restart when too many iterations happen without adding edges
	- If A is the adjacency matrix, (A^k)[i][j] gives the number of paths from i to j with k edges
	- If the rows and columns of A were permuted into B, B^k would also be permuted the same way
	- To find the permutation, sort every row A^k and B^k and just try to match each row in A with each row in B
	- This won't work if the rows aren't distinct after sorting, just choose a different k or regenerate a graph
*/

import java.io.*;
import java.util.*;

public class Solution {
	static final Reader in = new Reader();
	static final PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		long[][][] mats=new long[41][][];
		int[] pow = new int[41];
		for(int ti=10; ti<=50; ++ti) {
			mats[ti-10] = new long[ti][ti];
			for(int i=0; i<ti; ++i)
				mats[ti-10][i][(i+1)%ti]=mats[ti-10][(i+1)%ti][i]=1;
			int[] deg = new int[ti];
			int trs=0;
			for(int i=0; i<ti&&trs<ti; ++i) {
				trs=0;
				while(deg[i]<2&&trs<ti) {
					int j=r(ti);
					if(j!=i&&mats[ti-10][i][j]==0&&deg[j]<2) {
						mats[ti-10][i][j]=mats[ti-10][j][i]=1;
						++deg[i];
						++deg[j];
					}
					++trs;
				}
			}
			if(trs<ti) {
				long[][] pa = new long[ti][], pa2 = new long[ti][];
				for(int i=0; i<ti; ++i)
					pa[i]=Arrays.copyOf(mats[ti-10][i], ti);
				for(int it=0; it<ti&&pow[ti-10]==0; ++it) {
					pa=matMultM(mats[ti-10], pa);
					for(int i=0; i<ti; ++i) {
						pa2[i]=Arrays.copyOf(pa[i], ti);
						Arrays.sort(pa2[i]);
					}
					boolean ok=true;
					for(int i=0; i<ti&&ok; ++i)
						for(int j=i+1; j<ti&&ok; ++j)
							ok=!Arrays.equals(pa2[i], pa2[j]);
					if(ok)
						pow[ti-10]=it+2;
				}
			}
			if(pow[ti-10]==0)
				--ti;
		}
		int tt=in.nextInt();
		for(int ti=1; ti<=tt; ++ti) {
			int l=in.nextInt(), r=in.nextInt();
			if(l==-1)
				return;
			out.println(l);
			for(int i=0; i<l; ++i)
				for(int j=i+1; j<l; ++j)
					if(mats[l-10][i][j]>0)
						out.println((i+1)+" "+(j+1));
			out.flush();
			long[][] mat1 = new long[l][l], mat2 = new long[l][l], mat3 = new long[l][l];
			in.nextInt();
			for(int i=0; i<l*2; ++i) {
				int u=in.nextInt()-1, v=in.nextInt()-1;
				mat2[u][v]=mat2[v][u]=mat3[u][v]=mat3[v][u]=1;
			}
			for(int i=0; i<l; ++i)
				mat1[i]=Arrays.copyOf(mats[l-10][i], l);
			for(int it=0; it<pow[l-10]-1; ++it) {
				mat1=matMultM(mats[l-10], mat1);
				mat2=matMultM(mat3, mat2);
			}
			for(int i=0; i<l; ++i) {
				Arrays.sort(mat1[i]);
				Arrays.sort(mat2[i]);
			}
			for(int i=0; i<l; ++i)
				for(int j=0; j<l; ++j)
					if(Arrays.equals(mat1[i], mat2[j]))
						out.print((j+1)+" ");
			out.println();
			out.flush();
		}
		out.close();
	}
	
	static long[][] matMultM(long[][] a, long[][] b) {
		long[][] product = new long[a.length][b[0].length];
		for(int i=0; i<a.length; ++i)
			for(int j=0; j<b[0].length; ++j)
				for(int k=0; k<b.length; ++k)
					product[i][j]+=a[i][k]*b[k][j];
		return product;
	}
	
	static int r(int n) {
		return (int)(Math.random()*n);
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
		int nextInt() {
			return Integer.parseInt(next());
		}
	}
}
