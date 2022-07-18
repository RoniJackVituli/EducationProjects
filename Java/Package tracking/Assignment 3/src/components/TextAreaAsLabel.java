package components;
import java.awt.Desktop;
import java.io.File;
import javax.swing.*;

@SuppressWarnings("serial")
public class TextAreaAsLabel extends JPanel {

	public TextAreaAsLabel() {}


	public void TEXT(){
		try  
		{  
			//constructor of file class having file as argument  
			File file = new File("C:/Users/roniz/eclipse-workspace/HW2_solution/src/components/tracking.txt");   
			if(!Desktop.isDesktopSupported())//check if Desktop is supported by Platform or not  
			{  
				System.out.println("not supported");  
				return;  
			}  
			Desktop desktop = Desktop.getDesktop();  
			if(file.exists())         //checks file exists or not  
				desktop.open(file);              //opens the specified file  
		}  
		catch(Exception e)  
		{  
			e.printStackTrace();  
		}  

	}
}