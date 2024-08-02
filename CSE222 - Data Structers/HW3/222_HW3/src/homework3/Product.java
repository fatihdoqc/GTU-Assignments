package homework3;

/**
 * Gathers all the products.
 * @author Fatih
 *
 */
public abstract class Product {
	
	private String name;
	private String model;
	private String color;
	private int Stock;
	
	public abstract void increaseStock();
	public abstract void decreaseStock();
	
	public String getModel() {
		return model;
	}
	public void setModel(String model) {
		this.model = model;
	}
	public String getColor() {
		return color;
	}
	public void setColor(String color) {
		this.color = color;
	}
	public int getStock() {
		return Stock;
	}
	public void setStock(int stock) {
		Stock = stock;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String toString() {
		return model + " " + color + " " + name;
	}
}
