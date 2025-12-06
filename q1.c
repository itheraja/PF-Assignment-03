#include <stdio.h>

void calculateRepayment(float loan, float interestRate, int years, int currentYear) {
    if (years == 0 || loan <= 0) {
        printf("\nLoan fully repaid!\n");
        return;
    }

    float interest = loan * (interestRate / 100.0f);
    float updatedLoan = loan + interest;

    printf("Year %d: Remaining loan = %.2f (Interest: %.2f)\n",
           currentYear, updatedLoan, interest);

    calculateRepayment(updatedLoan, interestRate, years - 1, currentYear + 1);
}

void calculateRepaymentWithExtra(float loan, float interestRate, int years,
                                 int currentYear, float extraPayment) {
    if (years == 0 || loan <= 0) {
        printf("\nLoan fully repaid!\n");
        return;
    }

    float interest = loan * (interestRate / 100.0f);
    float updatedLoan = loan + interest - extraPayment;

    if (updatedLoan <= 0) {
        printf("Year %d: Loan paid off! Final payment = %.2f\n",
               currentYear, loan + interest);
        return;
    }

    printf("Year %d: Remaining loan = %.2f (Interest: %.2f, Extra Payment: %.2f)\n",
           currentYear, updatedLoan, interest, extraPayment);

    calculateRepaymentWithExtra(updatedLoan, interestRate, years - 1,
                                currentYear + 1, extraPayment);
}

int main() {
    printf("=== Loan Repayment Calculator ===\n\n");

    printf("Test Case 1: Basic Repayment\n");
    printf("Loan: 100,000, Interest Rate: 5%%, Years: 3\n\n");
    calculateRepayment(100000, 5, 3, 1);

    printf("\nVersion with Extra Payments\n\n");
    printf("Test Case 2: With Extra Payment of 10,000 per year\n\n");
    calculateRepaymentWithExtra(100000, 5, 3, 1, 10000);

    printf("\n\nWhy recursion is suitable:\n");
    printf("- Each year's calculation depends on the previous year\n");
    printf("- Recursion naturally tracks state across years\n");
    printf("- Easy to modify for additional features like extra payments\n");

    return 0;
}
