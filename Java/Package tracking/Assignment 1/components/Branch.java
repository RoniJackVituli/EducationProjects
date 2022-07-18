package components;
import java.util.ArrayList;

/**
 * This class describes a local branch *
 * Describes a local branch. Keeps a list of packages stored at the branch or intended for collection from the sender's address to this branch
 * and a list of vans that collect the packages from the sending customers and deliver the packages to the receiving customers.
 * It has 4 fields:
 * 1. branchID -> branch number.
 * 2. branchName -> the branch name.
 * 3. listTrucks -> list of vans
 * 4. listPackage -> list of package in the branch.
 * 
 *  
 * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
 * 
 * */


public class Branch implements Node{
	private static int branchNum = -1;

	private	int branchId;
	private String branchName;
	private ArrayList<Truck> listTrucks;
	private ArrayList<Package> listPackage;
	
/**
 * A default constructor, 
 * a calculate serial number and creates the name of the branch, 
 * The rest of the variables are initialized to an empty list
 * 
 * */
	
	public Branch() {
		this.branchId = Branch.branchNum++;
		this.branchName = "Branch " + String.valueOf(this.branchId);
		this.listTrucks = null;
		this.listPackage = new ArrayList<Package>();
		System.out.println("Creating " +this.toString());	
	}
	
	/**
	 * A constructor, 
	 * get one parameter:
	 * @param branchName
	 * a calculate serial number,
	 * The rest of the variables are initialized to an empty list
	 * 
	 * */
	public Branch(String branchName) {
		this.branchName = branchName;
		this.branchId = Branch.branchNum++;
		this.listTrucks = null;
		this.listPackage = new ArrayList<Package>();
		System.out.println("Creating " +this.toString());	

	}
	
	public int getBranchId() {
		return branchId;
	}

	public void setBranchId(int branchId) {
		this.branchId = branchId;
	}

	public String getBranchName() {
		return branchName;
	}

	public void setBranchName(String branchName) {
		this.branchName = branchName;
	}

	public ArrayList<Package> getListPackage() {
		return listPackage;
	}

	public ArrayList<Truck> getListTrucks() {
		return listTrucks;
	}
	
	public void setListPackage(ArrayList<Package> listPackage) {
		this.listPackage = listPackage;
	}

	public void setListTrucks(ArrayList<Truck> listTrucks) {
		this.listTrucks = listTrucks;
	}
	
	public String toString() {
		return "Branch " + branchId + " name:" + branchName + ", packages:" +lenPackage() + ", trucks:" + lenTrucks() + "";
	}
	
	
	
	/**
	 * collectPackage add package to the list of the local branch.
	 * */
	
	@Override
	public void collectPackage(Package p) {
		if(p.getStatus() == Status.COLLECTION) {
			p.setStatus(Status.BRANCH_STORAGE);
			p.addTracking(this, p.getStatus());
			this.listPackage.add(p);
		}else if(p.getStatus() == Status.BRANCH_TRANSPORT) {
			p.setStatus(Status.DELIVERY);
			this.listPackage.add(p);
			p.addTracking(this, p.getStatus());
		}
	}
	

	@Override
	public void deliverPackage(Package p) {
		this.listPackage.remove(p);
	}
	
	protected int lenPackage() {
		if(getListPackage() == null)
			return 0;
		return getListPackage().size();
	}
	
	protected int lenTrucks() {
		if(getListTrucks() == null)
			return 0;
		return getListTrucks().size();
	}
	
	public String getName() {
		return "Branch " + getBranchId();
	}
	
	
	/**
	 * A work unit performed by a branch at every clock of the system clock
	 * For each package that is in the branch, if it is in the waiting status for collection from a customer, an attempt is made to collect.
	 * If there is a vehicle available, he goes out to pick up the package. 
	 * ride time is calculated as follows: the street number of the sender is divided by ten, for the remaining residue add one. 
	 * The value obtained is updated in the truck in the timeLeft field and the condition of the vehicle changes to "not available".
	 * 
	 * The same goes for any package waiting for distribution, if there is a vehicle available, it is sent to deliver the package. 
	 * Time is calculated according to the same formula, but according to the recipient's address.
	 * 
	 * This work also activates the works of vans
	 * 
	 * */
	@Override
	public void work() {	
		for(int i = 0; i < lenTrucks() ; i++) {
			if(getListTrucks().get(i).isAvailable()) {	
				for(int j = 0 ; j < lenPackage(); j++) {
					switch (this.getListPackage().get(j).getStatus()) {
						case CREATION: {
							this.getListPackage().get(j).setStatus(Status.COLLECTION);
							this.getListPackage().get(j).addTracking(((Van)getListTrucks().get(i)), getListPackage().get(j).getStatus());
							this.getListTrucks().get(i).collectPackage(this.getListPackage().get(j)); //מוסיף לואן 
							this.getListTrucks().get(i).setTimeLeft((getListPackage().get(j).getSenderAddress().getStreet()/10)%10 + 1);
							System.out.println("Van " + ((Van)getListTrucks().get(i)).getTruckID() + " is collecting package " + this.getListPackage().get(j).getPackageID() + ", time left: "+ ((Van)getListTrucks().get(i)).getTimeLeft());
							getListTrucks().get(i).setAvailable(false);
							break;
						}
						case DELIVERY:
							this.getListPackage().get(j).setStatus(Status.DISTRIBUTION);
							this.getListPackage().get(j).addTracking(((Van)getListTrucks().get(i)), getListPackage().get(j).getStatus());
							this.getListTrucks().get(i).collectPackage(this.getListPackage().get(j));
							this.getListTrucks().get(i).setTimeLeft((getListPackage().get(j).getDestinationAddress().getStreet()/10)%10 + 1);
							System.out.println("Van " + ((Van)getListTrucks().get(i)).getTruckID() + " is delivering package " + this.getListPackage().get(j).getPackageID() + ", time left: "+ ((Van)getListTrucks().get(i)).getTimeLeft());
							this.getListTrucks().get(i).setAvailable(false);
							this.deliverPackage(this.getListPackage().get(j));
							break;
						default:
							break;
						}
					}
				}
				getListTrucks().get(i).work();
				if(this.getListTrucks().get(i).getPackages().size() > 0 && this.getListTrucks().get(i).getPackages().get(0).getStatus() == Status.BRANCH_STORAGE) {
					this.getListTrucks().get(i).getPackages().get(0).addTracking(this, Status.BRANCH_STORAGE);
					this.getListTrucks().get(i).deliverPackage(this.getListTrucks().get(i).getPackages().get(0));
				}
			}
		}
	
		
}
		
	
