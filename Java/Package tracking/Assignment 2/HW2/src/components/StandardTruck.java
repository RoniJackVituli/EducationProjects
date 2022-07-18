package components;


import java.util.Random;


public class StandardTruck extends Truck {
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

	private int maxWeight;
	private Branch destination;
	private int time = 0; 
	private int time2 = 0;
	
	private int CordBranchX ,CordBranchY;
	private int CordHubX , CordHubY;


	/**
	 * 
	 * Default Constructor of the class
	 * activates Truck Constructor using super
	 * creates a random weight between 300 and 200
	 * Then runs the toString function and prints the generated data.
	 * */
	public StandardTruck() {
		super();
		maxWeight=((new Random()).nextInt(2)+2)*100;
		System.out.println(this);

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
		super(licensePlate,truckModel);
		this.maxWeight=maxWeight;
		System.out.println(this);

	}
	
	
	public Branch getDestination() {
		return destination;
	}
	
	
	public void setDestination(Branch destination) {
		this.destination = destination;
	}
	

	public int getMaxWeight() {
		return maxWeight;
	}

	
	public void setMaxWeight(int maxWeight) {
		this.maxWeight = maxWeight;
	}

	
	@Override
	public String toString() {
		return "StandartTruck ["+ super.toString() +",maxWeight=" + maxWeight + "]";
	}
	
	
	public void unload () {
		for (Package p: getPackages()) {
			deliverPackage(p);
		}
		getPackages().removeAll(getPackages());
		System.out.println(getName() + " unloaded packages at " + destination.getName());
	}
	
	
	@Override
	public void deliverPackage(Package p) {
		if (destination==MainOffice.getHub())
			p.addRecords(Status.HUB_STORAGE, destination);
		else 
			p.addRecords(Status.DELIVERY, destination);
		destination.addPackage(p);
	}
	
	public void load (Branch sender, Branch dest, Status status) {
		double totalWeight=0;
		for (int i=0; i< sender.getPackages().size();i++) {
			Package p=sender.getPackages().get(i);
			if (p.getStatus()==Status.BRANCH_STORAGE || (p.getStatus()==Status.HUB_STORAGE && p.getDestBranch()==dest)) {
				if (p instanceof SmallPackage && totalWeight+1<=maxWeight || totalWeight+((StandardPackage)p).getWeight()<=maxWeight) {
					getPackages().add(p);
					sender.removePackage(p);
					i--;
					p.addRecords(status, this);
				}
			}
		}
		System.out.println(this.getName() + " loaded packages at " + sender.getName());
	}
	
	
	
	public int getTime() {
		return time;
	}


	public int getTime2() {
		return time2;
	}


	public void setTime(int time) {
		this.time = time;
	}


	public void setTime2(int time2) {
		this.time2 = time2;
	}

	

	public synchronized void work() {
		if (!isAvailable()) {
			setTimeLeft(getTimeLeft()-1);
			if (getTimeLeft()==0) {
				System.out.println("StandardTruck "+ getTruckID()+ " arrived to " + destination.getName());
				unload();
				if (destination == MainOffice.getHub()) {
					setAvailable(true);
					destination=null;
				}else{
					this.getLocation().x = (int) destination.getLocation().getX();
					this.getLocation().y = (int) destination.getLocation().getY();	
					this.getTarget().x = (int) destination.getTarget().getX(); // return to hubX
					this.getTarget().y = (int) destination.getTarget().getY(); // return to hubY					
					load(destination, MainOffice.getHub(), Status.HUB_TRANSPORT);
					setTimeLeft(((new Random()).nextInt(6)+1)*10);
					this.time = getTimeLeft();
					this.time2 = 1;
					destination = MainOffice.getHub();	
					CordHubX = this.getTarget().x;
					CordHubY = this.getTarget().y;
					CordBranchX = this.getLocation().x;
					CordBranchY = this.getLocation().y;
					System.out.println(this.getName() + " is on it's way to the HUB, time to arrive: "+ getTimeLeft());
				}
			}else{
					if(destination != MainOffice.getHub()) {
						int x = (int) (destination.getTarget().getX() + (destination.getLocation().getX() - destination.getTarget().getX()) * time2/time);
						int y = (int) (destination.getTarget().getY() + (destination.getLocation().getY() - destination.getTarget().getY()) * time2/time);
						this.time2++;
						this.getLocation().x = x+1;
						this.getLocation().y = y-7;
						
					}else {	
						int x = (int) (CordBranchX + (CordHubX - CordBranchX) * time2/time);
						int y = (int) (CordBranchY + (CordHubY - CordBranchY) * time2/time);
						this.time2++ ;
						this.getLocation().x = x-1;
						this.getLocation().y = y-10;
					}
				}
			}
		}
	


	@Override
	public void run() {
		work();
		
	}
	
}
