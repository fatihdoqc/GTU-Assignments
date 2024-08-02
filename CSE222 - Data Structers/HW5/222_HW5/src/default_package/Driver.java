package default_package;

import java.util.Random;

import default_package.HashtableChain.MapIterator;

public class Driver {
	
	public static void main(String[] args) {
		
		
		HashtableChain<Integer, String> chain1 = new HashtableChain<>();
		HashTableTreeSet<Integer, String> chain2 = new HashTableTreeSet<>();
		HashTableCoalesced<Integer, String> chain3 = new HashTableCoalesced<>();
		Random rand = new Random();
		long start , end;
		
		chain1.put(1, "a");
		chain1.put(2, "b");
		chain1.put(3, "c");
		chain1.put(4, "d");
		System.out.println("Items in the HashMap: 1-a , 2-b , 3-c , 4-d ");
		System.out.println("Starting to iterate from 3");
		
		start = System.nanoTime();
		MapIterator iter = chain1.iter(3);
		
		while(iter.hasNext()) {
			System.out.println(iter.next());
		}
		end = System.nanoTime();
		System.out.println("Time pass for iterating all elements in the table: " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("\nStarting to iterate from 2");
		
		start = System.nanoTime();
		iter = chain1.iter(2);
		
		while(iter.hasNext()) {
			System.out.println(iter.next());
		}
		end = System.nanoTime();
		System.out.println("Time pass for iterating all elements in the table: " + (end - start) / Math.pow(10, 6) + " ms");
		
		start = System.nanoTime();
		System.out.println("Starting to iterate from 2 to the backwards.");
		iter = chain1.iter(2);
		
		while(iter.hasNext()) {
			System.out.println(iter.prev());
		}
		end = System.nanoTime();
		System.out.println("Time pass for iterating all elements in the table: " + (end - start) / Math.pow(10, 6) + " ms");
		
		start = System.nanoTime();
		iter = chain1.iter();
		System.out.println("\nPrinting the map to remember.");
		while(iter.hasNext()) {
			System.out.println(iter.next());
		}
		end = System.nanoTime();
		System.out.println("Time pass for iterating and printing all elements in the table: " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		iter = chain1.iter();
		iter.next();
		iter.next();
		
		System.out.println("When at the second index checking if the iterator has next.");
		
		start = System.nanoTime();
		System.out.println("Result of hasNext(): " + iter.hasNext() + " and Next item : " + iter.next());
		end = System.nanoTime();
		System.out.println("Time pass for iterating to next element in the table: " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println();
		System.out.println("When at the third index checking if the iterator has next.");
		
		start = System.nanoTime();
		System.out.println("Result of hasNext(): " + iter.hasNext() + " and Next item : " + iter.next());
		end = System.nanoTime();
		System.out.println("Time pass for iterating to next element in the table: " + (end - start) / Math.pow(10, 6) + " ms");

		System.out.println();
		System.out.println("When at the second index checking if the iterator has next.");
		
		start = System.nanoTime();
		System.out.println("Result of hasNext(): " + iter.hasNext() + " and there is no more item to iterate through.");
		end = System.nanoTime();
		System.out.println("Time pass for checking hasNext() and iterating to next element in the table: " 
		+ (end - start) / Math.pow(10, 6) + " ms");

		/* ---------- PART2 ---------- */
		System.out.println("---------- PART2 ----------\n");
		System.out.println("\n\n\nSmall Chain");
		chain1 = new HashtableChain<>();
		
		for(int i = 0; i<7; i++) {
			String temp = ("a" + i);
			int random = rand.nextInt(100) + 1;
			
			chain1.put( random , temp ) ;
		}
		System.out.println("Adding a key-value pair to the table");
		start = System.nanoTime();
		chain1.put(421, "q");
		end = System.nanoTime();
		System.out.println("Time pass for adding a key-value pair in the table: " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		chain1.put(411, "x");
		start = System.nanoTime();
		System.out.println("Size of the Small Chain Hash Map : " + chain1.size());
		end = System.nanoTime();
		System.out.println("Time pass for printing the size of the table: " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Removing an existing item from the Small Chain Hash Map : Removed key's value:" + chain1.remove(421) );
		end = System.nanoTime();
		System.out.println("Time pass for removing an existing item from the table: " + (end - start) / Math.pow(10, 6) + " ms");	
		System.out.println(" Size after removal: " + chain1.size() );
		System.out.println();
		
		start = System.nanoTime();
		System.out.println("Removing a non-existing item from the Small Chain Hash Map : Removed key's value:" + chain1.remove(1231231) );
		end = System.nanoTime();
		System.out.println("Time pass for removing a non-existing item from the table: " + (end - start) / Math.pow(10, 6) + " ms");
		System.out.println(" Size after removal: " + chain1.size());
		System.out.println();
		
		start = System.nanoTime();
		System.out.println("Reaching an existing key's value: " + chain1.get(411));
		end = System.nanoTime();
		System.out.println("Time pass for getting an existing key's value from the table: " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Reaching a non-existing key's value: " + chain1.get(99999));
		end = System.nanoTime();
		System.out.println("Time pass for getting a non-existing key's value from the table: " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		System.out.println("Adding a key that won't collide: Size before adding : " + chain1.size());
		
		start = System.nanoTime();
		chain1.put(0, "z");
		end = System.nanoTime();	
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain1.size());
		System.out.println();

		System.out.println("Adding a key that will collide: Size before adding : " + chain1.size());
		
		start = System.nanoTime();
		chain1.put(521, "b");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain1.size());
		System.out.println();

		System.out.println("Adding an existing key: Size before adding : " + chain1.size() + " Value of the key: " + chain1.get(411));
		
		start = System.nanoTime();
		chain1.put(411, "t");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding: " + chain1.size() + " Value of the key: " + chain1.get(411));
		
		/* chain medium */
		System.out.println("\n\n\nMedium Chain");
		chain1 = new HashtableChain<>();
		for(int i = 0; i<97; i++) {
			String temp = ("a" + i);
			int random = rand.nextInt(1000) + 1;
			
			chain1.put( random , temp ) ;
		}
		System.out.println("Adding a key-value pair to the table");
		start = System.nanoTime();
		chain1.put(1010, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		chain1.put(1011, "x");
		start = System.nanoTime();
		System.out.println("Size of the Medium Chain Hash Map : " + chain1.size());
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Removing an existing item from the Medium Chain Hash Map : Removed key's value:" + chain1.remove(1010) );
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println(" Size after removal: " + chain1.size());
		System.out.println();

		start = System.nanoTime();
		System.out.println("Removing a non-existing item from the Medium Chain Hash Map : Removed key's value:" + chain1.remove(1231231));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println(" Size after removal: " + chain1.size());
		System.out.println();

		start = System.nanoTime();
		System.out.println("Reaching an existing key's value: " + chain1.get(1011));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Reaching a non-existing key's value: " + chain1.get(99999));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		System.out.println("Adding a key that won't collide: Size before adding : " + chain1.size());
		start = System.nanoTime();
		chain1.put(0, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain1.size());
		System.out.println();

		System.out.println("Adding a key that will collide: Size before adding : " + chain1.size());
		start = System.nanoTime();
		chain1.put(1020, "b");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain1.size());
		System.out.println();

		System.out.println("Adding an existing key: Size before adding : " + chain1.size() + " Value of the key: " + chain1.get(1011));
		start = System.nanoTime();
		chain1.put(1011, "t");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding: " + chain1.size() + " Value of the key: " + chain1.get(1011));
		
		/* large chain */ 
		System.out.println("\n\n\nLarge Chain");
		chain1 = new HashtableChain<>();
		for(int i = 0; i<99997; i++) {
			String temp = ("a" + i);
			int random = rand.nextInt(1000000) + 4;
			
			chain1.put( random , temp ) ;
		}
		System.out.println("Adding a key-value pair to the table");
		start = System.nanoTime();
		chain1.put(1, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		chain1.put(2, "x");
		
		start = System.nanoTime();
		System.out.println("Size of the Large Chain Hash Map : " + chain1.size());
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Removing an existing item from the Large Chain Hash Map : Removed key's value:" + chain1.remove(1) );
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println(" Size after removal: " + chain1.size());
		System.out.println();

		start = System.nanoTime();
		System.out.println("Removing a non-existing item from the Large Chain Hash Map : Removed key's value:" + chain1.remove(1231231));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println(" Size after removal: " + chain1.size());
		System.out.println();

		start = System.nanoTime();
		System.out.println("Reaching an existing key's value: " + chain1.get(2));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Reaching a non-existing key's value: " + chain1.get(99999));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		System.out.println("Adding a key that won't collide: Size before adding : " + chain1.size());
		
		start = System.nanoTime();
		chain1.put(0, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain1.size());
		System.out.println();

		System.out.println("Adding a key that will collide: Size before adding : " + chain1.size());
		start = System.nanoTime();
		chain1.put(11, "b");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain1.size());
		System.out.println();

		System.out.println("Adding an existing key: Size before adding : " + chain1.size() + " Value of the key: " + chain1.get(2));
		start = System.nanoTime();
		chain1.put(2, "t");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding: " + chain1.size() + " Value of the key: " + chain1.get(2));
		
		
		/* small treeset */ 
		System.out.println("\n\n\nSmall TreeSet Hash");
		chain2 = new HashTableTreeSet<>();
		for(int i = 0; i<7; i++) {
			String temp = ("a" + i);
			int random = rand.nextInt(100) + 4;
			
			chain2.put( random , temp ) ;
		}
		System.out.println("Adding a key-value pair to the table");
		start = System.nanoTime();
		chain2.put(1, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		chain2.put(2, "x");
		
		start = System.nanoTime();
		System.out.println("Size of the Small TreeSet Hash Map : " + chain2.size());
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Removing an existing item from the Small TreeSet Hash Map : Removed key's value:" + chain2.remove(1));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println(" Size after removal: " + chain2.size());
		System.out.println();
		
		start = System.nanoTime();
		System.out.println("Removing a non-existing item from the Small TreeSet Hash Map : Removed key's value:" + chain2.remove(1231231));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println(" Size after removal: " + chain2.size());
		System.out.println();

		start = System.nanoTime();
		System.out.println("Reaching an existing key's value: " + chain2.get(2));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Reaching a non-existing key's value: " + chain2.get(99999));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		System.out.println("Adding a key that won't collide: Size before adding : " + chain2.size());
		
		start = System.nanoTime();
		chain2.put(0, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain2.size());
		System.out.println();

		System.out.println("Adding a key that will collide: Size before adding : " + chain2.size());
		start = System.nanoTime();
		chain2.put(11, "b");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain2.size());
		System.out.println();

		System.out.println("Adding an existing key: Size before adding : " + chain2.size() + " Value of the key: " + chain2.get(2));
		start = System.nanoTime();
		chain2.put(2, "t");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding: " + chain2.size() + " Value of the key: " + chain2.get(2));
		
		/* medium treeset */ 
		System.out.println("\n\n\nMedium TreeSet Hash");
		chain2 = new HashTableTreeSet<>();
		for(int i = 0; i<97; i++) {
			String temp = ("a" + i);
			int random = rand.nextInt(1000) + 4;
			
			chain2.put( random , temp ) ;
		}
		System.out.println("Adding a key-value pair to the table");
		start = System.nanoTime();
		chain2.put(1, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		chain2.put(2, "x");
		
		start = System.nanoTime();
		System.out.println("Size of the Medium TreeSet Hash Map : " + chain2.size());
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		start = System.nanoTime();
		System.out.println("Removing an existing item from the Medium TreeSet Hash Map : Removed key's value:" + chain2.remove(1));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		System.out.println(" Size after removal: " + chain2.size());
		System.out.println();

		start = System.nanoTime();
		System.out.println("Removing a non-existing item from the Medium TreeSet Hash Map : Removed key's value:" + chain2.remove(1231231));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println(" Size after removal: " + chain2.size());
		System.out.println();

		start = System.nanoTime();
		System.out.println("Reaching an existing key's value: " + chain2.get(2));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Reaching a non-existing key's value: " + chain2.get(99999));
		end = System.nanoTime();
		System.out.println("Adding a key that won't collide: Size before adding : " + chain2.size());
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		chain2.put(0, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain2.size());
		System.out.println();

		System.out.println("Adding a key that will collide: Size before adding : " + chain2.size());
		start = System.nanoTime();
		chain2.put(11, "b");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain2.size());
		System.out.println();

		System.out.println("Adding an existing key: Size before adding : " + chain2.size() + " Value of the key: " + chain2.get(2));
		start = System.nanoTime();
		chain2.put(2, "t");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding: " + chain2.size() + " Value of the key: " + chain2.get(2));
		
		/* large treeset */ 
		System.out.println("\n\n\nLarge TreeSet Hash");
		chain2 = new HashTableTreeSet<>();
		for(int i = 0; i<9997; i++) {
			String temp = ("a" + i);
			int random = rand.nextInt(100000) + 4;
			
			chain2.put( random , temp ) ;
		}
		System.out.println("Adding a key-value pair to the table");
		start = System.nanoTime();
		chain2.put(1, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		chain2.put(2, "x");
		
		start = System.nanoTime();
		System.out.println("Size of the Large TreeSet Hash Map : " + chain2.size());
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Removing an existing item from the Large TreeSet Hash Map : Removed key's value:" + chain2.remove(1));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println(	" Size after removal: " + chain2.size());
		System.out.println();

		start = System.nanoTime();
		System.out.println("Removing a non-existing item from the Large TreeSet Hash Map : Removed key's value:" + chain2.remove(1231231));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println(	" Size after removal: " + chain2.size());
		System.out.println();

		start = System.nanoTime();
		System.out.println("Reaching an existing key's value: " + chain2.get(2));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Reaching a non-existing key's value: " + chain2.get(99999));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		System.out.println("Adding a key that won't collide: Size before adding : " + chain2.size());
		
		start = System.nanoTime();
		chain2.put(0, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain2.size());
		System.out.println();

		System.out.println("Adding a key that will collide: Size before adding : " + chain2.size());
		
		start = System.nanoTime();
		chain2.put(11, "b");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding : " + chain2.size());
		System.out.println();

		System.out.println("Adding an existing key: Size before adding : " + chain2.size() + " Value of the key: " + chain2.get(2));
		start = System.nanoTime();
		chain2.put(2, "t");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding: " + chain2.size() + " Value of the key: " + chain2.get(2));
		
		/* Small Coalesced Hash */
		System.out.println("\n\n\nSmall Coalesced Hash");
		chain3 = new HashTableCoalesced<>();
		for(int i = 0; i<7; i++) {
			String temp = ("a" + i);
			int random = rand.nextInt(100) + 4;
			
			chain3.put( random , temp ) ;
		}
		System.out.println("Adding a key-value pair to the table");
		start = System.nanoTime();
		chain3.put(1, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		chain3.put(2, "x");
		
		start = System.nanoTime();
		System.out.println("Size of the Small Coalesced Hash Map : " + chain3.size());
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Removing an existing item from the Small Coalesced Hash Map : Removed key's value:" + chain3.remove(1));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");	
		System.out.println(" Size after removal: " + chain3.size());
		System.out.println();
		
		start = System.nanoTime();
		System.out.println("Removing a non-existing item from the Small Coalesced Hash Map : Removed key's value:" + chain3.remove(1231231));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		System.out.println(" Size after removal: " + chain3.size());
		System.out.println();

		start = System.nanoTime();
		System.out.println("Reaching an existing key's value: " + chain3.get(2));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Reaching a non-existing key's value: " + chain3.get(99999));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		System.out.println("Adding a key that won't collide: Size before adding : " + chain3.size());
		
		start = System.nanoTime();
		chain3.put(0, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		System.out.println("Size after adding : " + chain3.size());
		System.out.println();

		System.out.println("Adding a key that will collide: Size before adding : " + chain3.size());
		
		start = System.nanoTime();
		chain3.put(11, "b");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		System.out.println("Size after adding : " + chain3.size());
		System.out.println();

		System.out.println("Adding an existing key: Size before adding : " + chain3.size() + " Value of the key: " + chain3.get(2));
		
		start = System.nanoTime();
		chain3.put(2, "t");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		
		System.out.println("Size after adding: " + chain3.size() + " Value of the key: " + chain3.get(2));
		
		/* Medium Coalesced Hash */
		System.out.println("\n\n\nMedium Coalesced Hash");
		chain3 = new HashTableCoalesced<>();
		for(int i = 0; i<97; i++) {
			String temp = ("a" + i);
			int random = rand.nextInt(1000) + 4;
			chain3.put( random , temp ) ;
		}
		System.out.println("Adding a key-value pair to the table");
		start = System.nanoTime();
		chain3.put(1, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		chain3.put(2, "x");
		
		start = System.nanoTime();
		System.out.println("Size of the Medium Coalesced Hash Map : " + chain3.size());
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Removing an existing item from the Medium Coalesced Hash Map : Removed key's value:" + chain3.remove(1));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");	
		System.out.println(" Size after removal: " + chain3.size());
		System.out.println();
		
		start = System.nanoTime();
		System.out.println("Removing a non-existing item from the Medium Coalesced Hash Map : Removed key's value:" + chain3.remove(1231231));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		System.out.println(" Size after removal: " + chain3.size());
		System.out.println();

		start = System.nanoTime();
		System.out.println("Reaching an existing key's value: " + chain3.get(2));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Reaching a non-existing key's value: " + chain3.get(99999));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");	
		System.out.println("Adding a key that won't collide: Size before adding : " + chain3.size());
		System.out.println();
		
		start = System.nanoTime();
		chain3.put(0, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		System.out.println("Size after adding : " + chain3.size());
		System.out.println();
		
		System.out.println("Adding a key that will collide: Size before adding : " + chain3.size());
		
		start = System.nanoTime();
		chain3.put(11, "b");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");	
		System.out.println("Size after adding : " + chain3.size());
		System.out.println();
		
		System.out.println("Adding an existing key: Size before adding : " + chain3.size() + " Value of the key: " + chain3.get(2));
		
		start = System.nanoTime();
		chain3.put(2, "t");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");	
		System.out.println("Size after adding: " + chain3.size() + " Value of the key: " + chain3.get(2));
		
		/* Large Coalesced Hash */
		System.out.println("\n\n\nLarge Coalesced Hash");
		chain3 = new HashTableCoalesced<>();
		for(int i = 0; i<99997; i++) {
			String temp = ("a" + i);
			int random = rand.nextInt(1000000) + 4;
			chain3.put( random , temp ) ;
		}
		System.out.println("Adding a key-value pair to the table");
		start = System.nanoTime();
		chain3.put(1, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		chain3.put(2, "x");
		
		start = System.nanoTime();
		System.out.println("Size of the Large Coalesced Hash Map : " + chain3.size());
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Removing an existing item from the Large Coalesced Hash Map : Removed key's value:" + chain3.remove(1));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");		
		System.out.println(" Size after removal: " + chain3.size());
		System.out.println();
		
		start = System.nanoTime();
		System.out.println("Removing a non-existing item from the Large Coalesced Hash Map : Removed key's value:" + chain3.remove(1231231));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");	
		System.out.println(" Size after removal: " + chain3.size());
		System.out.println();
		
		start = System.nanoTime();
		System.out.println("Reaching an existing key's value: " + chain3.get(2));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		start = System.nanoTime();
		System.out.println("Reaching a non-existing key's value: " + chain3.get(99999));
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms\n");
		
		System.out.println("Adding a key that won't collide: Size before adding : " + chain3.size());
		
		start = System.nanoTime();
		chain3.put(0, "z");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");	
		System.out.println("Size after adding : " + chain3.size());
		System.out.println();
		
		System.out.println("Adding a key that will collide: Size before adding : " + chain3.size());
		
		start = System.nanoTime();
		chain3.put(11, "b");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");
		System.out.println("Size after adding : " + chain3.size());
		System.out.println();
		
		System.out.println("Adding an existing key: Size before adding : " + chain3.size() + " Value of the key: " + chain3.get(2));
		start = System.nanoTime();
		chain3.put(2, "t");
		end = System.nanoTime();
		System.out.println("Time pass : " + (end - start) / Math.pow(10, 6) + " ms");		
		System.out.println("Size after adding: " + chain3.size() + " Value of the key: " + chain3.get(2));
		
	}

}
