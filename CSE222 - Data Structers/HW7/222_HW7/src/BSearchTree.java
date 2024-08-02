/**
 * Structure of a Binary Search Tree.
 * @author Fatih
 *
 * @param <E>
 */

public class BSearchTree<E extends Comparable<E>> extends BinaryTree<E> {
	// Data Fields
	/** Return value from the public add method. */
	protected boolean addReturn;
	/** Return value from the public delete method. */
	protected E deleteReturn;
	/**
	 * Determine the color of the root.
	 * @return Returns true if the root is red, else returns false.
	 */
	public boolean isRed() {
		return root.isRed; // if the root is red , it can't be redblack Tree.
	}
	/** Determines if the binary tree is a Red-Black-Tree */
	public boolean is_red_black(BSearchTree<E> tree) {
		if(tree.isRed()) {
			return false; // Root cannot be red.
		}
		int[] maxh = new int[1];
		int[] minh = new int[1];
		
		if( !is_height_redblack(tree.root, maxh, minh)) {
			return false;
		}
		
		return true;		
	}
	/** Finds the max and min height of a node and checks if the values are okay for Red-Black-Tree */
	private boolean is_height_redblack(Node<E> localRoot , int maxh[] , int minh[]) {
		
		if(localRoot == null) {
			maxh[0] = 0;
			minh[0] = 0;
			return true;
		}
		
		int[] left_min = new int[1]; // Java doesn't have pointers , so 1 size arrays are needed to call by reference.
		int[] right_min = new int[1];
		int[] left_max = new int[1];
		int[] right_max = new int[1];
		
		is_height_redblack(localRoot.left, left_max, left_min); // Fill the max and min height of the left subtree.
		is_height_redblack(localRoot.right, right_max, right_min); // Fill the max and min height of the right subtree.
		
		maxh[0] = Math.max(left_max[0], right_max[0]) + 1;
		minh[0] = Math.min(left_min[0], right_min[0]) + 1;
		
		if(maxh[0] <= 2 * minh[0]) {
			return true;
		}
		return false;
		
	}
	/**
	 * Started method to determine if the "tree" is balanced.
	 * @param tree Tree to be checked.
	 * @return
	 */
	public boolean is_balanced(BSearchTree<E> tree) {
		return is_balanced(tree.root);
	}
	/**
	 * Compares height of the subtrees.
	 * @param localRoot Tree's root.
	 * @return
	 */
	public boolean is_balanced(Node<E> localRoot) {
		
		if(localRoot == null) {
			return true; // root is empty.
		}
		
		int left_h , right_h;
		
		left_h = height(localRoot.left);
		right_h = height(localRoot.right);
		
		is_balanced(localRoot.left);
		is_balanced(localRoot.right);
		
		if(Math.abs(left_h - right_h) <= 1) {
			return true;
		}
		return false;
	}
	private int height(Node<E> root) {
		if(root == null) {
			return 0;
		}
		return 1 + Math.max(height(root.left) , height(root.right));
		// The algorithm takes the taller one between right and left subtrees.
	}
	
