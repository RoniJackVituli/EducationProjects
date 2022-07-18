package application;
	
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;


public class Main extends Application {

	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(Stage stage) {
		try {	
			Parent root = FXMLLoader.load(getClass().getResource("MainMedicine.fxml"));
			Scene scene = new Scene(root,960,740);
			stage.setScene(scene);
			stage.setTitle("ברוכים הבאים למערכת הרפואית");
			stage.setResizable(false);
			stage.show();
		}catch (Exception e) {
			e.printStackTrace();
		}
	}
}