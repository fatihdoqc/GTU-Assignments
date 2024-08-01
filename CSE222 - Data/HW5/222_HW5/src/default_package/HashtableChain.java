package default_package;

import java.util.*;
/** Hash table implementation using chaining. */
public class HashtableChain<K, V> implements KWHashMap<K, V> {
	 // Insert inner class Entry<K, V> here.
	 /** The table */
	 private LinkedList<Entry<K, V>>[] table;
	 /** The number of keys */
	 private int numKeys;
	 /** The capacity */
	 private static final int CAPACITY = 10;
	 /** The maximum load factor */
	 private static final double LOAD_THRESHOLD = 3.0;
	 private K firstItem;
	 // Constructor
	 public HashtableChain() {
		 table = new LinkedList[CAPACITY];
	 }
	 /** Contains key-value pairs for a hash table. */
	 private static class Entry<K, V> {
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
	 }
	 /**
	  * Custom iterator with prev() feature.
	  * @author Fatih
	  *
	  */
	public class MapIterator implements Iterator{
		 
		private K key;
		private V value;
		private int nextList;
		private int nextIndex;
		private int iteratedItemNumber;
		private int holdList;
		private int holdIndex;
		 /**
		  * Constructor that starts the iterator to iterate from the beginning.
		  */
		public MapIterator() {
			key = null;
			value = null;
			nextList = 0;
			nextIndex = 0;
			iteratedItemNumber = 0;
			holdList = 0;
			holdIndex = 0;
		}
		/**
		 * Constructor that starts the iterator to iterate from the wanted key.
		 * @param wanted
		 */
		public MapIterator(K wanted) {
			this.key = key;
			value = null;
			nextList = 0;
			nextIndex = 0;
			iteratedItemNumber = 0;
			holdList = 0;
			holdIndex = 0;
			
			while(hasNext()) {
				int temp = holdList;
				if(next().equals(wanted)) {
					
					if(nextIndex == 0 && temp != holdList) { // After next() , if the iterator is not on the same list.
						value = table[holdList].get( holdIndex - 1 ).getValue();
					}
					else { // After next() , if the iterator is on the same list.
						value = table[nextList].get( nextIndex - 1 ).getValue();
					}
					iteratedItemNumber = 0;
					return;
				}
			}
			nextList = 0;
			nextIndex = 0;
			iteratedItemNumber = 0;
			holdList = 0;
			holdIndex = 0;
		}
		/**
		 * Returns if there are any non-iterated keys.	
		 */
		@Override
		public boolean hasNext() {
			return iteratedItemNumber < numKeys;
		}
		/**
		 * Moves the iterator backwards.
		 * @return iterated key.
		 */
		public K prev() {
			if(hasNext()) {
				
				while(table[nextList] == null) { // If the current list is null.
					nextList--;					 // Iterate another.
					if(nextList < 0) {			 // Circular array , iterator goes to the end of the table.
						nextList += table.length;
					}
					nextIndex = 0;
				}
				
				for(; nextIndex <table[nextList].size(); nextIndex++) { // Scanning the current list.
								
					if(table[nextList].get(nextIndex) != null) { // If the current list's current node is not null.
						K returnValue = table[nextList].get(nextIndex).getKey(); // Iterate through.
						returnValue = table[nextList].get(nextIndex).getKey();
						iteratedItemNumber++;
						nextIndex++;
						
						if(nextIndex == table[nextList].size()) { 	// if the list's all nodes scanned.
							nextList--;								// Index must be size.
							if(nextList < 0) {
								nextList += table.length;
							}
							nextIndex = 0;
						}
						
						return returnValue;
					}
				}
			}
			return firstItem;
		}
		/**
		 * Moves the iterator onwards.
		 */
		@Override
		public K next() {
			
			if(hasNext()) {
				
				while(table[nextList] == null) {  // If the current list is null.
					nextList++;					 // Go for another list.
					if(nextList == holdList) {	// All elements iterated.
						return firstItem;
					}
					if(nextList > table.length - 1) { // Index returns to beginning if all items haven't been scanned yet.
						nextList = 0;
					}
					nextIndex = 0;
				}
				
				for(; nextIndex <table[nextList].size(); nextIndex++) { // Scanning current list's nodes.
									
					if(table[nextList].get(nextIndex) != null) { // If the node is not empty.
						
						K returnValue = table[nextList].get(nextIndex).getKey(); // Go for it.
						returnValue = table[nextList].get(nextIndex).getKey();
						iteratedItemNumber++;
						nextIndex++;
						
						if(nextIndex == table[nextList].size()) { // This list is complete, go to next list.
							holdList = nextList;
							holdIndex = nextIndex;
							nextList++;
							if(nextList > table.length - 1) {
								nextList = 0;
							}
							nextIndex = 0;
						}
						
						return returnValue;
					}
					
				}
			}
			return firstItem;
		}
	 }
	 /** Method get for class HashtableChain.
	 @param key The key being sought
	 @return The value associated with this key if found;
	 otherwise, null
	 */
	/**
	 * Returns the wanted key's value.If the key is not in the table , returns null.
	 */
	@Override
	public V get(Object key) {
		 int index = key.hashCode() % table.length;
		 
		 if (index < 0)
			 index += table.length;
		 
		 if (table[index] == null)
			 return null; // key is not in the table.
		 
		 // Search the list at table[index] to find the key.
		 for (Entry<K, V> nextItem : table[index]) {
			 if (nextItem.getKey().equals(key))
				 return nextItem.getValue();
		 }
		 // assert: key is not in the table.
		 return null;
	}
	/**
	 * returns true if the table is empty.
	 */
	@Override
	public boolean isEmpty() {		
		return numKeys == 0;		
	}
	/** Method put for class HashtableChain.
	 This key-value pair is inserted in the
	 table and numKeys is incremented. If the key is already
	 in the table, its value is changed to the argument
	 value and numKeys is not changed.
	 @param key The key of item being inserted
	 @param value The value for this key
	 @return The old value associated with this key if
	 found; otherwise, null
	*/
	@Override
	public V put(K key, V value) {
		 int index = key.hashCode() % table.length;
		 
		 if(numKeys == 0) {
			 firstItem = key;
		 }
		 
		 if (index < 0)
			 index += table.length;
		 
		 if (table[index] == null) {
			 // Create a new linked list at table[index].
			 table[index] = new LinkedList<>();
		 }
	
		 // Search the list at table[index] to find the key.
		 for (Entry<K, V> nextItem : table[index]) { // Iterate the linked list at the current position.
			 // If the search is successful, replace the old value.
			 if (nextItem.getKey().equals(key)) {
				 
				 // Replace value for this key.
				 V oldVal = nextItem.getValue();
				 nextItem.setValue(value);
				 return oldVal;
			 }
		 }
		 // assert: key is not in the table, add new item.
		 table[index].addFirst(new Entry<>(key, value));
		 numKeys++;
		 if (numKeys > (LOAD_THRESHOLD * table.length))
			 rehash();
		 
		 return null;
	}
	/**
	 * Removes the wanted key from the table.
	 */
	@Override
	public V remove(Object key) {
		int index = key.hashCode() % table.length;
		
		if(index < 0)
			index += table.length;
		
		if(table[index] == null)
			return null;
		
		for(Entry<K ,V> nextItem : table[index]) { // Scanning the current list.
			
			if(nextItem.getKey().equals(key)) {		// Key found.
				V returnValue = nextItem.getValue();
				table[index].remove(nextItem); // Remove the node.
				numKeys--;
				
				if(table[index].isEmpty()) { // If the list is empty.
					table[index] = null; // Remove the list.
				}
				return returnValue;
			}
		}
		return null; // Key is not in the table.
	}
	/**
	 * Returns size.
	 */
	@Override
	public int size() {
		return numKeys;
	}
	/** Expands table size when loadFactor exceeds LOAD_THRESHOLD
	 @post The size of the table is doubled and is an odd integer.
	 Each nondeleted entry from the original table is
	 reinserted into the expanded table.
	 The value of numKeys is reset to the number of items
	 actually inserted; numDeletes is reset to 0.
	*/
	private void rehash() {
	 // Save a reference to oldTable.
	 LinkedList<Entry<K, V>>[] oldTable = table;
	 // Double capacity of this table.
	 table = new LinkedList[2 * oldTable.length + 1];
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
	 * Returns an iterator from the beginning of the table.
	 */
	public MapIterator iter() {
		return new MapIterator();
	}
	/**
	 * Returns an iterator from the wanted key and traverse the table.
	 * @param key
	 * @return
	 */
	public MapIterator iter(K key) {
		return new MapIterator(key);
	}
	/**
	 * Converts the values and keys to String.
	 */
	public String toString() {
		StringBuilder sb = new StringBuilder();
		
		sb.append("Key\t\tValue\n\n");
		
		for (int i = 0; i < table.length; i++) {
			 
			if(table[i] != null) {
				 for(Entry <K , V> nextItem : table[i]) {
					 sb.append(nextItem.getKey()).append("\t/\t").append(nextItem.getValue()).append("\n");
				 }
			}
		}
		return sb.toString();
	}
}