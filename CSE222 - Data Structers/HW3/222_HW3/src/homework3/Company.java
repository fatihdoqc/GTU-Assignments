package homework3;
/**
 * 
 * @author Fatih
 * The general class.
 * Stands for the company itself.
 */
import java.util.Random;

public class Company {
	
	private KWLinkedList<Branch> branches = new KWLinkedList<>();
	private KWArrayList<Admin> admins = new KWArrayList<>();
	private KWArrayList<Customer> customers = new KWArrayList<>();
	private Random rand = new Random();
	
	/**
	 * Initializing the company with openning branches , hiring admins and customers.
	 */
	public Company() {
		for(int i = 0; i< 4; i++) {
			branches.addLast(new Branch());
		}
		for(int i = 0; i< 2; i++) {
			admins.add(new Admin());
		}

		branches.get(0).setName("A");
		branches.get(1).setName("B");
		branches.get(2).setName("C");
		branches.get(3).setName("D");
		
		admins.get(0).setEmail("admin1@gmail.com");
		admins.get(0).setName("Banu");
		admins.get(0).setSurname("Yurt");
		admins.get(0).setPassword("123zxc");
		
		admins.get(1).setEmail("admin2@gmail.com");
		admins.get(1).setName("Mert");
		admins.get(1).setSurname("Kayık");
		admins.get(1).setPassword("1234qwer");
	}
	/** Returns true if the wanted product exists.
	 * 
	 * @param model is model of the product.
	 * @param color is color of the product.
	 * @param name is name of the product.
	 * @return
	 */
	public boolean check(String model , String color , String name) {
		for(int i = 0; i<branches.size(); i++) {
			if(branches.get(i).check_product(model, color, name) && branches.get(i).check_product(model, color, name)) {
				return true ;
			}
		}
		return false;
	}
	/**
	 * Lists all products of all branches.
	 */
	public void list_all() {
		for(int i = 0; i<branches.size(); i++) {
			System.out.println("\nBranch " + branches.get(i).getName() + " contains: ");
			branches.get(i).list_products();
		}
	}
	/**
	 * Checks if the inputs match with an existing admin.
	 * @param email
	 * @param password
	 * @return corresponding admin user.
	 */
	public Admin check_admin_info(String email , String password) {
		
		for(int i = 0; i < admins.size(); i++) {
			if(admins.get(i).getEmail().equals(email)) {
				if(admins.get(i).getPassword().equals(password)) {
					return (Admin) admins.get(i);
				}
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
		
		for(int i = 0 ; i<customers.size(); i++) {
			if(customers.get(i).getEmail().equals(email)) {
				if(customers.get(i).getPassword().equals(password)) {
					return (Customer) customers.get(i);
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
		
		( (Admin) admins.get(0)).query_branch(b1);
		
	}
	/**
	 * Adds the customer informations to the system. And creates a customer number for her/him.
	 * @param u
	 */
	public void add_customer(User u) {
	
		for(int i = 0; i< customers.size(); i++) {
			if(u.getEmail().equals(customers.get(i).getEmail())) {
				System.err.println("Operation failed. This E-mail is already taken. ");
				return;
			}
		}
		
		int x = rand.nextInt(1000);
		
		for(int i = 0; i<customers.size() ;i++) {
			if(x == ((Customer) customers.get(i)).getNumber() ) {
				x = rand.nextInt(1000);
				i = 0;
			}
		}
		((Customer) u).setNumber(x);	
		
		customers.add( (Customer) u);
	}
	public void del_customer(User u) {
		customers.removeFirstOccurence((Customer) u);
	}
	public void show_customers() {
		
		System.out.println("Customers:");
		for(int i = 0; i<customers.size(); i++) {
			System.out.println(customers.get(i).getName());
		}
	}
	/**
	 * Adds a branch to the company.
	 * @param u1
	 * @param b1
	 */
	
	public void add_branch(User u1 , Branch b1) {
		if(u1 instanceof Admin) {		
			branches.addLast(b1);
		}
		else {
			System.err.println("You are not authorized for this action.\n");
		}
	}
	public void show_branches() {
		System.out.println("Branches:");
		for(int i = 0; i< branches.size(); i++) {
			System.out.println(branches.get(i).getName());
		}
	}
	/**
	 * Deletes an existing branch.
	 * @param u1 must be admin.
	 * @param b1 is the branch which must exist.
	 * @throws Exception if there is no such a branch.
	 */
	public void del_branch(User u1 , Branch b1) throws Exception{
		int flag = 1;
		
		for(int i = 0; i<branches.size(); i++) {
			if(b1.getName().equals(branches.get(i).getName()) ) {
				flag = 0;
			}
		}
		if(flag == 1) {
			System.err.println("There is no such a branch.\n");
			throw new Exception();
		}
		
		if(u1 instanceof Admin) {
			branches.remove(b1);			
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
				
				for(int i = 0; i<branches.size(); i++) {
					if(b1.getName() == branches.get(i).getName() ) {
						branches.get(i).Add_Employee(u2);
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
				
				for(int i = 0; i<branches.size(); i++) {
					if(b1.getName() == branches.get(i).getName() ) {
						branches.get(i).Del_Employee(u2);
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
	public void show_employees(Branch b) {
		b.show_employees();
	}
	public void make_sale(User u1 , Branch b1 , Product x) {
		b1.make_sale(x, u1);
	}
}
