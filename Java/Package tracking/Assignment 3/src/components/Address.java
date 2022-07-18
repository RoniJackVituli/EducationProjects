package components;

public class Address {
	public final int zip;
	public final int street;
	
	public Address(int zip, int street ) {
		this.zip=zip;
		this.street=street;
	}

	public Object clone() {
		int zip = getZip();
		int street = getStreet();
		return new Address(zip, street);
	}
	
	
	
	public int getZip() {
		return zip;
	}

	public int getStreet() {
		return street;
	}
	
	@Override
	public String toString() {
		return zip + "-" + street;
	}	

}
