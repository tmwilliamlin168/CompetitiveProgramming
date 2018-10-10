public class ForumPostMedium {
	public int gt(String s) {
		char[] c=s.toCharArray();
		for(int i=0; i<8; ++i)
			c[i]-='0';
		return ((c[0]*10+c[1])*60+c[3]*10+c[4])*60+c[5]*10+c[6];
	}
	
	String getShownPostTime(String a, String b) {
		int c=gt(a)-gt(b);
		if(c<0)
			c+=24*60*60;
		if(c<60)
			return "few seconds ago";
		if(c/60<60)
			return c/60+" minutes ago";
		return c/3600+" hours ago";
	}
}
