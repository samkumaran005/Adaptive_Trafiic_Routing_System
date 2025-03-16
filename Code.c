#include <stdio.h> 
#include <string.h> 
#include <limits.h> // For INT_MAX (represents infinity) 
 
// Structure to represent a city 
typedef struct { 
    char name[20]; // City name 
} City; 
 
// Function prototypes 
void dijkstra(int n, int cost[10][10], int dist[10], int prev[10], int src_ind); 
int find_city_ind(City cities[], int n, char name[]); 
void path(int prev[], int dest_ind, City cities[]); 
 
int main() { 
    int n = 0; // Number of cities 
    int i, j, dist[10], cost[10][10], prev[10]; // Distance, cost matrix, and predecessor array 
    char sourceCity[20], destCity[20]; // Source and destination city names 
    int distance, src_ind, dest_ind; // Distance, source index, and destination index 
    City cities[10]; // Array to store city names 
 
    // Initialize cost matrix with INT_MAX (no direct connections) and 0 for self-loops 
    for (i = 0; i < 10; i++) { 
        for (j = 0; j < 10; j++) { 
            cost[i][j] = (i == j) ? 0 : INT_MAX; 
        } 
    } 
 
// Menu-driven program for user interaction 
 printf("\nMenu:\n"); 
        printf("1. Add City\n"); 
        printf("2. Add Connection\n"); 
        printf("3. Find Shortest Path\n"); 
        printf("4. Update Connection Weight\n"); 
        printf("5. Exit\n"); 
    while (1) { 
        printf("Enter your choice: "); 
        int choice; 
        scanf("%d", &choice); 
 
        switch (choice) { 
            case 1: 
                // Add a new city 
                if (n >= 10) { 
                    printf("Maximum number of cities reached.\n"); 
 
                } else { 
                    printf("Enter city name: "); 
                    scanf("%s", cities[n].name); 
                    n++; 
                    printf("City added successfully.\n"); 
                } 
                break; 
 
            case 2: 
                // Add a connection between two cities 
                if (n < 2) { 
                    printf("Add at least two cities first.\n"); 
                } else { 
                    printf("Enter connection (source city, destination city, distance): "); 
                    scanf("%s %s %d", sourceCity, destCity, &distance); 
 
                    // Find indices of the source and destination cities 
                    int srcIndex = find_city_ind(cities, n, sourceCity); 
                    int destIndex = find_city_ind(cities, n, destCity); 
 
                    // Validate city names and distance 
                    if (srcIndex == -1 || destIndex == -1) { 
                        printf("Invalid city name(s). Please try again.\n"); 
                    } else if (distance <= 0) { 
                        printf("Invalid distance. Please enter a positive value.\n"); 
                    } else { 
                        // Update cost matrix for the connection (undirected graph) 
                        cost[srcIndex][destIndex] = distance; 
                        cost[destIndex][srcIndex] = distance; 
                        printf("Connection added successfully.\n"); 
                    } 
                } 
                break; 
 
            case 3: 
                // Find the shortest path between two cities 
                if (n < 2) { 
                    printf("Add at least two cities and a connection first.\n"); 
                } else { 
                    printf("Enter source city: "); 
                    scanf("%s", sourceCity); 
                    src_ind = find_city_ind(cities, n, sourceCity); 
 
                    // Validate source city 
                    if (src_ind == -1) { 
                        printf("Invalid source city.\n"); 
                        break; 
                    } 
  
                    printf("Enter destination city: "); 
                    scanf("%s", destCity); 
                    dest_ind = find_city_ind(cities, n, destCity); 
 
                    // Validate destination city 
                    if (dest_ind == -1) { 
                        printf("Invalid destination city.\n"); 
                        break; 
                    } 
 
                    // Perform Dijkstra's algorithm 
                    dijkstra(n, cost, dist, prev, src_ind); 
 
                    // Check if a path exists 
                    if (dist[dest_ind] == INT_MAX) { 
                        printf("No roads found between %s and %s.\n", sourceCity, destCity); 
                    } else { 
                        printf("\nShortest path from %s to %s (distance = %d):\n", 
                               sourceCity, destCity, dist[dest_ind]); 
                        path(prev, dest_ind, cities); // Print the path 
                        printf("\n"); 
                    } 
                } 
                break; 
 
            case 4: 
                // Update the weight of an existing connection 
                if (n < 2) { 
                    printf("Add at least two cities first.\n"); 
                } else { 
                    printf("Enter connection to update (source city, destination city, new distance): "); 
                    scanf("%s %s %d", sourceCity, destCity, &distance); 
 
                    // Find indices of the source and destination cities 
                    int srcIndex = find_city_ind(cities, n, sourceCity); 
                    int destIndex = find_city_ind(cities, n, destCity); 
 
                    // Validate city names and new distance 
                    if (srcIndex == -1 || destIndex == -1) { 
                        printf("Invalid city name(s). Please try again.\n"); 
                    } else if (distance <= 0) { 
                        printf("Invalid distance. Please enter a positive value.\n"); 
                    } else { 
                        // Update the cost matrix 
                        cost[srcIndex][destIndex] = distance; 
                        cost[destIndex][srcIndex] = distance; 
                        printf("Connection weight updated successfully.\n"); 
                    } 
                } 
                break; 
 
            case 5: 
                // Exit the program 
                printf("Exiting program.\n"); 
                return 0; 
 
            default: 
                // Handle invalid menu choice 
                printf("Invalid choice. Please try again.\n"); 
        } 
    } 
 
    return 0; 
} 
 
