#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;
void print_balance(int startAge, double * balance, retire_info info) {
  for (int i = 0; i < info.months; i++) {
    int age_years = (startAge + i) / 12;
    int age_months = (startAge + i) % 12;

    printf("Age %3d month %2d you have $%.2f\n", age_years, age_months, *balance);

    *balance += (*balance * info.rate_of_return) + info.contribution;
  }
}
void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  print_balance(startAge, &initial, working);

  print_balance(startAge + working.months, &initial, retired);
}
int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  int startAge = 327;
  double initial = 21345;

  retirement(startAge, initial, working, retired);

  return 0;
}
