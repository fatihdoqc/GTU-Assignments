import java.util.Scanner;
/**
 * Driver class
 * @author Fatih
 *
 */
public class MyMain {
	/**
	 * Driver method.
	 * @param args
	 */
	public static void main(String[] args) {
		
		@SuppressWarnings("resource")
		Scanner scan = new Scanner(System.in);
		
		Company comp = new Company();
		Branch b1 = new Branch();
		User u1 = new Admin();
		User u2 = new Branch_employee();
		User u3 = new Customer();
		
		u2.setName("Melih");
		b1.setName("X");
		
		comp.add_branch(u1, b1);
		
		try {
			comp.add_employee(u1, u2, b1); /* u1 hires the person u2 from the branch b1 */  
		} catch (Exception e1) {
			e1.printStackTrace();
		} 
		
		try {
			comp.del_branch(u1, b1);
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		try {
			comp.del_employee(u1, u2, b1); /* u1 hires the person u2 from the branch b1 */  
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		comp.add_branch(u1, b1);
		
		try {
			comp.add_employee(u1, u2, b1); /* u1 hires the person u2 from the branch b1 */  
		} catch (Exception e1) {
			e1.printStackTrace();
		} 
		
		/* Menu with the switch and cases. */ 
		int option , choice = 0 ;
		String email , password , temp , model , color , name ;
		while(choice != 4) {
			System.out.println("Hello, Welcome to the Fatih Furniture. Please log in or register to view the products.\n");
			System.out.println("1)Log in ");
			System.out.println("2)Sign in ");
			System.out.print("Choice: ");
			
			choice = scan.nextInt();
			switch(choice) {
				case 1:
					System.out.println("1) Admin");
					System.out.println("2) Customer");
					System.out.println("4) Exit");
					System.out.print("Choice: ");
					option = scan.nextInt();
					switch(option) {
						case 1:
							System.out.print("E-mail: ");
							email = scan.next();
							System.out.print("Password: ");
							password = scan.next();
							
							u1 = comp.check_admin_info(email, password);
							
							if(u1 != null) {
								System.out.println("Login successful." + " Welcome " + u1.getName());
								choice = 4;
							}else {
								System.err.println("Login failed.");
							}
							break;
						case 2:
							System.out.print("E-mail: ");
							email = scan.next();
							System.out.print("Password: ");
							password = scan.next();
							u3 = comp.check_customer_info(email, password);
							
							if(u3 != null) {
								System.out.println("Login successful." + " Welcome " + u3.getName());
								choice = 4;
							}else {
								System.err.println("Login failed.");
							}
							break;
						case 4:
							return;
						default:
							System.err.println("There is no such an option.");
							return;
							
					}
					break;
					
				case 2:
					System.out.print("E-mail: ");
					email = scan.next();
					u3.setEmail(email);
					
					System.out.print("Password: ");	
					password = scan.next();
					u3.setPassword(password);
					
					System.out.print("Name: ");
					temp = scan.next();
					u3.setName(temp);
					
					System.out.print("Surname: ");
					temp = scan.next();
					u3.setSurname(temp);
					
					comp.add_customer(u3);
					
					System.out.println("Registiration complete. Welcome "+ u3.getName());
					System.out.println("Your customer id is " + ((Customer) u3).getNumber());
					choice = 4;
					
					break;
					
				default:
					System.err.println("There is no such an option.");
					return;
			}
		}
		choice = 9;
		while(choice != 5) {
			System.out.println("What would you like to do ?");
			System.out.println("1) Search for a specific product.");
			System.out.println("2) List all the products.");
			System.out.println("3) Shop online.");
			System.out.println("4) See history of yours.");
			System.out.println("5) Exit");
			
			choice = scan.nextInt();
			switch(choice) {
				case 1:
					System.out.println("Please write the product as Model Color Product ");
					model = scan.next();
					color = scan.next();
					name = scan.next();
					comp.search(model, color, name);
					break;
				case 2:
					comp.list_all();
					break;
				case 3:
					System.out.println("Please write the product that you want to buy as Model Color Product ");
					model = scan.next();
					color = scan.next();
					name = scan.next();
					if(comp.check(model, color, name) != true) {
						System.err.println("Sorry, we have no such a product!");
						continue;
					}
					System.out.print("Adress to deliver: ");
					((Customer) u3).setAdress(scan.next());
					System.out.print("Phone number: ");
					((Customer) u3).setPhone(scan.next());
					System.out.println("Thanks for your shopping!");
					b1.sale(u3, model, color, name);
					break;
				case 4:
					((Branch_employee) u2).check_history(u3);
					break;
				case 5:
					choice = 4;
					return;
					
				default:
					System.err.println("Sorry , that is not an option.");
					break;
			}
		}
		
		
		
		
		
		
	}

}
