package components;
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

public abstract class Truck implements Node{

	private static int numTruck = 2000;
	private int numOfPackage = 0;
	private int add = 0;
	
	private int truckID;
	private	String licensePlate;
	private	String truckModel; 
	private	boolean available; //truck isAvliable
	private	int timeLeft; // time arrive
	private ArrayList<Package> packages; // חבילות שיש במשאית.

	public Truck() { 
		/**
		 *  Default Constructor of the class
		 *  The Constructor builds a truck in this way:
		 *  1. Randomly creates a car model between M(0-4).
		 *  2. Says the truck is available.
		 *  3. create randomly number for license plate (xxx-xx-xxx)
		 * */
		//Create Random number of model
		Random rand = new Random();
		int M = rand.nextInt(5);
		this.truckModel = "M" + String.valueOf(M);
		this.available = true;
		this.packages = new ArrayList<Package>();
		
		//Create Random LicensePlate.
		int FirstNum, SecNum ,ThirdNum;
		FirstNum = rand.nextInt(1000-100) + 100;
		SecNum = rand.nextInt(100-10) + 10;
		ThirdNum = rand.nextInt(1000-100) + 100;
		this.licensePlate = String.valueOf(FirstNum) + "-" + String.valueOf(SecNum) + "-" + String.valueOf(ThirdNum);
		this.truckID = numTruck++;
	
	}
	
	/**
	 * Constructor of the class
	 * get two parameters 
	 * @param licensePlate
	 * @param truckModel
	 * */
	public Truck(String licensePlate, String truckModel) {
		this.licensePlate = licensePlate;
		this.truckModel = truckModel;
		this.truckID = numTruck++;
		this.packages = new ArrayList<Package>();
	}
	
	
	public void setTruckModel(String truckModel) {
		this.truckModel = truckModel;
	}

	public void setLicensePlate(String licensePlate) {
		this.licensePlate = licensePlate;
	}
	
	//Gets & Sets
	public int getTruckID() {
		return truckID;
	}

	public String getLicensePlate() {
		return licensePlate;
	}

	public String getTruckModel() {
		return truckModel;
	}

	
	
	public boolean isAvailable() {
		return this.available;
	}

	public void setAvailable(boolean available) {
		this.available = available;
	}

	public int getTimeLeft() {
		return timeLeft;
	}

	public ArrayList<Package> getPackages() {
		return packages;
	}
	
	public void setPackages(ArrayList<Package> packages) {
		this.packages = packages;
	}
	
	public void setTimeLeft(int timeLeft) {
		if(timeLeft < 0)
			this.timeLeft += timeLeft;
		else
			this.timeLeft = timeLeft;
	}
	
	protected void addPackageSuccessed() {
		this.numOfPackage += 1;
	}
	
	protected void subPackageSuccessed() {
		this.numOfPackage -= 1;
	}

	public boolean isAdd() {
		if(this.numOfPackage > this.add) {
			this.add++;
			return true;
		}
		return false;
	
	}
	
	public abstract boolean addPackageToTruck(Package p);
	
	@Override
	public boolean equals(Object obj){
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Truck other = (Truck) obj;
		if (licensePlate == null) {
			if (other.licensePlate != null)
				return false;
		} else if (!licensePlate.equals(other.licensePlate))
			return false;
		return true;
	}
	


	
	
	
	
	
}
