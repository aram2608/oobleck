#include <stdio.h>
#include <stdlib.h>

// https://www.tutorialspoint.com/cprogramming/c_flexible_array_members_in_structures.htm

struct Student {
    int id;
    int count;      // This field helps track current array size
    int marks[];    // Flexible array member
};

int main() {
    // Step 1: Initial allocation for 3 marks
    int initial_elements = 3;
    struct Student *s = malloc(sizeof(struct Student) + initial_elements * sizeof(int));
    
    if (s != NULL) {
        s->id = 101;
        s->count = initial_elements;  // Store current array size
        
        // Display initial sizes
        printf("Structure size: %zu bytes\n", sizeof(struct Student)); // Output: 8 bytes (id + count)
        printf("Initial array elements: %d\n", s->count);              // Output: 3
        printf("Initial total memory: %zu bytes\n", 
           sizeof(struct Student) + initial_elements * sizeof(int)); // Output: 20 bytes
        
        // Step 2: Resize to hold 6 marks
        int new_elements = 6;
        struct Student *temp = realloc(s, sizeof(struct Student) + new_elements * sizeof(int));
        
        if (temp != NULL) {
            s = temp;
            s->count = new_elements;  // Update array size tracker
            
            // Display new sizes
            printf("\nAfter resizing:\n");
            printf("Structure size: %zu bytes\n", sizeof(struct Student)); // Still 8 bytes
            printf("New array elements: %d\n", s->count);                  // Output: 6
            printf("New total memory: %zu bytes\n", 
               sizeof(struct Student) + new_elements * sizeof(int));   // Output: 32 bytes
        }
        
        free(s);
    }
    return 0;
}