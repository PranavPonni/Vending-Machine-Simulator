# Vending-Machine-Simulator
Make a vending machine simulator using data structures and dynamic memory allocation

Make a vending machine simulator with the functions below.
You should be noted that in the future, this system will be expanded to a larger scale vending system by increasing the number of supported bills, coins, and a variety of products. Therefore, static arrays should not be used to handle products, bills, and coins. However, static arrays may be used to handle strings.
Please search for "dynamic memory allocation" and "data structures" as a first step.

Create a simulator that can perform the following tasks.

[1] A menu list is displayed, and the user is asked to enter the item number to be purchased from the list. When the user selects a menu item, the system keeps asking the user to select it until an existing item number is entered. The number of items in stock is finite, and if the item is not in stock, the system displays the message "sold out" and stops selling it.

[2] The system will ask the user to repeatedly enter the amount of money to be paid until it exceeds the price of the product. Six types of money can be used for input:
10 yen, 50 yen, 100 yen, 500 yen, 1,000 yen, and 5,000 yen.
The number of bills and coins is finite. When the number of coins and bills remaining in the vending machine is below a certain number, the system displays the message "out of change" and stops vending.

[3] When the amount of money entered exceeds the price of the product, the purchase is completed, and the change is returned. The number of changes for each bill or coin is displayed; if the number is zero, it should not be displayed.

By entering the "admin password" in [1] above, an administrator can enter the "administrator menu" and perform the following tasks
• Check / add Inventory: Display the inventory of all products and add inventory.

• Add / reduce bills and coins: Select the type of bills and coins and enter the number to add or reduce

• Add / reduce products: Add a new product or delete a product.

• Exit and resume sales: Exit the administrator menu and resume sales.

If additional functions needed for an actual vending machine are added other than those listed above, additional points will be given.
8
