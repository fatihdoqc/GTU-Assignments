import java.util.ArrayList;

public class MergeSort{
	
	public void sort(ArrayList<Product> table) {
		
		if(table.size() > 1){
			int halfSize = table.size() / 2;
			
			//ArrayList<Product> hold = table;
			ArrayList<Product> leftTable = new ArrayList<>();
			ArrayList<Product> rightTable = new ArrayList<>();
			
			for(int i = 0; i<halfSize; i++) {
				leftTable.add(table.get(i));
			}
			
			for(int i = halfSize; i < table.size(); i++) {
				rightTable.add(table.get(i));
			}
			
			//table = new ArrayList<>();
			
			sort(leftTable);
			sort(rightTable);
			
			merge(leftTable , rightTable , table);
			
		}
	}
	
	public void merge(ArrayList<Product> leftTable , ArrayList<Product> rightTable , ArrayList<Product> table) {
		
		int i = 0; // left
		int j = 0; // right
		int k = 0; // table
		
		while(i < leftTable.size() && j < rightTable.size()) {
			
			if(leftTable.get(i).getName().compareTo(rightTable.get(j).getName()) < 0){
				table.set(k++, leftTable.get(i++));
			}
			else {
				table.set(k++, rightTable.get(j++));
			}
		}
		while(i < leftTable.size() ) {
			table.set(k++, leftTable.get(i++));
		}
		while(j < rightTable.size()) {		
			table.set(k++, rightTable.get(j++));
		}
		
	}
}
