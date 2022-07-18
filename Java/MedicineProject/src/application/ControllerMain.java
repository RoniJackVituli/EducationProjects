package application;


import java.io.IOException;
import java.util.Hashtable;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonType;
import javafx.stage.Stage;
import javafx.scene.Node;

public class ControllerMain{
	public static boolean flagLogIn = true;
	public static Hashtable<String, String[] > listuser = new Hashtable<String, String[]>();

	public ControllerMain() {
		listuser.put("258963147", new String[]{"Sergey12!", "Sergey12"});
		listuser.put("321456987", new String[]{"Mohamed23#","Mohamed23"});
	}


	//right button
	public void LogIn(ActionEvent event) {
		if(flagLogIn) {
			try {
				FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("login.fxml"));
				Parent root1 = (Parent) fxmlLoader.load();
				Stage stage = new Stage();
				stage.setScene(new Scene(root1));
				stage.setTitle("התחברות");
				stage.setResizable(false);
				stage.show();  
			} catch (Exception e) {
				e.printStackTrace();
			}
		}else {
			Alert alert = new Alert(AlertType.WARNING, "אתה כבר מחובר למערכת.", ButtonType.CANCEL);
			alert.showAndWait();
		}
	}	

	//middle button
	public void addPatientDetalis(ActionEvent event) {
		if(!flagLogIn) {
			try {
				Parent root = FXMLLoader.load(getClass().getResource("filldetalis.fxml"));
				Stage stage = (Stage)((Node)event.getSource()).getScene().getWindow();
				Scene scene = new Scene(root);
				stage.setScene(scene);
				stage.setResizable(false);
				stage.show();

			}catch(IOException e) {
				e.printStackTrace();
			}

		}else {
			Alert alert = new Alert(AlertType.WARNING, "אנא, התחבר למערכת.", ButtonType.CANCEL);
			alert.showAndWait();
		}
	}

	//left button
	public void DiagnosisButton(ActionEvent event) {
		try {
			Parent root = FXMLLoader.load(getClass().getResource("Diagnosis.fxml"));
			Stage stage = (Stage)((Node)event.getSource()).getScene().getWindow();
			Scene scene = new Scene(root);
			stage.setScene(scene);
			stage.setResizable(false);
			stage.show();
		}catch(IOException e) {
			e.printStackTrace();
		}
	}
	


	
	

}