	/** Starter method find.
	 pre: The target object must implement
	 the Comparable interface.
	 @param target The Comparable object being sought
	 @return The object, if found, otherwise null
	*/
	public E find(E target) {
		return find(root, target);
	}
	/** Recursive find method.
	 @param localRoot The local subtree's root
	 @param target The object being sought
	 @return The object, if found, otherwise null
	*/
	private E find(Node<E> localRoot, E target) {
		 if (localRoot == null)
			 return null;
		 // Compare the target with the data field at the root.
		 int compResult = target.compareTo(localRoot.data);
		 
		 if (compResult == 0)
			 return localRoot.data;
		 else if (compResult < 0)
			 return find(localRoot.left, target);
		 else
			 return find(localRoot.right, target);
	}
	/** Starter method add.
	 pre: The object to insert must implement the
	 Comparable interface.
	 @param item The object being inserted
	 @return true if the object is inserted, false
	 if the object already exists in the tree
	*/
	public boolean add(E item) {
		 root = add(root, item);
		 return addReturn;
	}
	/** Recursive add method.
	 post: The data field addReturn is set true if the item is added to
	 the tree, false if the item is already in the tree.
	 @param localRoot The local root of the subtree
	 @param item The object to be inserted
	 @return The new local root that now contains the
	 inserted item
	*/
	private Node<E> add(Node<E> localRoot, E item) {
		 if (localRoot == null) {
			 // item is not in the tree — insert it.
			 addReturn = true;
			 return new Node<>(item);
		 } else if (item.compareTo(localRoot.data) == 0) {
			 // item is equal to localRoot.data
			 addReturn = false;
			 return localRoot;
		 } else if (item.compareTo(localRoot.data) < 0) {
			 // item is less than localRoot.data
			 localRoot.left = add(localRoot.left, item);
			 return localRoot;
		 } else {
			 // item is greater than localRoot.data
			 localRoot.right = add(localRoot.right, item);
			 return localRoot;
		 }
	}
	
	/** Starter method delete.
	 post: The object is not in the tree.
	 @param target The object to be deleted
	 @return The object deleted from the tree
	 or null if the object was not in the tree
	 @throws ClassCastException if target does not implement
	 Comparable
	*/
	public E delete(E target) {
	 root = delete(root, target);
	 return deleteReturn;
	}
	/** Recursive delete method.
	 post: The item is not in the tree;
	 deleteReturn is equal to the deleted item
	 as it was stored in the tree or null
	 if the item was not found.
	 @param localRoot The root of the current subtree
	 @param item The item to be deleted
	 @return The modified local root that does not contain
	 the item
	*/
	private Node<E> delete(Node<E> localRoot, E item) {
		 if (localRoot == null) {
			 // item is not in the tree.
			 deleteReturn = null;
			 return localRoot;
		 }
		 // Search for item to delete.
		 int compResult = item.compareTo(localRoot.data);
		 if (compResult < 0) {
			 // item is smaller than localRoot.data.
			 localRoot.left = delete(localRoot.left, item);
			 return localRoot;
		 } else if (compResult > 0) {
			 // item is larger than localRoot.data.
			 localRoot.right = delete(localRoot.right, item);
			 return localRoot;
		 } else {
				 // item is at local root.
				 deleteReturn = localRoot.data;
			 if (localRoot.left == null) {
				 // If there is no left child, return right child
				 // which can also be null.
				 return localRoot.right;
			 } else if (localRoot.right == null) {
				 // If there is no right child, return left child.
				 return localRoot.left;
			 } else {
				 // Node being deleted has 2 children, replace the data
				 // with inorder predecessor.
				 if (localRoot.left.right == null) {
					 // The left child has no right child.
					 // Replace the data with the data in the
					 // left child.
					 localRoot.data = localRoot.left.data;
					 // Replace the left child with its left child.
					 localRoot.left = localRoot.left.left;
					 return localRoot;
				 } else {
					 // Search for the inorder predecessor (ip) and
					 // replace deleted node's data with ip.
					 localRoot.data = findLargestChild(localRoot.left);
					 return localRoot;
				 }
			 }
		 }
	}
		 
	/** Find the node that is the
	 inorder predecessor and replace it
	 with its left child (if any).
	 post: The inorder predecessor is removed from the tree.
	 @param parent The parent of possible inorder
	 predecessor (ip)
	 @return The data in the ip
	*/
	private E findLargestChild(Node<E> parent) {
		 // If the right child has no right child, it is
		 // the inorder predecessor.
		 if (parent.right.right == null) {
			 E returnValue = parent.right.data;
			 parent.right = parent.right.left;
			 return returnValue;
		 } else {
			 return findLargestChild(parent.right);
		 }
	}
}
