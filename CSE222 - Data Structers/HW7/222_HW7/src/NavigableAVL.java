
import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NavigableSet;
import java.util.SortedSet;

/**
 * NavigableSet structure implemented by AVL tree.
 * @author Fatih
 *
 * @param <E>
 */
public class NavigableAVL<E extends Comparable<E>> implements NavigableSet<E>{
	
	private AVLTree<E> theData;
	
	public NavigableAVL() {
		theData = new AVLTree<>();
	}
	
	@Override
	public boolean add(E e) { // insert.
		return theData.add(e);
	}
	@Override
	public NavigableSet<E> headSet(E toElement, boolean inclusive) {
		Iterator<E> iter = theData.iterator();
		NavigableAVL<E> returnSet = new NavigableAVL<>();
		
		while(iter.hasNext()) {
			E temp = iter.next();
			if(inclusive) {
				if(temp.compareTo(toElement) <= 0) {
					returnSet.add(temp);
				}
			}
			else {
				if(temp.compareTo(toElement) < 0) {
					returnSet.add(temp);
				}
			}
		}
		
		return returnSet;
	}
	public NavigableSet<E> tailSet(E fromElement , boolean inclusive){
		Iterator<E> iter = theData.iterator();
		NavigableAVL<E> returnSet = new NavigableAVL<>();
		
		while(iter.hasNext()) {
			E temp = iter.next();
			if(inclusive) {
				if(temp.compareTo(fromElement) >= 0) {
					returnSet.add(temp);
				}
			}
			else {
				if(temp.compareTo(fromElement) > 0) {
					returnSet.add(temp);
				}
			}
		}
		
		return returnSet;
	}
	public String toString() {
		Iterator<E> iter = theData.iterator();
		StringBuilder sb = new StringBuilder();
		
		while(iter.hasNext()) {
			sb.append(iter.next());
			if(iter.hasNext()) {
				sb.append(" , ");
			}
		}
		
		return sb.toString();
	}	
	
	@Override
	public Iterator<E> iterator() { // Iterator implementation is in the BinaryTree.java
		return theData.iterator();
	}
	
	/* END OF THE HOMEWORK */
	
	

	@Override
	public Comparator<? super E> comparator() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public E first() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public E last() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int size() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean contains(Object o) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public Object[] toArray() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public <T> T[] toArray(T[] a) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean remove(Object o) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean containsAll(Collection<?> c) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean addAll(Collection<? extends E> c) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean retainAll(Collection<?> c) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean removeAll(Collection<?> c) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void clear() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public E lower(E e) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public E floor(E e) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public E ceiling(E e) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public E higher(E e) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public E pollFirst() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public E pollLast() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public NavigableSet<E> descendingSet() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Iterator<E> descendingIterator() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public SortedSet<E> subSet(E fromElement, E toElement) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public SortedSet<E> tailSet(E fromElement) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public SortedSet<E> headSet(E toElement) {
		// TODO Auto-generated method stub
		return null;
	}
	
}
