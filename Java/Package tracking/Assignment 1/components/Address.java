package components;

/**
 * The Address class 
 * represents the address of the sender or recipient
 * 
 * The address consists of two things:

1. zip -> The zip determines the branch to which the address belongs
2. Street number -> Street number, can have values of only 6 digits.

 * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
 * 
 * */



public class Address {
	private int zip;
	private int street;
	
	public Address(int zip, int street) {
		this.zip = zip;
		this.street = street;
	}
	
	public int getZip() {
		return zip;
	}
	
	@Override
	public String toString() {
		return " " + zip + "-" + street;
	}

	public void setZip(int zip) {
		this.zip = zip;
	}

	public int getStreet() {
		return street;
	}
	
	
	
}
