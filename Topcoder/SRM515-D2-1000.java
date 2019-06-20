/*
	- Iterate over the first time that a customer appears
*/

import java.util.*;

public class NewItemShopTwo {
    Buy[] buys;
    
    public double getMaximum(String[] customers) {
        double ans=0;
        buys = new Buy[26];
        gb(customers[0], 0);
        gb(customers[1], 1);
        for(int i=0; i<24; ++i) {
            if(buys[i]==null)
            	continue;
            double e2=0, p2=0;
            for(int j=i+1; j<26; ++j) {
				if(buys[j]!=null&&buys[j].i!=buys[i].i) {
                    e2+=buys[j].c*buys[j].p;
                    p2+=buys[j].p;
                }
            }
            if(p2<1e-4)
                continue;
            e2/=p2;
            ans+=buys[i].p*p2*Math.max(buys[i].c, e2);
        }
        return ans;
    }
    
    void gb(String cust, int ci) {
        buys[24+ci] = new Buy(0, ci, 1);
        StringTokenizer st = new StringTokenizer(cust, ", ");
        while(st.hasMoreTokens()) {
            int t=Integer.parseInt(st.nextToken()), c=Integer.parseInt(st.nextToken());
            double p=Integer.parseInt(st.nextToken())/100.0;
            buys[t] = new Buy(c, ci, p);
            buys[24+ci].p-=p;
        }
    }
    
    class Buy {
        int c, i;
        double p;
        Buy(int c, int i, double p) {
            this.c=c;
            this.i=i;
            this.p=p;
        }
    }
}
