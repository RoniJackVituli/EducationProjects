module MedicineProject {
	requires javafx.controls;
	requires javafx.fxml;
	requires java.desktop;
	requires javafx.graphics;
	requires junit;
	exports tests;
	
	opens application to javafx.graphics, javafx.fxml;
}
