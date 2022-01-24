package default_package;

import java.util.*;

/**
 * Driver class.
 * @author Fatih
 *
 */
public class Main {
	public static int get_index(ArrayList<Integer> arr , int item) {
		for(int i = 0 ; i < arr.size(); i++) {
			if(arr.get(i) == item) {
				return i;
			}
		}
		return -1;
	}
	public static int find_occurance(ArrayList<Integer> arr, int item) {

		int temp = 0;
		
		for(int i =0 ; i< arr.size() ; i++) {
			if(arr.get(i) == item) {
				
				temp = i;
				while(arr.get(i) == item ) {
					i++;
					if(i >= arr.size()) {
						break;
					}
				}
				
				return i - temp;
			}
		}
		
		return 0;
	}
	public static int max_occur(ArrayList<Integer> arr) {
		
		int max = 0 , index = 0;
		
		for(int i = 0; i< 3000; i++) {
			
			int temp = find_occurance(arr, arr.get(i));
			if( temp > max) {
				max = temp;
				index = i;
			}
		}
		
		return index;
	}
	public static void main(String [] args) {
		
		MyHeap<Integer> heap = new MyHeap<>();
		
		heap.add(1523);
		heap.add(12934);
		heap.add(153);
		heap.add(189);
		heap.add(173);
		heap.add(423);
		heap.add(23);
		heap.add(7323);
		heap.add(1522);
		heap.add(14);
		heap.add(10);		
		System.out.println("Heap: \n" + heap);
		
		System.out.println("\nRemoving the root.");
		heap.remove();
		System.out.println("Heap: \n" + heap);
		System.out.println("\nRemoving the root.");
		heap.remove();
		System.out.println("Heap: \n" + heap);
		
		System.out.println("\nRemoving fifth largest element.");
		System.out.println("fifth largest element: " + heap.remove_wanted_largest(5));
		System.out.println("Heap: \n" + heap);
		
		System.out.println("\nRemoving fourth largest element.");
		System.out.println("fourth largest element: " + heap.remove_wanted_largest(4));
		System.out.println("Heap: \n" + heap);
		
		MyHeap<Integer> another = new MyHeap<>();
		
		another.add(1);
		another.add(2);
		another.add(3);
		another.add(4);
		another.add(10000);
		
		System.out.println("\nHeap: \n" + heap);
		System.out.println("Another Heap: \n" + another);
		
		System.out.println("Merging heaps: ");
		heap.merge(another);
		System.out.println("Heap: \n" + heap);
		
		System.out.println("\nSearching...(-1 means item is not in the heap.)");
		System.out.println("Item: " + 10000 + " , Index: " + heap.search(10000));
		System.out.println("Item: " + 23 + " , Index: " + heap.search(23));
		System.out.println("Item: " + 153 + " , Index: " + heap.search(153));
		System.out.println("Item: " + 423 + " , Index: " + heap.search(423));
		System.out.println("Item: " + 14 + " , Index: " + heap.search(14));
		System.out.println("Item: " + 99999 + " , Index: " + heap.search(99999));
		System.out.println("Item: " + 123456 + " , Index: " + heap.search(123456));
		System.out.println("Item: " + 11 + " , Index: " + heap.search(11));
		
		System.out.println("\nPrinting the heap with an iterator:");
		MyHeap.MyIterator iter = heap.iterator();
		
		for(int i = 0; i< heap.size(); i++) {
			if(iter.hasNext()) {
				System.out.print(iter.next() + " ");
			}
		}
		System.out.println();
		
		System.out.println("\nSetting the last returned item by the iterator 99999");
		
		
		iter = heap.iterator();
		for(int i = 0; i< heap.size(); i++) {
			if(iter.hasNext()) {
				System.out.print(iter.next() + " ");
			}
			if(i == 3) {
				System.out.print(iter.setLast(99999) + " ");
			}
		}
		System.out.println();
			
		/* ******************* */
		BSTHeapTree<Integer> tree = new BSTHeapTree<>();
		Random rand = new Random();
		ArrayList<Integer> arr = new ArrayList<>();
		
		for(int i = 0; i<3000; i++) {
			int temp = rand.nextInt(5000);
			tree.add(temp);
			arr.add(temp);
		}
		Collections.sort(arr);
		System.out.println("BSTHeapTree:");
		System.out.println(tree);
		
		System.out.println("Items exist in tree: ");
		for(int i = 0; i< 100; i++) {
			int temp = arr.get(rand.nextInt(3000));
			while(tree.find(temp) == 0) {
				temp = arr.get(rand.nextInt(3000));
			}
			System.out.println("Item: " + temp + " , Occurance in the array: " + find_occurance(arr, temp) + " , Occurance in the tree: " + tree.find(temp));
		}
		
		System.out.println("\nItems doesn't exist in tree: ");
		for(int i = 0; i<10 ; i++) {
			int temp = rand.nextInt(1000) + 5000;
			System.out.println("Item: " + temp + " , Occurance in the array: " + find_occurance(arr, temp) + " , Occurance in the tree: " + tree.find(temp));
		}

		System.out.println("\nMode of the tree: " + tree.find_mode() + " Occurance in the array: " + find_occurance(arr,  arr.get(max_occur(arr))) +
				" Occurance in the tree: " + tree.find(tree.find_mode()) );
		
		System.out.println();
		
		for(int i = 0; i<100 ; i++) {
			int temp = arr.get(rand.nextInt(2000));
			while(tree.find(temp) == 0) {
				temp = arr.get(rand.nextInt(2000));
			}		
			System.out.println("Removed item: " + temp + "\t,\tBefore removal occurance: " + tree.find(temp) + "\t,\tAfter removal: " + tree.remove(temp));
		}
		System.out.println("\n\n");
		for(int i = 0; i< 10; i++) {
			int temp =	rand.nextInt(1000) + 5000
					;
			System.out.println("Trying to remove non-existing item: " + temp + "\t,\tBefore removal occurance: " + tree.find(temp) + "\t,\tAfter removal: " + tree.remove(temp));
		}		
	}

}
