import java.util.Date;
import java.util.Calendar;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.Duration;

public class date {
	public static void main(String args[]) throws ParseException {
		//  规定读入日期的格式
		SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
		//	将字符串解析成日期Date格式
		Date date1 = simpleDateFormat.parse(args[0]);
		Date date2 = simpleDateFormat.parse(args[1]);
		//	计算天数差
		int days = (int)((date2.getTime() - date1.getTime()) / (1000*60*60*24));
		System.out.printf("%s与%s天数间隔为：", args[0], args[1]);
		System.out.println(days);
	}
}
