import java.util.ArrayList;

public class ShellSort {
	
	public void shellSort(ArrayList<Product> table) {
		
		int gap = table.size() / 2;
		
		while(gap > 0) {
			
			for(int nextPos = gap; nextPos < table.size() ; nextPos++) {
				insert(table , nextPos , gap);
			}
			
			if(gap == 2) {
				gap = 1;
			}
			else {
				gap = (int)(gap / 2.2);
			}
		}
		
	}
	
	private void insert(ArrayList<Product> table , int nextPos , int gap) {
		
		Product nextVal = table.get(nextPos);
		
		while(nextPos > gap - 1 && nextVal.getDiscount() < table.get(nextPos-gap).getDiscount()) {
			
			table.set(nextPos, table.get(nextPos - gap));
			
			nextPos = nextPos - gap;
		}
		table.set(nextPos, nextVal);
	}
}
