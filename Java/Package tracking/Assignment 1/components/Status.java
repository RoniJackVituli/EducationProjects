package components;

/**
 * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
 * */


public enum Status {
	CREATION, // Initial status of each package created.
	
	COLLECTION, // when the vehicle is on the way to pick up the package from the sender's address
	
	BRANCH_STORAGE, // the package is pick up from the client and arrived to branch local. 
	
	HUB_TRANSPORT, // the package is on the way from the branch local to sorting center 
	
	HUB_STORAGE, // the package arrived to sorting center and waiting to transform to the destination branch 
	
	BRANCH_TRANSPORT, // the package is on the way from sorting center to the destination branch 
	
	DELIVERY, // the package has arrived at the destination branch and is ready for delivery to the end customer.
	
	DISTRIBUTION, // the package on the way from the destination branch to the end customer.
	
	DELIVERED // the package was delivered to the final customer.
}
