package components;

public class Originator {
	private MainOffice mainOffice;
	
	public void setMainOffice(MainOffice mainOffice) {
		this.mainOffice = mainOffice; 
	}
	public Memento createMemento() {
		return new Memento(mainOffice);
	}
	
}
