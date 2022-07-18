package components;
import java.awt.Point;
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

public class Branch implements Node , Runnable {
	private static int counter=-1;
	private int branchId;
	private String branchName;
	
//	private double BranchCordX, BranchCordY;
	private Point target = new Point();
	private Point location = new Point(); // Location Branch
	
	protected ArrayList <Package> packages = new ArrayList<Package>();
	protected ArrayList <Truck> listTrucks = new ArrayList<Truck>();
	
	/**
	 * A default constructor, 
	 * a calculate serial number and creates the name of the branch, 
	 * The rest of the variables are initialized to an empty list
	 * 
	 * */
	
	public Branch() {
		this("Branch "+counter);
	}
	
	public Branch(String branchName) {
		this.branchId=counter++;
		this.branchName=branchName;
		System.out.println("\nCreating "+ this);
	}
	
	public Branch(String branchName, Package[] plist, Truck[] tlist) {
		this.branchId=counter++;
		this.branchName=branchName;
		addPackages(plist);
		addTrucks(tlist);
	}
	
	
	public void printBranch() {
		System.out.println("\nBranch name: "+branchName);
		System.out.println("Packages list:");
		for (Package pack: packages)
			System.out.println(pack);
		System.out.println("Trucks list:");
		for (Truck trk: listTrucks)
			System.out.println(trk);
	}
	
	
	public void addPackage(Package pack) {
		packages.add(pack);
	}
	
	
	public void addTruck(Truck trk) {
		listTrucks.add(trk);
	}
	
	
	public void addPackages(Package[] plist) {
		for (Package pack: plist)
			packages.add(pack);
	}
	
	
	public void addTrucks(Truck[] tlist) {
		for (Truck trk: tlist)
			listTrucks.add(trk);
	}

	
	public int getBranchId() {
		return branchId;
	}
	
	
	public String getName() {
		return branchName;
	}

	
	@Override
	public String toString() {
		return "Branch " + branchId + ", branch name:" + branchName + ", packages: " + packages.size()
				+ ", trucks: " + listTrucks.size();
	}

	/**
	 * collectPackage add package to the list of the local branch.
	 * */
	@Override
	public void collectPackage(Package p) {
		for (Truck v : listTrucks) {
			if (v.isAvailable()) {
				v.collectPackage(p);
				return;
			}
		}
	}

	@Override
	public void deliverPackage(Package p) {
		for (Truck v : listTrucks) {
			if (v.isAvailable()) {
				v.deliverPackage(p);
				new Thread(v).start();
				return;
			}
		}	
	}
	
	
	@Override
	public void work() {
		for (Truck t: listTrucks) {
			new Thread(t).start();
		}
		localWork();
	}
	
	
	public void localWork() {
		for (Package p: packages) {
			if (p.getStatus()==Status.CREATION) {
				collectPackage(p);
			}
			if (p.getStatus()==Status.DELIVERY) {
				deliverPackage(p);
			}
		}
	}
	
	public boolean ThereIsBranchStorage() {
		for(int i = 0; i < this.getPackages().size(); i++) {
			if(this.getPackages().get(i).getStatus() == Status.BRANCH_STORAGE)
				return true;
		}
		return false;
	}

	
	
	public ArrayList<Package> getPackages() {
		return packages;
		}
	
	public ArrayList<Truck> getTrucks() {
		return listTrucks;
	}

	public void removePackage(Package p) {
		packages.remove(p);
	}


	public Point getLocation() {
		return location;
	}
	
	public Point getTarget() {
		return target;
	}
	
	
	@Override
	public void run() {
		work();
	}















}
