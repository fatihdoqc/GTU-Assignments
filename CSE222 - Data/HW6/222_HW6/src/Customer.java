import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.TreeSet;

/**
 * The user Customer class.
 * @author Fatih
 *
 */
public class Customer implements Users {
	
	private String name;
	private int ID;
	private int password;
	private Queue<Product> orders;
	
	public Customer() {
		orders= new LinkedList<>();
	}
	public Customer(String name) {
		this.name = name;
		orders= new LinkedList<>();
	}
	public Customer(String name , int ID , int password) {
		this.name = name;
		this.ID = ID;
		this.password = password;
		orders= new LinkedList<>();
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}

	public int getID() {
		return ID;
	}

	public void setID(int iD) {
		ID = iD;
	}

	public int getPassword() {
		return password;
	}

	public void setPassword(int password) {
		this.password = password;
	}
	/**
	 * Filters the search results by category.
	 * @param arr
	 * @param category
	 */
	public void filter_results_category(ArrayList<Product> arr , String category) {
	
		
		for(int i = 0; i< arr.size(); i++) {
			
			TreeSet<String> categories = new TreeSet<String>();
			
			String[] tokens = arr.get(i).getCategory().split(" >> ");
			
			for(String a : tokens) {
				a = a.replaceAll("[\\[\"\\]]", "");
				categories.add(a);
			}
			
			if(categories.contains(category)) {
				Product prod = arr.get(i);
				System.out.println("Name: " + prod.getName() + "\t, ID: " + prod.getID() +
						"\t, Price: " + prod.getPrice() + "\t, Discount: " + prod.getDiscount());
			}
		}
	}
	/**
	 * Filters the search results by price.
	 * @param arr
	 * @param price_start
	 * @param price_end
	 */
	public void filter_price(ArrayList<Product> arr, int price_start , int price_end) {
		
		for(int i = 0; i< arr.size(); i++) {		
			if(arr.get(i).getPrice() > price_start && arr.get(i).getPrice() < price_end) {
				Product prod = arr.get(i);
				System.out.println("Name: " + prod.getName() + "\t, ID: " + prod.getID() +
						"\t, Price: " + prod.getPrice() + "\t, Discount: " + prod.getDiscount());
			}
		}
	}
	/**
	 * Asks to company to show a specific trader's products.
	 * @param filePath
	 * @param trad
	 * @throws IOException
	 */
	public void display_products(String filePath , Trader trad) throws IOException {
		
		FileReader fr = new FileReader(filePath);
		BufferedReader br = new BufferedReader(fr);
		String line;
		
		while( (line=br.readLine()) != null) {
			
			Product prod = new Product();
			prod.setID(line.substring(4));
			
			line=br.readLine();
			prod.setName(line.substring(6));
			
			line=br.readLine();
			prod.setCategory(line.substring(10));
			
			line=br.readLine();
			prod.setPrice( Integer.parseInt(line.substring(7)) );
			
			line = br.readLine();
			prod.setDiscount(Integer.parseInt(line.substring(18)));
			
			line=br.readLine();
			prod.setDescription(line.substring(13));
			
			line = br.readLine();
			prod.setTrader(new Trader(line.substring(8)));
			
			br.readLine(); // Skipping the row with '\n'.
			
			if(prod.getTrader().getName().equals(trad.getName())) {
				System.out.println("Name: " + prod.getName() + "\t, ID: " + prod.getID() +
				"\t, Price: " + prod.getPrice() + "\t, Discount: " + prod.getDiscount());
			}
			
		}
		
		br.close();
		fr.close();
	}
	/**
	 * Creates an order by looking at search results.
	 * @param arr
	 * @param index
	 * @throws IOException
	 */
	public void order(ArrayList<Product> arr , int index) throws IOException {
		
		FileWriter fw = new FileWriter("Orders.txt",true);
		BufferedWriter bw = new BufferedWriter(fw);
		
		Product prod = arr.get(index);
		orders.add(prod);

		bw.write(prod.getID() + "\t,\t" + prod.getName());
		bw.newLine();
		
		bw.close();
		fw.close();
	}
	/**
	 * Creates an order.
	 * @param prod
	 * @throws IOException
	 */
	public void order(Product prod) throws IOException {
		FileWriter fw = new FileWriter("Orders.txt",true);
		BufferedWriter bw = new BufferedWriter(fw);
		
		orders.add(prod);
		
		bw.write(prod.getID() + "\t,\t" + prod.getName());
		bw.newLine();
		
		bw.close();
		fw.close();
	}
}
