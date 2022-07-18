package components;

/**
 * 
 * <h1>The Tracking Class</h1>
 * The class Tracking represents a record in the transfer history of the package.
 * each package has a collection of records of this type.
 * in this class it have 3 fields: time, node, status.
 * 1. time -> this is the value of the system clock as soon as the record is created.
 * 2. node -> package location - customer / branch / hub / transport vehicle.
 * 3. status -> this variable, receives each time the status of the package i.e. the shipping stages of the package.
 
 * within the class there are also set & get methods for each variable. 
 In addition there is a constructor that accepts the three parameters and builds a new object.
 
 * We also ran the toString method to print our variables in the order they requested.
 * 
 * 
 * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
 * */
public class Tracking {
	public final int time;
	public final Node node;
	public final Status status;
	
	public Tracking(int time, Node node, Status status) {
		super();
		this.time = time;
		this.node = node;
		this.status = status;
	}

	public Tracking (Node node, Status status) {
		this(MainOffice.getClock(),node,status);
	}
	
	@Override
	public String toString() {
		String name = (node==null)? "Customer" : node.getName();
		return time + ": " + name + ", status=" + status;
	}

	
}
