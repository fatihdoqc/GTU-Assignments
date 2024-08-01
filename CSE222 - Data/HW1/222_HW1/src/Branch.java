/**
 * Represents a branch of the company
 * @author Fatih
 *
 */
public class Branch {
	
	private Product[] desks = new Desk[2];
	private Product[] bookcases = new Bookcase[4];
	private Product[] cabinets = new Cabinet[3];
	private String name;
	
	private User[] employees = new Branch_employee[4];
	
	/**
	 * Initializes the branch with hiring employees and adding products.
	 */
	public Branch() {
		for(int i = 0; i<desks.length; i++) {
			desks[i] = new Desk();
		}
		for(int i = 0; i<bookcases.length; i++) {
			bookcases[i] = new Bookcase();
		}
		for(int i = 0; i<cabinets.length; i++) {
			cabinets[i] = new Cabinet();
		}
		for(int i = 0; i < employees.length; i++) {
			employees[i] = new Branch_employee();
		}
		employees[0].setName("Serdar");
		employees[1].setName("Ahmet");
		employees[2].setName("Murat");
		employees[3].setName("Aliye");
		
		desks[0].setModel("Round");
		desks[1].setModel("Square");
		
		desks[0].setColor("Black");
		desks[1].setColor("Black");
		
		desks[0].setStock(100);
		desks[1].setStock(9);
		
		bookcases[0].setModel("Big");
		bookcases[1].setModel("Small");
		bookcases[2].setModel("Big");
		bookcases[3].setModel("Small");
		
		bookcases[0].setColor("White");
		bookcases[1].setColor("White");
		bookcases[2].setColor("Black");
		bookcases[3].setColor("Black");
		
		bookcases[0].setStock(100);
		bookcases[1].setStock(400);
		bookcases[2].setStock(10);
		bookcases[3].setStock(300);
		
		cabinets[0].setModel("Oval");
		cabinets[1].setModel("Oval");
		cabinets[2].setModel("Oval");
		
		cabinets[0].setColor("Green");
		cabinets[1].setColor("Red");
		cabinets[2].setColor("Blue");
		
		cabinets[0].setStock(50);
		cabinets[1].setStock(500);
		cabinets[2].setStock(5000);
	}
	/**
	 * Orders an employee to make sale to the person "u".
	 * @param x
	 * @param u
	 */
	public void make_sale(Product x , User u) {
		((Branch_employee) employees[3]).sale(x , u); // Sale x to the person u.
	}
	/**
	 * Orders an employee to create a product.
	 * @param x
	 */
	public void add_product(Product x) {
		((Branch_employee) employees[1]).add_prod(x);
	}
	/**
	 * Orders an employee to delete a product.
	 * @param x
	 */
	public void del_product(Product x) {
		((Branch_employee) employees[1]).delete_product(x);
	}
	/**
	 * If the stocks are not enough, orders to an employee to inform the manager about stocks.
	 * @param x
	 */
	public void requested_amount(Product x) {
		if(x.getStock() < 50) { // Every product stock's must be higher than 50.
			((Branch_employee) employees[0]).inform_the_manager(x);
		}
	}
	/**
	 * A customer can buy a product by himself/herself with online shopping.
	 * @param u is the customer
	 * @param model
	 * @param color
	 * @param name
	 */
	public void sale(User u , String model , String color , String name) {
		if(name.equals(desks[0].getName())) {
			for(int i = 0; i< desks.length; i++) {
				if(desks[i].getModel().equals(model) && desks[i].getColor().equals(color) && desks[i].getStock() > 0) {
					desks[i].decreaseStock();
					((Customer) u).addHistory(model , color , name);
					return;
				}
			}
		}
		else if(name.equals(bookcases[0].getName())) {
			for(int i = 0; i< bookcases.length; i++) {
				if(bookcases[i].getModel().equals(model) && bookcases[i].getColor().equals(color) && bookcases[i].getStock() > 0) {
					bookcases[i].decreaseStock();
					((Customer) u).addHistory(model , color , name);
					return;
				}
			}
			
		}
		else if(name.equals(cabinets[0].getName())) {
			for(int i = 0; i< cabinets.length; i++) {
				if(cabinets[i].getModel().equals(model) && cabinets[i].getColor().equals(color) && cabinets[i].getStock() > 0) {
					cabinets[i].decreaseStock();
					((Customer) u).addHistory(model , color , name);
					return;
				}
			}
		}
	}
	/**
	 * Checks the products if the wanted one exists.
	 * @param model
	 * @param color
	 * @param name
	 * @return
	 */
	public boolean check_product(String model , String color , String name) {
		if(name.equals(desks[0].getName())) {
			for(int i = 0; i< desks.length; i++) {
				if(desks[i].getModel().equals(model) && desks[i].getColor().equals(color)) {
					return true ;
				}
			}
		}
		else if(name.equals(bookcases[0].getName())) {
			for(int i = 0; i< bookcases.length; i++) {
				if(bookcases[i].getModel().equals(model) && bookcases[i].getColor().equals(color)) {
					return true ;
				}
			}
			
		}
		else if(name.equals(cabinets[0].getName())) {
			for(int i = 0; i< cabinets.length; i++) {
				if(cabinets[i].getModel().equals(model) && cabinets[i].getColor().equals(color)) {
					return true ;
				}
			}
		}
		return false;
	}
	/**
	 * Checks the stocks of the products.And sends a feedback if the product is out of stock.
	 */
	public void stock_check() {
		for(int i = 0 ; i<desks.length; i++) {
			if(desks[i].getStock() <= 0) {
				System.out.println(desks[i].getModel() + " " + desks[i].getColor() +" is out of stock");
			}
		}
		for(int i = 0 ; i<bookcases.length; i++) {
			if(bookcases[i].getStock() <= 0) {
				System.out.println(bookcases[i].getModel() + " " + bookcases[i].getColor() +" is out of stock");
			}
		}
		for(int i = 0 ; i<cabinets.length; i++) {
			if(cabinets[i].getStock() <= 0) {
				System.out.println(cabinets[i].getModel() + " " + cabinets[i].getColor() +" is out of stock");
			}
		}
	}
	/**
	 * List all of the products in this branch.
	 */
	public void list_products() {
		for(int i = 0 ; i<desks.length; i++) {
				System.out.println(desks[i].getModel() + " " + desks[i].getColor() + " Desk ");
		}
		for(int i = 0 ; i<bookcases.length; i++) {
				System.out.println(bookcases[i].getModel() + " " + bookcases[i].getColor() + " Bookcase ");
		}
		for(int i = 0 ; i<cabinets.length; i++) {
				System.out.println(cabinets[i].getModel() + " " + cabinets[i].getColor() + " Cabinet ");
		}
	}
	/**
	 * Searches the products if the wanted one exists. Sends feedback.
	 * @param model
	 * @param color
	 * @param name
	 */
	public void search_product(String model , String color , String name) {
		if(name.equals(desks[0].getName())) {
			for(int i = 0; i< desks.length; i++) {
				if(desks[i].getModel().equals(model) && desks[i].getColor().equals(color) && desks[i].getStock() > 0) {
					System.out.println("We have that product! ");
					return;
				}
			}
		}
		else if(name.equals(bookcases[0].getName())) {
			for(int i = 0; i< bookcases.length; i++) {
				if(bookcases[i].getModel().equals(model) && bookcases[i].getColor().equals(color) && bookcases[i].getStock() > 0) {
					System.out.println("We have that product! ");
					return;
				}
			}
			
		}
		else if(name.equals(cabinets[0].getName())) {
			for(int i = 0; i< cabinets.length; i++) {
				if(cabinets[i].getModel().equals(model) && cabinets[i].getColor().equals(color) && cabinets[i].getStock() > 0) {
					System.out.println("We have that product! ");
					return;
				}
			}
		}
		System.out.println("Sorry , we haven't got any of that product.");
		
	}
	/**
	 * getter for name.
	 * @return
	 */
	public String getName() {
		return name;
	}
	/**
	 * setter for name.
	 * @param name
	 */
	public void setName(String name) {
		this.name = name;
	}
	/**
	 * Hires u2 to the branch as an employee.
	 * @param u2
	 */
	public void Add_Employee(User u2) {
		if(u2 instanceof Branch_employee) {
			User[] temp_employees = new Branch_employee[employees.length + 1];
			for(int i = 0; i < employees.length; i++) {
				temp_employees[i] = employees[i];
			}
			
			temp_employees[employees.length] = u2;
			employees = temp_employees;
		}
		else {
			System.err.println("The person you wanted to hire is not an employee");
		}
	}
	/**
	 * Fires the employee u2 from the branch.
	 * @param u2
	 */
	public void Del_Employee(User u2) {
		int counter = 0;
		
		if(u2 instanceof Branch_employee) {
			User[] temp_employees = new Branch_employee[employees.length - 1];
			for(int i = 0; i < employees.length; i++) {
				if(employees[i].getName() != u2.getName() ) {
					temp_employees[counter] = employees[i];
					counter++;
				}
			}
			employees = temp_employees;
		}
		else {
			System.err.println("The person you wanted to hire is not an employee");
		}
	}
	
}
