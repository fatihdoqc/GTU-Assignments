import java.util.ArrayList;

public class QuickSort {
	
	public void sort(ArrayList<Product> table) {
		quickSort(table , 0 , table.size() - 1);
	}
	
	public int partition(ArrayList<Product> table , int first , int last) {
		
		sort3(table, first, last);
		swap(table, first, (first + last) / 2);
		
		
		Product pivot = table.get(first);
		int up = first;
		int down = last;
		
		
		do {
			while ((up < last) && pivot.getPrice() >= table.get(up).getPrice() ) {			
				up++;		
			}			
			while(pivot.getPrice() < table.get(down).getPrice()) {
				down--;					
			}
			if(up < down) {
				swap(table , up , down);
			}
			
		}while(up < down);
		
		swap(table , first , down);
		return down;
	}
	private void quickSort(ArrayList<Product> table, int first, int last) {
		
			if (first < last) { // There is data to be sorted.
				 // Partition the table.
				
				 int pivIndex = partition(table, first, last);
				 
				 // Sort the left half.
				 quickSort(table, first, pivIndex - 1);
				 // Sort the right half.
				 quickSort(table, pivIndex + 1, last);
			}
	}
	public void sort3(ArrayList<Product> table , int first , int last) {
		
		int middle = (first + last ) / 2;
		
		if(table.get(middle).getPrice() < table.get(first).getPrice()) {
			swap(table , first , middle);
		}
		
		if(table.get(last).getPrice() < table.get(middle).getPrice() ) {
			swap(table , middle , last);
		}
		
		if(table.get(middle).getPrice() < table.get(first).getPrice() ) {
			swap(table , middle , first);
		}
		
	}
	public void swap(ArrayList<Product> table , int a , int b) {
		Product temp = table.get(a);
		table.set(a, table.get(b));
		table.set(b, temp);
	}
}
