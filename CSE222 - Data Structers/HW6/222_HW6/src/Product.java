/**
 * Product class for keeping products.
 * @author Fatih
 *
 */
public class Product {
	
	private String ID;
	private String category;
	private String name;
	private String description;
	private int price;
	private int discount;
	private Trader trader;
	
	public Product(String ID , String category , String name , String description , int price , int discount , Trader trader) {
		this.ID = ID;
		this.category = category;
		this.name = name;
		this.description = description;
		this.price = price;
		this.discount = discount;
		this.trader = trader;
		
	}
	public Product() {
		
	}
	
	public Trader getTrader() {
		return trader;
	}
	public void setTrader(Trader trad) {
		trader = trad;
	}
	public String getID() {
		return ID;
	}
	public void setID(String iD) {
		ID = iD;
	}
	
	public String getCategory() {
		return category;
	}
	public void setCategory(String category) {
		this.category = category;
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	
	public int getPrice() {
		return price;
	}
	public void setPrice(int price) {
		this.price = price;
	}
	
	public int getDiscount() {
		return discount;
	}
	public void setDiscount(int discount) {
		this.discount = discount;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
}
