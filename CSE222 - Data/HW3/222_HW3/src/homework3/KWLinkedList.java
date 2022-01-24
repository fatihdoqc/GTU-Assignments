package homework3;

import java.util.*;

public class KWLinkedList<E> {	
	/**
	 *  A Node is the building block for a double-linked list. 
	 *  
	 */
	
	 private static class Node<E> {
		 /** The data value. */
		 private E data;
		 /** The link to the next node. */
		 private Node<E> next = null;
		 /** The link to the previous node. */
		 private Node<E> prev = null;
		 /** Construct a node with the given data value.
		 @param dataItem The data value
		 */
		 private Node(E dataItem) {
		 data = dataItem;
		 }
	 }
	 /** Inner class to implement the ListIterator interface. */
	 private class KWListIter {
		/** A reference to the next item. */
		private Node<E> nextItem;
		/** A reference to the last item returned. */
		private Node<E> lastItemReturned;
		/** The index of the current item. */
		private int index = 0;
		
		public KWListIter() {
			index = 0;
			nextItem = head;
			lastItemReturned = null;
		}
		
		/** Construct a KWListIter that will reference the ith item.
		 @param i The index of the item to be referenced
		*/
		public KWListIter(int i) {
			// Validate i parameter.
			if (i < 0 || i > size) {
				throw new IndexOutOfBoundsException("Invalid index " + i);
			}
			lastItemReturned = null; // No item returned yet.
			// Special case of last item.
			if (i == size) {
				index = size;
				nextItem = null;
			}else { // Start at the beginning
				nextItem = head;
				for (index = 0; index < i; index++) {
					nextItem = nextItem.next;
				 }
			}
		}
		public boolean hasNext() {
			
			return nextItem != null;
		}
		public E next() {
			
			if(!hasNext()) {
				return null;
			}
			lastItemReturned = nextItem;
			nextItem = nextItem.next;
			index++;
			return lastItemReturned.data;
		}
		public boolean hasPrevious() {
			return (nextItem == null && size != 0)
					|| nextItem.prev != null;
			}
		/** Move the iterator backward and return the previous item.
		 @return The previous item in the list
		 @throws NoSuchElementException if there is no such object
		*/
		public void get() {
			System.out.println(nextItem.data + "\n");
		}
		public E previous() {
			if (!hasPrevious()) {
				throw new NoSuchElementException();
			}
			if (nextItem == null) { // Iterator is past the last element
				nextItem = tail;
			}else {
				nextItem = nextItem.prev;
			}
			lastItemReturned = nextItem;
			index--;
			return lastItemReturned.data;
		}
		public int nextIndex() {
			if(index == size) {
				return size;
			}
			
			return index + 1;
		}
		public int previousIndex() {
			if(index == 0) {
				return -1;
			}
			
			return index - 1;
		}
		public Node<E> remove() {
			
			Node<E> returnValue = lastItemReturned;
			
			if(lastItemReturned == head) {
				if(size == 1) {
					head = null;
				}
				else {
					head = lastItemReturned.next;
				}
		
			}
			else if(lastItemReturned == tail) {
				tail = lastItemReturned.prev;
			}
			else {
				lastItemReturned.prev.next = lastItemReturned.next;
				lastItemReturned.next.prev = lastItemReturned.prev;
				
				lastItemReturned = lastItemReturned.prev;
				nextItem = lastItemReturned.next;
			}		
			size--;
			return returnValue;
		}
		/** Add a new item between the item that will be returned
		 by next and the item that will be returned by previous.
		 If previous is called after add, the element added is
		 returned.
		 @param obj The item to be inserted
		*/
		public void add(E obj) {
			if (head == null) { // Add to an empty list.
				head = new Node<>(obj);
				tail = head;
			} else if (nextItem == head) { // Insert at head.
				 // Create a new node.
				 Node<E> newNode = new Node<>(obj);
				 // Link it to the nextItem.
				 newNode.next = nextItem;  // Step 1
				 // Link nextItem to the new node.
				 nextItem.prev = newNode;  // Step 2
				 // The new node is now the head.
				 head = newNode; // Step 3
			} else if (nextItem == null) { // Insert at tail.
				 // Create a new node.
				 Node<E> newNode = new Node<>(obj);
				 // Link the tail to the new node.
				 tail.next = newNode; // Step 1
				 // Link the new node to the tail.
				 newNode.prev = tail; // Step 2
				 // The new node is the new tail.
				 tail = newNode; // Step 3
			} else { // Insert into the middle.
				 // Create a new node.
				 Node<E> newNode = new Node<>(obj);
				 // Link it to nextItem.prev.
				 newNode.prev = nextItem.prev; // Step 1
				 nextItem.prev.next = newNode; // Step 2
				 // Link it to the nextItem.
				 newNode.next = nextItem; // Step 3
				 nextItem.prev = newNode; // Step 4
				}
			// Increase size and index and set lastItemReturned.
			 size++;
			 index++;
			 lastItemReturned = null;
			} // End of method add. 
	}
	// Data Fields
	/** A reference to the head of the list. */
	private Node<E> head = null;
	/** A reference to the end of the list. */
	private Node<E> tail = null;
	/** The size of the list. */
	private int size = 0;
	
	/** Add an item at position index.
	 @param index The position at which the object is to be
	 inserted
	 @param obj The object to be inserted
	 @throws IndexOutOfBoundsException if the index is out
	 of range (i < 0 || i > size())
	 */
	public KWListIter listIterator(int index) {
		
		return new KWListIter(index);
			
	}
	public void add(int index, E obj) {
		listIterator(index).add(obj);
	}
	public void addFirst(E obj) {
		add(0, obj);
	}
	public void addLast(E obj) {
		add(size, obj);
	}
	/** Get the element at position index.
	 @param index Position of item to be retrieved
	 @return The item at index
	 */
	public E get(int index) {
		return listIterator(index).next();
	}
	public String toString() {
		StringBuilder str = new StringBuilder();
		
		for(int i = 0; i<size; i++) {
			str.append(get(i)).append(" ");
		}
		
		return str.toString();
	}
	public int size() {
		return size;
	}
	public E getFirst() {
		return get(0);
	}
	public E getLast() {
		return get(size - 1);
	}
	public boolean remove(E obj) {
		KWListIter iter = new KWListIter();
		for(int i = 0; i< size; i++) {
		
			if(iter.next().equals(obj)) {
				iter.remove();
				return true;
			}
		}
		return false;
	}
	
}
