package components;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Random;

/**
 * The Truck class 
 * 
 * Class represents the vehicles transporting packages
 * 
 * The class has 9 fields:
 *
 * 1. numTruck -> serial number of truck starting from 2000.
 * 2. numOfPackage -> the number of packages in the truck.
 * 3. add -> how many packages the truck is picked.
 * 4. truckID -> the serial number of the truck.
 * 5. licensePlate -> Truck license number.
 * 6. truckModel -> what model the truck.
 * 7. available -> if the truck is available.
 * 8. timeLeft -> The time that the truck needs to reach its destination.
 * 9. packages -> list of the packages in the truck.
 * 
 * 
 * 
 * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
 * 
 * */

public  abstract class Truck implements Node, Runnable {
	private static int countID=2000;
	final private int truckID;
	private String licensePlate;
	private String truckModel;
	private boolean available=true;
	private int timeLeft=0;
	protected int timeNonA = 0;
	protected int timeNonB = 0;
	protected boolean goBackToBranchFromSen = false;
	private ArrayList<Package> packages=new ArrayList<Package>();

	private Point target = new Point();
	private Point location = new Point();

		

	/**
	 * Constructor of the class
	 * get two parameters 
	 * @param licensePlate
	 * @param truckModel
	 * */
	public Truck() {
		truckID=countID++;
		Random r= new Random();
		licensePlate=(r.nextInt(900)+100)+"-"+(r.nextInt(90)+10)+"-"+(r.nextInt(900)+100);
		truckModel="M"+r.nextInt(5);
		System.out.print("Creating ");
	}

	
	public Truck(String licensePlate,String truckModel) {
		truckID=countID++;
		this.licensePlate=licensePlate;
		this.truckModel=truckModel;
		System.out.print("Creating ");
	}
	
	
	public ArrayList<Package> getPackages() {
		return packages;
	}


	public int getTimeLeft() {
		return timeLeft;
	}

	
	public void setTimeLeft(int timeLeft) {
		this.timeLeft = timeLeft;
	}
	

	public Point getLocation() {
		return location;
	}
	
	public Point getTarget() {
		return target;
	}
	

	@Override
	public String toString() {
		return "truckID=" + truckID + ", licensePlate=" + licensePlate + ", truckModel=" + truckModel + ", available= " + available ;
	}


	@Override
	public void collectPackage(Package p) {
		setAvailable(false);
		int time=(p.getSenderAddress().getStreet()%10+1);
		this.setTimeLeft(time*10);
		this.timeNonA = time*10;
		this.timeNonB = 1;
		this.packages.add(p);
		p.setStatus(Status.COLLECTION);
		p.addTracking(new Tracking(MainOffice.getClock(), this, p.getStatus()));
		System.out.println(getName() + " is collecting package " + p.getPackageID() + ", time to arrive: "+ getTimeLeft()  );
	}


	public boolean isAvailable() {
		return available;
	}
	

	public int getTruckID() {
		return truckID;
	}

	
	public void setAvailable(boolean available) {
		this.available = available;
	}
	
	
	public void addPackage(Package p) {
		this.packages.add(p);
	}
	
	
	public String getName() {
		return this.getClass().getSimpleName()+" "+ getTruckID();
	}
	
}
