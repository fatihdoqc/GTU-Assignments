package homework3;

/**
 * Represents a branch of the company
 * @author Fatih
 *
 */
public class Branch {
	
	private HybridList<Desk> desks = new HybridList<>();
	private HybridList<Bookcase> bookcases = new HybridList<>();
	private HybridList<Cabinet> cabinets = new HybridList<>();
	private String name;
	
	private KWArrayList<Branch_employee> employees = new KWArrayList<>();
	
	/**
	 * Initializes the branch with hiring employees and adding products.
	 */
	public Branch() {
		for(int i = 0; i<4; i++) {
			desks.addLast(new Desk());
		}
		for(int i = 0; i<2; i++) {
			bookcases.addLast(new Bookcase());
		}
		for(int i = 0; i<11; i++) {
			cabinets.addLast(new Cabinet());
		}
		for(int i = 0; i < 4; i++) {
			employees.add(new Branch_employee());
		}
		employees.get(0).setName("Serdar");
		employees.get(1).setName("Ahmet");
		employees.get(2).setName("Murat");
		employees.get(3).setName("Aliye");
		
		desks.get(0).setModel("Round");
		desks.get(0).setColor("Black");
		desks.get(0).setStock(150);
		
		desks.get(1).setModel("Round");
		desks.get(1).setColor("White");
		desks.get(1).setStock(15000);
		
		desks.get(2).setModel("Square");
		desks.get(2).setColor("Black");
		desks.get(2).setStock(10);
		
		desks.get(3).setModel("Square");
		desks.get(3).setColor("White");
		desks.get(3).setStock(500);
		
		bookcases.get(0).setModel("Big");
		bookcases.get(0).setColor("White");
		bookcases.get(0).setStock(1200);
		
		bookcases.get(1).setModel("Big");
		bookcases.get(1).setColor("Black");
		bookcases.get(1).setStock(10);
		
		
		cabinets.get(0).setModel("Oval");
		cabinets.get(0).setColor("Red");
		cabinets.get(0).setStock(40);
			
		cabinets.get(1).setModel("Oval");
		cabinets.get(1).setColor("Green");
		cabinets.get(1).setStock(400);
		
		cabinets.get(2).setModel("Oval");
		cabinets.get(2).setColor("White");
		cabinets.get(2).setStock(100);
		
		cabinets.get(3).setModel("Oval");
		cabinets.get(3).setColor("Purple");
		cabinets.get(3).setStock(49);
		
		cabinets.get(4).setModel("Tall");
		cabinets.get(4).setColor("Red");
		cabinets.get(4).setStock(3);
		
		cabinets.get(5).setModel("Tall");
		cabinets.get(5).setColor("Green");
		cabinets.get(5).setStock(4000);
		
		cabinets.get(6).setModel("Tall");
		cabinets.get(6).setColor("Green");
		cabinets.get(6).setStock(4000);
		
		cabinets.get(7).setModel("Tall");
		cabinets.get(7).setColor("White");
		cabinets.get(7).setStock(4000);
		
		cabinets.get(8).setModel("Tall");
		cabinets.get(8).setColor("Purple");
		cabinets.get(8).setStock(4000);
		
		cabinets.get(9).setModel("Rectengular");
		cabinets.get(9).setColor("Red");
		cabinets.get(9).setStock(4000);
		
		cabinets.get(10).setModel("Rectengular");
		cabinets.get(10).setColor("Black");
		cabinets.get(10).setStock(4000);
	}
	/**
	 * Orders an employee to make sale to the person "u".
	 * @param x
	 * @param u
	 */
	public void make_sale(Product x , User u) {
		employees.get(3).sale(x , u); // Sale x to the person u.
	}
	/**
	 * Orders an employee to create a product.
	 * @param x
	 */
	public void add_product(Product x) {
		employees.get(1).add_prod(x);
	}
	/**
	 * Orders an employee to delete a product.
	 * @param x
	 */
	public void del_product(Product x) {
		employees.get(1).delete_product(x);
	}
	/**
	 * If the stocks are not enough, orders to an employee to inform the manager about stocks.
	 * @param x
	 */
	public void requested_amount(Product x) {
		if(x.getStock() < 50) { // Every product stock's must be higher than 50.
			((Branch_employee) employees.get(1)).inform_the_manager(x);
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
		if(name.equals(desks.get(0).getName())) {
			for(int i = 0; i< desks.size(); i++) {
				if(desks.get(i).getModel().equals(model) && desks.get(i).getColor().equals(color) && desks.get(i).getStock() > 0) {
					desks.get(i).decreaseStock();
					((Customer) u).addHistory(model , color , name);
					return;
				}
			}
		}
		else if(name.equals(bookcases.get(0).getName())) {
			for(int i = 0; i< bookcases.size(); i++) {
				if(bookcases.get(i).getModel().equals(model) && bookcases.get(i).getColor().equals(color) && bookcases.get(i).getStock() > 0) {
					bookcases.get(i).decreaseStock();
					((Customer) u).addHistory(model , color , name);
					return;
				}
			}
			
		}
		else if(name.equals(cabinets.get(0).getName())) {
			for(int i = 0; i< cabinets.size(); i++) {
				if(cabinets.get(i).getModel().equals(model) && cabinets.get(i).getColor().equals(color) && cabinets.get(i).getStock() > 0) {
					cabinets.get(i).decreaseStock();
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
		if(name.equals(desks.get(0).getName())) {
			for(int i = 0; i< desks.size(); i++) {
				if(desks.get(i).getModel().equals(model) && desks.get(i).getColor().equals(color) && desks.get(i).getStock() != 0) {
					return true ;
				}
			}
		}
		else if(name.equals(bookcases.get(0).getName())) {
			for(int i = 0; i< bookcases.size(); i++) {
				if(bookcases.get(i).getModel().equals(model) && bookcases.get(i).getColor().equals(color) && bookcases.get(i).getStock() != 0) {
					return true ;
				}
			}
			
		}
		else if(name.equals(cabinets.get(0).getName())) {
			for(int i = 0; i< cabinets.size(); i++) {
				if(cabinets.get(i).getModel().equals(model) && cabinets.get(i).getColor().equals(color) && cabinets.get(i).getStock() != 0) {
					return true ;
				}
			}
		}
		return false;
	}
	/**
	 * List all of the products in this branch.
	 */
	public void list_products() {
		for(int i = 0 ; i<desks.size(); i++) {
				System.out.println(desks.get(i).getModel() + " " + desks.get(i).getColor() + " Desk ");
		}
		for(int i = 0 ; i<bookcases.size(); i++) {
				System.out.println(bookcases.get(i).getModel() + " " + bookcases.get(i).getColor() + " Bookcase ");
		}
		for(int i = 0 ; i<cabinets.size(); i++) {
				System.out.println(cabinets.get(i).getModel() + " " + cabinets.get(i).getColor() + " Cabinet ");
		}
	}
	public void check_all_stocks() {
		for(int i = 0; i< desks.size(); i++) {
			if(desks.get(i).getStock() < 50) {
				System.out.println(desks.get(i).getModel() + " " + desks.get(i).getColor() + " " + desks.get(i).getName() + " is out of stocks");
			}
		}
		for(int i = 0; i< bookcases.size(); i++) {
			if(bookcases.get(i).getStock() < 50) {
				System.out.println(bookcases.get(i).getModel() + " " + bookcases.get(i).getColor() + " " + bookcases.get(i).getName() + " is out of stocks");
			}
		}
		for(int i = 0; i< cabinets.size(); i++) {
			if(cabinets.get(i).getStock() < 50) {
				System.out.println(cabinets.get(i).getModel() + " " + cabinets.get(i).getColor() + " " + cabinets.get(i).getName() + " is out of stocks");
			}
		}
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
			employees.add( (Branch_employee) u2);
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
			employees.removeFirstOccurence( (Branch_employee) u2);
		}
		else {
			System.err.println("The person you wanted to hire is not an employee");
		}
	}
	public void show_employees() {
		for(int i = 0; i< employees.size(); i++) {
			System.out.println(employees.get(i).getName());
		}
	}
}
