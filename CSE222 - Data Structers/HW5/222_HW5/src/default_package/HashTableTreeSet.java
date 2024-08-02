package default_package;

import java.util.LinkedList;
import java.util.TreeSet;
/** Hash table implementation using chaining with Tree Set. */
public class HashTableTreeSet<K extends Comparable<K> , V > implements KWHashMap<K, V>{
	
	private TreeSet<Entry<K, V>>[] table;
	 /** The number of keys */
	private int numKeys;
	 /** The capacity */
	private static final int CAPACITY = 7;
	 /** The maximum load factor */
	private static final double LOAD_THRESHOLD = 3.0;	
	 
	public HashTableTreeSet() {
		table = new TreeSet[CAPACITY];
	}
	
	private static class Entry<K extends Comparable<K>, V> implements Comparable<K>{
		  /** The key */
		  private final K key;
		  /** The value */
		  private V value;
		  /** Creates a new key-value pair.
		  @param key The key
		  @param value The value
		  */
		  public Entry(K key, V value) {
			  this.key = key;
			  this.value = value;
		  }
		  /** Retrieves the key.
		  @return The key
		  */
		  public K getKey() {
			  return key;
		  }
		  /** Retrieves the value.
		  @return The value
		  */
		  public V getValue() {
			  return value;
		  }
		  /** Sets the value.
		  @param val The new value
		  @return The old value
		  */
		  public V setValue(V val) {
			  V oldVal = value;
			  value = val;
			  return oldVal;
		  }
		@Override
		public int compareTo(K o) {
			return o.compareTo(key);
		}
	 }
	/**
	 * Returns the wanted key's value.
	 */
	@Override
	public V get(Object key) {
		int index = key.hashCode() % table.length;
		
		if(index < 0) {
			index += table.length;
		}
		
		if(table[index] == null) {
			return null; // key is not in the table.
		}
		 // Search the list at table[index] to find the key.
		for( Entry<K , V> nextItem : table[index]) {
			if (nextItem.getKey().equals(key))
				 return nextItem.getValue();
		}
		// assert: key is not in the table.
		return null;
	}
	/**
	 * Returns true if the table is empty, false if not.
	 */
	@Override
	public boolean isEmpty() {
		return numKeys == 0;
	}
	/**
	 * Puts the wanted key-value pair to the table.
	 */
	@Override
	public V put(K key, V value) {
		int index = key.hashCode() % table.length;
		 
		 if (index < 0)
			 index += table.length;
		 
		 if (table[index] == null) {
			 table[index] = new TreeSet<>();
		 }
		 
		 // Search the list at table[index] to find the key.
		 for (Entry<K, V> nextItem : table[index]) { // Iterate the Tree Set at the current position.
			 // If the search is successful, replace the old value.
			 if (nextItem.getKey().equals(key)) {
				 
				 // Replace value for this key.
				 V oldVal = nextItem.getValue();
				 nextItem.setValue(value);
				 return oldVal;
			 }
		 }
		 
		 table[index].add(new Entry(key , value));		 
		 numKeys++;
		 if (numKeys > (LOAD_THRESHOLD * table.length)) // If size is full , expand.
			 rehash();
		 
		 return null;
		 
	}
	private void rehash() {
		 // Save a reference to oldTable.
		 TreeSet<Entry<K, V>>[] oldTable = table;
		 // Double capacity of this table.
		 table = new TreeSet[2 * oldTable.length + 1];
		 // Reinsert all items in oldTable into expanded table.
		 numKeys = 0;
		 for (int i = 0; i < oldTable.length; i++) {
			 
			 if(oldTable[i] != null) {
				 for(Entry <K , V> nextItem : oldTable[i]) {
					 put(nextItem.getKey(), nextItem.getValue());
				 }
			 }
		 }
		}
	/**
	 * Removes the wanted key and its value from the table.
	 */
	@Override
	public V remove(Object key) {
		int index = key.hashCode() % table.length;
		
		if(index < 0)
			index += table.length;
		
		if(table[index] == null)
			return null;
		
		for(Entry<K ,V> nextItem : table[index]) { // Scanning the current tree.
			
			if(nextItem.getKey().equals(key)) {	// Wanted key is found.
				V returnValue = nextItem.getValue();
				table[index].remove(nextItem);	// Removing it from the tree.
				numKeys--;
				
				if(table[index].isEmpty()) {	// If the tree is empty after removal , delete tree too.
					table[index] = null;
				}
				return returnValue;
			}
		}
		return null;
	}
	/**
	 * Returns the size of the table.
	 */
	@Override
	public int size() {
		// TODO Auto-generated method stub
		return numKeys;
	}
	/**
	 * Converts datas to String.
	 */
	public String toString() {
		StringBuilder sb = new StringBuilder();
		
		for (int i = 0; i < table.length; i++) {
			 
			if(table[i] != null) {
				 for(Entry <K , V> nextItem : table[i]) {
					 sb.append(nextItem.getKey()).append(" , ").append(nextItem.getValue()).append("\n");
				 }
			}
		}
		return sb.toString();
	}

}
