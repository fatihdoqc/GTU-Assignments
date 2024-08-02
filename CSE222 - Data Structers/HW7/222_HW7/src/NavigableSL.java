
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NavigableSet;
import java.util.SortedSet;

/**
 * NavigableSet structure implemented by Skip Lists.
 * @author Fatih
 *
 * @param <E>
 */
public class NavigableSL<E extends Comparable<E>> implements NavigableSet<E> {
	
	private SkipList<E> theData;
	
	/**
	 * Descending iterator.
	 * @author Fatih
	 *
	 */
	private class DescIterator implements Iterator<E>{
		
		ArrayList<E> hold = new ArrayList<>();
		Iterator<E> iter = theData.iterator();
		int counter = 0;
		
		public DescIterator() {
			while(iter.hasNext()) {
				hold.add(iter.next());
			}
			
			Collections.sort(hold, Collections.reverseOrder()); // The skipList is already sorted by ascending order.
		}														// "hold" arraylist is used for the sort by descending order.
		
		@Override
		public boolean hasNext() {
			return hold.size() != counter;
		}

		@Override
		public E next() {
			if(hasNext()) {
				return hold.get(counter++);
			}
			return null;
		}
		
	}
	
	public NavigableSL() {
		theData = new SkipList<>();
	}
	
	@Override
	public boolean add(E e) {
		if(!theData.contains(e)) {
			theData.add(e);
			return true;
		}
		return false; // item is already in set.
	}
	
	public boolean remove(E e) {
		if(theData.contains(e)) {
			theData.remove(e);
			return true;
		}
		return false; // item is not in set.
	}
	@Override
	public Iterator<E> iterator(){
		return theData.iterator();
	}
	
	public Iterator<E> descendingIterator(){	
		return new DescIterator();
	}
	public String toString() {
		return theData.toString();
	}
	
	
	
	
	

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
	public NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public NavigableSet<E> headSet(E toElement, boolean inclusive) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public NavigableSet<E> tailSet(E fromElement, boolean inclusive) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public SortedSet<E> subSet(E fromElement, E toElement) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public SortedSet<E> headSet(E toElement) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public SortedSet<E> tailSet(E fromElement) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean remove(Object o) {
		// TODO Auto-generated method stub
		return false;
	}
}
