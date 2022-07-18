package components;

import java.awt.Point;
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


/**
 * Since this is an abstract class I pass these methods on to classes that inherit from it.
 * */

public abstract class Package {
	
	private static int countID=1000;
	final private int packageID;
	private Priority priority;
	private Status status;
	private Address senderAddress;
	private Address destinationAddress;
	private ArrayList<Tracking> tracking = new ArrayList<Tracking>();
	private double packageCordX, PackageCordClientY, PackageCordCustomerY ;
	private Point whereToGoClient, whereToGoCustomer;


	public Package(Priority priority, Address senderAddress,Address destinationAdress) {
		packageID = countID++;
		this.priority=priority;
		this.status=Status.CREATION;
		this.senderAddress=senderAddress;
		this.destinationAddress=destinationAdress;
		tracking.add(new Tracking( MainOffice.getClock(), null, status));
	}
	
	
	public double getPackageCordClientY() {
		return PackageCordClientY;
	}

	public double getPackageCordCustomerY() {
		return PackageCordCustomerY;
	}

	public void setPackageCordClientY(double packageCordClientY) {
		PackageCordClientY = packageCordClientY;
	}

	public void setPackageCordCustomerY(double packageCordCustomerY) {
		PackageCordCustomerY = packageCordCustomerY;
	}

	
	public double getPackageCordX() {
		return packageCordX;
	}


	public void setPackageCordX(double packageCordX) {
		this.packageCordX = packageCordX;
	}


	
	public Point getWhereToGoClient() {
		return whereToGoClient;
	}


	public Point getWhereToGoCustomer() {
		return whereToGoCustomer;
	}


	public void setWhereToGoClient(Point whereToGoClient) {
		this.whereToGoClient = whereToGoClient;
	}


	public void setWhereToGoCustomer(Point whereToGoCustomer) {
		this.whereToGoCustomer = whereToGoCustomer;
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

	
	public int getPackageID() {
		return packageID;
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

	public String getName() {
		return "package " + getPackageID(); 
	}
	
	
	public void setDestinationAddress(Address destinationAdress) {
		this.destinationAddress = destinationAdress;
	}

	
	public void addTracking(Node node, Status status) {
		tracking.add(new Tracking(MainOffice.getClock(), node, status));
	}
	
	
	public void addTracking(Tracking t) {
		tracking.add(t);
	}
	
	
	public ArrayList<Tracking> getTracking() {
		return tracking;
	}

	
	public void printTracking() {
		for (Tracking t: tracking)
			System.out.println(t);
	}
	
	
	public Branch getSenderBranch() {
		return MainOffice.getHub().getBranches().get(getSenderAddress().getZip());
	}
	
	
	public Branch getDestBranch() {
		return MainOffice.getHub().getBranches().get(getDestinationAddress().getZip());
	}
	
	
	@Override
	public String toString() {
		return "packageID=" + packageID + ", priority=" + priority + ", status=" + status + ", senderAddress=" + senderAddress + ", destinationAddress=" + destinationAddress;
	}

	public void addRecords(Status status, Node node) {
		setStatus(status);
		addTracking(node, status);
	}
	
	
}
