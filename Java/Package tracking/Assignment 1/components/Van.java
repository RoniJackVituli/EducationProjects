package components;

class Van extends Truck implements Node{
	/**
	 * <h1>The Van class</h1> 
	 * this class collects a package from the sender's address to the local branch and inherits from a Truck class.
	 * And also delivers the package from branch to destination address. The vehicle can take one package at a time and no more.
	 * This class has no fields.
	 *  @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
	 * */
	
	
	
	
	/** 
	 * Default Constructor of the class
	 * activates Truck Constructor using super
	 * Then runs the toString function and prints the generated data.
	 * */
	
	public Van() { 
		super();
		System.out.println("Creating "+ this.toString());	
	}
	
	/**
	 * 
	 * Constructor of the class
	 * get two parameters 
	 * @param licensePlate 
	 * @param truckModel
	 * activates Truck Constructor using super 
	 * Then runs the toString function and prints the generated data.
	 * */
	public Van(String licensePlate, String truckModel) {
		super(licensePlate, truckModel);
		System.out.println("Creating "+ this.toString());	
	}
	
	
	@Override
	public String toString() {
		return "Van [truckID = " + this.getTruckID()+ ", licensePlate = "+this.getLicensePlate()+", truckModel = " + this.getTruckModel()+ ", available = "+this.isAvailable()+"]";
	}
	
	
	/**
	 * 
	 * A work function performs a work unit under the following conditions:
	 * 1. If the vehicle is not available it does nothing. 
	 * 	else:
	 * 		if the vehicle is in travel time, it reduces the time in the field (timeLeft) by 1.
	 * 		if after the reduction the time (timeLeft) has reached zero ,so the trip was over.
	 * 		and now we need to check what the purpose of the trip was:
	 * 			1.First goal - collection from the customer 
	 * 				This means that the package at this stage will be transferred from the vehicle to the branch, the status of the package will be updated, 
	 * 				and a suitable registration will also be added to the tracking list of the package.
	 * 				Then prints a message that the vehicle picked up the package and came back to the branch.
	 * 				for example: "Van -X- has collected packages -Y- and arrived back to branch -Z-"
	 * 				X -> truckID
	 * 				Y -> packageID
	 * 				Z -> zip
	 * 				In addition the Van will become available.
	 * 			2.Second goal - delivery of the package to the customer.
	 * 				That is, if the status of the package at the branch is "DISTRIBUTION" 
	 * 				then the van will collect the package and drive to the customer to deliver it.
	 * 				If the package was a small package, you should check whether the option of sending a delivery confirmation is activated.
	 * 				and also updating the records in tracking.
	 * */
	
	public void work() {
		if(!this.isAvailable()) {
			if(this.getTimeLeft() == 0) {
				if(Purpose(this.getPackages().get(0))){ // מטרה לאסוף.
					System.out.println("Van " + this.getTruckID() + " has collected packages " + this.getPackages().get(0).getPackageID()+ " and arrived back to branch " + this.getPackages().get(0).getSenderAddress().getZip());
					this.getPackages().get(0).setStatus(Status.BRANCH_STORAGE);
					this.setAvailable(true);
				}else { // המשאית הגיעה ליעד
					System.out.println("Van "+ this.getTruckID() +" has delivered package "+this.getPackages().get(0).getPackageID() +" to the destination");
					this.getPackages().get(0).setStatus(Status.DELIVERED);
					if(this.getPackages().get(0) instanceof SmallPackage && ((SmallPackage)this.getPackages().get(0)).isAcknowledge())
						System.out.println("The package " + this.getPackages().get(0).getPackageID()+ " send");
					this.getPackages().get(0).addTracking(null, this.getPackages().get(0).getStatus());
					this.deliverPackage(this.getPackages().get(0));
					this.setAvailable(true);
					
				}
			}
			this.setTimeLeft(-1);
		}
		
	}
	
	
	
	public String getName() {
		return "Van " + this.getTruckID();
	}
	/**
	 * Purpose function check if the status of the package is collection.
	 * @return true
	 * else 
	 * @return false
	 * */
	private boolean Purpose(Package p) {
		if(p.getStatus() == Status.COLLECTION)
			return true;
		return false;
	}
	
	
	
	//This Method from Interface Node.
	@Override
	public void collectPackage(Package p) {
		if(addPackageToTruck(p)) {
			this.addPackageSuccessed();
		}
	
	}
	
	@Override
	public void deliverPackage(Package p) {
		this.getPackages().remove(p);
		}
	/**
	 * function addPackageToTruck check if the Package we need to collected is small or standard package.
	 * and if it's one of them it collected to the truck.
	 * */
	
	@Override
	public boolean addPackageToTruck(Package p) {
		if(p instanceof StandardPackage || p instanceof SmallPackage) {
			this.getPackages().add(p);
			return true;
		}
		return false;
	}
}