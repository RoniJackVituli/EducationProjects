package components;

public class StandardPackage extends Package {
	
	private double weight;
	
	
	public StandardPackage(Priority priority, Address senderAddress, Address destinationAdress,double weight) {
		super( priority, senderAddress,destinationAdress);
		this.weight=weight;
		System.out.println("Creating " + this);
	}

	
	public double getWeight() {
		return weight;
	}

	
	public void setWeight(double weight) {
		this.weight = weight;
	}
	@Override
	public Object clone() {
		Priority priority = this.getPriority();
		Address senderAddress = (Address)this.getSenderAddress().clone();
		Address destinationAdress = (Address)this.getDestinationAddress().clone();
		double weight = this.weight; 
		return new StandardPackage(priority, senderAddress, destinationAdress, weight);
	}
	
	@Override
	public String toString() {
		return "StandardPackage ["+ super.toString()+", weight=" + weight + "]";
	}
}
