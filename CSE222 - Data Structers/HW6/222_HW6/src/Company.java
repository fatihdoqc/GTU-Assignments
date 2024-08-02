import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.LinkedList;
/**
 * Owner of the application.
 * @author Fatih
 *
 */
public class Company {
	
	private LinkedList<Trader> traders;
	private ArrayList<Customer> customers;
	private Hashtable<Integer , Integer> infos;
	private int nextID = 10000000;
	
	/**
	 * Initializes the company.
	 */
	public Company() {
		traders = new LinkedList<>();
		customers = new ArrayList<>();
		infos = new Hashtable<>();
		
		try {
			organize_file("e-commerce-samples.csv" , "Data.txt"); // Creating a better text file.
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	/**
	 * Creates a better text file.
	 * @param filepath
	 * @param dataPath
	 * @throws IOException
	 */
	public void organize_file(String filepath , String dataPath) throws IOException {
		
		File f = new File(dataPath);
		f.delete();
		
		FileReader fr = new FileReader(filepath);
		BufferedReader br = new BufferedReader(fr);
		
		FileWriter fw = new FileWriter(dataPath,true);
		BufferedWriter bw = new BufferedWriter(fw);
		
		String line;
		br.readLine(); // Ignore the first line of the file.
		
		while( (line=br.readLine()) != null){
			String[] tokens = line.split(";");

			bw.write("ID: " + tokens[0]);
			bw.newLine();
			bw.write("Name: " + tokens[1]);
			bw.newLine();
			bw.write("Category: " + tokens[2]);
			bw.newLine();
			bw.write("Price: " + tokens[3]);
			bw.newLine();
			bw.write("Discounted Price: " + tokens[4]);
			bw.newLine();
			bw.write("Description: " + tokens[5]);
			bw.newLine();
			bw.write("Trader: " + tokens[6]);
			bw.newLine();
			bw.newLine();
			
			if(  !already_signed(new Trader(tokens[6]))  ) {			
				register_traders(new Trader(tokens[6]), "111111"); // default password.
				traders.add(new Trader(tokens[6]));
			}
		}
		
		bw.close();
		br.close();
		fw.close();
		fr.close();
	}
	/**
	 * Checks if the user already in the system.
	 * @param u
	 * @return
	 */
	private boolean already_signed(Users u) {
		
		for(Trader trad : traders) {
			if(trad.getName().equals(u.getName())) {
				return true;
			}
		}
		return false;
	}
	/**
	 * Adds product.
	 * @param prod
	 * @throws IOException
	 */
	public void add_product(Product prod) throws IOException {
		
		FileReader fr = new FileReader("Data.txt");
		BufferedReader br = new BufferedReader(fr);
		String line;

		while( (line = br.readLine()) != null) {
			
			if(line.equals("ID: " + prod.getID())) {
				System.err.println("Product exists.");
				
				fr.close();
				br.close();
				return;
			}
		}
		
		fr.close();
		br.close();
		
		FileWriter fw = new FileWriter("Data.txt",true);
		BufferedWriter bw = new BufferedWriter(fw);
		
		bw.write("ID: " + prod.getID());
		bw.newLine();
		bw.write("Name: " + prod.getName());
		bw.newLine();
		bw.write("Category: " + prod.getCategory());
		bw.newLine();
		bw.write("Price: " + prod.getPrice());
		bw.newLine();
		bw.write("Discounted Price: " + prod.getDiscount());
		bw.newLine();
		bw.write("Description: " + prod.getDescription());
		bw.newLine();
		bw.write("Trader: " + prod.getTrader().getName());
		bw.newLine();
		bw.newLine();
		
		if(  !already_signed(prod.getTrader())  ) {
			register_traders(prod.getTrader(), Integer.toString(prod.getTrader().getPassword()));
			traders.add(prod.getTrader());
		}
		
		bw.close();
		fw.close();
	}
	/**
	 * Removes a specific product.
	 * @param prod
	 * @throws IOException
	 */
	public void remove(Product prod) throws IOException {
		
		FileReader fr = new FileReader("Data.txt");
		BufferedReader br = new BufferedReader(fr);
		
		File f1 = new File("Temp.txt");
		if(f1.exists()) {
			f1.delete();
		}
		
		FileWriter fw = new FileWriter("Temp.txt",true);
		BufferedWriter bw = new BufferedWriter(fw);
		
		String line;
		
		while( (line=br.readLine()) != null) {
			bw.write(line);
			bw.newLine();
		}
		
		bw.close();
		br.close();
		fr.close();
		fw.close();
		
		File f = new File("Data.txt");
		f.delete();
		
		fr = new FileReader("Temp.txt");
		br = new BufferedReader(fr);
		
		fw = new FileWriter("Data.txt",true);
		bw = new BufferedWriter(fw);
		
		while( (line=br.readLine()) != null) {
			
			if(line.equals("ID: " + prod.getID())) {
				
				for(int i = 0; i<7; i++) {
					br.readLine();
				}
				continue;
			}
			
			bw.write(line);
			bw.newLine();
		}
		
		bw.close();
		br.close();
		fr.close();
		fw.close();
		
		f = new File("Temp.txt");
		if(f.exists()) {
			f.delete();
		}
		
		
	}
	/**
	 * Removes a specific product by ID.
	 * @param ID
	 * @throws IOException
	 */
	public void remove(String ID) throws IOException {
	
		FileReader fr = new FileReader("Data.txt");
		BufferedReader br = new BufferedReader(fr);
		
		File f1 = new File("Temp.txt");
		if(f1.exists()) {
			f1.delete();
		}
		
		FileWriter fw = new FileWriter("Temp.txt",true);
		BufferedWriter bw = new BufferedWriter(fw);
		
		String line;
		
		while( (line=br.readLine()) != null) {
			bw.write(line);
			bw.newLine();
		}
		
		bw.close();
		br.close();
		fr.close();
		fw.close();
		
		File f = new File("Data.txt");
		f.delete();
		
		fr = new FileReader("Temp.txt");
		br = new BufferedReader(fr);
		
		fw = new FileWriter("Data.txt",true);
		bw = new BufferedWriter(fw);
		
		while( (line=br.readLine()) != null) {
			
			if(line.equals("ID: " + ID)) {
				
				for(int i = 0; i<7; i++) {
					br.readLine();
				}
				continue;
			}
			
			bw.write(line);
			bw.newLine();
		}
		
		bw.close();
		br.close();
		fr.close();
		fw.close();
		
		f = new File("Temp.txt");
		if(f.exists()) {
			f.delete();
		}
		
	}
	/**
	 * Traders can edit product's informations.
	 * @param prod
	 * @throws IOException
	 */
	public void edit(Product prod) throws IOException {
		
		FileReader fr = new FileReader("Data.txt");
		BufferedReader br = new BufferedReader(fr);
		
		File f1 = new File("Temp.txt");
		if(f1.exists()) {
			f1.delete();
		}
		
		FileWriter fw = new FileWriter("Temp.txt",true);
		BufferedWriter bw = new BufferedWriter(fw);
		
		String line;
		
		while( (line=br.readLine()) != null) {
			bw.write(line);
			bw.newLine();
		}
		
		bw.close();
		br.close();
		fr.close();
		fw.close();
		
		File f = new File("Data.txt");
		f.delete();
		
		fr = new FileReader("Temp.txt");
		br = new BufferedReader(fr);
		
		fw = new FileWriter("Data.txt",true);
		bw = new BufferedWriter(fw);
		
		while( (line=br.readLine()) != null) {
			
			if(line.equals("ID: " + prod.getID())) {

				bw.write("ID: " + prod.getID());
				bw.newLine();
				bw.write("Name: " + prod.getName());
				bw.newLine();
				bw.write("Category: " + prod.getCategory());
				bw.newLine();
				bw.write("Price: " + prod.getPrice());
				bw.newLine();
				bw.write("Discounted Price: " + prod.getDiscount());
				bw.newLine();
				bw.write("Description: " + prod.getDescription());
				bw.newLine();
				bw.write("Trader: " + prod.getTrader().getName());
				bw.newLine();
				bw.newLine();
				
				for(int i = 0; i<7; i++) {
					br.readLine();
				}
				continue;
			}
			
			bw.write(line);
			bw.newLine();
		}
		
		bw.close();
		br.close();
		fr.close();
		fw.close();
		
		f = new File("Temp.txt");
		if(f.exists()) {
			f.delete();
		}
	}
	/**
	 * Canceling or meeting the order will cause order to be removed.
	 * @param order_number
	 * @throws IOException
	 */
	public void remove_order(int order_number) throws IOException{
		
		int flag = 0;
		
		FileReader fr = new FileReader("Orders.txt");
		BufferedReader br = new BufferedReader(fr);
		
		FileWriter fw = new FileWriter("Temp.txt",true);
		BufferedWriter bw = new BufferedWriter(fw);
		
		String line;
		
		int i = 1;
		while( (line=br.readLine()) != null) {
			
			if(i == order_number) {			
				flag = 1;
				i++;
				continue;
			}
			
			bw.write(line);
			bw.newLine();
			i++;
		}
		bw.close();
		br.close();
		fr.close();
		fw.close();
		
		if(flag == 0) {
			System.err.println("There is no order like that.");
			File f = new File("Temp.txt");
			f.delete();
			return;
		}
		
		File f = new File("Orders.txt");
		f.delete();
		
		fr = new FileReader("Temp.txt");
		br = new BufferedReader(fr);
		
		fw = new FileWriter("Orders.txt",true);
		bw = new BufferedWriter(fw);
		
		while( (line=br.readLine()) != null) {
			bw.write(line);
			bw.newLine();
		}
		
		bw.close();
		br.close();
		fr.close();
		fw.close();
		
		f = new File("Temp.txt");
		f.delete();
	}
	/**
	 * Lists orders.
	 * @throws IOException
	 */
	public void list_orders() throws IOException {
		FileReader fr = new FileReader("Orders.txt");
		BufferedReader br = new BufferedReader(fr);
		String line;
		
		int i = 1;
		System.out.println("\tID\t\t\t\tNAME");
		while( (line=br.readLine()) != null) {
			System.out.println( i + ")\t" + line);
			i++;
		}
		
		br.close();
		fr.close();
	}
	/**
	 * Searchs a specific text in the names and descriptions.
	 * @param text
	 * @param items
	 * @throws IOException
	 */
	public void search(String text , ArrayList<Product> items) throws IOException {
		
		FileReader fr = new FileReader("Data.txt");
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
			
			if(prod.getName().contains(text)) {
				items.add(prod);
			}
			else if(prod.getDescription().contains(text)) {
				items.add(prod);
			}
			
		}
		
		br.close();
		fr.close();
		
	}
	/**
	 * Checks if the wanted informations to login are correct.
	 * @param ID
	 * @param password
	 * @return
	 */
	public boolean login(String ID , String password) {
		
		if(infos.containsKey(Integer.parseInt(ID))) {
			if(infos.get(Integer.parseInt(ID)) == Integer.parseInt(password)) {
				return true;
			}
		}
		return false;
	}
	/**
	 * Registers a customer to the system.
	 * @param u1
	 * @param password
	 * @throws IOException
	 */
	public void register(Users u1 , String password) throws IOException {
		
		FileWriter fw = new FileWriter("Customers.txt",true);
		BufferedWriter bw = new BufferedWriter(fw);
		
		bw.write(Integer.toString(nextID));
		bw.newLine();
		
		u1.setID(nextID);
		u1.setPassword(Integer.parseInt(password));
		
		infos.put(nextID, Integer.parseInt(password));
		
		nextID++;
		customers.add((Customer) u1);
		
		bw.close();
		fw.close();
		
	}
	/**
	 * Registers a trader to the system.
	 * @param t
	 * @param password
	 * @throws IOException
	 */
	public void register_traders(Trader t , String password) throws IOException{
		FileWriter fw = new FileWriter("Traders.txt",true);
		BufferedWriter bw = new BufferedWriter(fw);
		
		bw.write(Integer.toString(nextID));
		bw.newLine();
		
		t.setID(nextID);
		t.setPassword(Integer.parseInt(password));
		
		infos.put(nextID, Integer.parseInt(password));
		
		nextID++;
		
		bw.close();
		fw.close();
	}
}
