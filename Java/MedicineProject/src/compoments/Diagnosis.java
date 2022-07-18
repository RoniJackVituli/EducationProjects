package compoments;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map.Entry;

import application.Status;

public class Diagnosis {

	private HashMap<String, String> temp = new HashMap<>();
	private HashMap<String, Integer> diseases = new HashMap<>();
	private HashMap<String, Integer> indexDiseases = new HashMap<>();
	private String [] AllDiseases = {"אנמיה","דיאטה","דימום","שומנים בדם","תאי דם","הפרעה המטולוגית","הרעלת ברזל",
			"התייבשות","זיהום","חוסר בוויטמינים","מחלה ויראלית","מחלות בדרכי המרה","מחלת לב", "מחלת דם","מחלת כבד","מחלת כליה","מחסור בברזל","מחלות שריר","מעשנים","מחלת ריאות",
			"בלוטת התריס","סוכרת מבוגרים","סרטן","צריכה מוגברת של בשר","תת תזונה","תרופות שונות"};

	private Patient p;
	private String disease ,treatment;
	
	private WriteAndReadFile wr = new WriteAndReadFile("C:/Users/roniz/eclipse-workspace/MedicineProject/src/compoments/Diagnosis.txt");

	public Diagnosis(Patient p) {
		for(String s : AllDiseases) 
			diseases.put(s, 0);
		for(int i = 1; i <= AllDiseases.length ; i++)
			indexDiseases.put(AllDiseases[i-1], i);
		this.p = p;
	}

