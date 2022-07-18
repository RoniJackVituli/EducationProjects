package components;
import java.util.ArrayList;
import java.util.Random;

public class MainOffice{
	/**
	 * <h1>The MainOffice class </h1>
	 * An object of this class manages the entire system, operates a clock,
	 * the branches and vehicles, 
	 * creates the packages (simulates customers) and transfers them to the appropriate branches.
	 * 
	 * The class has 4 fields: 
	 * 1. count
	 * 2. clock - Initialized to zero, each time preceded by one. 
	 * 			 represents the number of pulses passing from the operation of the system.
	 * 3. hub - An object of a Hub, containing all the active branches in the game.
	 * 4. packages - A collection of all the packages that exist in the system 
	 * 				 (including those that have already been delivered to the customer).
	 * 
	 *  @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
	 * */
	
	private static int count = 4;
	private static int clock;
	private Hub hub; 
	private ArrayList<Package> packages; 
		
	
	/**
	 * 
	 * Constructor that accepts the amount of branches that will be playing and the number of vehicles per branch. 
	 * The constructor creates a sorting center (Hub) and adds it to standard trucks TrucksForBranch parameter quantity. 
	 * In addition to adding non-standard truck Hub One.
	 * After creating branches (Branch) in parameter appears branches 
	 * and to each such branch adds Van trucks in an amount that matches the trucksForBranch parameter.
	 * 
	 * */

	public MainOffice(int branches, int trucksForBranch) {
		hub = new Hub();
		hub.setListTrucks(new ArrayList<Truck>());
		hub.setListPackage(new ArrayList<Package>());
		for(int i=0;i<trucksForBranch;i++) {
			hub.getListTrucks().add(new StandardTruck());
		}
		hub.getListTrucks().add(new NonStandardTruck());
		System.out.println();
		for(int i = 0 ; i < branches; i++) {
			hub.getBranches().add(new Branch("Branch " + i));
			hub.getBranches().get(i).setListTrucks(new ArrayList<Truck>());
			hub.getBranches().get(i).setListPackage(new ArrayList<Package>());
			for(int j = 0; j < trucksForBranch ; j++) {
				hub.getBranches().get(i).getListTrucks().add(new Van());
			}
			System.out.println();
		}
		this.packages = new ArrayList<Package>();
	}
	
	public static int getClock() {
		return MainOffice.clock;
		}
	
	/**
	 * Function receives as an argument the number of beats them perform system 
	 * and operates the pulse (tick) the amount of times this.
	 * */
	public void play(int playTime) {
		System.out.println("========================== START ==========================");
		for(int i = 0 ; i < playTime; i++) {
			tick();
		}
		System.out.println("========================== STOP ==========================");
		printReport();
	}
	
	/**
	 * Prints a tracking report for all existing packages in the system: 
	 * For each package prints the entire contents of the collection tracking of the package
	 * */
	public void printReport() {
		System.out.println("");
		for(int i = 0 ; i < this.packages.size() ; i++) {
			System.out.println("Tracking " + this.packages.get(i).toString());
			this.packages.get(i).printTracking();
			System.out.println("");
		}
	}
	
	public String clockString() {
		int sec = getClock() % 60; 
		int minutes = getClock() / 60;
		return String.format("%02d:%02d", minutes, sec);
	}
	
	
	/**
	 * Each time you activate this function, the following actions are performed:
	 * 1. The clock is printed and promoted at one. example: MM:SS
	 * 2. All branches, Hub and Trucks perform one work unit.
	 * 3. Every 5 beats a random new package is created(SmallPackage , StandardPackage, NonStandardPackage).
	 * 4. After the last beat, a notice of termination of employment is printed ("STOP").
	 * 5. Then a transfer history report is printed for all packages created during the run
	 * */
	public void tick() {
		System.out.println(clockString());
		MainOffice.clock++;
		MainOffice.count++;
		if(MainOffice.count == 5) {
			addPackage();
			MainOffice.count = 0;
		}
		hub.work();
		
	}
	
	
	/**
	 * addPackage is activated every 5 beats.
	 * Label the type of package (small / standard / non-standard) the priority, the addresses of the sender and recipient 
	 * (so that they match the requirements in the Address class)
	 * Also depending on the type of package raffled off the additional data:
	 * 		1.for a small package the value of acknowledge is drawn.
	 * 		2.for a standard package the weight is drawn - an actual number between 1 and 10.
	 * 		3.for a non-standard package from the height grills (integer up to 400), The width (integer up to 500), and length (integer up to 1000).
	 * 
	 * After the data is drawn, a suitable package is created and associated with the appropriate branch: 
	 * small or standard packages are transferred to a local branch 
	 * and non-standard packages are delivered to HUB
	 * 
	 * */
	public void addPackage() {
		Package p = null;
		Random rand = new Random();
		Address senderAddress, destintionAddress;
		Priority [] VALUES = Priority.values();
		int SIZE = Priority.values().length;
		senderAddress = new Address(rand.nextInt(this.hub.getBranches().size()) ,rand.nextInt(1000000-99999) + 99999);
		destintionAddress = new Address(rand.nextInt(this.hub.getBranches().size()) ,rand.nextInt(1000000-99999) + 99999);		
		int x = rand.nextInt(4-1)+1;
		switch(x) {
		  case 1:
			  	p = new SmallPackage(VALUES[rand.nextInt(SIZE)], senderAddress, destintionAddress, rand.nextBoolean());
			  	p.addTracking(null, p.getStatus());
 		    break;
		  case 2:
			   	p = new StandardPackage(VALUES[rand.nextInt(SIZE)], senderAddress, destintionAddress, RandFloat());
			   	p.addTracking(null, p.getStatus());
 			  break;
		  case 3:
			  	p = new NonStandardPackage(VALUES[rand.nextInt(SIZE)], senderAddress, destintionAddress, rand.nextInt(500), rand.nextInt(1000), rand.nextInt(400));
			  	p.addTracking(null, p.getStatus());
			  break;
		}
		if(p != null) {
			this.packages.add(p);

		}
		if(p instanceof SmallPackage || p instanceof StandardPackage) {
			this.hub.getBranches().get(p.getSenderAddress().getZip()).getListPackage().add(p);       
		}else if(p instanceof NonStandardPackage) {
			this.hub.getListPackage().add(p);
		}
	}
	

	public float RandFloat() {
		float leftLimit = 1F;
	    float rightLimit = 10F;
	    return leftLimit + new Random().nextFloat() * (rightLimit - leftLimit);
	}

	
}
