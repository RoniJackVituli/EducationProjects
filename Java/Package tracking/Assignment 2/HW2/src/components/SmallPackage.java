package components;

public class SmallPackage extends Package {
	private boolean acknowledge;
	/**
	 * <h1>The SmallPackage class</h1>
	 * represents small packages and inherits from a package class.
	 * gets another field acknowledge That this field receives true or false value if the package requires sending a confirmation of delivery after delivery
	 * 
	 *  
	 *  @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349

	 * */

	
	/**
	 * Constructor of the class
	 * Gets 4 parameters.
	 * 3 parameters are sent to the package class by using super
	 * @param priority.
	 * @param senderAddress.
	 * @param destinationAdress.
	 * 
	 * and parameter acknowledge 
	 * @param acknowledge
	 * 
	 * 
	 * */
	
	public SmallPackage(Priority priority, Address senderAddress,Address destinationAdress, boolean acknowledge){
		super(priority, senderAddress,destinationAdress);
		this.acknowledge=acknowledge;
		System.out.println("Creating " + this);

	}
	
	
	public boolean isAcknowledge() {
		return acknowledge;
	}
	
	
	public void setAcknowledge(boolean acknowledge) {
		this.acknowledge = acknowledge;
	}
	
	
	@Override
	public String toString() {
		return "SmallPackage ["+ super.toString() +", acknowledge=" + acknowledge + "]";
	}
	
		
}
