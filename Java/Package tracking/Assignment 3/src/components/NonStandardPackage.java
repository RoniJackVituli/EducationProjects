package components;

public class NonStandardPackage extends Package {
	private int width, length, height;	
	
	public NonStandardPackage(Priority priority, Address senderAddress,Address destinationAdress,int width, int length, int height) {
			super( priority, senderAddress,destinationAdress);
			this.width=width;
			this.length=length;
			this.height=height;	
			System.out.println("Creating " + this);
	}
	
	@Override
	public Object clone() {
		Priority priority = this.getPriority();
		Address senderAddress = (Address)this.getSenderAddress().clone();
		Address destinationAdress = (Address)this.getDestinationAddress().clone();
		int width = this.width;
		int length = this.length;
		int height = this.height;
		return new NonStandardPackage(priority, senderAddress, destinationAdress, width, length, height);
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
	public String toString() {
		return "NonStandardPackage ["+super.toString() + ", width=" + width + ", length=" + length + ", height=" + height + "]";
	}
	
}
