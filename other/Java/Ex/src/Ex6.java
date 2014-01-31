/*
 * 通过键盘读一个字符，如果字符是数字，正常；否则，就抛异常。
 */
import java.io.IOException;

class NotANumberException extends Exception {
	public char name;
	public NotANumberException(char c) {
		super(c + "is not a number");
		name = c;
	}
}
class ExceptionEx{
	public static void main(String[] args) 
		throws NotANumberException, IOException
	{
		int c = 0;
		try
		{
			c = System.in.read();
			if (c < '0' || c > '9')
				throw new NotANumberException((char)c);
		} catch (NotANumberException e) {
			System.out.print(c + " is not a number.");
		}
		
	}
}