	public void clearTemp() {
		temp.clear();
	}
	
	
	public void start() {

		//WBC 
		if(!p.getIndices().get("WBC")[0].equals(Status.NORMAL.toString())) {
			if(p.getIndices().get("WBC")[0].equals(Status.HIGHT.toString())) {
				diseases.put("זיהום", diseases.get("זיהום") + 1);
				diseases.put("מחלת דם", diseases.get("מחלת דם") + 1);
				diseases.put("סרטן", diseases.get("סרטן") + 1);
			}else if(p.getIndices().get("WBC")[0].equals(Status.LOW.toString())) {
				diseases.put("מחלה ויראלית", diseases.get("זיהום") + 1);
				diseases.put("סרטן", diseases.get("סרטן") + 1);
			}	
		}
		//Neut
		if(!p.getIndices().get("NEUT")[0].equals(Status.NORMAL.toString())) {
			if(p.getIndices().get("NEUT")[0].equals(Status.HIGHT.toString())) {
				diseases.put("זיהום", diseases.get("זיהום") + 1);
			}else if(p.getIndices().get("NEUT")[0].equals(Status.LOW.toString())) {
				diseases.put("זיהום", diseases.get("זיהום") + 1);
				diseases.put("תאי דם", diseases.get("תאי דם") + 1);
				diseases.put("סרטן", diseases.get("סרטן") + 1);
			}
		}
		//Lymph
		if(!p.getIndices().get("Lymph")[0].equals(Status.NORMAL.toString())) {
			if(p.getIndices().get("Lymph")[0].equals(Status.HIGHT.toString())) {
				diseases.put("זיהום", diseases.get("זיהום") + 1);
				diseases.put("סרטן", diseases.get("סרטן") + 1);
			}else if(p.getIndices().get("Lymph")[0].equals(Status.LOW.toString())) {
				diseases.put("תאי דם", diseases.get("תאי דם") + 1);
			}
		}
		//RBC
		if(!p.getIndices().get("RBC")[0].equals(Status.NORMAL.toString())) {
			if(p.getIndices().get("RBC")[0].equals(Status.HIGHT.toString())) {
				diseases.put("מעשנים", diseases.get("מעשנים") + 1);
				diseases.put("מחלת ריאות", diseases.get("מחלת ריאות") + 1);
				diseases.put("תאי דם", diseases.get("תאי דם") + 1);
			}else if(p.getIndices().get("RBC")[0].equals(Status.LOW.toString())) {
				diseases.put("אנמיה", diseases.get("אנמיה") + 1);
				diseases.put("דימום", diseases.get("דימום") + 1);
			}
		}
		//HCT
		if(!p.getIndices().get("HCT")[0].equals(Status.NORMAL.toString())) {
			if(p.getIndices().get("HCT")[0].equals(Status.HIGHT.toString())) {
				diseases.put("מעשנים", diseases.get("מעשנים") + 1);
			}else if(p.getIndices().get("HCT")[0].equals(Status.LOW.toString())) {
				diseases.put("אנמיה", diseases.get("אנמיה") + 1);
				diseases.put("דימום", diseases.get("דימום") + 1);
			}
		}
		//Urea
		if(!p.getIndices().get("Urea")[0].equals(Status.NORMAL.toString())) {
			if(p.getIndices().get("Urea")[0].equals(Status.HIGHT.toString())) {
				diseases.put("מחלת כליה", diseases.get("מחלת כליה") + 1);
				diseases.put("התייבשות", diseases.get("התייבשות") + 1);
				diseases.put("דיאטה", diseases.get("דיאטה") + 1);
			}else if(p.getIndices().get("Urea")[0].equals(Status.LOW.toString())) {
				diseases.put("תת תזונה", diseases.get("תת תזונה") + 1);
				diseases.put("דיאטה", diseases.get("דיאטה") + 1);
				diseases.put("מחלת כבד", diseases.get("מחלת כבד") + 1);
			}
		}
		//hb
		if(!p.getIndices().get("Hb")[0].equals(Status.NORMAL.toString())) {
			if(p.getIndices().get("Hb")[0].equals(Status.LOW.toString())) {
				diseases.put("אנמיה", diseases.get("אנמיה") + 1);
				diseases.put("הפרעה המטולוגית", diseases.get("הפרעה המטולוגית") + 1);
				diseases.put("הרעלת ברזל", diseases.get("הרעלת ברזל") + 1);
				diseases.put("דימום", diseases.get("דימום") + 1);
			}
		}
		//Creatinine
		if(!p.getIndices().get("Creatinine")[0].equals(Status.NORMAL.toString())) {
			if(p.getIndices().get("Creatinine")[0].equals(Status.HIGHT.toString())) {
				diseases.put("מחלת כליה", diseases.get("מחלת כליה") + 1);
				diseases.put("מחלות שריר", diseases.get("מחלות שריר") + 1);
				diseases.put("צריכה מוגברת של בשר", diseases.get("צריכה מוגברת של בשר") + 1);
			}else if(p.getIndices().get("Creatinine")[0].equals(Status.LOW.toString())) {
				diseases.put("תת תזונה", diseases.get("תת תזונה") + 1);
				diseases.put("מחלות שריר", diseases.get("מחלות שריר") + 1);
			}
		}
		//Iron
		if(!p.getIndices().get("Iron")[0].equals(Status.NORMAL.toString())) {
			if(p.getIndices().get("Iron")[0].equals(Status.HIGHT.toString())) {
				diseases.put("הרעלת ברזל", diseases.get("הרעלת ברזל") + 1);
			}else if(p.getIndices().get("Iron")[0].equals(Status.LOW.toString())) {
				diseases.put("תת תזונה", diseases.get("תת תזונה") + 1);
				diseases.put("דימום", diseases.get("דימום") + 1);
			}
		}
		//HDL
		if(!p.getIndices().get("HDL")[0].equals(Status.NORMAL.toString())) {
			if(p.getIndices().get("HDL")[0].equals(Status.LOW.toString())) {
				diseases.put("מחלת לב", diseases.get("מחלת לב") + 1);
				diseases.put("שומנים בדם", diseases.get("שומנים בדם") + 1);
				diseases.put("סוכרת מבוגרים", diseases.get("סוכרת מבוגרים") + 1);
			}
		}
		//AP
		if(!p.getIndices().get("AP")[0].equals(Status.NORMAL.toString())) {
			if(p.getIndices().get("AP")[0].equals(Status.HIGHT.toString())) {
				diseases.put("מחלת כבד", diseases.get("מחלת כבד") + 1);
				diseases.put("מחלות בדרכי המרה", diseases.get("מחלות בדרכי המרה") + 1);
				diseases.put("בלוטת התריס", diseases.get("בלוטת התריס") + 1);
				diseases.put("תרופות שונות", diseases.get("תרופות שונות") + 1);
			}else if(p.getIndices().get("AP")[0].equals(Status.LOW.toString())) {
				diseases.put("תת תזונה", diseases.get("תת תזונה") + 1);
				diseases.put("חוסר בוויטמינים", diseases.get("חוסר בוויטמינים") + 1);
			}
		}

		// Q1
		if(p.isSmoke()) {
			diseases.put("מעשנים", diseases.get("מעשנים") + 1);
			if(!p.getIndices().get("WBC")[0].equals(Status.NORMAL.toString())) {   // גם ערכים גבוהים ונמוכים מעידים על סרטן
				diseases.put("סרטן", diseases.get("סרטן") + 1);

			}
			if(p.getIndices().get("NEUT")[0].equals(Status.LOW.toString())) {   
				diseases.put("סרטן", diseases.get("סרטן") + 1);

			}
			if(p.getIndices().get("Lymph")[0].equals(Status.HIGHT.toString())) { 
				diseases.put("סרטן", diseases.get("סרטן") + 1);

			}
			if(p.getIndices().get("RBC")[0].equals(Status.HIGHT.toString())) { 
				diseases.put("מעשנים", diseases.get("מעשנים") + 1);
				diseases.put("מחלת ריאות", diseases.get("מחלת ריאות") + 1);
			}
			if(p.getIndices().get("HCT")[0].equals(Status.HIGHT.toString())) { 
				diseases.put("מעשנים", diseases.get("מעשנים") + 1);

			}	
		}

		// Q2
		if(p.isTired()) {
			if(p.getIndices().get("Urea")[0].equals(Status.HIGHT.toString())) {   
				diseases.put("התייבשות", diseases.get("התייבשות") + 1);
			}
			if(p.getIndices().get("Hb")[0].equals(Status.LOW.toString())) {
				diseases.put("מחסור בברזל", diseases.get("מחסור בברזל") + 1);
			}
			if(p.getIndices().get("Creatinine")[0].equals(Status.LOW.toString())) {
				diseases.put("תת תזונה", diseases.get("תת תזונה") + 1);
			}
			if(p.getIndices().get("Iron")[0].equals(Status.LOW.toString())) {
				diseases.put("הרעלת ברזל", diseases.get("הרעלת ברזל") + 1);
				diseases.put("תת תזונה", diseases.get("תת תזונה") + 1);
			}
			if(p.getIndices().get("AP")[0].equals(Status.LOW.toString())) { 
				diseases.put("תת תזונה", diseases.get("תת תזונה") + 1);
				diseases.put("חוסר בוויטמינים", diseases.get("חוסר בוויטמינים") + 1);
			}


		}
		// Q3
		if(p.isHeart_diseases()) {
			if(p.getIndices().get("HDL")[0].equals(Status.LOW.toString())) { 
				diseases.put("מחלת לב", diseases.get("מחלת לב") + 1);

			}

		}
		// Q4
		if(p.isStomach_pain()) {
			if(p.getIndices().get("Creatinine")[0].equals(Status.HIGHT.toString())) { 
				diseases.put("מחלות שריר", diseases.get("מחלות שריר") + 1);

			}		
		}

		// Q5
		if(p.isDrinkingAlcohol()) {
			if(p.getIndices().get("Urea")[0].equals(Status.LOW.toString())) { 
				diseases.put("מחלת כבד", diseases.get("מחלת כבד") + 1);

			}
			if(p.getIndices().get("AP")[0].equals(Status.HIGHT.toString())) { 
				diseases.put("מחלת כבד", diseases.get("מחלת כבד") + 1);
			}

		}

		// Q6
		if(p.isDrugSensitive()) {
			if(p.getIndices().get("AP")[0].equals(Status.LOW.toString())) { 
				diseases.put("תרופות שונות", diseases.get("תרופות שונות") + 1);

			}
		}

		// Q7
		if(p.isPregnant() && p.getGender()=="WOMAN") {
			if(p.getIndices().get("Iron")[0].equals(Status.LOW.toString())) { 
				diseases.put("מחסור בברזל", diseases.get("מחסור בברזל") + 1);
			}
		}
	}

