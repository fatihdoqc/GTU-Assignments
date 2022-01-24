/**
 * Class to decide if a tree is red-black or AVL or both.
 * @author Fatih
 *
 * @param <E>
 */
public class Is_AVL_RB<E extends Comparable<E>> {
	
	public void determine(BSearchTree<E> tree) {
		
		boolean avl , rb;
		
		if(rb = tree.is_red_black(tree)) {
			System.out.println("The tree is Red-Black-Tree.");
		}
		
		if( avl = tree.is_balanced(tree)) {
			System.out.println("The tree is an AVL tree.");
		}
		
		if(!rb && !avl) {
			System.out.println("The tree is neither a Red-Black-Tree nor an AVL tree.");
		}
		
	}
}
