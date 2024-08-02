
import java.util.*;

public class Fatih {
	
	public static void main(String[] args) {
		
		/* PART1 */
		
		NavigableSL<Integer> nav1 = new NavigableSL<Integer>();
		System.out.println("Adding elements to the Navigable Skip List Set: ");
		
		nav1.add(5);
		nav1.add(10);
		nav1.add(4);
		nav1.add(3);
		
		System.out.println(nav1);
		
		System.out.println("Adding a non-existing element: (109) ");
		nav1.add(109);
		
		System.out.println(nav1);
		
		System.out.println("Adding an existing element: (5) ");
		nav1.add(5);
		
		System.out.println(nav1);
		
		System.out.println("Deleting an existing element: (3)");
		nav1.remove(3);
		
		System.out.println(nav1);
		
		System.out.println("Deleting a non-existing element: (111111)");
		nav1.remove(111111);
		
		System.out.println(nav1);
		
		Iterator<Integer> descIter = nav1.descendingIterator();
		
		System.out.println("Traversing the set with a descending iterator: ");
		
		while(descIter.hasNext()) {
			System.out.print(descIter.next() + " ");
		}
		System.out.println();
		
		/* *******************************************************/
		System.out.println("/********************************************************/");
		NavigableAVL<Integer> nav2 = new NavigableAVL<Integer>();
		
		System.out.println("\nAdding elements to the Navigable AVL Set: ");
		
		nav2.add(5);
		nav2.add(10);
		nav2.add(4);
		nav2.add(3);
		
		System.out.println(nav2);
		
		System.out.println("Adding a non-existing element: (109) ");
		nav2.add(109);
		
		System.out.println(nav2);
		
		System.out.println("Adding an existing element: (5) ");
		nav2.add(5);
		
		System.out.println(nav2);
		
		System.out.println("Traversing the set with an iterator: ");
		
		Iterator<Integer> iter = nav2.iterator();
		
		while(iter.hasNext()) {
			System.out.print(iter.next() + " ");
		}
		System.out.println();
		
		System.out.println("Usage of headSet method with true inclusive: ");
		NavigableAVL<Integer> head = (NavigableAVL<Integer>) nav2.headSet(10, true);
		
		System.out.println(head);
		
		System.out.println("Usage of headSet method with false inclusive: ");
		NavigableAVL<Integer> head2 = (NavigableAVL<Integer>) nav2.headSet(10, false);
		
		System.out.println(head2);
		
		System.out.println("Usage of tailSet method with true inclusive: ");
		NavigableAVL<Integer> tail = (NavigableAVL<Integer>) nav2.tailSet(10, true);
		
		System.out.println(tail);
		
		System.out.println("Usage of tailSet method with false inclusive: ");
		NavigableAVL<Integer> tail2 = (NavigableAVL<Integer>) nav2.tailSet(10, false);
		
		System.out.println(tail2);
		
		/* PART2 */
		System.out.println("\n PART2 *********");
		BSearchTree<Integer> tree1 = new BSearchTree<>(); // Both
		
		tree1.add(9);
		tree1.add(10);
		tree1.add(3);
		tree1.add(1);
		tree1.add(5);
		//q.add(4);
		
		BSearchTree<Integer> tree2 = new BSearchTree<>(); // Only Red-Black
		
		tree2.add(10);
		tree2.add(5);
		tree2.add(100);
		tree2.add(50);
		tree2.add(150);
		tree2.add(40);
		
		BSearchTree<Integer> tree3 = new BSearchTree<>(); // Neither
		
		tree3.add(3);
		tree3.add(2);
		tree3.add(1);
		
		Is_AVL_RB<Integer> compare = new Is_AVL_RB<>();
		
		System.out.println("\nProperties of tree1: (Which is red-black and AVL) ");
		compare.determine(tree1);
		System.out.println("\nProperties of tree2: (Which is only Red-Black)");
		compare.determine(tree2);
		System.out.println("\nProperties of tree3: (Which is neither of them.)");
		compare.determine(tree3);
		
		/* PART3 */
		System.out.println("PART3 ***********");
		
		Random rand = new Random();
		
		BSearchTree<Integer> search1 = new BSearchTree<Integer>();
		RedBlackTree<Integer> rb = new RedBlackTree<>();
		TwoThreeTree<Integer> tt = new TwoThreeTree<Integer>();
		BTree<Integer> bt = new BTree<>(8);
		SkipList<Integer> sl = new SkipList<Integer>();
		
		Integer arr[] = new Integer[10000];
		long start , end;
		
		int sum_search = 0 , sum_rb = 0 , sum_tt = 0 , sum_bt = 0 , sum_sl = 0;
		
		/* 10k */
		for(int k = 0; k< 10; k++) {
			search1 = new BSearchTree<>();
			rb = new RedBlackTree<Integer>();
			tt = new TwoThreeTree<Integer>();
			bt = new BTree<Integer>(8);
			sl = new SkipList<Integer>();
			
			for(int i = 0; i< 10000; i++) {
				arr[i] = i;
			}		
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 10000; i++) {
				search1.add(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 10000; i++) {
				rb.add(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 10000; i++) {
				tt.insert(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 10000; i++) {
				bt.insert(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 10000; i++) {
				sl.add(arr[i]);
			}
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				search1.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_search += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				rb.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_rb += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				tt.insert((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_tt += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				bt.insert((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_bt += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				sl.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_sl += end - start;
		}
		
		System.out.println("\nAvarage time of insertion of the 100 elements to the structures over 10K elements");
		System.out.println("Binary Search Tree: " + (sum_search / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Red Black Tree: " + (sum_rb / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Two Three Tree: " + (sum_tt / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("B-Tree: " + (sum_bt / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Skip List: " + (sum_sl / 10 ) / Math.pow(10, 6) + " ms");
		
		sum_bt = sum_tt = sum_search = sum_rb = sum_sl = 0 ;
		arr = new Integer[20000];
		/* 20k */
		for(int k = 0; k< 10; k++) {
			
			search1 = new BSearchTree<>();
			rb = new RedBlackTree<Integer>();
			tt = new TwoThreeTree<Integer>();
			bt = new BTree<Integer>(8);
			sl = new SkipList<Integer>();
			
			for(int i = 0; i< 20000; i++) {
				arr[i] = i;
			}		
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 20000; i++) {
				search1.add(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 20000; i++) {
				rb.add(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 20000; i++) {
				tt.insert(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 20000; i++) {
				bt.insert(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 20000; i++) {
				sl.add(arr[i]);
			}
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				search1.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_search += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				rb.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_rb += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				tt.insert((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_tt += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				bt.insert((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_bt += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				sl.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_sl += end - start;
		}
		
		System.out.println("\nAvarage time of insertion of the 100 elements to the structures over 20K elements");
		System.out.println("Binary Search Tree: " + (sum_search / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Red Black Tree: " + (sum_rb / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Two Three Tree: " + (sum_tt / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("B-Tree: " + (sum_bt / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Skip List: " + (sum_sl / 10 ) / Math.pow(10, 6) + " ms");
		
		sum_bt = sum_tt = sum_search = sum_rb = sum_sl = 0 ;
		arr = new Integer[40000];
		/* 40k */
		for(int k = 0; k< 10; k++) {
			
			search1 = new BSearchTree<>();
			rb = new RedBlackTree<Integer>();
			tt = new TwoThreeTree<Integer>();
			bt = new BTree<Integer>(8);
			sl = new SkipList<Integer>();
			
			for(int i = 0; i< 40000; i++) {
				arr[i] = i;
			}		
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 40000; i++) {
				search1.add(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 40000; i++) {
				rb.add(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 40000; i++) {
				tt.insert(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 40000; i++) {
				bt.insert(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 40000; i++) {
				sl.add(arr[i]);
			}
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				search1.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_search += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				rb.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_rb += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				tt.insert((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_tt += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				bt.insert((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_bt += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				sl.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_sl += end - start;
		}
		
		System.out.println("\nAvarage time of insertion of the 100 elements to the structures over 40K elements");
		System.out.println("Binary Search Tree: " + (sum_search / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Red Black Tree: " + (sum_rb / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Two Three Tree: " + (sum_tt / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("B-Tree: " + (sum_bt / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Skip List: " + (sum_sl / 10 ) / Math.pow(10, 6) + " ms");
		
		sum_bt = sum_tt = sum_search = sum_rb = sum_sl = 0 ;
		arr = new Integer[80000];
		/* 80k */
		for(int k = 0; k< 10; k++) {
			
			search1 = new BSearchTree<>();
			rb = new RedBlackTree<Integer>();
			tt = new TwoThreeTree<Integer>();
			bt = new BTree<Integer>(8);
			sl = new SkipList<Integer>();
			
			for(int i = 0; i< 80000; i++) {
				arr[i] = i;
			}		
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 80000; i++) {
				search1.add(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 80000; i++) {
				rb.add(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 80000; i++) {
				tt.insert(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 80000; i++) {
				bt.insert(arr[i]);
			}
			Collections.shuffle(Arrays.asList(arr));	
			for(int i = 0; i< 80000; i++) {
				sl.add(arr[i]);
			}
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				search1.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_search += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				rb.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_rb += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				tt.insert((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_tt += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				bt.insert((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_bt += end - start;
			
			start = System.nanoTime();  
			for(int i = 0; i< 100; i++) {
				sl.add((int) Math.abs(rand.nextInt() + 100000));
			}
			end = System.nanoTime();		
			sum_sl += end - start;
		}
		
		System.out.println("\nAvarage time of insertion of the 100 elements to the structures over 80K elements");
		System.out.println("Binary Search Tree: " + (sum_search / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Red Black Tree: " + (sum_rb / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Two Three Tree: " + (sum_tt / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("B-Tree: " + (sum_bt / 10 ) / Math.pow(10, 6) + " ms");
		System.out.println("Skip List: " + (sum_sl / 10 ) / Math.pow(10, 6) + " ms");
	}
}
