package application;

import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Alert.AlertType;

public class Information {

	private Alert alert;
	
	private final String MSG1 = "ערכים תקינים" + "\n" + "במבוגרים: 4500 - 11000." + "\n" + "בילדים: 5500 - 15500." + "\n"+ "בפעוטות: 6000 - 17500.";
	private final String MSG2 = "ערכים תקינים" + "\n" + "54% - 28%."; 
	private final String MSG3 = "ערכים תקינים" + "\n" + "52% - 36%.";
	private final String MSG4 = "ערכים תקינים" + "\n" + "4.5 - 6." ;
	private final String MSG5 = "ערכים תקינים" + "\n" + "גברים: 54% - 37%." + "\n" + "נשים: 47% - 33%.";
	private final String MSG6 = "ערכים תקינים" + "\n" + "17 - 43 מיליגרם" + "\n" + " אצל יוצאי עדות המזרח הערכים גבוהים בעוד 10%.";
	private final String MSG7 = "ערכים תקינים" + "\n" + "גברים: 12 - 18 מיליגרם" + "\n" + "נשים: 12 - 16 מיליגרם." + "\n" +"ילדים: 11.5 - 15.5 מיליגרם.";
	private final String MSG8 = "ערכים תקינים" + "\n" + "מבוגרים(18-59): 0.6 - 1." + "\n" + "קשישים(60+): 0.6 - 1.2." + "\n" + "ילדים(3-17): 0.5 - 1." + "\n" + "תינוקות(0-2): 0.2 - 0.5.";
	private final String MSG9 = "ערכים תקינים" + "\n" + "60 - 160." + "\n" + "אצל נשים נמוך ב-20%.";
	private final String MSG10 = "ערכים תקינים" + "\n" + "גברים: 29 - 62 מיליגרם." + "\n" + "נשים: 34 - 82 מיליגרם." + "\n" + "אצל כהה עור זה גבוה יותר ב-20%.";
	private final String MSG11 = "ערכים תקינים" + "\n" + "יוצאי עדות המזרח: 60 - 120 יחידות" + "\n" + "שאר האוכלוסיה: 30 - 90 יחידות.";
	
	
	public Information() {}
	
	public void ShowCorrectInfo(int num) {
		switch (num) {
		case 1:
			alert = new Alert(AlertType.NONE,MSG1,ButtonType.CLOSE);
			alert.setTitle("White Blood Cells");
			alert.showAndWait();
			break;
		case 2:
			alert = new Alert(AlertType.NONE,MSG2,ButtonType.CLOSE);
			alert.setTitle("Neutrophil");
			alert.showAndWait();
			break;
		case 3:
			alert = new Alert(AlertType.NONE,MSG3,ButtonType.CLOSE);
			alert.setTitle("Lymphocytes");
			alert.showAndWait();
			break;
		case 4:
			alert = new Alert(AlertType.NONE,MSG4,ButtonType.CLOSE);
			alert.setTitle("Red Blood Cells");
			alert.showAndWait();
			break;
		case 5:
			alert = new Alert(AlertType.NONE,MSG5,ButtonType.CLOSE);
			alert.setTitle("HCT");
			alert.showAndWait();
			break;
		case 6:
			alert = new Alert(AlertType.NONE,MSG6,ButtonType.CLOSE);
			alert.setTitle("Urea");
			alert.showAndWait();
			break;
		case 7:
			alert = new Alert(AlertType.NONE,MSG7,ButtonType.CLOSE);
			alert.setTitle("Hemoglobin");
			alert.showAndWait();
			break;
		case 8:
			alert = new Alert(AlertType.NONE,MSG8,ButtonType.CLOSE);
			alert.setTitle("Creatinine");
			alert.showAndWait();
			break;
		case 9:
			alert = new Alert(AlertType.NONE,MSG9,ButtonType.CLOSE);
			alert.setTitle("Iron");
			alert.showAndWait();
			break;
		case 10:
			alert = new Alert(AlertType.NONE,MSG10,ButtonType.CLOSE);
			alert.setTitle("High Density Lipoprotein");
			alert.showAndWait();
			break;
		case 11:
			alert = new Alert(AlertType.NONE,MSG11,ButtonType.CLOSE);
			alert.setTitle("Alkaline Phosphastase");
			alert.showAndWait();
			break;		
		default:
			throw new IllegalArgumentException("Unexpected value: " + num);
		}
		
	}
}
