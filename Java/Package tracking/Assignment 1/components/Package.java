package components;
import java.util.ArrayList;

/**
 * <h1> The Class Package </h1>
 * 
 * <p>
 * A package class from which 3 packages will be inherited.
 * It has 6 fields that are:
 * 1. packageID -> Package ID number - the number starts from 1000.
 * 2. priority -> represents the priority of the package.
 * 3. status -> a status that accepts the current status of the package.
 * 4. senderAddress -> The sender address of the package.
 * 5. destinationAddress -> represents the destination address of the package.
 * 6. tracking -> collection of records with transfer history of the package.

 * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
 * 
 * */

public abstract class Package{
	private static int numOfPack = 1000;

	
	private int packageID; // run number.
	private	Priority priority;
	private	Status status;
	private	Address senderAddress;
	private Address destinationAddress;
	private ArrayList<Tracking> tracking; 
	
	
	
	/**
	 * this is the constructor of the class.
	 * gets three parameters and produces a new object.
	 * @param priority -> Package priority.
	 * @param senderAddress -> sender's address.
	 * @param destinationAddress ->Destination address.
	 * */
	public Package(Priority priority, Address senderAddress, Address destinationAddress) {
		
		this.priority = priority;
		this.senderAddress = senderAddress; 
		this.destinationAddress = destinationAddress; 
		this.packageID = Package.numOfPack++;
		this.status = Status.CREATION; 
		this.tracking = new ArrayList<Tracking>();
	}
	
//	public Package(Package p) {
//		this.priority = p.getPriority();
//		this.senderAddress = p.getSenderAddress(); 
//		this.destinationAddress = p.getDestinationAddress();
//		this.packageID = Package.numOfPack++;
//		this.status = p.getStatus(); 
//		this.tracking = p.getTracking();
//	}
	
	/**
	 * Since this is an abstract class I pass these methods on to classes that inherit from it.
	 * 
	 * Weight method - should return the weight of the package.
	 * addTracking method - gets the location of the package and the status of the package and the method adds to tracking
	 * printTracking - Prints the package history list
	 * 
	 * */
	
	public abstract double weight();
	public abstract void addTracking (Node node, Status status);
	public abstract void printTracking();
	

	/**
	 * 
	 * Methodical sessions of set & gets
	 * 
	 * */
	//GET & SET
	
	public int getPackageID() {
		return packageID;
	}
	

	public Priority getPriority() {
		return priority;
	}


	public void setPriority(Priority priority) {
		this.priority = priority;
	}


	public Status getStatus() {
		return status;
	}


	public void setStatus(Status status) {
		this.status = status;
	}


	public Address getSenderAddress() {
		return senderAddress;
	}


	public void setSenderAddress(Address senderAddress) {
		this.senderAddress = senderAddress;
	}


	public Address getDestinationAddress() {
		return destinationAddress;
	}


	public void setDestinationAddress(Address destinationAddress) {
		this.destinationAddress = destinationAddress;
	}


	public void setTracking(ArrayList<Tracking> tracking) {
		this.tracking = tracking;
	}

	public ArrayList<Tracking> getTracking() {
		return tracking;
	}

	
}
