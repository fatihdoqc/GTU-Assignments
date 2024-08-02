package homework3;

/**
 * Represents the cabinets.
 * @author Fatih
 *
 */
public class Cabinet extends Product {
	
	public Cabinet() {
		setName("Cabinet");
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
