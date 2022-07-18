package components;
import java.util.Random;

/**
 * <h1>The StandardTruck class</h1>
 * represents a truck for transporting packages from the hub to branches and back and inherits from a Truck class.
 * all trucks belong to the hub.
 * The class has two fields:
 * 1. maxWeight -> the maximum weight that the truck can load.
 * 2. destination -> the destination branch that the truck needs to ride or drive back to the hub.
 *
 * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
 * */

public class StandardTruck extends Truck implements Node{
	
	private int maxWeight;
	private Branch destination;
	/**
	 * 
	 * Default Constructor of the class
	 * activates Truck Constructor using super
	 * creates a random weight between 300 and 200
	 * Then runs the toString function and prints the generated data.
	 * */
	public StandardTruck (){
		super();
		Random rand = new Random();
		this.maxWeight = rand.nextInt(300-200)+200;
		System.out.println("Creating " + this.toString());	
	}
	/**
	 * 
	 * Constructor of the class
	 * get three parameters 
	 * @param licensePlate 
	 * @param truckModel
	 * @param maxWeight
	 * activates Truck Constructor using super 
	 * Then runs the toString function and prints the generated data.
	 * */
	public StandardTruck(String licensePlate,String truckModel,int maxWeight) {
		super(licensePlate, truckModel);
		 this.maxWeight = maxWeight;
		 System.out.println("Creating " + this.toString());	
	}
	/**
	 * 
	 * Copy Constructor of the class
	 * get one parameter(object) 
	 * @param standardTruck 
	 * and copy the truck to the new truck.
	 * */
	public StandardTruck(StandardTruck standardTruck) { // Copy Ctor.
		this.maxWeight = standardTruck.getMaxWeight();
		this.destination = standardTruck.getDestination();
	}

	
	/**
	 * collectPackage checks the status of the package under two conditions:
	 * 1. If the status of the package is BRANCH_STORAGE then the package is collected from the local branch to the hub
	 * 2. else if the status of the package is HUB_STORAGE then the package is collected from hub to the destination branch 
	 * */
	@Override
	public void collectPackage(Package p) {
			if(p.getStatus() == Status.BRANCH_STORAGE) {
				if(addPackageToTruck(p)) {
					p.setStatus(Status.HUB_TRANSPORT);
					p.addTracking(this, p.getStatus());
					this.addPackageSuccessed();
				}					
			}else if(p.getStatus() == Status.HUB_STORAGE && this.destination.getBranchId() == p.getDestinationAddress().getZip())
				if(addPackageToTruck(p)) {
					p.setStatus(Status.BRANCH_TRANSPORT);
					p.addTracking(this, p.getStatus());
					this.addPackageSuccessed();
				}	
		}
		
	
	/**
	 * downPackage downloads packages from a truck to the destination it arrived at.
	 * */
	public void downPackages() {
		for(int i = 0; i < lenPackage(); i++) {
			deliverPackage(this.getPackages().get(i));
			if(removePackage(this.getPackages().get(i))) {
				i--;
				this.subPackageSuccessed();
			}
		}
	}
	
	public boolean removePackage(Package p) {
		for(int i = 0 ; i < lenPackage(); i++) {
			if(this.getPackages().get(i).equals(p)) {
				this.getPackages().remove(i);
				return true;
			}
		}
		return false;
	}
	/**
	 * upPackage uploads packages from a truck from where it is.
	 * */
	public void upPackages() {
		for(int i = 0 ; i < this.destination.getListPackage().size() ; i++) {
			if(this.destination instanceof Hub)
				collectPackage(this.destination.getListPackage().get(i));
			else if(this.destination.getListPackage().get(i).getStatus() == Status.BRANCH_STORAGE)
				collectPackage(this.destination.getListPackage().get(i));				
			if(this.isAdd()) {
				this.destination.deliverPackage(this.destination.getListPackage().get(i));
				i--;
			}
		}
	}
	
	
	
	@Override
	public void deliverPackage(Package p) { 
		this.destination.collectPackage(p); 
	
	}
	
	public int getMaxWeight() {
		return maxWeight;
	}

	public void setMaxWeight(int maxWeight) {
		this.maxWeight = maxWeight;
	}
	
	public String getName() {
		return "StandardTruck " + this.getTruckID();
	}
	
	
	
	/**
	 * The work function performs one work unit.
	 * A truck that is on the ride reduces the time left to complete the task
	 * If after the reduction the time value is equal to zero then the ride is over
	 * need to print accordingly notice that the truck has reached its destination
	 * example:   " StandardTruck X arrived to Branch Y
					StandardTruck X unloaded packages at Branch Y
					StandardTruck X loaded packages at Branch Y
					StandardTruck X is on it's way to Z, time to arrive: T"
					X -> truckID
					Y -> branchID
					Z -> destination 
					T -> time to arrive. 
	 * 		
	 * If the ride ended in a hub then the truck becomes available.
	 * */
	@Override
	public void work() {
		
		if(this.getTimeLeft() == 0) {
			
			System.out.println("StandardTruck "+ this.getTruckID() + " arrived to " + this.getDestination().getBranchName());
	
			System.out.println("StandardTruck "+ this.getTruckID() + " unloaded packages at " + this.getDestination().getBranchName());
			downPackages();
			
			System.out.println("StandardTruck "+ this.getTruckID() + " loaded packages at "+this.getDestination().getBranchName());
			upPackages();
			
			if(getDestination().getBranchId() == -1) {
				this.setAvailable(true);
			}
			
		}else if(isAvailable()){
			System.out.println("StandardTruck "+ this.getTruckID() + " loaded packages at "+this.getDestination().getBranchName());
			upPackages();
			setAvailable(false);
			
		}
			
		this.setTimeLeft(-1);

	}

	
	public Branch getDestination() {
		return destination;
	}

	public void setDestination(Branch destination) {
		this.destination = destination;
	}

	@Override
	
	
	public String toString() {
		return "StandardTruckTruck [truckID = " + this.getTruckID()+ ", licensePlate = "+this.getLicensePlate()+", truckModel = " + this.getTruckModel()+ ", available = "+this.isAvailable()+", maxWeight = "+this.maxWeight + "]";
	}
		

	
	/**
	 * addPackageToTruck is a function that checks:
	 * 1.If the package received is a small or standard package
	 * 2.Check that the total weight of the packages in the truck + the weight of the new package does not exceed the maximum weight of the truck
	 * If all conditions are met:
	 * @return true 
	 * else 
	 * @return false
	 * */
	public boolean addPackageToTruck(Package p) {
		if(p instanceof NonStandardPackage)
			return false;
		if(allWeightPackage(p) <= this.getMaxWeight() && p.getStatus() == Status.HUB_STORAGE ) {
			this.getPackages().add(p);
			return true;
		}else if(allWeightPackage(p) <= this.getMaxWeight() && p.getStatus() == Status.BRANCH_STORAGE){
			this.getPackages().add(p);
			return true;
		}
		return false;
	}
	
	
	/**
	 * The allWeightPackage function calculates 
	 * the weight of all the packages in the truck including the new package that needs to enter.
	 * @return sum
	 * */
	
	public int allWeightPackage(Package p) {
		int sum = 0;
		for(int i = 0; i < lenPackage(); i++) {
			sum += this.getPackages().get(i).weight();
		}
		sum += p.weight();
		return sum;
	}

	
	
	private int lenPackage() {
		if(this.getPackages() == null)
			return 0;
		return this.getPackages().size();
		
	}

	
	
	
	}
	
	
