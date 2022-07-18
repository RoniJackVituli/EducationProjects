package components;

/**
 * <h1>The SmallPackage class</h1>
 * represents small packages and inherits from a package class.
 * gets another field acknowledge That this field receives true or false value if the package requires sending a confirmation of delivery after delivery
 * 
 *  
 *  @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349

 * */

public class SmallPackage extends Package {
	private boolean acknowledge;
	private static final double WEIGHT = 1; 
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
	public SmallPackage(Priority priority, Address senderAddress, Address destinationAdress, boolean acknowledge) {
		super(priority, senderAddress, destinationAdress);
		this.acknowledge = acknowledge;
		System.out.println("Creating " + toString());
	}
	
	
	public String toString() {
		return "SmallPackage [packageID="+this.getPackageID()+ ", priority = "+this.getPriority()+", status = " +this.getStatus() + ", startTime=, senderAddress="+ this.getSenderAddress().toString() + ", destinationAddress = " + this.getDestinationAddress().toString() +", acknowledge = "+this.isAcknowledge()+"]";
	}

	public boolean isAcknowledge() {
		return acknowledge;
	}

	public void setAcknowledge(boolean acknowledge) {
		this.acknowledge = acknowledge;
	}
	
	
	/**
	 * Implementation of a weight method which returns a weight of 1 kg.
	 * @return WEIGHT
	 * */
	public double weight() {
		return WEIGHT;
	}

	/**
	 * Implementing the addTracking method which adds a new record to Tracking.
	 * */
	@Override
	public void addTracking(Node node, Status status) {
		this.getTracking().add(new Tracking(MainOffice.getClock() , node, status));
		
	}

	@Override
	/**
	 * Implementation of the printTracking method which prints the record of to Tracking
	 * */
	public void printTracking() {
		for(int i = 0 ; i < getTracking().size(); i++) {
			System.out.println(getTracking().get(i).toString());
		}
	}
}
