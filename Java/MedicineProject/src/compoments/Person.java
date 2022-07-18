package compoments;

public abstract class Person {
	private String ID;
	private	String fullName;
	private float age;
	private String gender;
	private String ethnic_group;
	

	public Person(String id, String name, float age, String gender, String group){
		this.ID = id;
		this.fullName = name;
		this.age = age;
		this.gender = gender;
		this.ethnic_group = group;
	}

	public String getGender() {
		return gender;
	}
	public String getID() {
		return ID;
	}

	public String getName() {
		return fullName;
	}

	public float getAge() {
		return age;
	}

	public void setID(String iD) {
		ID = iD;
	}

	public void setName(String name) {
		this.fullName = name;
	}

	public void setAge(float age) {
		this.age = age;
	}
	@Override
	public String toString() {
		return "-----------------------Personal Information------------------------\n\n" + 
				"Full Name: " + this.fullName + 
				"\nAge: " + this.age + 
				"\nID: " + this.ID + 
				"\nGender: " + gender + 
				"\nGroup: " + this.ethnic_group;
	}

	public String getEthnic_group() {
		return ethnic_group;
	}
	

}
