/**
 * Represents the bookcases.
 * @author Fatih
 *
 */
public class Bookcase extends Product {
	
	public Bookcase() {
		setName("Bookcase");
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
