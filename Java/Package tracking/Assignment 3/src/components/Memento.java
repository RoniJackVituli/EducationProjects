package components;

import java.util.ArrayList;
import java.util.concurrent.locks.ReadWriteLock;

import javax.swing.JPanel;

public class Memento {
	
	private static Hub hub;
	private static ArrayList<Package> packages=new ArrayList<Package>();

	public Memento(MainOffice mainOffice) {
		System.out.println("HUB BEFORE ===> " + mainOffice.getHub().toString());
		this.hub = (Hub)mainOffice.getHub().clone();
		System.out.println("HUB AFTER ===> " + this.hub.toString());
		
		System.out.println("Packages Before =====> " + mainOffice.getPack().size());
		this.packages = (ArrayList<Package>)mainOffice.getPack().clone();
		System.out.println("Packages After =====> " + this.packages.size());
	}
	
	public Hub getHub() {
		return hub;
	}
	public  ArrayList<Package> getPackages(){
		return packages;
	}
}
