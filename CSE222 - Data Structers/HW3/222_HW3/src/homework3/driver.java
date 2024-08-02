package homework3;

public class driver {
	
	public static void main(String [] args) {
		Company comp = new Company();
		Branch b1 = new Branch();
		Branch b2 = new Branch();
		User u1 = new Admin();
		User u2 = new Branch_employee();
		User u4 = new Branch_employee();
		User u3 = new Customer();
		Product product1 = new Desk();
		
		product1.setModel("Round");
		product1.setColor("Black");
		product1.setStock(51);
		
		b1.setName("G");
		b2.setName("T");
		
		u1.setEmail("admin1@gmail.com");
		u1.setPassword("123zxc");
		
		u4.setEmail("employeee@gmail.com");
		u4.setName("Emre");
		u4.setPassword("1234");
		u4.setSurname("Göktürk");
		
		u2.setEmail("employeee@gmail.com");
		u2.setName("Ali");
		u2.setPassword("1234");
		u2.setSurname("Göktürk");
		
		u3.setEmail("customer@gmail.com");
		u3.setName("Mert");
		u3.setPassword("12344321");
		u3.setSurname("Doğdu");
		
		System.out.println("=============");
		System.out.println("All the products:");
		comp.list_all();
		System.out.println("=============");
		System.out.println("Checking for a specific product (Oval Green Cabinet) ");
		if(comp.check("Oval", "Green", "Cabinet")) {
			System.out.println("This item exists.");
		}
		else {
			System.out.println("This item does not exist.");
		}
		
		System.out.println("Checking for a specific product (Oval Green Bookcase) ");
		if(comp.check("Oval", "Green", "Bookcase")) {
			System.out.println("This item exists.");
		}
		else {
			System.out.println("This item doesn't exist.");
		}
		System.out.println("=============");
		System.out.println("Checking the stocks of a branch.\n");
		comp.check_stocks(b1);
		
		System.out.println("=============");
		System.out.println("Adding a customer.\n");
		comp.add_customer(u3);
		comp.show_customers();
		System.out.println("=============");
		System.out.println("Deleting a customer.\n");
		comp.del_customer(u3);
		comp.show_customers();
		System.out.println("=============");
		System.out.println("Adding branch 'G' and 'T' to the company by an admin.\n");
		comp.add_branch(u1, b1);
		comp.add_branch(u1, b2);
		comp.show_branches();
		System.out.println("=============");
		System.out.println("Deleting branch 'G' by an admin.\n");
		try {
			comp.del_branch(u1, b1);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		comp.show_branches();
		System.out.println("=============");
		System.out.println("Adding employees to the branch 'T'.\n");
		System.out.println("Before adding:");
		comp.show_employees(b2);
		try {
			comp.add_employee(u1, u2, b2);
			comp.add_employee(u1, u4, b2);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("\nAfter adding:");
		comp.show_employees(b2);
		System.out.println("=============");
		System.out.println("Removing employees from the branch 'T'.\n");
		System.out.println("Before removing:");
		comp.show_employees(b2);
		
		System.out.println("\nAfter removing:");
		try {
			comp.del_employee(u1, u2, b2);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		comp.show_employees(b2);
		System.out.println("============");
		System.out.println("Check admin log in info:\n");
		if(comp.check_admin_info(u1.getEmail(), u1.getPassword()) != null) {
			System.out.println("Logging in succesful");
		}
		else {
			System.out.println("System couldn't recognize you.\n");
		}
		System.out.println("============");
		System.out.println("Make sale");
		System.out.println("Before sale");
		System.out.println("Stock of the product: " + product1.getStock());
		comp.make_sale(u3, b1, product1);
		System.out.println("After sale: ");
		System.out.println("Stock of the product: " + product1.getStock());
		System.out.println("============");
		System.out.println("Before Adding product1: ");
		System.out.println(product1.getStock());
		System.out.println("\nAfter Adding product1");
		b1.add_product(product1);
		System.out.println(product1.getStock());
		System.out.println("============");
		System.out.println("Before Deleting product1: ");
		System.out.println(product1.getStock());
		System.out.println("\nAfter Deleting product1");
		b1.del_product(product1);
		System.out.println(product1.getStock());
		System.out.println("============");
		
		
	}
}
