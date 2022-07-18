package application;

import compoments.Patient;

public class CheckIndice {
	private final String MAN = "זכר";
	private final String WOMAN = "נקבה";
	private final String DS = "כהה עור";
	private final String MZ = "מזרח";
	private Patient p;
	
	public CheckIndice(Patient p) {
		this.p = p ;
	}
	
	public Status wbc(int wbc){
		if(p.getAge() >= 18) {
			if(wbc >= 4500 && wbc <= 11000)
				return Status.NORMAL;
			else if(wbc > 11000)
				return Status.HIGHT;
			return Status.LOW;
			
		}else if(p.getAge() >= 4 && p.getAge() <= 17) {
			if(wbc >= 5500 && wbc <= 15500)
				return Status.NORMAL;
			else if(wbc > 15500)
				return Status.HIGHT;
			return Status.LOW;
			
		}else if(p.getAge() >= 0 && p.getAge() <= 3) {
			if(wbc >= 6000 && wbc <= 17500)
				return Status.NORMAL;
			else if(wbc > 17500)
				return Status.HIGHT;
			return Status.LOW;
		}
		return null;		
	}

	public Status Neut(int n) {
		if(n >= 28 && n <= 54)
			return Status.NORMAL;
		else if(n > 54)
			return Status.HIGHT;
		return Status.LOW;
	}
	
	
	public Status Lymph(int l) {
		if(l >= 36 && l <= 52)
			return Status.NORMAL;
		else if(l > 52)
			return Status.HIGHT;
		return Status.LOW;
	}
	
	public Status RBC(float rbc) {
		if(rbc >= 4.5 && rbc <= 6)
			return Status.NORMAL;
		else if(rbc > 6)
			return Status.HIGHT;
		return Status.LOW;
	}
	
	
	public Status HCT(int hct) {
		if(p.getGender() == MAN) {
			if(hct >= 37 && hct <= 54)
				return Status.NORMAL;
			else if(hct > 54)
				return Status.HIGHT;
			return Status.LOW;
		}else if(p.getGender() == WOMAN){
			if(hct >= 33 && hct <= 47)
				return Status.NORMAL;
			else if(hct > 47)
				return Status.HIGHT;
			return Status.LOW;
		}
		return null;
	}
	
	
	public Status Urea(int urea) {	
		
		if(p.getEthnic_group() == MZ) {
			if(urea >= 19 && urea <= 47)
				return Status.NORMAL;
			else if(urea > 47)
				return Status.HIGHT;
			return Status.LOW;
		}
		if(urea >= 17 && urea <= 43)
			return Status.NORMAL;
		else if(urea > 43)
			return Status.HIGHT;
		return Status.LOW;
	}
	
	
	public Status Hb(float hb) {
		if(p.getAge() >= 0 && p.getAge() <= 17) {
			if(hb >= 11.5 && hb <= 15.5)
				return Status.NORMAL;
			else if(hb > 15.5)
				return Status.HIGHT;
			return Status.LOW;
		}else if(p.getGender() == MAN) {
			if(hb >= 12 && hb <= 18)
				return Status.NORMAL;
			else if(hb > 18)
				return Status.HIGHT;
			return Status.LOW;
		}else if(p.getGender() == WOMAN) {
			if(hb >= 12 && hb <= 16)
				return Status.NORMAL;
			else if(hb > 16)
				return Status.HIGHT;
			return Status.LOW;
		}
		return null;
	}
	
	
	public Status Creatinine(float creatinine) {
		//Ages 0-2
		if(p.getAge() >= 0 && p.getAge() <= 2) {
			if(creatinine >= 0.2 && creatinine <= 0.5)
				return Status.NORMAL;
			else if(creatinine > 0.5)
				return Status.HIGHT;
			return Status.LOW;
		//Ages 3-17	
		}else if(p.getAge() >= 3 && p.getAge() <= 17) {
			if(creatinine >= 0.5 && creatinine <= 1)
				return Status.NORMAL;
			else if(creatinine > 1)
				return Status.HIGHT;
			return Status.LOW;
		//Ages 18-59
		}else if(p.getAge() >= 18 && p.getAge() <= 59) {
			if(creatinine >= 0.6 && creatinine <= 1)
				return Status.NORMAL;
			else if(creatinine > 1)
				return Status.HIGHT;
			return Status.LOW;
		//Ages 60+
		}else if(p.getAge() >= 60) {
			if(creatinine >= 0.6 && creatinine <= 1.2)
				return Status.NORMAL;
			else if(creatinine > 1.2)
				return Status.HIGHT;
			return Status.LOW;
		}
		return null;
	}
	
	
	public Status Iron(int iron) {
		if(p.getGender() == MAN) {
			if(iron >= 60 && iron <= 160)
				return Status.NORMAL;
			else if(iron > 160)
				return Status.HIGHT;
			return Status.LOW;
		}else if(p.getGender() == WOMAN) {
			if(iron >= 48 && iron <= 128)
				return Status.NORMAL;
			else if(iron > 128)
				return Status.HIGHT;
			return Status.LOW;
		}
		return null;
	}
	
	
	public Status HDL(int hdl) {
		if(p.getEthnic_group() != DS) {
			if(p.getGender() == MAN) {
				if(hdl >= 29 && hdl <= 62)
					return Status.NORMAL;
				else if(hdl > 62)
					return Status.HIGHT;
				return Status.LOW;
			}else if(p.getGender() == WOMAN) {
				if(hdl >= 34 && hdl <= 82)
					return Status.NORMAL;
				else if(hdl > 82)
					return Status.HIGHT;
				return Status.LOW;
			}
		}else {
			if(p.getGender() == MAN) {
				if(hdl >= 64 && hdl <= 74)
					return Status.NORMAL;
				else if(hdl > 74)
					return Status.HIGHT;
				return Status.LOW;
			}else if(p.getGender() == WOMAN) {
				if(hdl >= 41 && hdl <= 98)
					return Status.NORMAL;
				else if(hdl > 98)
					return Status.HIGHT;
				return Status.LOW;
			}
		}
		return null;
	}
	
	
	public Status AP(int ap) {
		if(p.getEthnic_group() == MZ) {
			if(ap >= 60 && ap <= 120)
				return Status.NORMAL;
			else if(ap > 120)
				return Status.HIGHT;
			return Status.LOW;
		}
		if(ap >= 30 && ap <= 90)
			return Status.NORMAL;
		else if(ap > 90)
			return Status.HIGHT;
		return Status.LOW;
	}
	
	
}
