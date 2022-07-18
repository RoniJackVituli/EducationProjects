package application;

import java.io.IOException;
import java.net.URL;
import java.util.HashMap;
import java.util.ResourceBundle;


import compoments.Patient;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.stage.Stage;

public class DetalisController implements Initializable{

	private Patient p;
	private Information info = new Information();
	//private ArrayList<Patient> listPatient = new ArrayList<Patient>();
	public static HashMap<String, Patient> dict_Patient = new HashMap<String, Patient>();
	boolean flagPatien = false;

	//Fields for patient.
	@FXML private TextField Fname;
	@FXML private TextField Lname;
	@FXML private TextField Age;
	@FXML private TextField ID;

	@FXML private ChoiceBox<String> myChoiceBoxGender;
	@FXML private ChoiceBox<String> myChoiceBoxGroup;

	@FXML private Label LabNeut;
	@FXML private Label LabLym;
	@FXML private Label LabHct;

	//CheckBox for the question.
	@FXML private CheckBox Q1; 
	@FXML private CheckBox Q2; 
	@FXML private CheckBox Q3;
	@FXML private CheckBox Q4; 
	@FXML private CheckBox Q5;
	@FXML private CheckBox Q6;
	@FXML private CheckBox Q7;

	//Indices of patient;

	@FXML private Slider NEUT;
	@FXML private Slider LYMPH;
	@FXML private Slider HCT;
	@FXML private TextField WBC;
	@FXML private TextField RBC;
	@FXML private TextField UREA;
	@FXML private TextField Hb;
	@FXML private TextField CREATININE;
	@FXML private TextField IRON;
	@FXML private TextField HDL;
	@FXML private TextField AP;

	private String ConfOne = "פרטי המטופל נקלטו בהצלחה, אנא ענה על השאלות.\nלחץ אוקי להמשיך.";
	private String ConfTwo = "השאלות נקלטו בהצלחה, אנא מלא את המדדים\nלחץ אוקי להמשיך.";
	private String firstName, lastName, fullName, id, choiceGender, choiceGroup;
	private float age;
	private int wbc, urea, iron, hdl, ap;
	private float rbc, hb, creatinine;
	int neut, lymph, hct;

	public void Confirmation(ActionEvent event) {
		int index = 0;
		try {
			firstName = Fname.getText();
			lastName = Lname.getText();
			id = ID.getText();
			if(!isThereOnlyLetters(firstName) ||!isThereOnlyLetters(lastName)) {
				index = 1;
				throw new Exception("שם מורכב מאותיות א'ב בלבד.");
			}
			fullName = firstName + " " + lastName;
			choiceGender = myChoiceBoxGender.getValue();
			choiceGroup = myChoiceBoxGroup.getValue();
			if(choiceGender == null) {
				index = 2;
				throw new Exception("נא לבחור מין");
			}
			else if(choiceGroup == null) {
				index = 3;
				throw new Exception("נא לבחור עדה");
			}
			index = 4;
			age =  Float.parseFloat(Age.getText());	
			checkTheDetalis(id, age);
			p = new Patient(id, fullName, age, choiceGender, choiceGroup);
			if(!ControllerMain.listuser.containsKey(p.getID()) && !dict_Patient.containsKey(p.getID())) {
				dict_Patient.put(p.getID(), p);
				flagPatien = true;
				Alert alert = new Alert(AlertType.NONE,ConfOne,ButtonType.OK);
				alert.showAndWait();
			}else {
				throw new Exception("תעודת זהות קיימת כבר במערכת.");
			}
		}catch (Exception e) {
			switch (index) {
			case 1: 
				Fname.clear();
				Lname.clear();
				break;
			case 2:
				myChoiceBoxGender.valueProperty().set(null);
				break;
			case 3:
				myChoiceBoxGroup.valueProperty().set(null);
				break;
			case 4:
				Age.clear();
				ID.clear();
				break;
			}
			Alert alert = new Alert(AlertType.WARNING, e.getMessage() , ButtonType.CANCEL);
			alert.showAndWait();
		}
	}

	public boolean isThereOnlyLetters(String name) {
		char [] chars = name.toCharArray();
		for(char c : chars) {
			if(!Character.isAlphabetic(c)) {
				return false;
			}
		}
		return true;
	}

