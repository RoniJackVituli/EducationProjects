package components;

import java.util.ArrayList;
import java.util.Random;

public class Hub extends Branch{
	
	private ArrayList<Branch> branches=new ArrayList<Branch>();
	private int currentIndex=0;
	
	public Hub() {
		super("HUB");
	}
	

	public ArrayList<Branch> getBranches() {
		return branches;
	}

	
	public void add_branch(Branch branch) {
		branches.add(branch);
	}

	
	public void shipNonStandard(NonStandardTruck t) {
		for (Package p: packages) {
			if (p instanceof NonStandardPackage) {
				if (1 <= t.getHeight() && 1 <= t.getLength() && 1 <=t.getWidth()){
						t.collectPackage(p);
						packages.remove(p);
						return;
					}
			}
		}	
	}
	
	
	@Override
	public void localWork() {
		for (Truck t : listTrucks) {
			if (t.isAvailable()){
				if(t instanceof NonStandardTruck) 
					shipNonStandard((NonStandardTruck)t);
				else{
					sendTruck((StandardTruck)t);
				}
			}	
		}	
	}
	
	
	public void sendTruck(StandardTruck t) {
		t.setAvailable(false);
		t.setDestination(branches.get(currentIndex));
		t.load(this, t.getDestination(), Status.BRANCH_TRANSPORT);
		t.setTimeLeft(((new Random()).nextInt(20)+1)*10);
		t.setTime(t.getTimeLeft());
		t.setTime2(1);
		System.out.println(t.getName() + " is on it's way to " + t.getDestination().getName() + ", time to arrive: "+t.getTimeLeft());	
		currentIndex=(currentIndex+1)%branches.size();
	}
	

}
