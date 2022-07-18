package components;

/**
 * <h1>The NonStandardPackage class</h1>
 * represents  nonstandard packages and inherits from a package class.
 * gets another 3 fields: width, length, height These fields represent the size of the package.
 *  
 *  @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349

 * */

public class NonStandardPackage extends Package {
	private int width;
	private int length;
	private int height;
	
	
	/**
	 * Constructor of the class
	 * Gets 6 parameters.
	 * 3 parameters are sent to the package class by using super
	 * @param priority.
	 * @param senderAddress.
	 * @param destinationAdress.
	 * 
	 * and 3 parameters for width, length, height. 
	 * @param width
	 * @param length
	 * @param height
	 * 
	 * 
	 * */
	public NonStandardPackage(Priority priority, Address senderAddress, Address destinationAdress,int width, int length, int height) {
		
		super(priority, senderAddress, destinationAdress);
		this.width = width;
		this.length = length;
		this.height = height;
		System.out.println("Creating " + toString());
	}

	public int getWidth() {
		return width;
	}

	public void setWidth(int width) {
		this.width = width;
	}

	public int getLength() {
		return length;
	}

	public void setLength(int length) {
		this.length = length;
	}

	public int getHeight() {
		return height;
	}

	public void setHeight(int height) {
		this.height = height;
	}
	
	/**
	 * Implementation of a weight method which returns a weight.
	 * @return (width*length*height)/5000
	 **/
	public double weight() {
		return (width*length*height)/5000;
	}

	@Override
	public String toString() {
		return "NonStandardPackage [packageID="+this.getPackageID()+ ", priority = "+this.getPriority()+", status = " +this.getStatus() + ", startTime=, senderAddress="+ this.getSenderAddress().toString() + ", destinationAddress = " + this.getDestinationAddress().toString() +", width = "+this.getWidth()+ ", length = "+ this.getLength() +", height = "+this.getHeight()+"]";
	}
	/**
	 * Implementing the addTracking method which adds a new record to Tracking.
	 * */
	@Override
	public void addTracking(Node node, Status status) {
		this.getTracking().add(new Tracking(MainOffice.getClock() , node, status));		
	}
	
	public int capacity() {
		return this.length*this.height*this.width;
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
}

