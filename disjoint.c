#include <stdio.h>

#define MAX 20

int parent[MAX];
int rank[MAX];

/* MAKE-SET operation
   Creates a separate set for each element */
void makeSet(int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;   // Each element is its own parent
        rank[i] = 0;     // Initially, rank is 0
    }
}

/* FIND operation
   Finds the representative (root) of the set containing x */
int find(int x)
{
    if (parent[x] != x)
    {
        parent[x] = find(parent[x]);  // Path compression
    }

    return parent[x];
}

/* UNION operation using Union by Rank */
void unionSet(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    /* If both have the same root,
       they are already in the same set */
    if (rootX == rootY)
    {
        printf("%d and %d are already in the same set.\n", x, y);
        return;
    }

    /* Attach the tree with smaller rank
       under the tree with larger rank */
    if (rank[rootX] < rank[rootY])
    {
        parent[rootX] = rootY;
    }
    else if (rank[rootX] > rank[rootY])
    {
        parent[rootY] = rootX;
    }
    else
    {
        /* Both ranks are equal.
           Choose rootX as the new root */
        parent[rootY] = rootX;

        /* Height may increase by one */
        rank[rootX]++;
    }
}

/* Display parent and rank of each element */
void display(int n)
{
    printf("\nElement\tParent\tRank\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n", i, parent[i], rank[i]);
    }
}

int main()
{
    int n, choice, x, y;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    makeSet(n);

    while (1)
    {
        printf("\n--- DISJOINT SET ---\n");
        printf("1. FIND\n");
        printf("2. UNION\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter element: ");
                scanf("%d", &x);

                printf("Representative of %d = %d\n",
                       x, find(x));
                break;

            case 2:
                printf("Enter two elements: ");
                scanf("%d %d", &x, &y);

                unionSet(x, y);
                break;

            case 3:
                display(n);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

