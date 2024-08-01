package homework3;

/**
 * Represents the employees
 * @author Fatih
 *
 */
public class Branch_employee extends User {
	
	/**
	 * inform the manager about stocks of a product
	 * @param x
	 */
	public void inform_the_manager(Product x) {
		System.out.println("Manager informed!");
	}
	/**
	 * Deletes a product.
	 * @param x
	 */
	public void delete_product(Product x) {
		x.setStock(0);;
	}
	/**
	 * Creates a product.
	 * @param x
	 */
	public void add_prod(Product x) {
		x.setStock(x.getStock() + 50); 
	}
	/**
	 * Sales a product x to the user u.
	 * @param x
	 * @param u
	 */
	public void sale(Product x , User u) {
		((Customer) u).addHistory(x);
		x.decreaseStock();
	}
	/**
	 * Checks the purchase history of an user.
	 * @param u
	 */
	
	public void check_history(User u) {
		((Customer) u).see_history();
	}
}
