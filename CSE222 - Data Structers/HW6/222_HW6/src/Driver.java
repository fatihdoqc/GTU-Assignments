import java.io.IOException;
import java.util.ArrayList;

public class Driver {

	public static void main(String[] args) {
		
		Company comp = new Company();
		
		Users u1 = new Customer("Selim");
		Users u2 = new Trader("Ali");
		
		Product prod1 = new Product("S000000000000000", "MyCategory" , "Cheap Table" , "Nothing to read" , 10 , 5 , (Trader) u2);
		Product prod2 = new Product("SBEEH3QGU7MFYJFY", "MyCategory" , "Expensive Table" , "Nothing to read" , 1000 , 5 , (Trader) u2);
		Product prod3 = new Product("S000000000000000", "YourCategory" , "Test" , "Nothing to read" , 10 , 5 , (Trader) u2);
		
		ArrayList<Product> items = new ArrayList<Product>();
		
		MergeSort mergeSorter = new MergeSort(); // sort by name.
		QuickSort quickSorter = new QuickSort(); // sort by price.
		ShellSort shellSorter = new ShellSort(); // sort by discount.
		
		try {
			comp.add_product(prod1);
			comp.remove("SRTEH2FF9KEDEFGF"); // First product in the txt.
			comp.remove(prod2);	// Second product in the txt.
			comp.edit(prod3);
			((Customer) u1).order(prod3);
			((Customer) u1).order(prod3);
			System.out.println("Before gathering the order: ");
			comp.list_orders();
			comp.remove_order(1);
			System.out.println("\nAfter gathering the order: ");
			comp.list_orders();
			
			comp.search("Alisha", items); // Search by name;
			
			mergeSorter.sort(items); // sort by name.
			System.out.println("Sorted by name:");
			for(int i = 0; i< items.size(); i++) {
				System.out.println(items.get(i).getName() + " ,\t" + items.get(i).getPrice());
			}
			
			quickSorter.sort(items); // sort by price.
			System.out.println("\nSorted by price:");
			for(int i = 0; i< items.size(); i++) {
				System.out.println(items.get(i).getName() + " ,\t" + items.get(i).getPrice());
			}
			
			shellSorter.shellSort(items); // sort by discount.
			System.out.println("\nSorted by discount:");
			for(int i = 0; i< items.size(); i++) {
				System.out.println(items.get(i).getName() + " ,\t" + items.get(i).getDiscount());
			}
			items = new ArrayList<Product>();
			
			comp.search("Lingerie, Sleep & Swimwear", items); // Searched for category.
			
			mergeSorter.sort(items); // sort by name.
			System.out.println("Sorted by name:");
			for(int i = 0; i< items.size(); i++) {
				System.out.println(items.get(i).getName() + " ,\t" + items.get(i).getPrice());
			}
			
			quickSorter.sort(items); // sort by price.
			System.out.println("\nSorted by price:");
			for(int i = 0; i< items.size(); i++) {
				System.out.println(items.get(i).getName() + " ,\t" + items.get(i).getPrice());
			}
			
			shellSorter.shellSort(items); // sort by discount.
			System.out.println("\nSorted by discount:");
			for(int i = 0; i< items.size(); i++) {
				System.out.println(items.get(i).getName() + " ,\t" + items.get(i).getDiscount());
			}
			
		} catch (IOException e) {
			e.printStackTrace();
		}		
	}

}