// Function to implement Dijkstra's algorithm 
void dijkstra(int n, int cost[10][10], int dist[10], int prev[10], int src_ind) { 
    int visited[10] = {0}; // Array to track visited nodes 
    int count, i, v, min; 
 
    // Initialize distances and predecessors 
    for (i = 0; i < n; i++) { 
        dist[i] = cost[src_ind][i]; 
        prev[i] = (cost[src_ind][i] != INT_MAX && i != src_ind) ? src_ind : -1; 
    } 
    visited[src_ind] = 1; // Mark the source as visited 
    dist[src_ind] = 0; // Distance to the source is 0 
 
    count = 1; // Count of visited nodes 
 
    // Process nodes until all are visited 
    while (count < n) { 
        min = INT_MAX; 
        for (i = 0; i < n; i++) { 
            if (!visited[i] && dist[i] < min) { 
                min = dist[i]; 
                v = i; // Nearest unvisited node 
            } 
        } 
 
        if (min == INT_MAX) break; // No reachable unvisited nodes 
 
        visited[v] = 1; // Mark the nearest node as visited 
        count++; 
 
        // Update distances to unvisited nodes 
        for (i = 0; i < n; i++) { 
            if (!visited[i] && cost[v][i] != INT_MAX && dist[v] + cost[v][i] < dist[i]) { 
                dist[i] = dist[v] + cost[v][i]; 
                prev[i] = v; // Update predecessor 
            } 
        } 
    } 
} 
 
// Function to find the index of a city by its name 
int find_city_ind(City cities[], int n, char name[]) { 
    for (int i = 0; i < n; i++) { 
        if (strcmp(cities[i].name, name) == 0) { 
            return i; // Return index if found 
        } 
    } 
    return -1; // City not found 
} 
 
// Function to print the shortest path recursively 
void path(int prev[], int dest_ind, City cities[]) { 
    if (prev[dest_ind] == -1) { 
        // Base case: no predecessor (starting city) 
        printf("%s", cities[dest_ind].name); 
        return; 
    } 
    path(prev, prev[dest_ind], cities); // Recursive call for previous nodes 
    printf(" -> %s", cities[dest_ind].name); // Print current city 
} 
