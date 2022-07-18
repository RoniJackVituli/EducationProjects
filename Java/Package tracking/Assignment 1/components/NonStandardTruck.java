package components;
import java.util.Random;
import java.lang.Math;


/**
 * <h1>The NonStandardTruck class</h1>
 * represents a truck for transporting packages from the hub to client and inherits from a Truck class. 
 * all trucks belong to the hub.
 * The class has three fields:
 * 1. width 
 * 2. length 
 * 3. height 
 * all this three fields calculate the capacity of the truck.
 * 
 * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
 * */


public class NonStandardTruck extends Truck implements Node{
	private int width;
	private int length;
	private int height; 
	
	/**
	 * 
	 * Default Constructor of the class
	 * activates Truck Constructor using super
	 * creates a random length, width, height.
	 * Then runs the toString function and prints the generated data.
	 * */
	
	public NonStandardTruck () {	
		super();
		Random rand = new Random();
		this.length = rand.nextInt(1500-999)+999;
		this.width = rand.nextInt(1000-99)+99;
		this.height = rand.nextInt(1000-99)+99;
		System.out.println("Creating " + this.toString());	
		
	
	}
	
	/**
	 * 
	 * Constructor of the class
	 * get five parameters 
	 * @param licensePlate 
	 * @param truckModel
	 * @param length
	 * @param width
	 * @param height
	 * activates Truck Constructor using super 
	 * Then runs the toString function and prints the generated data.
	 * */
	public NonStandardTruck(String licensePlate, String truckModel, int length, int width, int height) {
		super(licensePlate, truckModel);
		this.width = width;
		this.length = length;
		this.height = height;
		System.out.println("Creating " + this.toString());	
		}
	
	
	
	@Override
	public void collectPackage(Package p) {
		if(addPackageToTruck(p)) {
			this.addPackageSuccessed();
		}
	}
	
	
	/**
	 * Delivers the package to the customer and deletes it from a truck
	 * */
	public void deliverPackage(Package p) {
		p.setStatus(Status.DELIVERED);
		p.addTracking(null, p.getStatus());
		this.getPackages().remove(p);
	}
	
	/**
	 * work function:
	 * 1. Performs a work unit
	 * 2. If a truck is available, do nothing.
	 * 3. Does the truck while driving reduce the time left by 1 ,
	 * 		If after the reduction a value is equal to zero then the truck has reached the destination it was to ride.
	 * 		the travel of this truck has two purposes:
	 * 			1. Collect the package - The truck ride to collect the package from the customer and the truck will move to make delivery
	 * 				and prints an appropriate message that the truck picked up the package example:
	 * 				"NonStandartTruck 'X' is collecting package 'Y', time left: 'T' "
	 * 				X - truckID
	 * 				Y - packageID
	 * 				T - time to arrive.
	 * 			2. Delivery of the package - The package will be removed from the truck's package list
	 * 						 				 and the package status will be updated accordingly.
	 * 						                 prints an appropriate message that the package was delivered to the customer
	 * 										 example: "NonStandartTruck 'X' has delivered package 'Y' to the destination"
	 *									     X - truckID
	 * 				                         Y - packageID
	 * 										 then the truck is available.
	 * */
	@Override
	public void work() {
		if(!this.isAvailable()) {
			if(this.getTimeLeft() == 0) {
				if(Purpose(this.getPackages().get(0))){ // מטרה לאסוף.
					System.out.println("NonStandartTruck " + this.getTruckID() + " has collected packages " + this.getPackages().get(0).getPackageID());
					this.getPackages().get(0).setStatus(Status.DISTRIBUTION);
					this.getPackages().get(0).addTracking(this, this.getPackages().get(0).getStatus());
					this.setTimeLeft(Math.abs((this.getPackages().get(0).getSenderAddress().getStreet() - (this.getPackages().get(0).getDestinationAddress().getStreet())/10))%10 + 1);
					System.out.println("NonStandartTruck " + this.getTruckID() + " is delivering package " + this.getPackages().get(0).getPackageID() + ", time left: " + this.getTimeLeft());
					
				}else { // המשאית הגיעה ליעד
					System.out.println("NonStandartTruck "+ this.getTruckID() +" has delivered package "+this.getPackages().get(0).getPackageID() +" to the destination");
					this.deliverPackage(this.getPackages().get(0));
					this.setAvailable(true);
				}
			}
			this.setTimeLeft(-1);
		}
		
	}
	
	// calculate the capacity of the truck.
	public int capacity() {
		return this.length*this.height*this.width;
	}
	
	public String toString() {
		return "NonStandrandTruck [truckID = " + this.getTruckID()+ ", licensePlate = "+this.getLicensePlate()+", truckModel = " + this.getTruckModel()+ ", available = "+this.isAvailable()+", length = "+this.length + ", width = "+this.width+", height = " +this.height + "]";
	}

	private boolean Purpose(Package p) {
		if(p.getStatus() == Status.COLLECTION)
			return true;
		return false;
	}
	
//	@Override
	public boolean addPackageToTruck(Package p) {
		if(p instanceof NonStandardPackage) {
			this.getPackages().add(p);
			return true;
		}
		return false;
	}


	public String getName() {
		return "NonStandardTruck " + this.getTruckID();
	}

}

