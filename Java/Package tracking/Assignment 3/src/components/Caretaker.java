package components;
//

import java.util.List;
import java.util.ArrayList;


public class Caretaker {
	private List<Memento> mainOfficeList = new ArrayList<Memento>();
	
	public void addMemento(Memento m) {
		mainOfficeList.add(m);
	}
	public Memento getMemento(){
		Memento m;
		if(mainOfficeList.size() > 1) {
			m = mainOfficeList.get(mainOfficeList.size()-1);
			mainOfficeList.remove(mainOfficeList.size()-1);
			return m;
		}
		if(!mainOfficeList.isEmpty()) {
			m = mainOfficeList.get(0);
			mainOfficeList.remove(0);
			return m;
		}
		return null;
	}
	
	public boolean isEmpty() {
		return mainOfficeList.isEmpty();
	}
}
