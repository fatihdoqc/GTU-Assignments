package default_package;

import java.util.LinkedList;
/** Hash table implementation using Coalescing */
public class HashTableCoalesced<K , V> implements KWHashMap<K, V> {
	
	/** The table */
	private Entry<K,V>[] table;
	/** The number of keys */
	private int numKeys;
	/** The capacity */
	private static final int CAPACITY = 10;
	/** The maximum load factor */
	private static final double LOAD_THRESHOLD = 0.8;
	
	public HashTableCoalesced() {
		table = new Entry[CAPACITY];
	}
	
	private static class Entry<K, V> {
		  /** The key */
		  private final K key;
		  /** The value */
		  private V value;
		  private int next;
		  /** Creates a new key-value pair.
		  @param key The key
		  @param value The value
		  */
		  public Entry(K key, V value) {
			  this.key = key;
			  this.value = value;
			  next = -1;
		  }
		  public Entry(K key, V value , int next) {
			  this.key = key;
			  this.value = value;
			  this.next = next;
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
		public int getNext() {
			return next;
		}
		public void setNext(int next) {
			this.next = next;
		}
		/*public String toString() {
			StringBuilder sb = new StringBuilder();
			sb.append(key);
			return sb.toString();
		}*/
	 }	
	/**
	 * Returns the wanted key's corresponding value.
	 */
	@Override
	public V get(Object key) {
		int index = key.hashCode() % table.length,
			startIndex = index,
			probe = 0;
		
		if(index < 0)
			index += table.length;
		
		if(table[index] == null) { // Key doesn't exist.
			return null;
		}
		
		while( !table[index].getKey().equals(key)) { // Searching key.
			probe++;
			index = ( startIndex + (probe * probe) ) % table.length;
			
			if(index < 0)
				index += table.length;
			
			if(table[index] == null) { // Key doesn't exist , because there is nothing left to scan.
				return null;
			}
		}
		return table[index].getValue();
	}
	/**
	 * Returns true if the table is empty, false if not.
	 */
	@Override
	public boolean isEmpty() {
		return numKeys == 0;
	}
	/**
	 * Inserts the wanted key-value pair to the table.
	 */
	@Override
	public V put(K key, V value) {
		int index = key.hashCode() % table.length,
			startIndex = index,
			probe = 0;
		
		if (index < 0)
			 index += table.length;
		
		while(table[index] != null) {	// If the key's index is occupied. Find another place with quadratic probing.
			probe++;
			if(table[index].getKey().equals(key)) { // If the key exist , replacing the value.
				table[index].setValue(value);
				return value;
			}
			
			index = ( startIndex + (probe * probe) ) % table.length;
			
			if(index < 0) {
				index += table.length;
			}
		}
		int hold = startIndex; // Memorizing the previous pointers.
		
		while(table[hold] != null) {
			
			if(table[hold].getNext() == -1) {
				table[hold].setNext(index); // Setting the index to the previous's next.
				break;
			}
			hold = table[hold].getNext();
		}

		numKeys++;
		table[index] = new Entry(key , value);
		
		if(numKeys > table.length * LOAD_THRESHOLD) { // Table is full.
			rehash();
		}
		
		return null;
		
	}
	private void rehash() {
		 // Save a reference to oldTable.
		 Entry<K, V>[] oldTable = table;
		 // Double capacity of this table.
		 table = new Entry[2 * oldTable.length + 1];
		 // Reinsert all items in oldTable into expanded table.
		 numKeys = 0;
		 for (int i = 0; i < oldTable.length; i++) {
			
			 if(oldTable[i] != null) {
			 	put(oldTable[i].getKey() , oldTable[i].getValue());
			 }
		 }
		}
	/**
	 * Deletes the wanted key.
	 */
	@Override
	public V remove(Object key) {
		
		int index = key.hashCode() % table.length,
			startIndex = index,
			probe = 0;
		
		if(index < 0) {
			index += table.length;
		}
		
		if(table[index] == null) // Key is not in the table.
			return null;
		
		while( !table[index].getKey().equals(key)) {
			probe++;
			index = ( startIndex + (probe * probe) ) % table.length;
			
			if(index < 0) {
				index += table.length;
			}
			
			if(table[index] == null) { // Key is not in the table. There is nothing more to scan.
				return null;
			}
		}
		
		if(table[index].getNext() != -1) { // Key is in the table and its next exists.
			V returnValue = table[index].getValue();
			
			int temp = table[index].getNext(); // Memorizing the next of the index to be deleted.
			table[index] = table[ table[index].getNext() ]; // Removing operation.
			table[temp] = null;
			numKeys--;
			return returnValue;
		}
		
		V returnValue = table[index].getValue();
		numKeys--;
		table[index] = null;
		
		return returnValue;
	}
	/**
	 * Returns the number of the keys in the table.
	 */
	@Override
	public int size() {
		return numKeys;
	}
	/**
	 * Converts datas to String.
	 */
	public String toString() {
		StringBuilder sb = new StringBuilder();
		
		for(int i = 0; i<table.length; i++) {
			if(table[i] != null) {
				if(table[i].getNext() != -1) {
					sb.append(i).append("\t ").append(table[i].getKey()).append("\t ").append(table[i].getNext()).append("\n");
				}
				else {
					sb.append(i).append("\t ").append(table[i].getKey()).append("\t ").append("null").append("\n");
				}
			}
			else {
				sb.append(i).append("\t ").append("null").append("\t ").append("null").append("\n");
			}
		}
		return sb.toString();
	}
}
