/**
 * Represtens the product "Desk".
 * @author Fatih
 *
 */
public class Desk extends Product{
	
	public Desk() {
		setName("Desk");
	}

	@Override
	public void increaseStock() {
		setStock(getStock()+1);
	}

	@Override
	public void decreaseStock() {
		setStock(getStock()-1);
		
	}
	

}
