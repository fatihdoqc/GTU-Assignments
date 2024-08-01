package homework3;

import java.util.*;

public class KWArrayList<E> {
	
	// Data Fields
	/** The default initial capacity */
	private static final int INITIAL_CAPACITY = 50;
	/** The underlying data array */
	private E[] theData;
	/** The current size */
	private int size = 0;
	/** The current capacity */
	private int capacity = 0;
	
	public KWArrayList() {
		capacity = INITIAL_CAPACITY;
		theData = (E[]) new Object[capacity];
		
	}
	public boolean add(E anEntry) {
		 if (size == capacity) {
			 reallocate();
		 }
		 
		 theData[size] = anEntry;
		 size++;
		 return true;
	}
	public void add(int index, E anEntry) {
		 if (index < 0 || index > size) {
			 throw new ArrayIndexOutOfBoundsException(index);
		 }
		 if (size == capacity) {
			 reallocate();
		 }
		 /* Shift data in elements from index to size - 1*/
		 for (int i = size; i > index; i--) {
			 theData[i] = theData[i - 1];
		 }
		 /* Insert the new item.*/
		 theData[index] = anEntry;
		 size++;
	}
	private void reallocate() {
		 capacity = 2 * capacity;
		 theData = Arrays.copyOf(theData, capacity);
	}
	public E get(int index) {
		 if (index < 0 || index >= size) {
			 throw new ArrayIndexOutOfBoundsException(index);
		 }
		 
		 return theData[index];
	}
	public E set(int index, E newValue) {
		 if (index < 0 || index >= size) {
			 throw new ArrayIndexOutOfBoundsException(index);
		 }
		 
		 E oldValue = theData[index];
		 theData[index] = newValue;
		 return oldValue;
	}
	public E remove(int index) {
		 if (index < 0 || index >= size) {
			 throw new ArrayIndexOutOfBoundsException(index);
		 }
		 
		 E returnValue = theData[index];
		 for (int i = index + 1; i < size; i++) {
			 theData[i - 1] = theData[i];
		 }
		 size--;
		 return returnValue;
	}
	public boolean removeFirstOccurence(E obj) {
		
		for(int i = 0; i< size; i++) {
			if(theData[i].equals(obj)) {
				remove(i);
				return true;
			}
		}
		return false;
	}
	public int size() {
		return size;
	}
	public String toString() {
		StringBuilder str = new StringBuilder();
		
		for(int i = 0; i<size; i++) {
			str.append(get(i)).append(" ");
		}
		
		return str.toString();
		
	}
}