	public void checkTheDetalis(String id , float age) throws Exception  {
		int ID = Integer.parseInt(id);
		int count = 0;
		if(age < 0 || age > 120)
			throw new Exception("Error Age");
		if(ID > 0) {
			while(ID != 0) {
				ID = ID/10;
				count++;
			}
			if (count != 9) {
				throw new Exception("ID should be with 9 digits."); 
			}
		}else{
			throw new Exception("ID cant not be negative.");
		}
	}


	public void BackToMain(ActionEvent event) {
		try {
			Parent root = FXMLLoader.load(getClass().getResource("MainMedicine.fxml"));
			Stage stage = (Stage)((Node)event.getSource()).getScene().getWindow();
			Scene scene = new Scene(root);
			stage.setScene(scene);
			stage.show();
		}catch(IOException e) {
			System.out.println(e);
		}
	}


	public void ConfQuestion(ActionEvent event) {
		boolean flag = true;
		if(flagPatien) {
			p.setSmoke(Q1.isSelected());
			p.setHeart_diseases(Q2.isSelected());
			p.setStomach_pain(Q3.isSelected());
			p.setDrinkingAlcohol(Q4.isSelected());
			p.setDrugSensitive(Q5.isSelected());
			p.setTired(Q6.isSelected());
			if(p.getGender() != "זכר") {
				p.setPregnant(Q7.isSelected());
			}else if(Q7.isSelected()) {
				Alert alert = new Alert(AlertType.ERROR, "גבר לא יכול להיות בהריון!" , ButtonType.CANCEL);
				alert.showAndWait();
				Q7.setSelected(false);
				p.setPregnant(Q7.isSelected());
				flag = false;
			}
			if(flag) {
				Alert alert = new Alert(AlertType.NONE, ConfTwo, ButtonType.OK);
				alert.showAndWait();
			}
		}else {
			Alert alert = new Alert(AlertType.WARNING, "תמלא את הפרטים של המטופל" , ButtonType.CANCEL);
			alert.showAndWait();
			clearCheckBox();
		}
	}

	public void clearCheckBox() {
		Q1.setSelected(false);
		Q2.setSelected(false);
		Q3.setSelected(false);
		Q4.setSelected(false);
		Q5.setSelected(false);
		Q6.setSelected(false);
		Q7.setSelected(false);
	}



	public void confIndices(ActionEvent event) {
		if(flagPatien) {
			int index = 0;
			CheckIndice check = new CheckIndice(p);
			try {
				//1
				wbc = Integer.parseInt(WBC.getText());
				if(check.wbc(wbc) == null || wbc < 0) {
					index = 1;
					throw new Exception("wbc ערך לא תקין.");
				}
				p.getIndices().put("WBC", new String[]{check.wbc(wbc).toString(), "Value: " + Integer.toString(wbc)});
				//2
				if(neut > 100 || neut < 0)
					throw new Exception("neut ערך לא תקין");
				p.getIndices().put("NEUT", new String[]{check.Neut(neut).toString(), "Value: " + Integer.toString(neut)});

				//3
				if(lymph > 100 || lymph < 0)
					throw new Exception("lymph ערך לא תקין");
				p.getIndices().put("Lymph", new String[]{check.Lymph(lymph).toString(), "Value: " + Integer.toString(lymph)});

				//4
				rbc = Float.parseFloat(RBC.getText());
				if(rbc < 0) {
					index = 2;
					throw new Exception("RBC ערך לא תקין");
				}
				p.getIndices().put("RBC", new String[]{check.RBC(rbc).toString(), "Value: " + Float.toString(rbc)});

				//5
				if(check.HCT(hct) == null || hct > 100 || hct < 0) 
					throw new Exception("HCT ערך לא תקין");
				p.getIndices().put("HCT", new String[]{check.HCT(hct).toString(),"Value: " + Integer.toString(hct)});

				//6
				urea = Integer.parseInt(UREA.getText());
				if(check.Urea(urea) == null || urea < 0) {
					index = 3;
					throw new Exception("Urea ערך לא תקין");
				}
				p.getIndices().put("Urea", new String[]{check.Urea(urea).toString(),"Value: " + Integer.toString(urea)});

				//7
				hb = Float.parseFloat(Hb.getText());
				if(check.Hb(hb) == null || hb < 0) {
					index = 4;
					throw new Exception("Hb ערך לא תקין");
				}
				p.getIndices().put("Hb", new String[]{check.Hb(hb).toString(),"Value: " + Float.toString(hb)});

				//8
				creatinine = Float.parseFloat(CREATININE.getText())/100;
				if(check.Creatinine(creatinine) == null || creatinine > 1 || creatinine < 0) {
					index = 5;
					throw new Exception("Creatinine ערך לא תקין");
				}
				p.getIndices().put("Creatinine", new String[]{check.Creatinine(creatinine).toString(),"Value: " +Float.toString(creatinine)});

				//9
				iron = Integer.parseInt(IRON.getText());
				if(check.Iron(iron) == null || iron < 0) {
					index = 6;
					throw new Exception("Iron ערך לא תקין");
				}
					p.getIndices().put("Iron", new String[]{check.Iron(iron).toString(),"Value: " +Integer.toString(iron)});

					//10
					hdl = Integer.parseInt(HDL.getText());
					if(check.HDL(hdl) == null || hdl < 0) {
						index = 7;
						throw new Exception("HDL ערך לא תקין");
					}
					p.getIndices().put("HDL", new String[]{check.HDL(hdl).toString(),"Value: " +Integer.toString(hdl)});

					//11
					ap = Integer.parseInt(AP.getText());
					if(ap < 0) {
						index = 8;
						throw new Exception("AP ערך לא תקין");
					}
					p.getIndices().put("AP", new String[]{check.AP(ap).toString(),"Value: " +Integer.toString(ap)});

					ClearFileds();
					Alert alert = new Alert(AlertType.NONE, "הפרטים מולאו בהצלחה, לחץ אוקיי לחזרה לתפריט." , ButtonType.OK);
					alert.setTitle("Success");
					alert.showAndWait();
					if(alert.getResult() == ButtonType.OK) {
						BackToMain(event);
					}
			}catch(Exception e) {
				Alert alert = new Alert(AlertType.WARNING, e.getMessage(), ButtonType.CANCEL);
				alert.showAndWait();
				ClearIndiceFileds(index);
			}
		}else {
			Alert alert = new Alert(AlertType.WARNING, "תמלא את הפרטים של המטופל" , ButtonType.CANCEL);
			alert.showAndWait();
			clearCheckBox();
		}


	}

