/*
 *将一个文本文件倒置读出；
 *将用户从键盘输入的10个整数存入文件，然后顺序读出。 
 */
import java.io.*;
import java.util.*;
import java.nio.ByteBuffer; 

class IOEx {
	public static void main(String[] args) 
		throws IOException 
	{
		/*从键盘读入要打开的文件名*/
		String path;
		System.out.println("输入要打开文件的文件名：");
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		path = in.readLine();
		
		/*倒置读出文件*/
		RandomAccessFile file = new RandomAccessFile(path, "r");
		int lenth = (int)file.length();
		ByteBuffer bb = ByteBuffer.allocate(lenth);

		file.getChannel().read(bb);
		byte[] strOrigin = new byte[lenth];
		byte[] strReversed = new byte[lenth];

		strOrigin = bb.array();
		for(int i = 0; i < lenth; i++) {
			strReversed[i] = strOrigin[lenth - 1 - i];
		}
		file.close();
		
		/*从键盘读入10个整数存入数组*/
		int[] nums = new int[10]; 
		System.out.println("\n请输入10个整数:");
        
		Scanner sc = new Scanner(System.in);
        for (int i=0; i < 10; i++) {
        	nums[i] = sc.nextInt();
        }
        sc.close();
        
		/*将数组中的10个整数写入文件out.txt*/
        FileOutputStream fout = new FileOutputStream("out.txt");
        PrintStream fos = new PrintStream(fout);
		for (int i=0; i < 10; i++) {
			fos.println(nums[i]);
		}
		fout.close();
		
		/*将out.txt文件中10个整数读出并输出*/
		FileInputStream fin = new FileInputStream("out.txt");
		Scanner sc2 = new Scanner(fin);
		System.out.println("文件中的10数是:");
        for (int i=0; i < 10; i++) {
        	System.out.print(sc2.nextInt());
        	System.out.print(" ");
        }
        sc2.close();
	}
}