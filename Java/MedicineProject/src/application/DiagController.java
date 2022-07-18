package application;
//
//import java.io.BufferedReader;
//import java.io.FileReader;
import java.io.IOException;
import java.net.URL;
import java.util.HashMap;
import java.util.ResourceBundle;


import compoments.Diagnosis;
import compoments.WriteAndReadFile;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextArea;
import javafx.scene.control.Alert.AlertType;
import javafx.stage.Stage;

public class DiagController implements Initializable {

	@FXML private ChoiceBox<String>  myChoiceBoxPatient;
	private String choiceBox;
	private Diagnosis dia, concerns;
	@FXML private TextArea YourTextArea1;
	@FXML private TextArea YourTextArea2;
	//private String path = "C:/Users/roniz/eclipse-workspace/MedicineProject/src/compoments/Diagnosis.txt";
	private WriteAndReadFile W_R_F = new WriteAndReadFile("C:/Users/roniz/eclipse-workspace/MedicineProject/src/compoments/Patients.txt");

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

	public void DiagnosisOfPatient(ActionEvent event) {
		YourTextArea1.clear();
		YourTextArea2.clear();
		try {
			choiceBox = myChoiceBoxPatient.getValue();
			if(choiceBox == null) 
				throw new Exception("לא בחרת מטופל");
			dia = new Diagnosis(DetalisController.dict_Patient.get(choiceBox));	
			dia.start();
			concerns = dia;
			DetalisController.dict_Patient.get(choiceBox).setDia(new HashMap<String, String>(dia.dises()));
			concerns.clearTemp();
			DetalisController.dict_Patient.get(choiceBox).setCon(new HashMap<String, String>(concerns.dises()));
			W_R_F.WriteFile(DetalisController.dict_Patient);
			print(choiceBox);

		}catch(Exception e){
			Alert alert = new Alert(AlertType.WARNING, e.getMessage() , ButtonType.CANCEL);
			alert.showAndWait();
		}
	}

	
	public void print(String id) {
		YourTextArea1.appendText(DetalisController.dict_Patient.get(id).toString());
		YourTextArea2.appendText(DetalisController.dict_Patient.get(id).printDia() + DetalisController.dict_Patient.get(id).printCon());
	}
	@Override
	public void initialize(URL arg0, ResourceBundle arg1) {
		for(String key: DetalisController.dict_Patient.keySet())
			myChoiceBoxPatient.getItems().addAll(key);
	}
}
