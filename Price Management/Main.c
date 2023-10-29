#include <stdio.h>
#include <string.h>

// Product Lister

// Storing Data for Products
struct Product
{
    char productName[100];
    float price;
    int isAvailable;
    // isAvailable will serve as a bool func if product is available or not
};

// Prompt the user to input product
void add_Product(struct Product products[], int *productCount)
{
    printf("\nInput Product Name: ");
    scanf("%s", products[*productCount].productName);
    printf("\nInput Product Price: ");
    scanf("%f", &products[*productCount].price);
    // scanf functions asks the user to input and store values to the struct Product
    // "*" is used to point the memory allocation which is in the data of the struct of "Product"

    products[*productCount].isAvailable = 1;
    //1 means products is available
    //1 = true

    (*productCount)++; // increment the value of productCount

    printf("\nProduct is Added Successfully!\n");
}

// Display the list of products
void display_Products(struct Product products[], int productCount)
{
    printf("\nProduct List:\n");

    //Loop to Print List until it is = to count of Product
    //The loop lists the array of products name and price
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].isAvailable)
        {
            printf("\n%d. %s: %.2f Pesos", i + 1, products[i].productName, products[i].price);
        }
    }
}

void delete_Product(struct Product products[], int productCount)
{
    int deleteProduct;
    display_Products(products, productCount);

    printf("\nEnter the Number of Product to Delete: ");
    scanf("%d", &deleteProduct);

    if (deleteProduct >= 1 && deleteProduct <= productCount)
    {
        products[deleteProduct - 1].isAvailable = 0;
        printf("\nProduct is Successfully Deleted!\n");
    }
    else
    {
        printf("\nInvalid Teh...\n");
    }
}

// Update Product Price if Price changes
void update_Price(struct Product products[], int productCount)
{
    int choice;
    display_Products(products, productCount);

    printf("\nEnter Number of Products You Want to Update: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= productCount)
    {
        //Allocate data for product and change the data for product
        printf("\nEnter New Price for %s: ", products[choice - 1].productName);
        scanf("%f", &products[choice - 1].price);
        printf("\nPrice Updated Successfully!\n");
    }
    else
    {
        printf("\nError Teh...\n");
    }
}

// Save products to a file
void saveProductsToFile(struct Product products[], int productCount)
{
    FILE *file = fopen("products.txt", "w"); //File is saved to file "products.txt"

    if (file == NULL) //Means if File is empty kuno
    {
        printf("Error opening file, Wa man ni sud!\n");
        return;
    }

    for (int i = 0; i < productCount; i++)
    {
        fprintf(file, "%s %.2f %d\n", products[i].productName, products[i].price, products[i].isAvailable);
    }

    fclose(file);
    printf("Data has been saved to the file, Naks naman.\n");
}

// Load products from a file
int loadProductsFromFile(struct Product products[])
{
    FILE *file = fopen("products.txt", "r");

    if (file == NULL)
    {
        printf("No previous data found, delulu man ka.\n");
        return 0;
    }

    int productCount = 0;

    while (fscanf(file, "%s %f %d", products[productCount].productName, &products[productCount].price, &products[productCount].isAvailable) == 3)
    {
        productCount++;
    }

    fclose(file);
    printf("Data has been loaded from the file, wow naks.\n");
    return productCount;
}

int main()
{
    //Maximum products stored is set to 100 as seen in array
    struct Product products[100];
    int productCount = 0;

    productCount = loadProductsFromFile(products);

    int option;

    //Adi na nat CLI/GUI na pangmalakasan HAHAHAHA
    //#innovative HAHAHA
    do
    {
        printf("\n\nButchoy's Sari-Sari Store\n");
        printf("\nProduct Price Lister\n");
        printf("\nOptions\n");
        printf("1. Add Product\n");
        printf("2. Display List of Products\n");
        printf("3. Update Products Price\n");
        printf("4. Delete A Product\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &option);

        //di ta magif statements dols kasi toxic daw
        //SWITCH CASE!!

        switch (option)
        {
        case 1:
            add_Product(products, &productCount);
            break;
        case 2:
            display_Products(products, productCount);
            break;
        case 3:
            update_Price(products, productCount);
            break;
        case 4:
            delete_Product(products, productCount);
            break;
        case 5:
            saveProductsToFile(products, productCount);
            printf("\nBye Bye Po....\n");
            break;
        default:
            printf("\nINVALID CHOICE! MAGTRY KA ULI SAKIN...\n");
        }

    } while (option != 5);

    return 0;
}
