/*
 *在HelloWorld.java的基础上，定义常量/变量，并进行简单的逻辑/数学运算，生成JavaBase.java。 
 */


class JavaBase {
	public static void main(String[] args) {
		System.out.println("Hello Java!");
		
		final double π = 3.1415927;
		double radix = 5;
		double area = π * radix * radix;
		System.out.println(String.format("半径为5的圆的面积是%f", area));
	
		/*用位运算进行高低字节序转换*/
        long t = 123;
        t =  ((t & 0x000000ff) << 24) | ((t & 0x0000ff00) << 8)
           | ((t & 0x00ff0000) >> 8) | ((t & 0xff000000) >> 24);
		System.out.println(t);
	}
}