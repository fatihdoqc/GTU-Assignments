import java.util.Random;

/**
 * 
 * @author Fatih
 * The general class.
 * Stands for the company itself.
 */
public class Company {
	
	private Branch[] branches = new Branch[4];
	private User[] admins = new Admin[2];
	private User[] customers = new Customer[1];
	private Random rand = new Random();
	
	/**
	 * Initializing the company with openning branches , hiring admins and customers.
	 */
	public Company() {
		for(int i = 0; i< branches.length; i++) {
			branches[i] = new Branch();
		}
		for(int i = 0; i< admins.length; i++) {
			admins[i] = new Admin();
		}
		for(int i = 0; i< customers.length; i++) {
			customers[i] = new Customer();
		}
		branches[0].setName("A");
		branches[1].setName("B");
		branches[2].setName("C");
		branches[3].setName("D");
		
		admins[0].setEmail("admin1@gmail.com");
		admins[0].setName("Banu");
		admins[0].setSurname("Yurt");
		admins[0].setPassword("123zxc");
		
		admins[1].setEmail("admin2@gmail.com");
		admins[1].setName("Mert");
		admins[1].setSurname("Kayık");
		admins[1].setPassword("1234qwer");
	}
	/** Returns true if the wanted product exists.
	 * 
	 * @param model is model of the product.
	 * @param color is color of the product.
	 * @param name is name of the product.
	 * @return
	 */
	public boolean check(String model , String color , String name) {
		for(int i = 0; i<branches.length; i++) {
			if(branches[i].check_product(model, color, name)) {
				return true ;
			}
		}
		System.out.println("Sorry , we have no such a product.");
		return false;
	}
	/**
	 * Lists all products of all branches.
	 */
	public void list_all() {
		for(int i = 0; i<branches.length; i++) {
			System.out.println("\nBranch " + branches[i].getName() + " contains: ");
			branches[i].list_products();
		}
	}
	/**
	 * Searches all of the branches for the wanted product and sends a feedback.
	 * @param model
	 * @param color
	 * @param name
	 */
	public void search(String model , String color , String name) {
		for(int i = 0; i<branches.length; i++) {
			
			System.out.println("Branch " + branches[i].getName());
			branches[i].search_product(model, color, name);
		}
	}
	/**
	 * Checks if the inputs match with an existing admin.
	 * @param email
	 * @param password
	 * @return corresponding admin user.
	 */
	public Admin check_admin_info(String email , String password) {
		if(admins[0].getEmail().equals(email)) {
			if(admins[0].getPassword().equals(password)) {
				return (Admin) admins[0];
			}
		}
		else if(admins[1].getEmail().equals(email)) {
			if(admins[1].getPassword().equals(password)) {
				return (Admin) admins[1];
			}
		}
		return null;
	}
	/**
	 * Checks if the inputs match with an existing customer.
	 * @param email
	 * @param password
	 * @return
	 */
	public Customer check_customer_info(String email , String password) {
		
		for(int i = 0 ; i<customers.length; i++) {
			if(customers[i].getEmail().equals(email)) {
				if(customers[i].getPassword().equals(password)) {
					return (Customer) customers[i];
				}
			}
		}
		return null;
	}
	/**
	 * Asks from an admin to check an existing branch's stocks.
	 * @param b1
	 */
	public void check_stocks( Branch b1 ) {
		
		( (Admin) admins[0]).query_branch(b1);
		
	}
	/**
	 * Adds the customer informations to the system. And creates a customer number for her/him.
	 * @param u
	 */
	public void add_customer(User u) {
		
		if(customers[0] == null) {
			((Customer) u).setNumber(rand.nextInt(1000));
			customers[0] = u;
			
			return;
		}
		for(int i = 0; i< customers.length; i++) {
			if(u.getEmail().equals(customers[i].getEmail())) {
				System.err.println("Operation failed. This E-mail is already taken. ");
				return;
			}
		}
		
		int x = rand.nextInt(1000);
		User[] temp = new Customer[customers.length + 1];
		
		for(int i = 0; i<customers.length ;i++) {
			if(x == ((Customer) customers[i]).getNumber() ) {
				x = rand.nextInt(1000);
				i = 0;
			}
		}
		((Customer) u).setNumber(x);	
		
		for(int i = 0; i< customers.length; i++) {
			temp[i] = customers[i];
		}
		
		temp[customers.length] = u;
		
		customers = temp;
	}
	/**
	 * Adds a branch to the company.
	 * @param u1
	 * @param b1
	 */
	
	public void add_branch(User u1 , Branch b1) {
		if(u1 instanceof Admin) {
			Branch[] temp_branches = new Branch[branches.length + 1];
			for(int i = 0; i<branches.length; i++) {
				temp_branches[i] = branches[i];
			}
			temp_branches[branches.length] = b1;
			branches = temp_branches;
		}
		else {
			System.err.println("You are not authorized for this action.\n");
		}
	}
	/**
	 * Deletes an existing branch.
	 * @param u1 must be admin.
	 * @param b1 is the branch which must exist.
	 * @throws Exception if there is no such a branch.
	 */
	public void del_branch(User u1 , Branch b1) throws Exception{
		
		int counter = 0 , flag = 1;
		
		for(int i = 0; i<branches.length; i++) {
			if(b1.getName() == branches[i].getName()) {
				flag = 0;
			}
		}
		if(flag == 1) {
			System.err.println("There is no such a branch.\n");
			throw new Exception();
		}
		
		if(u1 instanceof Admin) {
			Branch[] temp = new Branch[branches.length - 1];
			
			for(int i = 0; i<branches.length ; i++) {
				
				if(b1.getName() != branches[i].getName()) {			
					temp[counter] = branches[i];
					counter++;
				}
			}
			branches = temp;
			
		}
		else {
			System.err.println("You are not authorized for this action.\n");
		}
	}
	/**
	 * Asks from an admin to hire a coworker.
	 * @param u1 must be Admin.
	 * @param u2 must be Branch_Employee
	 * @param b1 must exist.
	 */
	public void add_employee(User u1 , User u2 , Branch b1 ) throws Exception{
		int flag = 1;
		
		if(u1 instanceof Admin) {
			if(u2 instanceof Branch_employee) {
				
				for(int i = 0; i<branches.length; i++) {
					if(b1.getName() == branches[i].getName() ) {
						branches[i].Add_Employee(u2);
						flag = 0;
					}
				}
			}
			else {
				System.err.println("This person is not an employee.\n");
			}
			
		}
		else {
			System.err.println("You are not authorized for this action.\n");
		}
		if(flag == 1) {
			System.err.println("Branch must exist in the company.");
			throw new Exception();
		}
		
	}
	/**
	 * Fires an existing employee.
	 * @param u1 is the admin
	 * @param u2 is the employee
	 * @param b1 is the branch where the employee from.
	 * @throws Exception if there is no such an employee.
	 */
	public void del_employee(User u1, User u2 , Branch b1) throws Exception {
		int flag = 1;
		
		if(u1 instanceof Admin) {
			if(u2 instanceof Branch_employee) {
				
				for(int i = 0; i<branches.length; i++) {
					if(b1.getName() == branches[i].getName() ) {
						branches[i].Del_Employee(u2);
						flag = 0;
					}
				}
				
			}
			else {
				System.err.println("This person is not an employee.\n");
			}
			
		}
		else {
			System.err.println("You are not authorized for this action.\n");
		}
		
		if(flag == 1) {
			System.err.println("There is no such an employee");
			throw new Exception();
		}
	}
}
