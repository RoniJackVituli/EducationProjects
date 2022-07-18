package components;

import java.awt.Color;
import java.awt.Graphics;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

public class Branch implements Node, Runnable, observer, Cloneable, StopRunnable {
	private static int counter=0;
	protected final AtomicBoolean running = new AtomicBoolean(false);
	private int branchId;
	private String branchName;
	protected ArrayList <Package> unsafeListPackages = new ArrayList<Package>();
	protected List<Package> listPackages = unsafeListPackages; //Collections.synchronizedList(unsafeListPackages);
	protected ArrayList <Truck> listTrucks = new ArrayList<Truck>();
	private Point hubPoint;
	private Point branchPoint;
	protected boolean threadSuspend = false;
	
	private PropertyChangeSupport support; 
	
	
	public Branch() {
		this("Branch "+counter);

		support = new PropertyChangeSupport(this); 
		this.addPropertyChangeListener(MainOffice.getInstance());
	}
	
	public Branch(String branchName) {
		this.branchId=counter++;
		this.branchName=branchName;
		System.out.println("\nCreating "+ this);
	
		support = new PropertyChangeSupport(this); 
		this.addPropertyChangeListener(MainOffice.getInstance());
	}
	
	public Branch(Branch br) {
		this.branchId = br.branchId;
		this.branchName = br.branchName;
		this.unsafeListPackages = br.unsafeListPackages;
		this.listPackages = br.listPackages;
		this.listTrucks = br.listTrucks;
	}
	
	public Branch(String branchName, Package[] plist, Truck[] tlist) {
		this.branchName=branchName;
		addPackages(plist);
		addTrucks(tlist);

		support = new PropertyChangeSupport(this); 
		this.addPropertyChangeListener(MainOffice.getInstance());
	}
	
	
	public void addPropertyChangeListener(PropertyChangeListener pcl){ 	
		support.addPropertyChangeListener(pcl); 
	} 

	public void removePropertyChangeListener(PropertyChangeListener pcl){ 	
		support.removePropertyChangeListener(pcl); 
	} 

	
	@Override
	public Object clone() {
		Package[] packages = new Package[this.getPackages().size()];
		String br = this.getName();
		Truck[] trucks = new Truck[this.getTrucks().size()];
		for(int i = 0 ; i < this.getPackages().size() ; i++) {
			packages[i] = (Package)this.getPackages().get(i).clone();
		}
		for(int i = 0 ; i < this.getTrucks().size() ; i++) {
			if(this.getTrucks().get(i) instanceof StandardTruck)
				trucks[i] = (StandardTruck)this.getTrucks().get(i).clone();
			else if(this.getTrucks().get(i) instanceof NonStandardTruck)
				trucks[i] = (NonStandardTruck)this.getTrucks().get(i).clone();
			else if(this.getTrucks().get(i) instanceof Van)
				trucks[i] = (Van)this.getTrucks().get(i).clone();
		}
		return new Branch(br, packages, trucks);
	}
	
	
	
	public synchronized List <Package> getPackages(){
		return this.listPackages;
	}
	
	public void printBranch() {
		System.out.println("\nBranch name: "+branchName);
		System.out.println("Packages list:");
		for (Package pack: listPackages)
			System.out.println(pack);
		System.out.println("Trucks list:");
		for (Truck trk: listTrucks)
			System.out.println(trk);
	}
	
	
	public synchronized void addPackage(Package pack) {
		listPackages.add(pack);
	}
	
	
	public ArrayList <Truck> getTrucks(){
		return this.listTrucks;
	}
	
	public void addTruck(Truck trk) {
		listTrucks.add(trk);
	}
	
	
	public Point getHubPoint() {
		return hubPoint;
	}
	
	public Point getBranchPoint() {
		return branchPoint;
	}
	
	public synchronized void addPackages(Package[] plist) {
		for (Package pack: plist)
			listPackages.add(pack);
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
		return "Branch " + branchId + ", branch name:" + branchName + ", packages: " + listPackages.size()
				+ ", trucks: " + listTrucks.size();
	}

	
	@Override
	public synchronized void  collectPackage(Package p) {
		for (Truck v : listTrucks) {
			if (v.isAvailable()) {
				synchronized(v) {
					v.notify();
				}
				v.collectPackage(p);
				return;
			}
		}
	}

	@Override
	public synchronized void deliverPackage(Package p) {
		for (Truck v : listTrucks) {
			if (v.isAvailable()) {
				synchronized(v) {
					v.notify();
				}
				v.deliverPackage(p);
				return;
			}
		}	
	}

	@Override
	public void work() {	
		/*for (Package p: listPackages) {
			if (p.getStatus()==Status.CREATION) {
				collectPackage(p);
			}
			if (p.getStatus()==Status.DELIVERY) {
				deliverPackage(p);
			}
		}*/	
	}

	
	private boolean arePackagesInBranch() {
		for(Package p: listPackages) {
			if (p.getStatus() == Status.BRANCH_STORAGE)
				return true;
		}
		return false;
	}
	
	public void paintComponent(Graphics g, int y, int y2) {
		if (arePackagesInBranch())
			g.setColor(new Color(0,0,153));
		else
			g.setColor(new Color(51,204,255));
   		g.fillRect(20, y, 40, 30);
   		
   		g.setColor(new Color(0,102,0));
   		g.drawLine(60, y+15, 1120, y2);
   		branchPoint = new Point(60,y+15);
   		hubPoint = new Point(1120,y2);
	}

	@Override
	public void run() {
		running.set(true);
		while(running.get()) {
		    synchronized(this) {
                while (threadSuspend)
					try {
						wait();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
		    }
			synchronized(this) {
				for (Package p: listPackages) {
						if (p.getStatus()==Status.CREATION) {
							collectPackage(p);
						}
						if (p.getStatus()==Status.DELIVERY) {
							deliverPackage(p);
						}
				}
			}
		}
	}
	
	
	public synchronized void setSuspend() {
	   	threadSuspend = true;
	}

	public synchronized void setResume() {
	   	threadSuspend = false;
	   	notify();
	}
	@Override
	public void addObserver() {
		this.addPropertyChangeListener(MainOffice.getInstance());		
	}

	@Override
	public void stop() {
		running.set(false);		
	} 
}
