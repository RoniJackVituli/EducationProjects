package components;


public class Van extends Truck{
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
		System.out.println(this);
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
	public Van(String licensePlate,String truckModel) {
		super(licensePlate,truckModel);
		System.out.println(this);
	}
	

	@Override
	public String toString() {
		return "Van ["+ super.toString() + "]";
	}
	
	
	@Override
	public void deliverPackage(Package p) {
		addPackage(p);
		setAvailable(false);
		int time=p.getDestinationAddress().getStreet()%10+1;
		this.setTimeLeft(time*10);
		this.timeNonA = getTimeLeft();
		this.timeNonB = 1;
		p.addRecords(Status.DISTRIBUTION, this);
		System.out.println(getName() + " is delivering " + p.getName() + ", time left: "+ getTimeLeft()  );
	}
	
	
	@Override
	public synchronized void work() {
		if (!isAvailable()) {
			setTimeLeft(getTimeLeft()-1);
			Package p = getPackages().get(0);
			if (this.getTimeLeft()==0){
				if (p.getStatus()==Status.COLLECTION && !(this.goBackToBranchFromSen)) {
					System.out.println(getName() + " has collected " +p.getName()+" and arrived back to " + p.getSenderBranch().getName());
					this.goBackToBranchFromSen = true;
					this.getLocation().x = (int) p.getPackageCordX();
					this.getLocation().y = (int) p.getPackageCordClientY();
					goBackToBranchFromSen(p);
				}else if(this.goBackToBranchFromSen) {
					p.addRecords(Status.BRANCH_STORAGE,p.getSenderBranch());
					this.getPackages().removeAll(getPackages());
					this.setAvailable(true);
					this.goBackToBranchFromSen = false;
				}else {
					this.setAvailable(true);
					getPackages().remove(0);
					p.addRecords(Status.DELIVERED, null);
					p.getDestBranch().removePackage(p);
					this.getLocation().x = (int) p.getDestBranch().getLocation().getX();
					this.getLocation().y = (int) p.getDestBranch().getLocation().getY();
					System.out.println(getName() + " has delivered "+p.getName() + " to the destination");
					if (p instanceof SmallPackage && ((SmallPackage)p).isAcknowledge()) 
							System.out.println("Acknowledge sent for "+p.getName());
				}
			}else {
				if(p.getStatus()==Status.COLLECTION && !this.goBackToBranchFromSen) {
					int x = (int)(p.getSenderBranch().getLocation().getX() + (p.getPackageCordX() - p.getSenderBranch().getLocation().getX())*this.timeNonB/this.timeNonA) ;
					int y =  (int)(p.getSenderBranch().getLocation().getY() + (32  - p.getSenderBranch().getLocation().getY())*this.timeNonB/this.timeNonA);
					this.timeNonB++;
					this.getLocation().x = x-5; 
					this.getLocation().y = y - 5;
				}else if(this.goBackToBranchFromSen) {
					int x = (int)(p.getPackageCordX() + (p.getSenderBranch().getLocation().getX() - p.getPackageCordX())*this.timeNonB/this.timeNonA) ;
					int y = (int)(32 + (p.getSenderBranch().getLocation().getY() - 32)*this.timeNonB/this.timeNonA);
					this.timeNonB++;
					this.getLocation().x = x - 5; 
					this.getLocation().y = y;
				}else if(p.getStatus() == Status.DISTRIBUTION) {
					int x = (int)(p.getDestBranch().getLocation().getX() + (p.getPackageCordX() - p.getDestBranch().getLocation().getX())*this.timeNonB/this.timeNonA) ;
					int y =  (int)(p.getDestBranch().getLocation().getY() + (602  - p.getDestBranch().getLocation().getY())*this.timeNonB/this.timeNonA);
					this.timeNonB++;
					this.getLocation().x = x-5; 
					this.getLocation().y = y - 5;
				}
			}
		}
	}
	/**
	 * 
	 * Check if the Van is return to the branch after it collecting the package from the client
	 * 
	 * */
	
	
	public void goBackToBranchFromSen(Package p) {
		setAvailable(false);
		int time=(p.getSenderAddress().getStreet()%10+1);
		this.setTimeLeft(time*10);
		this.timeNonA = time*10;
		this.timeNonB = 1;
	}


	@Override
	public void run() {
		work();
		
	}
}
