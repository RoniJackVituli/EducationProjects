package components;

/**
 * Node is an interface
 * when this interface represents the location of a package and this interface applies to branches and trucks.
 * 
 * within the interface we created 4 methods:
 * 1.collectPackage -> A method that handles the collection / receipt of a package by the implementing department.
 * 2.deliverPackage -> A method that handles the delivery of the package to the next person in the transfer chain.
 * 3.work -> A method that performs a work unit.
 * 4.getName -> A method that returns the name of the implementing class.
 * 
 * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
 * */

interface Node { 
	public void collectPackage(Package p);
	public void deliverPackage(Package p);
	public void work();
	public String getName();
  
}
