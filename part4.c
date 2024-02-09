#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id, price, stock;
    char name[50];
} Product;

typedef struct {
    int value, count;
} CoinBill;

typedef struct {
    Product *products; 
    CoinBill *coins_bills; 
    char admin_password[20];
    int is_admin_mode;
} VendingMachine;

void display_products(VendingMachine *vm) {
    printf("Available Products:\n");
    for (int i = 0; i < 3; ++i)
        printf("%d: %s - %d yen (%d in stock)\n", vm->products[i].id, vm->products[i].name, vm->products[i].price, vm->products[i].stock);
}

Product *select_product(VendingMachine *vm) {
    int id;
    printf("Enter the product number you want to purchase: ");
    scanf("%d", &id);
    for (int i = 0; i < 3; ++i)
        if (vm->products[i].id == id && vm->products[i].stock > 0)
            return &vm->products[i];
    printf("Invalid product selection or product is sold out.\n");
    return NULL;
}

int insert_money(VendingMachine *vm, Product *p) {
    int total = 0;
    for (int i = 0; i < 6; ++i) {
        int count;
        printf("Enter the number of %d yen: ", vm->coins_bills[i].value);
        scanf("%d", &count);
        total += vm->coins_bills[i].value * count;
        vm->coins_bills[i].count += count;
    }
    return total;
}

void give_change(VendingMachine *vm, int change) {
    printf("Change:\n");
    for (int i = 0; i < 6; ++i) {
        if (change >= vm->coins_bills[i].value && vm->coins_bills[i].count > 0) {
            int count = change / vm->coins_bills[i].value;
            count = (count < vm->coins_bills[i].count) ? count : vm->coins_bills[i].count;
            if (count > 0) {
                printf("%d x %d yen\n", count, vm->coins_bills[i].value);
                change -= count * vm->coins_bills[i].value;
                vm->coins_bills[i].count -= count;
            }
        }
    }
}

void add_inventory(VendingMachine *vm, int id, int quantity) {
    for (int i = 0; i < 3; ++i)
        if (vm->products[i].id == id) {
            vm->products[i].stock += quantity;
            printf("Added %d units of %s to inventory.\n", quantity, vm->products[i].name);
            return;
        }
    printf("Invalid product ID.\n");
}

void manage_coins_bills(VendingMachine *vm) {
    printf("Current Coins/Bills:\n");
    for (int i = 0; i < 6; ++i)
        printf("%d yen: %d\n", vm->coins_bills[i].value, vm->coins_bills[i].count);
    int choice, value, count;
    printf("Enter 1 to add or 2 to reduce coins/bills: ");
    scanf("%d", &choice);
    printf("Enter the value of coin/bill: ");
    scanf("%d", &value);
    printf("Enter the number of coins/bills: ");
    scanf("%d", &count);
    CoinBill *selected_coin_bill = NULL;
    for (int i = 0; i < 6; ++i)
        if (vm->coins_bills[i].value == value)
            selected_coin_bill = &vm->coins_bills[i];
    if (selected_coin_bill) {
        if ((choice == 2 && selected_coin_bill->count >= count) || choice == 1) {
            selected_coin_bill->count += (choice == 1) ? count : -count;
            printf((choice == 1) ? "Added %d x %d yen to inventory.\n" : "Reduced %d x %d yen from inventory.\n", count, selected_coin_bill->value);
        } else
            printf("Invalid coin/bill value or insufficient quantity.\n");
    } else
        printf("Invalid coin/bill value.\n");
}

void manage_products(VendingMachine *vm) {
    printf("Current Products:\n");
    for (int i = 0; i < 3; ++i)
        printf("%d: %s - %d yen (%d in stock)\n", vm->products[i].id, vm->products[i].name, vm->products[i].price, vm->products[i].stock);
    int choice, id, price, stock;
    char name[50];
    printf("Enter 1 to add product or 2 to remove product: ");
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Enter a new ID for the product: ");
        scanf("%d", &id);
        printf("Enter the name of the product: ");
        scanf("%s", name);
        printf("Enter the price of the product: ");
        scanf("%d", &price);
        printf("Enter the initial stock of the product: ");
        scanf("%d", &stock);
        for (int i = 0; i < 3; ++i) {
            if (vm->products[i].id == 0) {
                vm->products[i] = (Product){id, price, stock, ""};
                strcpy(vm->products[i].name, name);
                printf("Added %s to products.\n", name);
                break;
            }
        }
    } else if (choice == 2) {
        printf("Enter the product ID to remove: ");
        scanf("%d", &id);
        for (int i = 0; i < 3; ++i) {
            if (vm->products[i].id == id) {
                printf("Removed %s from products.\n", vm->products[i].name);
                vm->products[i] = (Product){0, 0, 0, ""};
                break;
            }
        }
    } else
        printf("Invalid choice.\n");
}

void admin_menu(VendingMachine *vm) {
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);
    if (strcmp(password, vm->admin_password) == 0) {
        vm->is_admin_mode = 1;
        while (vm->is_admin_mode) {
            printf("\nAdmin Menu:\n1. Check/Add Inventory\n2. Add/Reduce Coins and Bills\n3. Add/Reduce Products\n4. Exit and Resume Sales\n");
            int choice;
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    display_products(vm);
                    int id, quantity;
                    printf("Enter the product ID to add inventory: ");
                    scanf("%d", &id);
                    printf("Enter the quantity to add: ");
                    scanf("%d", &quantity);
                    add_inventory(vm, id, quantity);
                    break;
                case 2:
                    manage_coins_bills(vm);
                    break;
                case 3:
                    manage_products(vm);
                    break;
                case 4:
                    vm->is_admin_mode = 0;
                    printf("Exiting admin mode.\n");
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
        }
    } else
        printf("Incorrect admin password.\n");
}

void start(VendingMachine *vm) {
    while (1) {
        printf("\nVending Machine Simulator:\n1. Display Products\n2. Purchase Product\n3. Admin Menu\n4. Exit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                display_products(vm);
                break;
            case 2: {
                Product *p = select_product(vm);
                if (p) {
                    int total = insert_money(vm, p);
                    if (total >= p->price) {
                        int change = total - p->price;
                        p->stock--;
                        give_change(vm, change);
                    } else
                        printf("Insufficient funds.\n");
                }
                break;
            }
            case 3:
                admin_menu(vm);
                break;
            case 4:
                printf("Exiting vending machine.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}

int main() {
    VendingMachine vm;
    vm.products = (Product *)malloc(3 * sizeof(Product)); 
    vm.coins_bills = (CoinBill *)malloc(6 * sizeof(CoinBill)); 
    vm.products[0] = (Product){1, 150, 10, "Cola"};
    vm.products[1] = (Product){2, 100, 15, "Chips"};
    vm.products[2] = (Product){3, 200, 8, "Chocolate"};
    vm.coins_bills[0] = (CoinBill){5000, 10};
    vm.coins_bills[1] = (CoinBill){1000, 20};
    vm.coins_bills[2] = (CoinBill){500, 30};
    vm.coins_bills[3] = (CoinBill){100, 50};
    vm.coins_bills[4] = (CoinBill){50, 100};
    vm.coins_bills[5] = (CoinBill){10, 200};
    strcpy(vm.admin_password, "admin123");
    vm.is_admin_mode = 0;
    start(&vm);
    free(vm.products);
    free(vm.coins_bills);
    return 0;
}

