import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int[] d={0, 0, 0, 0, 2};
		String[][] a={{"23", "25", "27"}, {"segmented", "plain", "reeded"}, {"waling-waling", "tayabak", "kapa-kapa"}};
		String[] b={"1", "5", "10", "APPRECIATE YOUR MONEY"};
		for(int i=0; i<3; ++i) {
			String s=in.next();
			for(int j=0; j<3; ++j)
				if(a[i][j].equals(s))
					++d[j+1];
		}
		for(int i=0; d[i]<2; ++i)
			if(d[i+1]>1)
				System.out.println(b[i]);
	}
}
