package default_package;

/**
 * Objet that keeps the data and the occurrence of it.
 * @author Fatih
 *
 * @param <E> The type of the object must be comparable.
 */
public class ValueOccurance<E extends Comparable<E>> implements Comparable<ValueOccurance<E>> {
	
	private E data;
	private int occur;
	
	/**
	 * Initializes the object with data.
	 * @param data The wanted data.
	 */
	public ValueOccurance(E data) {
		this.data = data;
		occur = 1;
	}
	/**
	 * 
	 * @return the occurrence.
	 */
	public int getOccur() {
		return occur;
	}
	/**
	 * Sets the occurrence of the data.
	 * @param occur Number that wanted to set the occurrence of the data.
	 */
	public void setOccur(int occur) {
		this.occur = occur;
	}
	/**
	 * 
	 * @return the data.
	 */
	public E getData() {
		return data;
	}
	/**
	 * 
	 * @param data data to be set.
	 */
	public void setData(E data) {
		this.data = data;
	}
	/**
	 * Increases the occurrence of the by one
	 */
	public void increaseOccur() {
		occur++;
	}
	/**
	 * Decreases the occurrence of the by one
	 */
	public void decreaseOccur() {
		occur--;
	}
	@Override
	/**
	 * Compares the data with another ValueOccurance's data.
	 */
	public int compareTo(ValueOccurance<E> o) {
		// TODO Auto-generated method stub
		return data.compareTo(o.getData());
	}
	/**
	 * @return Returns a string which contains the data.
	 */
	public String toString() {
		StringBuilder sb = new StringBuilder();
		
		sb.append(data.toString());
		return sb.toString();
	}
	
}
