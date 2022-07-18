package components;

import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;

public class Customer implements Runnable{
	private final int CREATION = 5, DELEVERY = 5;
	private int serialNumber;
	private static int ClientThatFinish = 0;
	private Address address;
	private boolean threadSuspend = false;
	private int counter = 0;
	private int delivery = 0;
	private final AtomicBoolean running = new AtomicBoolean(false);
	private ReadWriteFile write = ReadWriteFile.getInstance();
	private ReadWriteFile read = ReadWriteFile.getInstance();
	private ReadWriteLock rwl = new ReadWriteLock() {

		@Override
		public Lock writeLock() {
			write.writeFile(addPackage().toString(), MainOffice.setLine());
			return null;
		}

		@Override
		public Lock readLock() {
			setDelivey(read.readFile(getCusomter()));
			return null;
		}
	};


	private Customer getCusomter() {
		return this;
	}

	private void setDelivey(int num) {
		delivery = num;
	}

	public Customer(int serial, Address address) {
		this.serialNumber = serial;
		this.address = address;
	}

	public Package addPackage() {
		synchronized (this) {
			Random r = new Random();
			Package p;
			Branch br;
			Priority priority=Priority.values()[r.nextInt(3)];
			//			Address sender = new Address(r.nextInt(MainOffice.getHub().getBranches().size()), r.nextInt(999999)+100000);
			Address sender = new Address(r.nextInt(MainOffice.getHub().getBranches().size()), getAddressStreet());
			Address dest = new Address(r.nextInt(MainOffice.getHub().getBranches().size()), r.nextInt(999999)+100000);


			switch (r.nextInt(3)){
			case 0:
				p = new SmallPackage(priority,  sender, dest, r.nextBoolean() );
				br = MainOffice.getHub().getBranches().get(sender.zip);
				br.addPackage(p);
				p.setBranch(br); 
				break;
			case 1:
				p = new StandardPackage(priority,  sender, dest, r.nextFloat()+(r.nextInt(9)+1));
				br = MainOffice.getHub().getBranches().get(sender.zip); 
				br.addPackage(p);
				p.setBranch(br); 
				break;
			case 2:
				p=new NonStandardPackage(priority,  sender, dest,  r.nextInt(1000), r.nextInt(500), r.nextInt(400));
				MainOffice.getHub().addPackage(p);
				break;
			default:
				p=null;
			}
			MainOffice.getPack().add(p);				
			return p;
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
	public String toString() {
		return "Customer " + serialNumber + " and i live in: " + address;
	}

	//	@Override
	//	public void run() {
	//		while()
	//		
	//		synchronized (this) {
	//			while(counter != CREATION) {
	//				try {
	//					Thread.sleep(new Random().nextInt(5000-2000)+2000);
	//				} catch (InterruptedException e) {
	//					// TODO Auto-generated catch block
	//					e.printStackTrace();
	//				}
	//				while(threadSuspend) {
	//					try {
	//						wait();
	//					}catch (InterruptedException e1) {
	//						// TODO Auto-generated catch block
	//						e1.printStackTrace();
	//					}
	//				}
	//				rwl.writeLock();
	//				counter++;
	//			}
	//			while(delivery != DELEVERY) {
	//				try {
	//					Thread.sleep(10000);
	//					//				delivery = read.readFile(this);
	//					rwl.readLock();
	//				}catch(InterruptedException e) {
	//					e.printStackTrace();
	//				}
	//			}	
	//			ClientThatFinish++;
	//			if(ClientThatFinish == 2)
	//				MainOffice.callSetSuspend();
	//			System.out.println("ALL MY PACKAGE IS ARRIVED!");
	//		}
	//	}

	@Override
	public void run() {
		running.set(true);
		while(running.get()) {
			try {
				Thread.sleep(new Random().nextInt(5000-2000)+2000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if(counter >= CREATION) {
				while(delivery < DELEVERY) {
					try {
						Thread.sleep(10000);
						rwl.readLock();
					}catch(InterruptedException e){
						e.printStackTrace();
					}
				}
				ClientThatFinish++;
				running.set(false);
				if(ClientThatFinish == MainOffice.getNumOfClients()) {
					System.out.println("=======================All The Packages Arrived======================");
					MainOffice.callStop();
				}
			}else {
				synchronized(this) {
					while (threadSuspend)
						try {
							wait();
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
				}
				rwl.writeLock();
				counter++;
			}
		}
	}










	public int getAddressStreet() {
		return address.street;
	}

	public Address getAddress() {
		return address;
	}

}
