package homework3;

/**
 * Class that stores the datas in a linked list through ArrayList.
 * @author Fatih
 *
 * @param <E>
 */
public class HybridList<E> {
	
	KWArrayList<E> arr;
	KWLinkedList<KWArrayList<E>> theData;
	int size;
	int MAX_NUMBER ;
	
	/**
	 * theData is the linked list that holds ArrayLists.
	 * size is the size of the elements.
	 * MAX_NUMBER is the number of elements that can be hold in an ArrayList.
	 * arr is the ArrayList to hold elements.
	 */
	public HybridList() {
		theData = new KWLinkedList<>();
		size = 0;
		MAX_NUMBER = 5;
		arr = new KWArrayList<>();
		theData.addFirst(arr);
	}
	
	/**
	 * Adds the element to the wanted spot.
	 * @param index is the wanted spot.
	 * @param e is the item.
	 * @return
	 */
	public boolean add(int index , E e) {
		
		if(index == theData.size()) {
			if(theData.get(index-1).size() != MAX_NUMBER) {
				theData.get(index-1).add(e);
			}
			else {
				arr = new KWArrayList<>();
				arr.add(e);
				theData.add(index, arr);
			}
		}
		else {
			if(theData.get(index).size() != MAX_NUMBER) {
				theData.get(index).add(e);
			}
			else {
				arr = new KWArrayList<>();
				arr.add(e);
				theData.add(index, arr);
			}
		}
		size++;
		return true;
	}
	public boolean remove(E obj) {
		
		for(int i = 0; i < theData.size(); i++) {
			if(theData.get(i).removeFirstOccurence(obj) == true) {
				size--;
				if(theData.get(i).size() == 0 ) {
					theData.remove(theData.get(i));
				}
				return true;
			}
		}
		return false;
	}
	/**
	 * Adds the element to the head of the linked list.
	 * @param e is the element.
	 * @return returns false if the memory is out of space.
	 */
	public boolean addFirst(E e) {
		add(0, e);
		return true;
	}
	public boolean addLast(E e) {
		add(theData.size() , e);
		return true;
	}
	public E get(int index) {
		return theData.get(index / MAX_NUMBER).get(index % MAX_NUMBER);
	}
	/**
	 * Prints the HybridList.
	 */
	public String toString() {
		StringBuilder str = new StringBuilder();
		KWArrayList<E> temp;
		
		for(int i = 0; i<theData.size(); i++) {
			temp = theData.get(i); // The ArrayList at the spot.
			str.append(temp); // Taking ArrayList's elements.
		}
		return str.toString();
	}
	public int size_element() {
		return theData.size();
	}
	public int size() {
		return size;
	}
	
}
