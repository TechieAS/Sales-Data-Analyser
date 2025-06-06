#include <stdio.h>
#include <stdlib.h>

#define FILENAME "sales_data.bin"

struct sales_record
{
    int id;
    char item[30];
    float amount;
};

void importSalesData()
{
    FILE *file = fopen(FILENAME, "ab");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    struct sales_record record;
    int n;

    printf("Enter the number of sales records to import: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter details for record %d:\n", i + 1);
        printf("Sale ID: ");
        scanf("%d", &record.id);
        printf("Item Name: ");
        scanf(" %s", record.item);
        printf("Sale Amount: ");
        scanf("%f", &record.amount);

        fwrite(&record, sizeof(struct sales_record), 1, file);
    }

    fclose(file);
    printf("Sales data imported successfully!\n");
}

void calculateMetrics()
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    struct sales_record record;
    float totalSales = 0.0;
    int count = 0;

    while (fread(&record, sizeof(struct sales_record), 1, file) == 1)
    {
        totalSales += record.amount;
        count++;
    }

    fclose(file);

    if (count > 0)
    {
        printf("\nMetrics:\n");
        printf("Total Sales: %.2f\n", totalSales);
        printf("Average Sales: %.2f\n", totalSales / count);
    }
    else
    {
        printf("No sales data available.\n");
    }
}
void generateReport()
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    struct sales_record record;

    printf("\nSales Report:\n");
    printf("ID\tItem Name\t\tAmount\n");

    while (fread(&record, sizeof(struct sales_record), 1, file) == 1)
    {
        printf("%d\t%s\t%2f\n", record.id, record.item, record.amount);
    }

    fclose(file);
}
int main()
{
    int choice;
    do
    {
        printf("enter 1 to import data:\n");
        printf("enter 2 to calculate Metrics\n");
        printf("enter 3 to generate Report\n");
        printf("enter 4 to exit program\n");
        printf("enter your choice:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            importSalesData();
            break;
        case 2:
            calculateMetrics();
            break;
        case 3:
            generateReport();
            break;
        case 4:
            printf("exiting program.....\n");
            printf("exit program succesfully\n");
            break;
        default:
            printf("invalid choice\n");
        }
    } while (choice != 4);
    return 0;
}