package components;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;

import javax.swing.JPanel;

import program.PostSystemPanel;



public class MainOffice implements Runnable, PropertyChangeListener, observer, StopRunnable {

	private static MainOffice mainOffice;
	private static int clock=0;
	private static Hub hub;
	private static ArrayList<Package> packages=new ArrayList<Package>();
	private JPanel panel;
	private ReadWriteLock rwl;
	private boolean threadSuspend = false;
	private ArrayList<Customer> customers = new ArrayList<Customer>();
	private ReadWriteFile readWriteFile;
	private static int line = 1;
	private Originator originator = new Originator();
	private Caretaker caretaker = new Caretaker();
	private static int numOfClients = 10;
	private final AtomicBoolean running = new AtomicBoolean(false);

	public static MainOffice getInstance() {
		return mainOffice;
	}

	public static MainOffice getInstance(int branches, int trucksForBranch, JPanel panel) {
		if(mainOffice == null) {
			synchronized (MainOffice.class) {
				if(mainOffice == null) {
					mainOffice = new MainOffice(branches,trucksForBranch, panel);	
				}
			}
		}
		return mainOffice;
	}

	private MainOffice (int branches, int trucksForBranch, JPanel panel) {
		this.panel = panel;
		//		this.maxPackages = maxPack;
		addHub(trucksForBranch);
		addBranches(branches, trucksForBranch);
		int sizeOfBranch = hub.getBranches().size(), random;
		for(int i = 0; i < numOfClients ; i++) {
			random = new Random().nextInt(sizeOfBranch);
			Address address = new Address(random, new Random().nextInt(999999)+100000);
			customers.add(new Customer(i+1, address));
		}
		try {
			PrintWriter writer = new PrintWriter(new File("C:/Users/roniz/eclipse-workspace/HW2_solution/src/components/tracking.txt"));
			writer.print("");
			writer.close();

		}catch(IOException e) {
			e.printStackTrace();
		}
		readWriteFile = ReadWriteFile.getInstance();
		System.out.println("\n\n========================== START ==========================");
	}

	
	@Override
	public synchronized void propertyChange(PropertyChangeEvent evt) {
		Object d = evt.getNewValue();
		Package p = (Package)evt.getSource();
		p.setStatus((Status)d);
		rwl = new ReadWriteLock() {
			
			@Override
			public Lock writeLock() {
				readWriteFile.writeFile(p.toString(), line++);
				return null;
			}
			
			@Override
			public Lock readLock() {
				// TODO Auto-generated method stub
				return null;
			}
		};
		rwl.writeLock();
		
	}


	public static int setLine() {
		return line++;
	}

	public static Hub getHub() {
		return hub;
	}


	public static int getClock() {
		return clock;
	}

	public static synchronized ArrayList<Package> getPack(){
		return packages;
	}
	@Override
	public void run() {
		
		Thread hubThrad = new Thread(hub);
		
		for(Customer c : customers) {
			Thread customer = new Thread(c);
			customer.start();
		}
		hubThrad.start();
		for (Truck t : hub.listTrucks) {
			Thread trackThread = new Thread(t);
			trackThread.start();
		}
		for (Branch b: hub.getBranches()) {
			Thread branch = new Thread(b);
			for (Truck t : b.listTrucks) {
				Thread trackThread = new Thread(t);
				trackThread.start();
			}
			branch.start();
		}
		for(Customer c: customers) {
			Thread CustomerThread = new Thread(c);
			CustomerThread.start();
		}
		running.set(true);
		while(running.get()) {
			synchronized(this) {
				while (threadSuspend)
					try {
						wait();
					} catch (InterruptedException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
			}
			tick();
		}
	}


	public static int getNumOfClients() {
		return numOfClients;
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
		try {
			Thread.sleep(300);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println(clockString());
		clock++;
		//		if (clock++%5==0) {
		//			addPackage();
		//		}
		/*branchWork(hub);
		for (Branch b:hub.getBranches()) {
			branchWork(b);
		}*/
		panel.repaint();
	}
	
	

	public void branchWork(Branch b) {
		for (Truck t : b.listTrucks) {
			t.work();
		}
		b.work();
	}


	public void addHub(int trucksForBranch) {
		hub=new Hub();
		for (int i=0; i<trucksForBranch; i++) {
			Truck t = new StandardTruck();
			hub.addTruck(t);
		}
		Truck t=new NonStandardTruck();
		hub.addTruck(t);
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


	public synchronized void setSuspend() {
		threadSuspend = true;
		
		for(Customer c: customers) {
			c.setSuspend();
		}
		
		for (Truck t : hub.listTrucks) {
			t.setSuspend();
		}
		for (Branch b: hub.getBranches()) {
			for (Truck t : b.listTrucks) {
				t.setSuspend();
			}
			b.setSuspend();
		}
		hub.setSuspend();
	}



	public synchronized void setResume() {
		threadSuspend = false;
		notify();
		hub.setResume();
		for (Truck t : hub.listTrucks) {
			t.setResume();
		}
		for (Branch b: hub.getBranches()) {
			b.setResume();
			for (Truck t : b.listTrucks) {
				t.setResume();
			}
		}
		for(Customer c: customers)
			c.setResume();
	
	}

	@Override
	public void addObserver() {
		for (Truck t : hub.listTrucks) {
			t.addObserver();
		}
		hub.addObserver();
		for (Branch b: hub.getBranches()) {
			for (Truck t : b.listTrucks) {
				t.addObserver();
			}
			b.addObserver();
		}	
	}
	
	public void addBranch(int index) {
		this.setSuspend();
		originator.setMainOffice(this);
		Memento memento = originator.createMemento();
		caretaker.addMemento(memento);
		hub.addBranch(index);	
		System.out.println("Packages After add Branch =====> " + this.getPack().size());
		this.setResume();

		System.out.println("HUB AFTER ADD BRANCH===> " + hub.toString());
	}
	
	public void restore() {
		this.setSuspend();
		this.stop();
		Memento memento = caretaker.getMemento();
		if(memento != null) {
			System.out.println(memento.getHub().toString());
			hub = memento.getHub();
			packages = memento.getPackages();
		}
		System.out.println(" PACKAGES AFTER RESTORE =========> SIZE: " + this.packages.size() + 
				"\nTHE PACKAGES ON THE SYSTEM " + this.packages.toString());
		this.setResume();
		new Thread(this).start();
//		new Thread(hub).start();
//		for (Truck t : hub.listTrucks) {
//			Thread trackThread = new Thread(t);
//			trackThread.start();
//		}
//		for (Branch b: hub.getBranches()) {
//			Thread branch = new Thread(b);
//			for (Truck t : b.listTrucks) {
//				System.out.println("WHAT TRUCK IAM: "+ t.toString());
//				Thread trackThread = new Thread(t);
//				trackThread.start();
//			}
//			branch.start();
//		}
//		
		if(!caretaker.isEmpty())
			PostSystemPanel.subBranches();
		System.out.println("SUCCSES");
	}

	public static void callSetSuspend() {
		mainOffice.setSuspend();
	}

	public void stop() {
		
		for (Truck t : hub.listTrucks) {
			t.stop();
		}
		for (Branch b: hub.getBranches()) {
			for (Truck t : b.listTrucks) {
				t.stop();
			}
			b.stop();
		}
		hub.stop();
		running.set(false);	
	}


	public ArrayList<Customer> getCustomers() {
		return customers;
	}
	
	public static void callStop() {
		mainOffice.stop();
	}

}
