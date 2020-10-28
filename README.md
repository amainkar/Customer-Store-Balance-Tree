# Customer-Store-Balance-Tree
Make a BST and store customers in it

Write a program in C to implement a system that stores customer loyalty accounts at a grocery store, then processes basic orders for said customers.
Customers Loyalty accounts will have the following (ID-A unique 4 digit ID number (0-9999), Name-The customer’s name, Store Balance-Amount of store credit they have accrued.
The customers’ accounts should be stored in a BST, use the customer’s ID as the key to compare against when creating this tree.

The system should allow for 4 operations to happen:
 1. Add a customer to the system
      a. Complete with name, ID, and balance
 2. Remove a customer from the system
      a. An ID will be given to do this
 3. Process a list of orders for customers in our system
      a. A text file (to be given via the console) will contain a series of orders for
      customers consisting of IDs and cash totals for the order
      b. Go through the orders one by one, subtract the order total from the customer’s
      Store Balance first, then take payment for the remainder.
      c. After each order, print a message to the console detailing the order
 4. Close down the system
      a. Prompt the user to select, pre-order, in-order, or post-order.
      b. Write the current BST to a file “newcustomers.txt” in the order specified in
      the step above.
      c. Close the program
