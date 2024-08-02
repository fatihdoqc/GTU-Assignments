package default_package;

import java.util.ArrayList;

import com.sun.jdi.Value;

/**
 * Generic type Binary Search Tree with max-heap nodes.
 * BSTHeapTree contains variables for root , size  and occurrence.
 * 
 * 
 * @author Fatih
 *
 * @param <E> Type must be Comparable.
 */
public class BSTHeapTree<E extends Comparable<E>> {
	/**
	 * Protected node class.
	 * @author Fatih
	 *
	 * @param <E> E is the generic type to store in that node.
	 * That node also stores its left and right nodes.
	 */
	protected class Node<E>{
		
		protected E data;
		protected Node<E> left;
		protected Node<E> right;
		
		/**
		 * Constructor to initialize a node with data in it.
		 * @param data 
		 */
		public Node(E data){
			this.data = data;
			left = null;
			right = null;
		}
		public E get() {
			return data;
		}
		public String toString() {
			StringBuilder sb = new StringBuilder();
			sb.append(data);
			return sb.toString();
		}
		
	}
	protected Node< MyHeap < ValueOccurance<E> > > root;
	private int size;
	private int occur;
	
	public BSTHeapTree(){
		root = null;
		size = 0;
	}
	/**
	 * Adds the "e" to the tree.
	 * @param e Is the item to add to the BSTHeapTree.
	 * @return The occurance of e in the tree.
	 */
	public int add(E e) {
		root = add(root , e);
		size++;
		return occur;
	}
	private Node<MyHeap<ValueOccurance<E>>> add(Node<MyHeap< ValueOccurance<E>>> localRoot , E e ){
		
		ValueOccurance<E> value = new ValueOccurance<>(e);
		
		if(localRoot == null) { // Means the item doesn't exist in the tree. So initialize it.
			
			MyHeap<ValueOccurance<E>> heap = new MyHeap<>(); // Temporary heap.
			heap.add(value);								
			localRoot = new Node<MyHeap< ValueOccurance< E > > >(heap); // Adding the heap with the data to the tree.
			occur = 1;
			return localRoot;
		}
		
		int index = localRoot.data.search(value); // localRoot is a node which holds a heap.
												  // Looking for the value in that heap if it contains it.
												  // -1 means it doesn't. If it does , index will be the index of the value in the heap.
		
		if(localRoot.data.size() < 7 && index == -1) { // There is a space in the heap. So no need to initialize a new heap.
			
			localRoot.data.add(value);
			occur = value.getOccur();
			return localRoot;
		}
		
		if(index != -1) { // If the heap contains the value.
			localRoot.data.get(index).increaseOccur();
			occur = localRoot.data.get(index).getOccur();
			return localRoot;
		}
		else if(e.compareTo(localRoot.data.get(0).getData()) < 0){ 	// Comparing the value with the top of the heap.
			localRoot.left = add(localRoot.left , e);				// If the result is lesser than zero 
			return localRoot;										// That means The value I seek can't be in the right subtree.
		}
		else if(e.compareTo(localRoot.data.get(0).getData()) > 0){	// If greater than zero.
			localRoot.right = add(localRoot.right , e);				// That means The value I seek can't be in the left subtree.
			return localRoot;
		}
	
		return localRoot;
		
	}
	/**
	 * Removes the wanted item from tree.
	 * @param item Item that wants to be removed.
	 * @return Returns the occurance of this item after removal.
	 */
	public int remove(E item) {
		root = remove(root , item);
		size--;
		return occur;
	}
	private Node< MyHeap <ValueOccurance< E >>> remove(Node< MyHeap <ValueOccurance< E >>> localRoot , E item ){
		if(localRoot ==  null) { // item is not in the tree.
			return localRoot;
		}
		
		int searchResult = localRoot.data.search(new ValueOccurance<E>(item)); // If item is in localRoot's heap. Search result will be the index of the item.
		if(searchResult != -1) { // item is in that heap node;
			
			if(localRoot.data.size() == 1 && localRoot.data.get(0).getOccur() == 1) { // After removal that heap will be empty so it needs to be removed.
				localRoot = delete(localRoot , localRoot.data); // Heap remove method.
				occur = 0;
				return localRoot;
			}
			
			localRoot.data.get(searchResult).decreaseOccur();
			occur = localRoot.data.get(searchResult).getOccur();
			
			if(localRoot.data.get(searchResult).getOccur() == 0) { // If the item is removed completely.
				localRoot.data.remove(searchResult);				// Remove the corresponding heap node.
			}
			return localRoot;
		}
		else { // item is not in that heap , look for another.
			int compResult = item.compareTo(localRoot.data.get(0).getData()); 
			
			if(compResult < 0){	// If the item lesser than the current heap's root.
				localRoot.left = remove(localRoot.left , item);
				return localRoot;
			}
			else {	// If the item greater than the current heap's root.
				localRoot.right = remove(localRoot.right , item);
				return localRoot;
			}
			
		}
		
	}
	private Node< MyHeap <ValueOccurance< E >>> delete(Node< MyHeap <ValueOccurance< E >>> localRoot , MyHeap<ValueOccurance<E>> target){
		
		if(localRoot.data == null) {
			return null;
		}
		int compResult = target.compareTo(localRoot.data.get(0));
		
		if(compResult < 0) { // Trying to find the node that contains the heap that I seek for.
			localRoot.left = delete(localRoot.left , target);
			return localRoot;
		}
		else if(compResult > 0) {
			localRoot.right = delete(localRoot.right , target);
			return localRoot;
		}
		else {
			// Target is at localRoot
			if(localRoot.left == null) { // If left child is null. Replace the parent with right child.
				return localRoot.right;
			}
			else if(localRoot.right == null) {	// If left child is not null and right child is null. Replace the parent with left child.
				return localRoot.left;
			}
			else {	// If both child is not null.
				
				if(localRoot.right.left == null) {	// Look for the smallest child of the right subtree to not the break the BST structure.
					localRoot.data = localRoot.right.data;
					localRoot.right = localRoot.right.right;
					return localRoot;
				}
				else {
					localRoot.data = findSmallestChild(localRoot.right);
					return localRoot;
				}
			}
		}
	}
	private MyHeap <ValueOccurance< E >> findSmallestChild(Node< MyHeap <ValueOccurance< E >>> parent) {
		if(parent.left.left == null) { // parent's left is smallest in that case.
			MyHeap<ValueOccurance<E>> returnValue = parent.left.data;
			parent.left = parent.left.right;
			return returnValue;
		}
		else { // Looking for that case.
			return findSmallestChild(parent.left);
		}
	}
	/**
	 * 
	 * @param item Item that wants to be found.
	 * @return Returns the occurrence of the item.
	 */
	public int find(E item) {
		find(root , item );
		return occur;
	}
	/**
	 * Compares the occurrences of the elements in the tree.
	 * @return returns the element with max occurrence. 
	 */
	public E find_mode() {
		int max[] = new int[1];
		max[0] = -1;
		ValueOccurance<E> element = new ValueOccurance<E>(null);
		find_mode(root , max[0] , element);
		return element.getData();
	
	}
	private int find_mode(Node<MyHeap<ValueOccurance<E>>> localRoot , int max , ValueOccurance<E> max_element){
		
		if(localRoot == null) { // End of the tree.
			return max;
		}
		
		for(int i = 0; i<localRoot.data.size(); i++) { // Searching the max occurrence in the localRoot's heap.
			if(max < localRoot.data.get(i).getOccur()) {
				max = localRoot.data.get(i).getOccur();
				max_element.setData(localRoot.data.get(i).getData());
			}
		}
		max = find_mode(localRoot.left , max , max_element); // Same progress for the localRoot's childs.
		max = find_mode(localRoot.right , max , max_element); //  So that way I will be searched all of the items.
		return max;
	}
	private void find(Node<MyHeap<ValueOccurance<E>>> localRoot, E item ){
		
		if(localRoot == null) { // Item is not in the tree.
			occur = 0;
			return;
		}
		int searchResult = localRoot.data.search(new ValueOccurance<E>(item));
		if(searchResult != -1) { // item is in that heap node;
			occur = localRoot.data.get(searchResult).getOccur();
			return;
		}
		else { // Item is not in that heap. Look for another heap node.
			int compResult = item.compareTo(localRoot.data.get(0).getData());
			
			if(compResult < 0){ // Go left if the item is smaller than the heap's root.
				find(localRoot.left , item);
			}
			else {
				find(localRoot.right , item);
			}
		}
		
	}
	public String toString() {
		StringBuilder sb = new StringBuilder();
		traverseTree(root , 1 , sb);
		return sb.toString();	
	}
	private void traverseTree(Node<MyHeap< ValueOccurance<E>>> localRoot , int depth , StringBuilder sb) {
		
		for(int i = 1; i<depth; i++) {
			sb.append(" ");
		}
		if(localRoot == null) {
			sb.append("null\n");
		}
		else {
			for(int i = 0; i<localRoot.data.size(); i++) { // Filling the "sb" with the datas and the occurrences in of that heap.
				sb.append(localRoot.data.get(i).getData()).append(".").append(localRoot.data.get(i).getOccur()).append(" , ");
			}
			sb.append("\n");
			traverseTree(localRoot.left , depth + 1 , sb); // Scanning the whole tree.
			traverseTree(localRoot.right, depth + 1 , sb);
		}
	}
	/**
	 * 
	 * @return Number of the elements in the tree..
	 */
	public int size() {
		return size;
	}

	
	
}