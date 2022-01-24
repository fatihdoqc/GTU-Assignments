package default_package;

import java.util.*;

/**
 * Max-heap structure to store the values in the descending order.
 * @author Fatih
 *
 * @param <E> The type of the heap must be comparable.
 */
public class MyHeap<E extends Comparable<E>> implements Comparable<E>{
	
	private ArrayList<E> heap;
	/**
	 * Specific iterator for the heap.
	 * 
	 * @author Fatih
	 *
	 */
	public class MyIterator implements Iterator<E>{
		
		private int theData;
		private int lastReturnedItem;
		
		/**
		 * Initializes the iterator.
		 */
		public MyIterator() {
			theData = -1;
			lastReturnedItem = 0;
		}
		/**
		 * Checks if the pointer is at the end of the heap.
		 */
		@Override
		public boolean hasNext() {
			return (theData < heap.size() - 1);
		}
		/**
		 * If exist, returns the next item.
		 */
		@Override
		public E next() {		
			if(hasNext()) {
				
				theData++;
				lastReturnedItem = theData;
				return heap.get(theData);
			}
			return null;
		}
		/**
		 * 
		 * @param x X is the value to set to the last returned item.
		 * @return	Returns the item after insertion.
		 */
		public E setLast(E x) {
			heap.set(lastReturnedItem, x);
			return heap.get(lastReturnedItem);
		}
		
	}
	/**
	 * Initializes a new heap.
	 */
	public MyHeap() {
		heap = new ArrayList<>();
	}
	/**
	 * 
	 * @param item Item is the element to add to the heap.
	 * @return
	 */
	public boolean add(E item) {		
		int parent , current;
		
		heap.add(item);
		current = heap.size() - 1; // Smallest child.
		parent = (current - 1) / 2; // Its parent.
		
		while(heap.get(current).compareTo( heap.get(parent) ) > 0) { // If parent smaller than the child. 
			swap(current , parent); // swap.
			current = parent; // And look for its parent.
			parent = (current - 1) / 2;
		}	
		return true;
	}
	/**
	 *  Removes the root.
	 * @return Returns the removed item.
	 */
	public E remove() {
		
		int parent,
			leftChild,
			rightChild,
			maxChild;
		
		parent = 0;
		
		E returnValue = heap.get(parent);
		heap.set(parent , heap.remove(heap.size() - 1));	// The smallest value in the heap array is in the root now.
				
		while(true) { // Moving the root to its proper place.
			leftChild = (2*parent) + 1;
			rightChild = leftChild + 1;
			
			if(leftChild >= heap.size()) { // It means there is no child of the current parent.
				break;
			}
			maxChild = leftChild; // Assume the leftChild is greater.
			
			if(rightChild < heap.size() && heap.get(rightChild).compareTo(heap.get(maxChild)) > 0) {
				// If the rightChild is the greater one. Change the maxChild to rightChild.
				maxChild = rightChild;
			}
			
			if(heap.get(parent).compareTo( heap.get(maxChild)) < 0) { // If the parent is smaller than the maxchild
				swap(parent , maxChild); // Swap parent and the maxChild
				parent = maxChild;
			}
			else { // Structure is good now. Break.
				break;
			}
		}
		return returnValue;
	}
	/**
	 * Removing by index.
	 * @param index
	 * @return The removed item.
	 */
	public E remove(int index) {
		ArrayList<E> hold = new ArrayList<>(); 
		int size = size();
		E returnValue = heap.get(index); 
		for(int i = 0; i<size; i++) {
			if(i != index) { // Keeping the values. Except the index that wanted to be deleted. 
				hold.add(heap.get(i));
			}
		}
		heap = new ArrayList<>(); // Creating a new heap to replace the old one.
		for(int i = 0; i<size - 1;i++) {	// That heap doesn't contain the item at the wanted index.
			heap.add(hold.get(i));
		}
		
		return returnValue;
	}
	/**
	 * Removes the ith largest item.
	 * @param wanted I'th largest item that wanted to be deleted.
	 * @return Returns the removed item.
	 */
	public E remove_wanted_largest(int wanted) {
		
		int counter = 1;
		ArrayList<E> hold = new ArrayList<>();
		E returnValue = null;
		
		if(heap.size() == 0) {
			return null;
		}
		
		for(int i = 0; i<heap.size(); i++) {
			if(counter == wanted) { 
				returnValue = remove();
				break;
			}
			else {		
				hold.add(remove()); // remove() deletes the root of the heap which is the largest item.
									// And keeping the values except the removed item.
				counter++;	// and counting.
			}
		}
		
		for(int i = 0; i<hold.size(); i++) { // Inserting the stored items to the heap.
			add(hold.get(i));
		}
		
		return returnValue;
		
	}
	/**
	 * Merges two same type of heaps.
	 * @param another Another is the heap to be added to the current heap.
	 */
	public void merge(MyHeap<E> another) {
		
		if(another.size() == 0 ) {
			return;
		}
		
		for(int i = 0; i< another.size(); i++) {
			add(another.get(i)); // Adding all of the indexes of the another heap to the current heap.
		}
	}
	/**
	 * 
	 * @param index
	 * @return Returns the item at the wanted index.
	 */
	public E get(int index) {
		return heap.get(index);
	}
	/**
	 * Finds the index of the wanted item.
	 * @param item 	Wanted item.
	 * @return	 Returns the index of the wanted item.
	 */
	public int search(E item) {
		for(int i = 0; i<heap.size(); i++) {
			if(heap.get(i).compareTo(item) == 0) { // checks if the "i" is the wanted index.
				return i;
			}
		}
		return -1;
	}
	/**
	 * Swaps the indexes of the array.
	 * @param index1
	 * @param index2
	 */
	/* Swaps the wanted two indexes. */
	private void swap(int index1 , int index2) {
		
		E temp = heap.get(index1);	
		heap.set(index1, heap.get(index2));
		heap.set(index2, temp);
	}
	/**
	 * 
	 * @return Returns an iterator at the root of the heap.
	 */
	public MyIterator iterator() {
		return new MyIterator();
	}
	/**
	 * 
	 * @return The number of elements in the heap.
	 */
	public int size() {
		return heap.size();
	}
	/**
	 * @return The string contains the elements in the heap.
	 */
	public String toString() {
		if(heap.size() == 0) {
			return null;
		}
		return heap.toString();
	}
	@Override
	/**
	 * Compares the element with the root's data.
	 */
	public int compareTo(E o) {
		
		return heap.get(0).compareTo(o);
	}
}