	public HashMap<String, String> dises() {
		int count = count();
		System.err.println("How many diese: " + count);
		if(count > 1) {
			for(int i = 0 ; i < count; i++) {
				disease = BringMax();
				treatment = MsgTreatment(indexDiseases.get(disease));
				temp.put(disease, treatment);
				System.err.println("dises is: " + disease);
				diseases.remove(disease);
				
			}
		}else if(count != 0){
			disease = BringMax();
			treatment = MsgTreatment(indexDiseases.get(disease));
			temp.put(disease, treatment);
			diseases.remove(disease);
		}else {
			temp.put("לא נמצאה מחלה", "המדדים שלך תקינים");
		}
		wr.WriteFileString(temp);
		return temp;	
	}

	private int count() {
		int maxValue = (Collections.max(diseases.values()));
		int count = 0;
		if(maxValue != 0) {
			for(Entry<String, Integer> entry : diseases.entrySet()) {
				if(entry.getValue() == maxValue)
					count++;
			}
			System.out.println("maxvalue = " + maxValue + ", countDieses = " + count);
			return count;
		}		
		System.out.println("maxvalue = " + maxValue + ", countDieses = " + count);
		return count;

	}

	private String BringMax() {
		int maxValue = (Collections.max(diseases.values()));
		for(Entry<String, Integer> entry : diseases.entrySet()) {
			if(entry.getValue() == maxValue)
				return entry.getKey();
		}
		return null;

	}


