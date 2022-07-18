package components;

/**
 * <h1>The StandardPackage class</h1>
 * represents standard packages and inherits from a package class.
 * gets another field weight That this field receives weight of the package And its weight is over 1 kg.
 *  
 *  @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349

 * */

public class StandardPackage extends Package{
	private double weight;
	/**
	 * Constructor of the class
	 * Gets 4 parameters.
	 * 3 parameters are sent to the package class by using super
	 * @param priority.
	 * @param senderAddress.
	 * @param destinationAdress.
	 * 
	 * and parameter weight 
	 * @param weight
	 * 
	 * 
	 * */
	public StandardPackage (Priority priority, Address senderAddress, Address destinationAdress, double weight) {
		super(priority, senderAddress, destinationAdress);
		this.weight = weight;
		System.out.println("Creating " + toString());
	}
	

	public String toString() {
		return "StandardPackage [packageID="+this.getPackageID()+ ", priority = "+this.getPriority()+", status = " +this.getStatus() + ", startTime=, senderAddress="+ this.getSenderAddress().toString() + ", destinationAddress = " + this.getDestinationAddress().toString() +", weight = "+this.getWeight()+"]";
	}
	
	
	public double getWeight() {
		return weight;
	}

	public void setWeight(double weight) {
		this.weight = weight;
	}

	/**
	 * Implementing the addTracking method which adds a new record to Tracking.
	 * */
	@Override
	public void addTracking(Node node, Status status) {
		this.getTracking().add(new Tracking(MainOffice.getClock() , node, status));
		
	
	}
	/**
	 * Implementation of the printTracking method which prints the record of to Tracking
	 * */
	@Override
	public void printTracking() {
		for(int i = 0 ; i < getTracking().size(); i++) {
			System.out.println(getTracking().get(i).toString());
		}
		
	}
	/**
	 * Implementation of a weight method which returns a weight.
	 * @return weight
	 * */
	@Override
	public double weight() {
		return this.weight;
	}
}

