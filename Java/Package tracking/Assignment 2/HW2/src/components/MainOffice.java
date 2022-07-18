package components;

import java.util.ArrayList;
import java.util.Random;


public class MainOffice implements Runnable {
	/**
	 * <h1>The MainOffice class </h1>
	 * An object of this class manages the entire system, operates a clock,
	 * the branches and vehicles, 
	 * creates the packages (simulates customers) and transfers them to the appropriate branches.
	 * 
	 * The class has 4 fields: 
	 * 
	 * 1. clock - Initialized to zero, each time preceded by one. 
	 * 			 represents the number of pulses passing from the operation of the system.
	 * 2. hub - An object of a Hub, containing all the active branches in the game.
	 * 3. packages - A collection of all the packages that exist in the system 
	 * 				 (including those that have already been delivered to the customer).
	 * 
	 *  @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
	 * */
	
	
	private static int clock=0;
	private static Hub hub;
	private int numOfPacakge = 0, HowManyPackageToCreate;
	private ArrayList<Package> packages=new ArrayList<Package>();
	public static boolean Flag = false;
	
	/**
	 * 
	 * Constructor that accepts the amount of branches that will be playing and the number of vehicles per branch. 
	 * The constructor creates a sorting center (Hub) and adds it to standard trucks TrucksForBranch parameter quantity. 
	 * In addition to adding non-standard truck Hub One.
	 * After creating branches (Branch) in parameter appears branches 
	 * and to each such branch adds Van trucks in an amount that matches the trucksForBranch parameter.
	 * 
//	 * */
	
	public MainOffice(int branches, int trucksForBranch , int numOfPacakge) {
		addHub(trucksForBranch);
		addBranches(branches, trucksForBranch);
		this.HowManyPackageToCreate = numOfPacakge;
		System.out.println("\n\n========================== START ==========================");

	}
	
	public int getNumOfPackage() {
		return numOfPacakge;
	}
	
	public static Hub getHub() {
		return hub;
	}


	public static int getClock() {
		return clock;
	}

	
	public void play(int playTime) {	
		for (int i=0; i<playTime; i++) {
			tick();
		}
		System.out.println("\n========================== STOP ==========================\n\n");
		printReport();
	}
	
	
	public void printReport() {
		for (Package p: packages) {
			System.out.println("\nTRACKING " +p);
			for (Tracking t: p.getTracking())
				System.out.println(t);
		}
	}
	
	public String clockString() {
		String s="";
		int minutes=clock/60;
		int seconds=clock%60;
		s+=(minutes<10) ? "0" + minutes : minutes;
		s+=":";
		s+=(seconds<10) ? "0" + seconds : seconds;
		return s;
	}
	
	
	public void tick() {
		System.out.println(clockString());
		if (clock%5==0 && HowManyPackageToCreate > 0) {
			addPackage();
			HowManyPackageToCreate--;
			numOfPacakge++;
		}
		new Thread(hub).start();
		for (Branch b: hub.getBranches()) {
			new Thread(b).start();
		}
		clock++;
	}
		
	
	public void addHub(int trucksForBranch) {
		hub=new Hub();
		for (int i=0; i<trucksForBranch; i++) {
			hub.addTruck(new StandardTruck());
		}
		hub.addTruck(new NonStandardTruck());
	}
	
	
	public void addBranches(int branches, int trucks) {
		for (int i=0; i<branches; i++) {
			Branch branch=new Branch();
			for (int j=0; j<trucks; j++) {
				branch.addTruck(new Van());
			}
			hub.add_branch(branch);		
		}
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
		Random r = new Random();
		Package p;
		Priority priority=Priority.values()[r.nextInt(3)];
		Address sender = new Address(r.nextInt(hub.getBranches().size()), r.nextInt(999999)+100000);
		Address dest = new Address(r.nextInt(hub.getBranches().size()), r.nextInt(999999)+100000);

		switch (r.nextInt(3)){
		case 0:
			p = new SmallPackage(priority,  sender, dest, r.nextBoolean() );
			p.getSenderBranch().addPackage(p);
			break;
		case 1:
			p = new StandardPackage(priority,  sender, dest, r.nextFloat()+(r.nextInt(9)+1));
			p.getSenderBranch().addPackage(p);
			break;
		case 2:
			p=new NonStandardPackage(priority,  sender, dest,  r.nextInt(1000), r.nextInt(500), r.nextInt(400));
			hub.addPackage(p);
			break;
		default:
			p=null;
			return;
		}
		
		this.packages.add(p);
		
	}


	public ArrayList<Package> getPackages() {
		return packages;
	}

	@Override
	public void run() {
		while(Flag) {
			tick();
			try {
				Thread.sleep(500);
			}catch(InterruptedException e) {
				System.out.println(e); 
			}
		}		
	}
}
