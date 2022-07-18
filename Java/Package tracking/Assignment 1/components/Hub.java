package components;
/* This Class describes the main office of the Courier company  */
import java.util.ArrayList;
import java.util.Random;
//import java.lang.Math;



public class Hub extends Branch implements Node{ 
	/**
	 * <h1>The Hub class</h1>
	 * Hub represents a main branch.
	 * 
	 * It has a field with the array of the other branches:
	 * branches -> all the branches in program.
	 * 
	 *  @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
	 * */
	
	
	private static int whereToGo = 0;
	private ArrayList<Branch> branches;
	
	/**
	 * A default constructor, 
	 * Creates a branch object with the name HUB
	 * */
	public Hub() {
		super("HUB");
		this.branches = new ArrayList<Branch>();
	}

	public ArrayList<Branch> getBranches() {
		return branches;
	}


	public void setBranches(ArrayList<Branch> branches) {
		this.branches = branches;
	}

	/**
	 *Collection of packages to the main branch
	 * */
	@Override
	public void collectPackage(Package p) {
		if(p.getStatus() == Status.HUB_TRANSPORT)
			p.setStatus(Status.HUB_STORAGE);
		p.addTracking(this, p.getStatus());
		this.getListPackage().add(p);
	}
	/**
	 * Delivers packages for loads
	 * */
	@Override
	public void deliverPackage(Package p) {
		if(p instanceof NonStandardPackage)
			this.getListTrucks().get(lenTrucks()-1).collectPackage(p);
		this.getListPackage().remove(p);
	}
	
