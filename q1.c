#include <stdio.h>

// Recursive function to calculate loan repayment
void calculateRepayment(float loan, float interestRate, int years, int currentYear) {
    // Base case: no more years remaining or loan is paid off
    if (years == 0 || loan <= 0) {
        printf("\nLoan fully repaid!\n");
        return;
    }
    
    // Calculate interest for this year
    float interest = loan * (interestRate / 100);
    float newLoan = loan + interest;
    
    // Print current year status
    printf("Year %d: Remaining loan = %.2f (Interest: %.2f)\n", 
           currentYear, newLoan, interest);
    
    // Recursive case: calculate for remaining years
    calculateRepayment(newLoan, interestRate, years - 1, currentYear + 1);
}

// Extended version with extra payments
void calculateRepaymentWithExtra(float loan, float interestRate, int years, 
                                  int currentYear, float extraPayment) {
    // Base case
    if (years == 0 || loan <= 0) {
        printf("\nLoan fully repaid!\n");
        return;
    }
    
    // Calculate interest
    float interest = loan * (interestRate / 100);
    float newLoan = loan + interest - extraPayment;
    
    // Check if loan is paid off
    if (newLoan <= 0) {
        printf("Year %d: Loan paid off! Final payment = %.2f\n", 
               currentYear, loan + interest);
        return;
    }
    
    printf("Year %d: Remaining loan = %.2f (Interest: %.2f, Extra Payment: %.2f)\n", 
           currentYear, newLoan, interest, extraPayment);
    
    // Recursive call
    calculateRepaymentWithExtra(newLoan, interestRate, years - 1, 
                                currentYear + 1, extraPayment);
}

int main() {
    printf("=== Loan Repayment Calculator ===\n\n");
    
    // Test case: 100,000 loan at 5% for 3 years
    printf("Test Case 1: Basic Repayment\n");
    printf("Loan: 100,000, Interest Rate: 5%%, Years: 3\n\n");
    calculateRepayment(100000, 5, 3, 1);
    
    printf("\n\n=== Extended Version with Extra Payments ===\n\n");
    printf("Test Case 2: With Extra Payment of 10,000 per year\n\n");
    calculateRepaymentWithExtra(100000, 5, 3, 1, 10000);
    
    printf("\n\nWhy recursion is suitable:\n");
    printf("- Each year's calculation depends on the previous year\n");
    printf("- Recursion naturally tracks state across years\n");
    printf("- Easy to modify for additional features like extra payments\n");
    
    return 0;
}
