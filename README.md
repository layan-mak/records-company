# records-company
Data structure to manage data about records and customers using generic manually implemented hash tables, union-find, and rank trees.

Implementations of:
- Generic rank tree.
- Dynamic hashtable with pseudo chain hashing: using the rank tree implemented instead of a linked list - for better performance.
- Union find with union by size and path compression, using the dynamic hashtable implemented for storing the sets and the elements (instead of regular arrays).

Use of the data structures implemented to manage a records company: 
The company sells records to customers, which are stored in piles in the record store. 
- Customer data is stored in a hashtable. (key = ID)
- Members (customers with a membership) data is stored in a rank tree (ranked by their IDs).
- Record Piles are stored in Union Find. 

Try it: in mainWet2.cpp
