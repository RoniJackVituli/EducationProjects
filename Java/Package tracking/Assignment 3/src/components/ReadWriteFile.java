package components;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;



public class ReadWriteFile {
	private static ReadWriteFile readWriteFile; 

	private String Path = "C:/Users/roniz/eclipse-workspace/HW2_solution/src/components/tracking.txt";
	private File file = new File(Path);

	private ReadWriteFile() throws IOException{}

	public static ReadWriteFile getInstance() {
		if(readWriteFile == null) {
			synchronized (MainOffice.class) {
				if(readWriteFile == null) {
					try {
						readWriteFile = new ReadWriteFile();	
					}catch(IOException e) {
						System.out.println("Cant open the files");
					}
				}
			}
		}
		return readWriteFile;
	}


	public synchronized void writeFile(String s ,int i) {
		try {
			try (BufferedWriter bf = new BufferedWriter(new FileWriter(file,true))) {
				bf.write(i+ ") " +s + "\n");
				bf.newLine();
			}

		}catch (IOException e) {
			e.printStackTrace();

		}
	}

	public synchronized int readFile(Customer customer) {
		try {
			int count = 0;
			try(BufferedReader br = new BufferedReader(new FileReader(file))){
				String line;
				while((line = br.readLine()) != null) {
					if(line.isEmpty())
						continue;
					if(check(line, customer)) {
						count++;
					}
				}
				return count;
			}
		}catch (IOException e) {
			e.printStackTrace();
		}
		return 0;
	}

	private synchronized boolean check(String line , Customer customer) {
		String addressCustomer = customer.getAddress().toString() +",";
		String [] s = line.split(" ");
		String status = "DELIVERED,";		
		if(s[10].compareTo(status) == 0 && s[13].compareTo(addressCustomer) == 0)
			return true;			
		return false;
	}
	
}
