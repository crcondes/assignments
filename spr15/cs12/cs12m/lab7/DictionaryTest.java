//-----------------------------------------------------------------------------
// Name:		Cecilia Condes
// ID:			ccondes
// Class:		12M
// Date:		5.22.15
// Filename:	DictionaryTest.java
// Description:	Tests the functionality of Dictionary.java
//-----------------------------------------------------------------------------

class DictionaryTest{

	public static void main(String[] args) {
		System.out.println("Everything compiled");
		// constructor
		// isEmpty()
		// size()
		// insert()
		// lookup()

		Dictionary d = new Dictionary();
		d.debug = true;
		System.out.println("there is a dictionary");

		System.out.println("Dictionary is empty: "+d.isEmpty()); // true - PASS
		System.out.println("size: "+d.size()); // 0 - PASS

		// d.insert("1", "a");
		// System.out.println("Dictionary is empty: "+d.isEmpty()); // false PASS
		// System.out.println("size: "+d.size()); // 1 PASS
		// System.out.println("root: "+d.root); // 1
		// d.insert("5", "e");
		// d.insert("2", "b");
		// d.insert("8", "h");
		// d.insert("6", "f");
		// d.insert("4", "d");
		// System.out.println("size: "+d.size()); // 4 PASS
		// System.out.println("d is "+d);

		// // System.out.println("3: "+d.lookup("3")); // exception PASS
		// System.out.println("1: "+d.lookup("1")); // a PASS
		// System.out.println("2: "+d.lookup("2")); // b PASS
		// System.out.println("4: "+d.lookup("4")); // d PASS

		String[] keys = {"8", "4", "2", "1", "3", "6", "5", "7", "12", "10", "9", "11", "14", "13", "15"};
		String[] vals = {"a", "b", "c", "d", "e", "f", "g", "h", "i",  "j",  "k", "l",  "m",  "n",  "o"};
		for(int i = 0; i < keys.length; i++){
			d.insert(keys[i], vals[i]);
		}

		System.out.println(d);
		d.delete("12");
		System.out.println(d);

		d.makeEmpty();
		System.out.println(d);

	}
}