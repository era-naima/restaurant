#include <stdio.h>
#include <string.h>

void displayMenu();
void takeOrder();
void deleteOrder();
void viewAllOrders();
void generateBill();
void calculateTotalCost();
void giveReview();
void viewReviews();
void loadReviewsFromFile();
void saveReviewsToFile();

char *menuItems[] = {"Coffee", "Tea", "Sandwich", "Burger", "Cake", "Pizza", "Pasta", "Salad"};
int prices[] = {50, 30, 100, 150, 80, 200, 150, 180};
int orderQuantity[8] = {0};

char reviews[100][255];
int reviewCount = 0;
const char *reviewFile = "reviews.txt";

int main() {

    int choice;

    loadReviewsFromFile();

    while (1) {

        printf("\n=== Restaurant Management System ===\n");
        printf("1. Display Menu\n");
        printf("2. Take Order\n");
        printf("3. Delete Food Item from Order\n");
        printf("4. View All Ordered Items\n");
        printf("5. Calculate Total Cost\n");
        printf("6. Generate Bill\n");
        printf("7. Give a Review\n");
        printf("8. View Reviews\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {

            case 1:
                displayMenu();
                break;
            case 2:
                takeOrder();
                break;
            case 3:
                deleteOrder();
                break;
            case 4:
                viewAllOrders();
                break;
            case 5:
                calculateTotalCost();
                break;
            case 6:
                generateBill();
                break;
            case 7:
                giveReview();
                break;
            case 8:
                viewReviews();
                break;
            case 9:
                printf("Thank you for visiting our restaurant!\n");
                saveReviewsToFile();
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void displayMenu() {

    printf("\n=== Restaurant Menu ===\n");
    for (int i = 0; i < 8; i++) {
        printf("%d. %s - tk. %d\n", i + 1, menuItems[i], prices[i]);
    }
}

void takeOrder() {

    int item, quantity;
    printf("\nEnter the item number you want to order (1-8): ");
    scanf("%d", &item);

    if (item < 1 || item > 8) {
        printf("Invalid item number!\n");
        return;
    }

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    if (quantity < 1) {
        printf("Invalid quantity!\n");
        return;
    }

    orderQuantity[item - 1] += quantity;
    printf("Added %d %s to your order.\n", quantity, menuItems[item - 1]);
}


void deleteOrder() {

    int item;
    printf("\nEnter the item number you want to delete from the order (1-8): ");
    scanf("%d", &item);

    if (item < 1 || item > 8) {
        printf("Invalid item number!\n");
        return;
    }

    if (orderQuantity[item - 1] > 0) {
        printf("Removed %d %s from your order.\n", orderQuantity[item - 1], menuItems[item - 1]);
        orderQuantity[item - 1] = 0;
    } else {
        printf("Item not found in your order.\n");
    }
}


void viewAllOrders() {

    printf("\n=== Ordered Items ===\n");
    int found = 0;

    for (int i = 0; i < 8; i++) {
        if (orderQuantity[i] > 0) {
            printf("%s - Quantity: %d\n", menuItems[i], orderQuantity[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No items ordered yet.\n");
    }
}

void generateBill() {

    int total = 0;
    printf("\n=== Bill ===\n");
    printf("Item\t\tQuantity\tPrice\n");

    for (int i = 0; i < 8; i++) {
        if (orderQuantity[i] > 0) {
            int cost = orderQuantity[i] * prices[i];
            printf("%s\t%d\t\ttk. %d\n", menuItems[i], orderQuantity[i], cost);
            total += cost;
        }
    }

    if (total == 0) {
        printf("No items ordered yet.\n");
    } else {
        printf("-----------------------------\n");
        printf("Total Bill: tk. %d\n", total);
    }
}


void calculateTotalCost() {

    int total = 0;

    for (int i = 0; i < 8; i++) {
        if (orderQuantity[i] > 0) {
            total += orderQuantity[i] * prices[i];
        }
    }

    printf("\nTotal cost of your order: tk. %d\n", total);
}

void giveReview() {

    if (reviewCount >= 100) {
        printf("Review limit reached! No more reviews can be added.\n");
        return;
    }

    printf("\nEnter your review: ");
    fgets(reviews[reviewCount], 255, stdin);

    reviews[reviewCount][strcspn(reviews[reviewCount], "\n")] = 0;
    reviewCount++;

    printf("Thank you for your review!\n");
}

void viewReviews() {

    printf("\n=== Customer Reviews ===\n");

    if (reviewCount == 0) {
        printf("No reviews yet.\n");
        return;
    }

    for (int i = 0; i < reviewCount; i++) {
        printf("%d. %s\n", i + 1, reviews[i]);
    }
}


void loadReviewsFromFile() {

    FILE *file = fopen(reviewFile, "r");
    if (file == NULL) {
        return;
    }

    fclose(file);
    file = fopen(reviewFile, "w");
    fclose(file);
}



void saveReviewsToFile() {

    FILE *file = fopen(reviewFile, "w");
    if (file == NULL) {
        printf("Error saving reviews to file!\n");
        return;
    }

    for (int i = 0; i < reviewCount; i++) {
        fprintf(file, "%s\n", reviews[i]);
    }

    fclose(file);
}
