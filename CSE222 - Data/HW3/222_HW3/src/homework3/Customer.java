package homework3;

/**
 * Represents customers.
 * @author Fatih
 *
 */
public class Customer extends User{
	
	private int number;
	private String phone;
	private String adress;
	private String[] history;
	
	public Customer() {
		history = new String[1];
	}

	public int getNumber() {
		return number;
	}

	public void setNumber(int number) {
		this.number = number;
	}

	public String getPhone() {
		return phone;
	}

	public void setPhone(String phone) {
		this.phone = phone;
	}

	public String getAdress() {
		return adress;
	}

	public void setAdress(String adress) {
		this.adress = adress;
	}
	/**
	 * Adds a product to the customer's purchase histroy.
	 * @param a
	 */
	public void addHistory(Product a) {
		if(history[0] == null) {
			history[0] = a.toString();
			return;
		}
		
		String[] temp = new String[history.length + 1];
		for(int i = 0; i<history.length; i++) {
			temp[i] = history[i];
		}
		temp[history.length] = a.toString();
		
		history = temp;
		
	}
	/**
	 * Adds a product to the customer's purchase histroy.
	 * @param model
	 * @param color
	 * @param name
	 */
	public void addHistory(String model , String color , String name) {
		if(history[0] == null) {
			history[0] = model + " " + color + " " + name;
			return;
		}
		
		String[] temp = new String[history.length + 1];
		for(int i = 0; i<history.length; i++) {
			temp[i] = history[i];
		}
		temp[history.length] = model + " " + color + " " + name;
		
		history = temp;
	}
	/**
	 * Shows the customers purchase history.
	 */
	public void see_history() {
		for(int i = 0; i<history.length; i++) {
			System.out.println(history[i]);
		}
	}


}