	public void ClearIndiceFileds(int index) {
		switch (index) {
		case 1: 
			WBC.clear();
			break;
		case 2:
			RBC.clear();
			break;
		case 3:
			UREA.clear();
			break;
		case 4:
			Hb.clear();
			break;
		case 5:
			CREATININE.clear();
			break;
		case 6:
			IRON.clear();
			break;
		case 7:
			HDL.clear();
			break;
		case 8:
			AP.clear();
			break;
		case 9:
			WBC.clear();
			RBC.clear();
			UREA.clear();
			Hb.clear();
			CREATININE.clear();
			IRON.clear();
			HDL.clear();
			AP.clear();
			break;
		}


	}

	public void ClearFileds() {
		int index = 9;
		myChoiceBoxGender.valueProperty().set(null);
		myChoiceBoxGroup.valueProperty().set(null);
		Fname.clear();
		Lname.clear();
		Age.clear();
		ID.clear();
		ClearIndiceFileds(index);
		clearCheckBox();
	}


	public void info(ActionEvent event) {
		Button b = (Button)event.getSource();
		int num = Integer.parseInt(b.getAccessibleText());
		info.ShowCorrectInfo(num);	
	}


	@Override
	public void initialize(URL arg0, ResourceBundle arg1) {
		String [] genders = {"זכר" , "נקבה"};
		String [] group = {"מזרח", "אשכנז", "כהה עור"};
		myChoiceBoxGender.getItems().addAll(genders);
		myChoiceBoxGroup.getItems().addAll(group);

		NEUT.valueProperty().addListener(new ChangeListener<Number>() {

			@Override
			public void changed(ObservableValue<? extends Number> arg0, Number arg1, Number arg2) {
				neut = (int)NEUT.getValue();
				LabNeut.setText(Integer.toString(neut)+ "%");
			}
		});

		LYMPH.valueProperty().addListener(new ChangeListener<Number>() {

			@Override
			public void changed(ObservableValue<? extends Number> arg0, Number arg1, Number arg2) {	
				lymph = (int)LYMPH.getValue();	
				LabLym.setText(Integer.toString(lymph)+ "%");
			}
		});
		HCT.valueProperty().addListener(new ChangeListener<Number>() {

			@Override
			public void changed(ObservableValue<? extends Number> arg0, Number arg1, Number arg2) {
				hct = (int)HCT.getValue();
				LabHct.setText(Integer.toString(hct) + "%");

			}
		});

	}
}
