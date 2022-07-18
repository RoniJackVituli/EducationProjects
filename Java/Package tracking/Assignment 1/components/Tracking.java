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

package components;

public class Tracking {
	private int time;	
	private Node node; 
	private Status status; 
	
	public Tracking(int time, Node node, Status status) { // ctor 
		this.time = time;
		if(node == null) {
			Node n = new Customer();
			this.node = n;
		}else{
			this.node = node;
		}
		this.status = status;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Tracking other = (Tracking) obj;
		if (node == null) {
			if (other.node != null)
				return false;
		} else if (!node.equals(other.node))
			return false;
		if (status != other.status)
			return false;
		if (time != other.time)
			return false;
		return true;
	}

	public int getTime() {
		return time;
	}


	public void setTime(int time) {
		this.time = time;
	}


	public Node getNode() {
		return node;
	}


	public void setNode(Node node) {
		this.node = node;
	}


	public Status getStatus() {
		return status;
	}


	public void setStatus(Status status) {
		this.status = status;
	}


	@Override
	public String toString() {
		return node.getName() +", status = " + getStatus() +" :" + getTime();
	}
}
