
import java.io.*;
import java.util.ArrayList;
import java.util.Iterator;

/** Class for a binary tree that stores type E objects. */

public class BinaryTree<E> implements Serializable {
 // Insert inner class Node<E> here.
 // Data Field
 /** The root of the binary tree */
 protected Node<E> root;

	/** Class to encapsulate a tree node. */
	protected static class Node<E> implements Serializable {
		 // Data Fields
		 /** The information stored in this node. */
		 protected E data;
		 /** Reference to the left child. */
		 protected Node<E> left;
		 /** Reference to the right child. */
		 protected Node<E> right;
		 /** Color indicator. True if red, false if black. */
		 protected boolean isRed;
		 // Constructors
		 /** Construct a node with given data and no children.
		 @param data The data to store in this node
		 */
		 public Node(E data) {
			 this.data = data;
			 left = null;
			 right = null;
		 }
		// Methods
		 /** Return a string representation of the node.
		 @return A string representation of the data fields
		 */
		 public String toString () {
			 return data.toString();
		 }
	}
	
	private class Iter implements Iterator<E>{
		  
		ArrayList<E> tree = new ArrayList<>();
		
		public Iter() {
			fill((Node<E>) root);
		}

		@Override
		public boolean hasNext() {
			return tree.size() != 0;
		}

		@Override
		public E next() {
			if(hasNext()) {
				return tree.remove(0);
			}
			return null;
		}
		public void fill(Node<E> localRoot) {
			if(localRoot == null) {
				return;
			}
			tree.add(localRoot.data);
			fill(localRoot.left);	
			fill(localRoot.right);	
		}
		  
	  }
	
	
	public BinaryTree() {
		 root = null;
	}
	
	protected BinaryTree(Node<E> root) {
		 this.root = root;
	}
	/** Constructs a new binary tree with data in its root leftTree
	 as its left subtree and rightTree as its right subtree.
	*/
	public BinaryTree(E data, BinaryTree<E> leftTree, BinaryTree<E> rightTree) {
		 root = new Node<>(data);
		 
		 if (leftTree != null) {
			 root.left = leftTree.root;
		 } else {
			 root.left = null;
		 }
		 if (rightTree != null) {
			 root.right = rightTree.root;
		 } else {
			 root.right = null;
		 }
	}
	/** Returns a pre-order iterator. */
	public Iterator<E> iterator(){
		  return new Iter();
	  }
	/** Return the left subtree.
	 @return The left subtree or null if either the root or
	 the left subtree is null
	*/
	public BinaryTree<E> getLeftSubtree() {
		 if (root != null && root.left != null) {
			 return new BinaryTree<>(root.left);
		 } else {
			 return null;
		 }
	}
	/** Return the right subtree.
	 @return The right subtree or null if either the root or
	 the right subtree is null
	*/
	public BinaryTree<E> getRightSubtree() {
		 if (root != null && root.right != null) {
			 return new BinaryTree<>(root.right);
		 } else {
			 return null;
		 }
	}
	public String toString() {
		 StringBuilder sb = new StringBuilder();
		 toString(root, 1, sb);
		 return sb.toString();
	}
	/** Converts a sub-tree to a string.
	 Performs a preorder traversal.
	 @param node The local root
	 @param depth The depth
	 @param sb The StringBuilder to save the output
	*/
	private void toString(Node<E> node, int depth, StringBuilder sb) {
		 for (int i = 1; i < depth; i++) {
			 sb.append(" ");
		 }
		 if (node == null) {
			 sb.append("null\n");
		 } else {
			 sb.append(node.toString());
			 sb.append("\n");
			 toString(node.left, depth + 1, sb);
			 toString(node.right, depth + 1, sb);
		 }
	}
}

	