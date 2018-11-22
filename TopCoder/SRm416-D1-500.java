import java.util.*;

public class CustomDice {
	static final int M=(int)1e9+7;
	int[] dp = new int[5999980];
	
	public int countDice(int m) {
		if(m<4)
			return 0;
		Arrays.fill(dp, 30);
		for(int i=1; i<=6; ++i)
			for(int j=i; j<=6*m-21; ++j)
				dp[j]=(dp[j]+dp[j-i])%M;
		return dp[6*m-21];
	}
}
