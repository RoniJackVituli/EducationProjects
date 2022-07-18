package application;


import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.control.Alert.AlertType;
import javafx.stage.Stage;

public class LogInController {

	@FXML 
	private javafx.scene.control.Button closeButton;
	@FXML 
	private TextField userName;
	@FXML
	private PasswordField passName;
	@FXML 
	private TextField ID;
	
	private String name = null, pass = null, id = null;

	public void ok(ActionEvent e) {
	
		try {
			name = userName.getText();
			pass = passName.getText();
			id = ID.getText();	
			if(name == ""|| pass == ""  || id == "")
				throw new Exception("נא לא להשאיר שדות ריקים.");
			if(!isThereOnlyDigits(id))
				throw new Exception("ת.ז מכיל ספרות בלבד!");
			if(!ControllerMain.listuser.containsKey(id) || !ControllerMain.listuser.get(id)[0].equals(pass) || !ControllerMain.listuser.get(id)[1].equals(name)) {
				throw new Exception("שם משתמש או סיסמא או ת'ז לא נכונים, נסה שנית");
			}else {
				ControllerMain.flagLogIn = false;
				cancel(e);
				Alert alert = new Alert(AlertType.NONE, "Welcome " + name, ButtonType.OK);
				alert.showAndWait();
			}
		}catch (Exception e1) {
			ButtonType bt1 = new ButtonType("נסה שנית");
			ButtonType bt2 = new ButtonType("בטל");
			Alert alert = new Alert(AlertType.ERROR, e1.getMessage(), bt1 ,bt2);
			alert.showAndWait();
			if(alert.getResult() == bt1) {
				ID.clear();
				userName.clear();
				passName.clear();				
			}else {
				cancel(e);
			}
		}
	}
	
	private boolean isThereOnlyDigits(String id) {
		char [] chars = id.toCharArray();
		for(char c: chars) {
			if(!Character.isDigit(c))
				return false;
		}
		return true;
	}

	@FXML
	public void cancel(ActionEvent e) {
		Stage stage = (Stage) closeButton.getScene().getWindow();
		stage.close();
	}
}
