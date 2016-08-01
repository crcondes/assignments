//-----------------------------------------------------------------------------
// Name:        Cecilia Condes
// ID:          ccondes
// Class:       12M
// Date:        5.22.15
// Filename:    Dictionary.java
// Description: Dictionary ADT based on a BST 
//-----------------------------------------------------------------------------

import java.util.*;

class Dictionary implements DictionaryInterface{

	// Fields
	Node root;
	int num_nodes;
	Boolean debug;		// for turning debug print statements on and off

	// Constructor
	Dictionary(){
		root = null;
		num_nodes = 0;
		debug = false;
	}

	// the members of the BST are linked nodes
	private class Node{
		String key;
		String value;
		Node left;
		Node right;

		Node(String k, String v){
			key = k;
			value = v;
			left = null;
			right = null;
		}

	}

	// Methods

	// isEmpty()
	// returns true if this Dictionary is empty, false otherwise
	// pre: none
	public boolean isEmpty(){
		return (root == null);
	}

	// size()
	// returns the number of entries in this Dictionary
	// pre: none
	public int size(){
		if(debug) System.out.println("size()");
		return num_nodes;
	}

	// lookup()
	// returns value associated key, or null reference if no such key exists
	// pre: none
	public String lookup(String key){
		if(debug) System.out.println("lookup() "+key);

		Node n = findNode(key);
		if(n == null)  return null; 
		else return n.value;
	}

	// insert()
	// inserts new (key,value) pair into this Dictionary
	// pre: lookup(key)==null
	public void insert(String key, String value) throws KeyCollisionException {
		if(debug) System.out.println("insert ("+key+", "+value+")");

		Node n = new Node(key, value);
		Node p = null;	// parent starts out null
		Node c = root;	// child starts out as root of tree

		// traverse tree until c occupies null position where n should be
		while(c != null){ 	
			p = c;			

			if(n.key.compareTo(c.key) < 0){
				c = c.left;
			}
			else if(n.key.compareTo(c.key) > 0){
				c = c.right;
			}
			else throw new KeyCollisionException("KeyCollisionException: key "
				+key+" already exists"); 
		}

		// tree was empty, n = root
		if(p == null){
			root = n; 
			// if(debug) System.out.println("new node "+n.toString());
			num_nodes++;
		}

		// otherwise
		else{
			if(n.key.compareTo(p.key) < 0) p.left = n;
			else if(n.key.compareTo(p.key) > 0) p.right = n;
			else throw new KeyCollisionException("KeyCollisionException: key "
				+key+" already exists"); 
			
			if(debug) System.out.println("new node "+n.toString());
			num_nodes++;
		}
	}

	// delete()
	// deletes pair with the given key by splicing target out of tree
	// pre: lookup(key)!=null
	public void delete(String key) throws KeyNotFoundException {
		if(debug) System.out.println("delete() "+key);

		Node n = findNode(key);
		if(n==null) throw new KeyNotFoundException("KeyNotFoundException: key "
				+key+" not found");
		Node p = findParent(key);

		if(debug) System.out.println("deleting node "+n+" with parent "+p);

		//   p  = parent
		//   n  = target node
		Node c1 = n.left;
		Node c2 = n.right;
		// c2 is necessarily greater than c1
		if(p!=null){
			p.right = c2;
		}
		else if(p==null){
			root = c2;
		}
		if(c1!=null){
			merge(c1, c2); // if c1 == null, no merging necessary
		}
		num_nodes--;
	}

	// merge()
	// merges two subtrees
	// pre: c1 & c2 are siblings and neither are null
	// 		c1 < c2
	// post: c2 is new parent of merged subtree
	private void merge(Node c1, Node c2){
		// precondition checking
		if(c1.key.compareTo(c2.key) >= 0){
			System.out.println("Programmer error, don't call merge() like that");
			System.exit(1);
		}

		// recursion
		if( (c2!=null) && (c2.left!=null) ){
			merge(c1, c2.left);
		}
		else if( (c2!= null) && (c2.left==null)){
			c2.left = c1;
		}
	}

	// makeEmpty()
	// pre: none
	public void makeEmpty(){
		if(debug) System.out.println("makeEmpty()");
		root = null;
	}

	// deleteSubTree()
	// recursive delete method 
	// based on PostOrderTreeWalk
	private void deleteSubTree(Node n){
		deleteSubTree(n.left);
		deleteSubTree(n.right);
		delete(n.key);
	}

	// toString()
	// returns a String representation of this Dictionary
	// overrides Object's toString() method
	// pre: none
	public String toString(){
		if(debug) System.out.println("toString()");

		StringBuffer sB = new StringBuffer();
		sB = toStringBuffer(root);

		return new String(sB);
	}

	// toStringBuffer()
	// private recursive helper method for toString()
	// based on InOrderTreeWalk algorithm
	// pre: none
	private StringBuffer toStringBuffer(Node n){
		StringBuffer sb = new StringBuffer();
		if(n!=null){
			if(n.left!=null) sb.insert(0, toStringBuffer(n.left));
			
			sb.append(n.key+" "+n.value+"\n"); // multi-line, k+v

			if(n.right!=null) sb.append(toStringBuffer(n.right));
		}
		return sb;
	}

	// findNode()
	// helper function that returns node with specified key
	// pre: none
	private Node findNode(String key){
		Node n = root;
		// if(debug) System.out.println("n is "+n);


		while( (n!=null) && (n.key.compareTo(key) != 0) ){
			if(key.compareTo(n.key) < 0){
				if(n.left == null) break;

				// if(debug) System.out.println("n is "+n);

				n = n.left;
			}
			else if(key.compareTo(n.key) > 0){
				if(n.right == null) break;

				// if(debug) System.out.println("n is "+n);
				n = n.right;
			}
			// if compareTo() == 0
			//		do nothing (loop breaks)
		}

		if(n.key.compareTo(key) != 0) n = null; // in case n = root

		// it's okay to return null
		return n;
	}

	// findParent()
	// helper function that returns parent of node with specified key
	// pre: none
	private Node findParent(String key){
		Node c = root;
		Node p = null;
		// if(debug) System.out.println("c is "+c);


		while( (c!=null) && (c.key.compareTo(key) != 0) ){
			if(key.compareTo(c.key) < 0){
				if(c.left == null) break;

				// if(debug) System.out.println("c is "+c);
				p = c;
				c = c.left;
			}
			else if(key.compareTo(c.key) > 0){
				if(c.right == null) break;

				// if(debug) System.out.println("c is "+c);
				p = c;
				c = c.right;
			}
			// if compareTo() == 0
			//		do nothing (loop breaks)
		}

		if(c.key.compareTo(key) != 0) c = null; // in case c = root

		// it's okay to return null
		return p;
	}
	
}