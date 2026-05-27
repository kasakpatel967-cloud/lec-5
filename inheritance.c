#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

// Function prototypes
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele(void);

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create family
    person *p = create_family(GENERATIONS);

    // Print family
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new family with generations
person *create_family(int generations)
{
    // Allocate memory for person
    person *new_person = malloc(sizeof(person));

    // Check allocation
    if (new_person == NULL)
    {
        return NULL;
    }

    // Base case
    if (generations == 1)
    {
        // Oldest generation has no parents
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;

        // Random alleles
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }

    // Recursive case
    else
    {
        // Create parents recursively
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // Assign parents
        new_person->parents[0] = parent0;
        new_person->parents[1] = parent1;

        // Child inherits one allele from each parent
        new_person->alleles[0] =
            parent0->alleles[rand() % 2];

        new_person->alleles[1] =
            parent1->alleles[rand() % 2];
    }

    return new_person;
}

// Free memory recursively
void free_family(person *p)
{
    // Handle NULL pointer
    if (p == NULL)
    {
        return;
    }

    // Free parents first
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free current person
    free(p);
}
void print_family(person *p, int generation)
{
    // Handle empty child
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n",
               generation,
               p->alleles[0],
               p->alleles[1]);
    }
    else
    {
        printf("Generation %i: blood type %c%c\n",
               generation,
               p->alleles[0],
               p->alleles[1]);
    }

    // Print parents recursively
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly return blood type allele
char random_allele(void)
{
    int r = rand() % 3;

    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
