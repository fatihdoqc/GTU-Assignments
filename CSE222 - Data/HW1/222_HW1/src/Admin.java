/**
 * Represents the admin part of Users.
 * @author Fatih
 *
 */
public class Admin extends User{
	
	/**
	 * Orders to an Admin to check the stocks of a branch.
	 * @param b1
	 */
	public void query_branch(Branch b1) {
		
		b1.stock_check();		
	}
	
}
