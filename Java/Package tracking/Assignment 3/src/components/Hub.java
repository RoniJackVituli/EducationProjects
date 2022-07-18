package components;

import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

import program.PostSystemPanel;

public class Hub extends Branch{
	
	private ArrayList<Branch> branches=new ArrayList<Branch>();
	private int currentIndex=0;
	
	public Hub() {
		super("HUB");
	}
	
	public Hub(Branch [] blist, Package[] plist, Truck[] tlist) {
		super("HUB",plist ,tlist);
		addBranches(blist);
	}
	
	
	public synchronized void addBranches(Branch[] blist) {
		for (Branch br: blist)
			branches.add(br);
	}
	
	@Override	
	public Object clone() {
		Package[] packages = new Package[this.getPackages().size()];
		Truck[] trucks = new Truck[this.getTrucks().size()];
		Branch [] branches = new Branch[this.getBranches().size()];
		for(int i = 0 ; i < this.getPackages().size() ; i++) {
			packages[i] = (Package)this.getPackages().get(i).clone();
		}
		for(int i = 0 ; i < this.getTrucks().size() ; i++) {
			if(this.getTrucks().get(i) instanceof StandardTruck)
				trucks[i] = (StandardTruck)this.getTrucks().get(i).clone();
			else if(this.getTrucks().get(i) instanceof NonStandardTruck)
				trucks[i] = (NonStandardTruck)this.getTrucks().get(i).clone();
		}
		for(int i = 0 ; i < this.getBranches().size() ; i++) {
			branches[i] = (Branch)this.getBranches().get(i).clone();
		}
		Object hub = new Hub(branches, packages,trucks);
		return hub;
		
	}

	public ArrayList<Branch> getBranches() {
		return branches;
	}

	
	public void add_branch(Branch branch) {
		branches.add(branch);
		System.out.println("ALL THE BRANCHES " + branches.toString() + "Size of Branches " + branches.size());
	}
	
	public void addBranch(int index) {
		System.out.println("INDEX " + index + "THE BRANCH COPY " + this.getBranches().get(index-1).getName());
		Branch branch = (Branch)this.getBranches().get(index-1).clone();
		add_branch(branch);
		PostSystemPanel.addBranches();
		
	}
	
	public synchronized void sendTruck(StandardTruck t) {
		synchronized(t) {
			t.notify();
		}
		t.setAvailable(false);
		t.setDestination(branches.get(currentIndex));
		t.load(this, t.getDestination(), Status.BRANCH_TRANSPORT);
		
		
		t.setTimeLeft(((new Random()).nextInt(10)+1)*10);
		t.initTime = t.getTimeLeft();
		System.out.println(t.getName() + " is on it's way to " + t.getDestination().getName() + ", time to arrive: "+t.getTimeLeft());	
		currentIndex=(currentIndex+1)%branches.size();
	}
	
	
	public synchronized void shipNonStandard(NonStandardTruck t) {
		for (Package p: listPackages) {
			if (p instanceof NonStandardPackage) {
				/*if (((NonStandardPackage) p).getHeight() <= t.getHeight() 
					&& ((NonStandardPackage) p).getLength()<=t.getLength()
					&& ((NonStandardPackage) p).getWidth()<=t.getWidth()){*/
						synchronized(t) {
							t.notify();
						}
						t.collectPackage(p);
						listPackages.remove(p);
						return;
					//}
			}
		}	
	}
	
	
	@Override
	public void work() {

	}
	

	@Override
	public void run() {
		this.running.set(true);
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
			for (Truck t : listTrucks) {
				if (t.isAvailable()){
					if(t instanceof NonStandardTruck) {
						shipNonStandard((NonStandardTruck)t);
					}
					else {
						sendTruck((StandardTruck)t);
					}
				}	
			}
		}
	}
	
	@Override
	public String toString() {
		if(this.getBranches() != null)
			return "NameBranch: " + this.getName() + " NumOfBranches: " + this.getBranches().size() + " NumOfTrucks: " + this.getTrucks().size();
		return "";
	}


}
