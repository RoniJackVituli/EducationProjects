package compoments;


import java.io.BufferedWriter;
import java.io.File;

import java.io.FileWriter;
import java.io.IOException;

import java.util.HashMap;
import java.util.Map;

public class WriteAndReadFile {

	private String Path;
	public WriteAndReadFile(String path) {
		this.Path = path;
	}

	public void WriteFile(HashMap<String, Patient> dict_p) {
		File file = new File(Path);
		BufferedWriter bf = null;
		try {
			
			bf = new BufferedWriter(new FileWriter(file));
			for (Map.Entry<String, Patient> entry : dict_p.entrySet()) {
				bf.write(entry.getValue() + " " + entry.getValue().printDia() + " " + entry.getValue().printCon());
				bf.write("\n-----------------------------------------------------------------------\n");
				bf.newLine();
			}
		}catch (IOException e) {
			e.printStackTrace();
		}
		finally {
			try {
				bf.close();
			}catch (Exception e) {
				// TODO: handle exception
			}

		}
	}

	public void WriteFileString(HashMap<String, String> dict_p) {
		File file = new File(Path);
		BufferedWriter bf = null;
		try {
			bf = new BufferedWriter(new FileWriter(file));
			for (Map.Entry<String, String> entry : dict_p.entrySet()) {
				bf.write("Disease: " + entry.getKey() + "\nTreatment: " + entry.getValue());
				bf.write("\n---------------------------------------------------------------------\n");
				bf.newLine();
			}
			bf.flush();
		}catch (IOException e) {
			e.printStackTrace();
		}
		finally {
			try {
				bf.close();
			}catch (Exception e) {
				// TODO: handle exception
			}

		}
	}

}
