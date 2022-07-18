package components;

import java.awt.Graphics;
import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;


public  abstract class Truck implements Node,Runnable,observer,Cloneable,StopRunnable {
	private static int countID=2000;
	final private int truckID;
	protected final AtomicBoolean running = new AtomicBoolean(false);
	private String licensePlate;
	private String truckModel;
	private boolean available=true;
	private int timeLeft=0;
	private ArrayList<Package> packages=new ArrayList<Package>();
	protected int initTime;
	protected boolean threadSuspend = false;
		
	
	//default random constructor
	public Truck() {
		truckID=countID++;
		Random r= new Random();
		licensePlate=(r.nextInt(900)+100)+"-"+(r.nextInt(90)+10)+"-"+(r.nextInt(900)+100);
		truckModel="M"+r.nextInt(5);
	}

	public Truck(String licensePlate,String truckModel) {
		truckID=countID++;
		this.licensePlate=licensePlate;
		this.truckModel=truckModel;
	}
	
	
	public ArrayList<Package> getPackages() {
		return packages;
	}


	public int getTimeLeft() {
		return timeLeft;
	}

	
	public void setTimeLeft(int timeLeft) {
		this.timeLeft = timeLeft;
	}


	@Override
	public String toString() {
		return "truckID=" + truckID + ", licensePlate=" + licensePlate + ", truckModel=" + truckModel + ", available= " + available ;
	}
	
	public abstract Object clone();


	@Override
	public synchronized void collectPackage(Package p) {
		setAvailable(false);
		int time=(p.getSenderAddress().street%10+1)*10;
		this.setTimeLeft(time);
		this.initTime = time;
		this.packages.add(p);
		p.setStatus(Status.COLLECTION);
		p.addTracking(new Tracking(MainOffice.getClock(), this, p.getStatus()));
		System.out.println(getName() + " is collecting package " + p.getPackageID() + ", time to arrive: "+ getTimeLeft()  );
	}


	@Override
	public synchronized void deliverPackage(Package p) {}


	public boolean isAvailable() {
		return available;
	}
	

	public int getTruckID() {
		return truckID;
	}

	
	public void setAvailable(boolean available) {
		this.available = available;
	}
	
	
	public String getName() {
		return this.getClass().getSimpleName()+" "+ truckID;
	}
	
	public synchronized void setSuspend() {
	   	threadSuspend = true;
	}

	public synchronized void setResume() {
	   	threadSuspend = false;
	   	notify();
	}
	
	public String getLicensePlate() {
		return licensePlate;
	}
	
	public String getTrukModel() {
		return truckModel;
	}
	
	public abstract void paintComponent(Graphics g);
	public abstract void addObserver();
    public abstract void stop();

}
