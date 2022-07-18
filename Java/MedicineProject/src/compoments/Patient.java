package compoments;

import java.util.HashMap;
import java.util.Map;


public class Patient extends Person{

	
	private HashMap<String, String[]> indices = new HashMap<String, String[]>();
	private HashMap<String, String> dia = new HashMap<String, String>();
	private HashMap<String, String> concerns = new HashMap<String, String>();
	
	//Question for patient
	private boolean isSmoke ;
	private boolean isTired; 
	private boolean heart_diseases;
	private boolean stomach_pain;
	private boolean isDrinkingAlcohol;
	private boolean isDrugSensitive;
	private boolean isPregnant;
	
	
	public Patient(String id , String name, float age, String gender, String group) {
		super(id, name, age, gender, group);
	}
	

	
	//Question Set&Get;
	public boolean isSmoke() {
		return isSmoke;
	}

	public boolean isTired() {
		return isTired;
	}

	public boolean isHeart_diseases() {
		return heart_diseases;
	}

	public boolean isStomach_pain() {
		return stomach_pain;
	}

	public boolean isDrinkingAlcohol() {
		return isDrinkingAlcohol;
	}

	public boolean isDrugSensitive() {
		return isDrugSensitive;
	}

	public boolean isPregnant() {
		return isPregnant;
	}

	public void setSmoke(boolean isSmoke) {
		this.isSmoke = isSmoke;
	}

	public void setTired(boolean isTired) {
		this.isTired = isTired;
	}

	public void setHeart_diseases(boolean heart_diseases) {
		this.heart_diseases = heart_diseases;
	}

	public void setStomach_pain(boolean stomach_pain) {
		this.stomach_pain = stomach_pain;
	}

	public void setDrinkingAlcohol(boolean isDrinkingAlcohol) {
		this.isDrinkingAlcohol = isDrinkingAlcohol;
	}

	public void setDrugSensitive(boolean isDrugSensitive) {
		this.isDrugSensitive = isDrugSensitive;
	}

	public void setPregnant(boolean isPregnant) {
		this.isPregnant = isPregnant;
	}//end Questions Set&Get


	
	
	public HashMap<String, String[]> getIndices() {
		return indices;
	}
	
	

	public void setDia(HashMap<String, String> dia) {
		this.dia = dia;
	}
	
	public void setCon(HashMap<String, String> con) {
		this.concerns = con;
	}
	

	public String printDia() {
		String diagnosis = new String();
		for(Map.Entry<String, String> entry : dia.entrySet())
			diagnosis += "Disease: " + entry.getKey() + "\n" + "Treatment: " + entry.getValue() + "\n\n";
		return "\n\n" + "-----------------Diagnosis-----------------\n"
					+ diagnosis;
	}
	
	public String printCon() {
		String con = new String();
		for(Map.Entry<String, String> entry : concerns.entrySet())
			con += "Disease: " + entry.getKey() + "\n" + "Treatment: " + entry.getValue() + "\n\n";
		
		return "\n\n" + "-----------------חששות-----------------\n"
					+ con;
	}
	
	@Override
	public String toString() {
		String indice = new String();
		for(Map.Entry<String, String[]> entry : indices.entrySet())
			indice += entry.getKey() + ":[Status: " + entry.getValue()[0] +", " +entry.getValue()[1] +"]"+"\n";	
		return super.toString() 
				+"\n\n-----------------Indices-----------------\n\n"
				+ indice;
	}
	
	
	
	
	
	
	
	
	
	
	
}