	public String getName() {
		return "HUB";
	}
		
	
	/**
	 * A work unit that is performed in one clock
	 * 
	 * Standard Truck:
	 * 		For each standard sorting center truck, if the truck is available, it is shipped to some local branch in order.
	 *		For the purpose of the trip, the truck will load all the packages that are waiting to be transferred to the branch to which it is traveling, as long as the weight of the packages is less than the maximum weight it can carry.
	 * 		The status of the packages and their history are updated accordingly, a message is printed stating that the truck is leaving for this branch, the travel time is a lottery value between 1 and 10.
	 * 		example: "StandardTruck 'X' is on it's way to Branch 'Y', time to arrive: 'T' "
	 * 		X -> truckID
	 * 		Y -> branchID
	 * 		T -> time to arrive.
	 * 
	 * NonStandard Truck:
	 * 		If the non-standard truck is available, it will be checked whether there is a non-standard package in the sorting center that is waiting to be collected and that its dimensions fit the truck. 
	 * 		If so, the truck will be sent to pick up the package. 
	 * 		The collection of the non-standard package from a customer is done according to exactly the same rules as the other packages, only by a non-standard truck.
	 * 
	 * The function also runs its work on each branch.
	 * */
	public void work() {
		Random rand = new Random();	
		for(int i = 0 ; i < getListTrucks().size() ; i++) {
			if(getListTrucks().get(i) instanceof StandardTruck) {
			
				if(getListTrucks().get(i).isAvailable()) {			
					((StandardTruck)getListTrucks().get(i)).setDestination(this);
					this.getListTrucks().get(i).setTimeLeft(rand.nextInt(10-1)+1);
					getListTrucks().get(i).work();	
					((StandardTruck)getListTrucks().get(i)).setDestination(this.getBranches().get(whereToGo()));					
					System.out.println("StandardTruck "+ this.getListTrucks().get(i).getTruckID() +" is on it's way to " + ((StandardTruck)getListTrucks().get(i)).getDestination().getBranchName()+ ", time to arrive: "+ (this.getListTrucks().get(i).getTimeLeft() + 1));
					
					 
				}else if(getListTrucks().get(i).getTimeLeft() == 0 && ((StandardTruck)getListTrucks().get(i)).getDestination().getBranchId() != -1){ // check if is arrive to one of the branches
					getListTrucks().get(i).work();
					getListTrucks().get(i).setTimeLeft(rand.nextInt(7-1)+1);
					System.out.println("StandardTruck "+ getListTrucks().get(i).getTruckID() +" is on it's way to HUB, time to arrive: " + getListTrucks().get(i).getTimeLeft());
					((StandardTruck)getListTrucks().get(i)).setDestination(this);
					getListTrucks().get(i).work();
				
				}else if(getListTrucks().get(i).getTimeLeft() == 0 && ((StandardTruck)getListTrucks().get(i)).getDestination().getBranchId() == -1){ // check if is arrive to HUB 
					getListTrucks().get(i).work();
					this.getListTrucks().get(i).setTimeLeft(rand.nextInt(10-1)+1);
					((StandardTruck)getListTrucks().get(i)).setDestination(this.getBranches().get(whereToGo()));		
					System.out.println("StandardTruck "+ getListTrucks().get(i).getTruckID() +" is on it's way to " + ((StandardTruck)getListTrucks().get(i)).getDestination().getBranchName() + ", time to arrive: " + getListTrucks().get(i).getTimeLeft());
					this.getListTrucks().get(i).setAvailable(false);
					addPackageToTruck(getListTrucks().get(i));
					getListTrucks().get(i).work();
					
				}else{
			
					getListTrucks().get(i).work();
				}	
				
			}else if(getListTrucks().get(i) instanceof NonStandardTruck) {
				for(int j = 0 ; j < lenPackage() && getListTrucks().get(i).isAvailable() ; j++) {
					if(this.getListPackage().get(j) instanceof NonStandardPackage && isThereNonStandradPackageAndCapacity(getListTrucks().get(i), this.getListPackage().get(j))) {
						this.getListPackage().get(j).setStatus(Status.COLLECTION);
						this.getListPackage().get(j).addTracking(((NonStandardTruck)getListTrucks().get(i)), this.getListPackage().get(j).getStatus());
						getListTrucks().get(i).setTimeLeft(rand.nextInt(10-1)+1);
						System.out.println("NonStandartTruck " + getListTrucks().get(i).getTruckID() + " is collecting package " + this.getListPackage().get(j).getPackageID() + ", time left: "+ getListTrucks().get(i).getTimeLeft());
						this.deliverPackage(this.getListPackage().get(j));
						getListTrucks().get(i).setAvailable(false);
					}
				}
				getListTrucks().get(i).work();
			}
		}// loop
		
		
		for(int i = 0 ; i < this.getBranches().size() ; i++) { //Work Branches.
			this.getBranches().get(i).work();		
			}
	}	
	
	
	// Returns true whether it is a small or standard package
	public boolean StandardOrSmall(Package p) {
		return p instanceof SmallPackage || p instanceof StandardPackage;
	}
	
	
	
	//Checks if the non-standard package can fit in the non-standard truck
	public boolean isThereNonStandradPackageAndCapacity(Truck T, Package p) {
		if(((NonStandardTruck)T).capacity() >= ((NonStandardPackage)p).capacity()) {
				return true;
		}
		return false;
	}
	
	
	
	private void addPackageToTruck(Truck T) {
		for(int i = 0; i < this.lenPackage() ; i++) {
			if(T instanceof StandardTruck && StandardOrSmall(this.getListPackage().get(i))) {
				if(this.getListPackage().get(i).getDestinationAddress().getZip() == ((StandardTruck)T).getDestination().getBranchId()) {
					T.collectPackage(this.getListPackage().get(i));
					this.deliverPackage(this.getListPackage().get(i));
				}
			}
		}
	}
	
	/**
	 * 
	 * The whereToGo function brings me the ride arrangement to the branches.
	 * 
	 * */
	
	public int whereToGo() {
		if(Hub.whereToGo == getBranches().size()) {
			Hub.whereToGo = 0;
			return Hub.whereToGo++;
		}
		return Hub.whereToGo++;
	}
	
}