	private String MsgTreatment(int index) {
		switch (index) {
		case 1: 
			return "שני כדורי 10 מ'ג של B12 ביום למשך חודש.";
		case 2: 
			return "לתאם פגישה עם תזונאי";

		case 3: 
			return "להתפנות בדחיפות לבית החולים";

		case 4: 
			return "לתאם פגישה עם תזונאי, כדור 5 מ'ג של סימוביל ביום למשך שבוע.";

		case 5: 
			return "כדור 10 מ\"ג של B12 ביום למשך חודש\r\n"
			+ "כדור 5 מ\"ג של חומצה פולית ביום למשך חודש";

		case 6: 
			return " זריקה של הורמון לעידוד ייצור תאי הדם האדומים";

		case 7: 
			return "להתפנות לבית החולים";

		case 8: 
			return "מנוחה מוחלטת בשכיבה, החזרת נוזלים בשתייה";

		case 9: 
			return "אנטיביוטיקה ייעודית";

		case 10: 
			return "הפנייה לבדיקת דם לזיהוי הוויטמינים החסרים";

		case 11: 
			return "לנוח בבית";

		case 12: 
			return "הפנייה לטיפול כירורגי";

		case 13: 
			return "לתאם פגישה עם תזונאי";

		case 14: 
			return "שילוב של ציקלופוספאמיד וקורטיקוסרואידים";

		case 15: 
			return "הפנייה לאבחנה ספציפית לצורך קביעת טיפול";

		case 16: 
			return "איזון את רמות הסוכר בדם";

		case 17: 
			return " שני כדורי 10 מ\"ג של B12 ביום למשך חודש";

		case 18: 
			return "שני כדורי 5 מ\"ג של כורכום c3 של אלטמן ביום למשך חודש";

		case 19: 
			return "להפסיק לעשן";

		case 20: 
			return "להפסיק לעשן / הפנייה לצילום רנטגן של הריאות";

		case 21: 
			return "Propylthiouracil להקטנת פעילות בלוטת התריס";

		case 22: 
			return "התאמת אינסולין למטופל";

		case 23: 
			return "אנטרקטיניב";

		case 24: 
			return " לתאם פגישה עם תזונאי";

		case 25: 
			return "הפנייה לרופא המשפחה לצורך בדיקת התאמה בין התרופות";

		case 26: 
			return "לתאם פגישה עם תזונאי";

		default:
			throw new IllegalArgumentException("Unexpected value: " + index);
		}
	}

	@Override
	public String toString() {
		return temp.toString();
	}

}



