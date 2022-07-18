package tests;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import application.CheckIndice;
import application.DetalisController;
import application.LogInController;
import application.Status;
import compoments.Patient;

public class Junit4AssertionTest {				
	DetalisController dc;	
	LogInController login;
	Patient P1 , P2;
	@Before
	public void setUp() {
		dc = new DetalisController();
		P1 = new Patient("258963147", "Daniel Dahan", 25, "זכר", "מזרח");
		P2 = new Patient("315369967", "Roni Jack Vituli", 26, "זכר", "אשכנז");
	}
	
    @Test		
    public void testName(){					
        //Assert statements	
    	assertFalse(dc.isThereOnlyLetters("21Roni"));										
    	assertFalse(dc.isThereOnlyLetters("ro4n1"));										
    	assertTrue(dc.isThereOnlyLetters("Roni"));		
    	assertTrue(dc.isThereOnlyLetters("Daniel"));		
    	assertFalse(dc.isThereOnlyLetters("231321"));		
    }	
    
    @Test
    public void testPatient() {
    	assertNotEquals(P2, P1);
    	assertNotEquals(P2.getID(),	 P1.getID());
    	assertEquals(P2.getGender(), P1.getGender());
    	assertNotEquals(P2.getEthnic_group(), P1.getEthnic_group());	
    }
    
    @Test
    public void testWBC() {
    	int wbc = 5000;
    	Status s1, s2 = Status.NORMAL;
    	CheckIndice checkIndice = new CheckIndice(P1);
    	s1 = checkIndice.wbc(wbc);
    	assertEquals(s2, s1);
    	wbc = 12000;
    	s1 = checkIndice.wbc(wbc);
    	assertNotEquals(s2, s1);
    	wbc = 1000;
    	s1 = checkIndice.wbc(wbc);
    	assertNotEquals(s2, s1);
    }
    
    @Test
    public void testRBC() {
    	int rbc = 5;
    	Status s1, s2 = Status.NORMAL;
    	CheckIndice checkIndice = new CheckIndice(P1);
    	s1 = checkIndice.RBC(rbc);
    	assertEquals(s2, s1);
    	rbc = 4;
    	s1 = checkIndice.RBC(rbc);
    	assertNotEquals(s2, s1);
    	rbc = 7;
    	s1 = checkIndice.RBC(rbc);
    	assertNotEquals(s2, s1);
    }
    
    
    
 
    
    
}		
