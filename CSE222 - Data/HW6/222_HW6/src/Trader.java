/**
 * The user Trader class.
 * @author Fatih
 *
 */
public class Trader implements Users{
	
	private String name;
	private int ID;
	private int password;
	
	public Trader(String name) {
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}

	public int getID() {
		return ID;
	}

	public void setID(int iD) {
		ID = iD;
	}

	public int getPassword() {
		return password;
	}

	public void setPassword(int password) {
		this.password = password;
	}
	
}
