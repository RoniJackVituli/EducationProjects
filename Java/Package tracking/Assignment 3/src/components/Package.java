package components;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;


public abstract class Package implements Cloneable{
	private static int countID=1000;
	final private int packageID;
	private Priority priority;
	private Status status;
	private Address senderAddress;
	private Address destinationAddress;
	private ArrayList<Tracking> tracking = new ArrayList<Tracking>();
	private Branch branch = null;
	private Point sendPoint;
	private Point destPoint;
	private Point bInPoint;
	private Point bOutPoint;

	
	
	public Package(Priority priority, Address senderAddress,Address destinationAdress) {
		packageID = countID++;
		this.priority=priority;
		this.status=Status.CREATION;
		//set update 
		this.senderAddress=senderAddress;
		this.destinationAddress=destinationAdress;
		tracking.add(new Tracking( MainOffice.getClock(), null, status));
	}	
	
	
	public abstract Object clone();

	public void setBranch(Branch branch) {
		this.branch = branch;
	}
	
	public Branch getBranch() {
		return this.branch;
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
	
	
	@Override
	public String toString() {
		return "packageID = " + packageID + ", priority = " + priority + ", status = " + status
				+ ", senderAddress = " + senderAddress + ", destinationAddress = " + destinationAddress;
	}
	
	public Point getSendPoint() {
		return sendPoint;
	}
	
	public Point getDestPoint() {
		return destPoint;
	}
	
	public Point getBInPoint() {
		return bInPoint;
	}
	
	public Point getBOutPoint() {
		return bOutPoint;
	}


	public void paintComponent(Graphics g, int x, int offset) {
		if (status==Status.CREATION || (branch==null && status == Status.COLLECTION))
			g.setColor(new Color(204,0,0));
		else
			g.setColor(new Color(255,180,180));
   		g.fillOval(x, 20, 30, 30);
   		
   		if (status==Status.DELIVERED)
   			g.setColor(new Color(204,0,0));
   		else
   			g.setColor(new Color(255,180,180));
   		g.fillOval(x, 583, 30, 30);
   		
		
   		if (branch!=null) {
	   		g.setColor(Color.BLUE);
	   		g.drawLine(x+15,50,40,100+offset*this.senderAddress.getZip());
	   		sendPoint = new Point(x+15,50);
	   		bInPoint = new Point(40, 100+offset*this.senderAddress.getZip());
	   		g.drawLine(x+15,583,40,130+offset*this.destinationAddress.getZip());
	   		destPoint = new Point(x+15,583);
	   		bOutPoint = new Point(40,130+offset*this.destinationAddress.getZip());
	   		
   		}
   		else {
   			g.setColor(Color.RED);
   			g.drawLine(x+15,50,x+15,583);
   			g.drawLine(x+15,50,1140, 216);
   			sendPoint = new Point(x+15,50);
   			destPoint = new Point(x+15,583);
   			
   		}
	}

	
	
	
}
