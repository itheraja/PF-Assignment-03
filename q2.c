#include <stdio.h>

// Recursive function to calculate spacecraft fuel
int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, 
                  int planet, int totalPlanets) {
    
    // Base case 1: Fuel exhausted
    if (fuel <= 0) {
        printf("\nMission Failed! Fuel exhausted at Planet %d\n", planet - 1);
        return 0;
    }
    
    // Base case 2: All planets visited successfully
    if (planet > totalPlanets) {
        printf("\nMission Successful! Journey completed with %d fuel remaining\n", fuel);
        return 1;
    }
    
    // Calculate fuel for current planet
    int newFuel = fuel - consumption + recharge;
    
    // Check for solar recharge (every 4th planet)
    if (planet % 4 == 0) {
        newFuel += solarBonus;
        printf("Planet %d: Fuel Remaining = %d (Solar Recharge +%d)\n", 
               planet, newFuel, solarBonus);
    } else {
        printf("Planet %d: Fuel Remaining = %d\n", planet, newFuel);
    }
    
    // Recursive case: move to next planet
    return calculateFuel(newFuel, consumption, recharge, solarBonus, 
                        planet + 1, totalPlanets);
}

int main() {
    printf("=== Spacecraft Fuel Simulation ===\n\n");
    
    // Test case 1: Successful mission
    printf("Test Case 1: Successful Mission\n");
    printf("Initial Fuel: 1000, Consumption: 100, Recharge: 30\n");
    printf("Solar Bonus: 150, Total Planets: 8\n\n");
    
    calculateFuel(1000, 100, 30, 150, 1, 8);
    
    printf("\n\n");
    
    // Test case 2: Failed mission (fuel runs out)
    printf("Test Case 2: Failed Mission\n");
    printf("Initial Fuel: 500, Consumption: 150, Recharge: 20\n");
    printf("Solar Bonus: 100, Total Planets: 8\n\n");
    
    calculateFuel(500, 150, 20, 100, 1, 8);
    
    printf("\n\n");
    
    // Test case 3: Close call mission
    printf("Test Case 3: Close Call Mission\n");
    printf("Initial Fuel: 800, Consumption: 120, Recharge: 50\n");
    printf("Solar Bonus: 200, Total Planets: 10\n\n");
    
    calculateFuel(800, 120, 50, 200, 1, 10);
    
    return 0;
}
