package components;

public class SmallPackage extends Package {
	private boolean acknowledge;
	
	
	public SmallPackage(Priority priority, Address senderAddress,Address destinationAdress, boolean acknowledge){
		super(priority, senderAddress,destinationAdress);
		this.acknowledge=acknowledge;
		System.out.println("Creating " + this);

	}
	
	
	public boolean isAcknowledge() {
		return acknowledge;
	}
	
	
	public void setAcknowledge(boolean acknowledge) {
		this.acknowledge = acknowledge;
	}
	
	
	@Override
	public String toString() {
		return "SmallPackage ["+ super.toString() +", acknowledge=" + acknowledge + "]";
	}


	@Override
	public Object clone() {
		Priority priority = this.getPriority();
		Address senderAddress = (Address)this.getSenderAddress().clone();
		Address destinationAdress = (Address)this.getDestinationAddress().clone();
		boolean acknowledge = this.acknowledge;
		return new SmallPackage(priority, senderAddress, destinationAdress, acknowledge);
	}
	
		
}
