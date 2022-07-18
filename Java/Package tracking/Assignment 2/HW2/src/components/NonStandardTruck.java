package components;

import java.util.Random;

public class NonStandardTruck extends Truck implements Runnable{
	
	/**
	 * <h1>The NonStandardTruck class</h1>
	 * represents a truck for transporting packages from the hub to client and inherits from a Truck class. 
	 * all trucks belong to the hub.
	 * The class has three fields:
	 * 1. width 
	 * 2. length 
	 * 3. height 
	 * all this three fields calculate the capacity of the truck.
	 * 
	 * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
	 * */

	private int width, length, height;	


	public NonStandardTruck() {
		super();
		Random r=new Random();
		width=(r.nextInt(3)+2)*100;
		length=(r.nextInt(6)+10)*100;
		height=(r.nextInt(2)+3)*100;
		System.out.println(this);
	}
	
	
	public NonStandardTruck(String licensePlate,String truckModel, int length, int width, int height) {
		super(licensePlate,truckModel);
		this.width=width;
		this.length=length;
		this.height=height;
		System.out.println(this);
	}

	
	public int getWidth() {
		return width;
	}

	
	public void setWidth(int width) {
		this.width = width;
	}

	
	public int getLength() {
		return length;
	}

	
	public void setLength(int length) {
		this.length = length;
	}

	
	public int getHeight() {
		return height;
	}

	
	public void setHeight(int height) {
		this.height = height;
	}
	
	
	@Override
	public synchronized void work() {
		if (!this.isAvailable()) {
			Package p = this.getPackages().get(0);
			this.setTimeLeft(this.getTimeLeft()-1);
			if (this.getTimeLeft()==0) {
				if (p.getStatus()==Status.COLLECTION) {
					this.getLocation().x = (int) p.getPackageCordX() + 7;
					this.getLocation().y = (int) p.getPackageCordClientY();
					this.getTarget().y =(int)p.getPackageCordCustomerY();
					System.out.println(getName() + " has collected "+p.getName());
					deliverPackage(p);
				}
					
				else {
					System.out.println(getName() + " has delivered "+p.getName() + " to the destination");
					this.getPackages().remove(p);
					p.addRecords(Status.DELIVERED, null);
					setAvailable(true);
				}
			}else {
				if(p.getStatus() == Status.COLLECTION) {
					int x = (int)(1125 + ((p.getPackageCordX()+10) - 1125)*this.timeNonB/this.timeNonA);
					int y = (int)(250 + ((p.getPackageCordClientY()+27) - 250)*this.timeNonB/this.timeNonA);
					this.timeNonB++;
					this.getLocation().x = x;
					this.getLocation().y = y-5;
				}else if(p.getStatus() == Status.DISTRIBUTION) {
					int y = (int)(p.getPackageCordClientY() + (p.getPackageCordCustomerY() - p.getPackageCordClientY())*this.timeNonB/this.timeNonA);
					this.timeNonB++;
					this.getLocation().y = y;
					
				}
			}
		}
	}
	
	
	@Override
	public void deliverPackage (Package p)  {
		int time=Math.abs(p.getDestinationAddress().getStreet()-p.getSenderAddress().getStreet())%10+1;
		this.setTimeLeft(time*10);
		this.timeNonA = time*10;
		this.timeNonB = 1;
		p.addRecords(Status.DISTRIBUTION, this);
		System.out.println(getName() + " is delivering " + p.getName() + ", time left: "+ this.getTimeLeft()  );
	}
	
	
	@Override
	public String toString() {
		return "NonStandardTruck ["+ super.toString() + ", length=" + length +  ", width=" + width + ", height="
				+ height + "]";
	}


	@Override
	public void run() {
		work();
	}
	
}

