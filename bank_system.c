#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


// Constants
#define DATA_FILE "records.dat"
#define PASSWORD "admin123"

// Structures
struct date {
  int month, day, year;
};

struct account {
  int acc_no;
  char name[100];
  int age;
  char address[100];
  char aadhar[20];
  char phone[15];
  char acc_type[20];
  float balance;
  struct date dob;
  struct date deposit_date;
} bank, upd, check, rem, transaction;

// Function Prototypes
void menu();
void new_acc();
void view_list();
void edit();
void transact();
void erase();
void see();
void close_app();
void loading_bar();
void header(const char *title);
int check_acc(int acc_no);
void get_password();
void clear_buffer();

// Helper to clear input buffer
void clear_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Global variables
int main_exit;

float calculate_interest(float t, float amount, int rate) {
  return (rate * t * amount) / 100.0;
}

void fordelay(int j) {
  // Standard delay using Windows API Sleep
  Sleep(
      j /
      1000000); // Approximate conversion for compatibility with original calls
}

void loading_bar() {
  printf("\n\n\t\t\tLOADING ");
  for (int i = 0; i <= 10; i++) {
    Sleep(100);        // 100ms delay per block
    printf("%c", 219); // Solid block character
  }
  printf("\n");
}

void header(const char *title) {
  system("cls");
  system("color 0B"); // Light Cyan text on Black background
  printf("\n\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2"
         "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2"
         "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
  printf("\t\t\xB2\xB2                                             \xB2\xB2\n");
  printf("\t\t\xB2\xB2      %-38s       \xB2\xB2\n", title);
  printf("\t\t\xB2\xB2                                             \xB2\xB2\n");
  printf("\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2"
         "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2"
         "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
}

void get_password() {
  char pass[20], ch;
  int i = 0;
  header("ADMIN LOGIN");
  printf("\n\t\tEnter Password: ");
  while (1) {
    ch = getch();
    if (ch == 13) { // Enter key
      pass[i] = '\0';
      break;
    } else if (ch == 8) { // Backspace
      if (i > 0) {
        i--;
        printf("\b \b");
      }
    } else {
      if (i < 19) {
        pass[i++] = ch;
        printf("*");
      }
    }
  }

  if (strcmp(pass, PASSWORD) == 0) {
    printf("\n\n\t\tAccess Granted!");
    loading_bar();
  } else {
    printf("\n\n\t\tAccess Denied! Incorrect Password.");
    getch();
    exit(0);
  }
}

int main() {
  get_password();
  while (1) {
    menu();
  }
  return 0;
}

void menu() {
  int choice;
  header("BANK MANAGEMENT SYSTEM");
  printf("\t\t1. Create New Account\n");
  printf("\t\t2. Update Information\n");
  printf("\t\t3. Transactions (Deposit/Withdraw)\n");
  printf("\t\t4. Check Account Details\n");
  printf("\t\t5. Remove Existing Account\n");
  printf("\t\t6. View Customer List\n");
  printf("\t\t7. Exit\n");
  printf("\n\t\tEnter your choice: ");

  if (scanf("%d", &choice) != 1) {
    clear_buffer();
    return;
  }

  switch (choice) {
  case 1:
    new_acc();
    break;
  case 2:
    edit();
    break;
  case 3:
    transact();
    break;
  case 4:
    see();
    break;
  case 5:
    erase();
    break;
  case 6:
    view_list();
    break;
  case 7:
    close_app();
    break;
  default:
    printf("\nInvalid Choice! Try again.");
    Sleep(1000);
  }
}

void new_acc() {
  FILE *ptr;
  header("ACCOUNT OPENING PROCESS");
  ptr = fopen(DATA_FILE, "a+");

  printf("\n\tEnter Account Number: ");
  scanf("%d", &check.acc_no);

  rewind(ptr);
  while (
      fscanf(ptr,
             "%d %[^|]| %d %d/%d/%d %[^|]| %[^|]| %[^|]| %[^|]| %f %d/%d/%d\n",
             &bank.acc_no, bank.name, &bank.age, &bank.dob.month, &bank.dob.day,
             &bank.dob.year, bank.address, bank.aadhar, bank.phone,
             bank.acc_type, &bank.balance, &bank.deposit_date.month,
             &bank.deposit_date.day, &bank.deposit_date.year) != EOF) {
    if (check.acc_no == bank.acc_no) {
      printf("\n\tError: Account number already exists!");
      fclose(ptr);
      getch();
      menu();
      return;
    }
  }

  bank.acc_no = check.acc_no;
  printf("\tEnter Today's Date (mm/dd/yyyy): ");
  scanf("%d/%d/%d", &bank.deposit_date.month, &bank.deposit_date.day,
        &bank.deposit_date.year);

  printf("\tEnter Full Name: ");
  clear_buffer();
  scanf("%[^\n]", bank.name);

  printf("\tEnter DOB (mm/dd/yyyy): ");
  scanf("%d/%d/%d", &bank.dob.month, &bank.dob.day, &bank.dob.year);

  printf("\tEnter Age: ");
  scanf("%d", &bank.age);

  printf("\tEnter Address: ");
  clear_buffer();
  scanf("%[^\n]", bank.address);

  printf("\tEnter Aadhar Number: ");
  scanf("%s", bank.aadhar);

  printf("\tEnter Phone Number: ");
  scanf("%s", bank.phone);

  printf("\tEnter Initial Deposit Amount: $");
  scanf("%f", &bank.balance);

  printf("\tEnter Account Type (Saving/Current/Fixed1/Fixed2/Fixed3): ");
  scanf("%s", bank.acc_type);

  fprintf(ptr, "%d %s| %d %d/%d/%d %s| %s| %s| %s| %.2f %d/%d/%d\n",
          bank.acc_no, bank.name, bank.age, bank.dob.month, bank.dob.day,
          bank.dob.year, bank.address, bank.aadhar, bank.phone, bank.acc_type,
          bank.balance, bank.deposit_date.month, bank.deposit_date.day,
          bank.deposit_date.year);

  fclose(ptr);
  printf("\n\n\tAccount Created Successfully!");

add_invalid:
  printf("\n\n\tEnter 1 to go to Main Menu and 0 to Exit: ");
  scanf("%d", &main_exit);
  if (main_exit == 1)
    menu();
  else if (main_exit == 0)
    close_app();
  else {
    printf("\nInvalid input!");
    goto add_invalid;
  }
}

void view_list() {
  FILE *view;
  int found = 0;
  header("CUSTOMER LIST");
  view = fopen(DATA_FILE, "r");

  printf("%-10s %-20s %-15s %-12s\n", "ACC. NO.", "NAME", "PHONE", "BALANCE");
  printf("------------------------------------------------------------\n");

  while (
      fscanf(view,
             "%d %[^|]| %d %d/%d/%d %[^|]| %[^|]| %[^|]| %[^|]| %f %d/%d/%d\n",
             &bank.acc_no, bank.name, &bank.age, &bank.dob.month, &bank.dob.day,
             &bank.dob.year, bank.address, bank.aadhar, bank.phone,
             bank.acc_type, &bank.balance, &bank.deposit_date.month,
             &bank.deposit_date.day, &bank.deposit_date.year) != EOF) {
    printf("%-10d %-20.20s %-15s $%-12.2f\n", bank.acc_no, bank.name,
           bank.phone, bank.balance);
    found++;
  }

  fclose(view);
  if (found == 0)
    printf("\n\n\tNo records found!");

  printf("\n\n\tEnter 1 to Main Menu and 0 to Exit: ");
  scanf("%d", &main_exit);
  if (main_exit == 1)
    menu();
  else
    close_app();
}

void edit() {
  int choice, test = 0;
  FILE *old, *newrec;
  header("UPDATE ACCOUNT INFO");
  old = fopen(DATA_FILE, "r");
  newrec = fopen("new.dat", "w");

  printf("\n\tEnter Account Number to update: ");
  scanf("%d", &upd.acc_no);

  while (
      fscanf(old,
             "%d %[^|]| %d %d/%d/%d %[^|]| %[^|]| %[^|]| %[^|]| %f %d/%d/%d\n",
             &bank.acc_no, bank.name, &bank.age, &bank.dob.month, &bank.dob.day,
             &bank.dob.year, bank.address, bank.aadhar, bank.phone,
             bank.acc_type, &bank.balance, &bank.deposit_date.month,
             &bank.deposit_date.day, &bank.deposit_date.year) != EOF) {
    if (bank.acc_no == upd.acc_no) {
      test = 1;
      printf("\n\tWhat do you want to change?\n\t1. Address\n\t2. "
             "Phone\n\tChoice: ");
      scanf("%d", &choice);
      if (choice == 1) {
        printf("\tEnter New Address: ");
        clear_buffer();
        scanf("%[^\n]", upd.address);
        fprintf(newrec, "%d %s| %d %d/%d/%d %s| %s| %s| %s| %.2f %d/%d/%d\n",
                bank.acc_no, bank.name, bank.age, bank.dob.month, bank.dob.day,
                bank.dob.year, upd.address, bank.aadhar, bank.phone,
                bank.acc_type, bank.balance, bank.deposit_date.month,
                bank.deposit_date.day, bank.deposit_date.year);
      } else if (choice == 2) {
        printf("\tEnter New Phone: ");
        scanf("%s", upd.phone);
        fprintf(newrec, "%d %s| %d %d/%d/%d %s| %s| %s| %s| %.2f %d/%d/%d\n",
                bank.acc_no, bank.name, bank.age, bank.dob.month, bank.dob.day,
                bank.dob.year, bank.address, bank.aadhar, upd.phone,
                bank.acc_type, bank.balance, bank.deposit_date.month,
                bank.deposit_date.day, bank.deposit_date.year);
      }
      printf("\n\tChanges Saved Successfully!");
    } else {
      fprintf(newrec, "%d %s| %d %d/%d/%d %s| %s| %s| %s| %.2f %d/%d/%d\n",
              bank.acc_no, bank.name, bank.age, bank.dob.month, bank.dob.day,
              bank.dob.year, bank.address, bank.aadhar, bank.phone,
              bank.acc_type, bank.balance, bank.deposit_date.month,
              bank.deposit_date.day, bank.deposit_date.year);
    }
  }

  fclose(old);
  fclose(newrec);
  remove(DATA_FILE);
  rename("new.dat", DATA_FILE);

  if (test == 0)
    printf("\n\tRecord Not Found!");

  printf("\n\n\tEnter 1 to Main Menu and 0 to Exit: ");
  scanf("%d", &main_exit);
  if (main_exit == 1)
    menu();
  else
    close_app();
}

void transact() {
  int choice, test = 0;
  FILE *old, *newrec;
  header("TRANSACTION HISTORY");
  old = fopen(DATA_FILE, "r");
  newrec = fopen("new.dat", "w");

  printf("\n\tEnter Account Number: ");
  scanf("%d", &transaction.acc_no);

  while (
      fscanf(old,
             "%d %[^|]| %d %d/%d/%d %[^|]| %[^|]| %[^|]| %[^|]| %f %d/%d/%d\n",
             &bank.acc_no, bank.name, &bank.age, &bank.dob.month, &bank.dob.day,
             &bank.dob.year, bank.address, bank.aadhar, bank.phone,
             bank.acc_type, &bank.balance, &bank.deposit_date.month,
             &bank.deposit_date.day, &bank.deposit_date.year) != EOF) {
    if (bank.acc_no == transaction.acc_no) {
      test = 1;
      if (stricmp(bank.acc_type, "fixed1") == 0 ||
          stricmp(bank.acc_type, "fixed2") == 0 ||
          stricmp(bank.acc_type, "fixed3") == 0) {
        printf(
            "\n\tError: Deposits/Withdrawals not allowed for Fixed accounts!");
        fprintf(newrec, "%d %s| %d %d/%d/%d %s| %s| %s| %s| %.2f %d/%d/%d\n",
                bank.acc_no, bank.name, bank.age, bank.dob.month, bank.dob.day,
                bank.dob.year, bank.address, bank.aadhar, bank.phone,
                bank.acc_type, bank.balance, bank.deposit_date.month,
                bank.deposit_date.day, bank.deposit_date.year);
        continue;
      }
      printf("\n\t1. Deposit\n\t2. Withdraw\n\tChoice: ");
      scanf("%d", &choice);
      if (choice == 1) {
        printf("\tEnter amount to Deposit: $");
        scanf("%f", &transaction.balance);
        bank.balance += transaction.balance;
        printf("\n\tDeposited Successfully!");
      } else if (choice == 2) {
        printf("\tEnter amount to Withdraw: $");
        scanf("%f", &transaction.balance);
        if (transaction.balance > bank.balance) {
          printf("\n\tInsufficient balance!");
        } else {
          bank.balance -= transaction.balance;
          printf("\n\tWithdrawn Successfully!");
        }
      }
      fprintf(newrec, "%d %s| %d %d/%d/%d %s| %s| %s| %s| %.2f %d/%d/%d\n",
              bank.acc_no, bank.name, bank.age, bank.dob.month, bank.dob.day,
              bank.dob.year, bank.address, bank.aadhar, bank.phone,
              bank.acc_type, bank.balance, bank.deposit_date.month,
              bank.deposit_date.day, bank.deposit_date.year);
    } else {
      fprintf(newrec, "%d %s| %d %d/%d/%d %s| %s| %s| %s| %.2f %d/%d/%d\n",
              bank.acc_no, bank.name, bank.age, bank.dob.month, bank.dob.day,
              bank.dob.year, bank.address, bank.aadhar, bank.phone,
              bank.acc_type, bank.balance, bank.deposit_date.month,
              bank.deposit_date.day, bank.deposit_date.year);
    }
  }

  fclose(old);
  fclose(newrec);
  remove(DATA_FILE);
  rename("new.dat", DATA_FILE);

  if (test == 0)
    printf("\n\tRecord Not Found!");

  printf("\n\n\tEnter 1 to Main Menu and 0 to Exit: ");
  scanf("%d", &main_exit);
  if (main_exit == 1)
    menu();
  else
    close_app();
}

void see() {
  FILE *ptr;
  int test = 0, choice;
  header("ACCOUNT DETAILS");
  ptr = fopen(DATA_FILE, "r");

  printf("\n\tCheck by:\n\t1. Account Number\n\t2. Name\n\tChoice: ");
  scanf("%d", &choice);

  if (choice == 1) {
    printf("\tEnter Account Number: ");
    scanf("%d", &check.acc_no);
  } else {
    printf("\tEnter Name: ");
    clear_buffer();
    scanf("%[^\n]", check.name);
  }

  while (
      fscanf(ptr,
             "%d %[^|]| %d %d/%d/%d %[^|]| %[^|]| %[^|]| %[^|]| %f %d/%d/%d\n",
             &bank.acc_no, bank.name, &bank.age, &bank.dob.month, &bank.dob.day,
             &bank.dob.year, bank.address, bank.aadhar, bank.phone,
             bank.acc_type, &bank.balance, &bank.deposit_date.month,
             &bank.deposit_date.day, &bank.deposit_date.year) != EOF) {
    if ((choice == 1 && bank.acc_no == check.acc_no) ||
        (choice == 2 && stricmp(bank.name, check.name) == 0)) {
      test = 1;
      printf("\n\tAccount No: %d", bank.acc_no);
      printf("\n\tName: %s", bank.name);
      printf("\n\tDOB: %d/%d/%d", bank.dob.month, bank.dob.day, bank.dob.year);
      printf("\n\tAge: %d", bank.age);
      printf("\n\tAddress: %s", bank.address);
      printf("\n\tAadhar No: %s", bank.aadhar);
      printf("\n\tPhone No: %s", bank.phone);
      printf("\n\tType: %s", bank.acc_type);
      printf("\n\tBalance: $%.2f", bank.balance);

      float interest = 0;
      if (stricmp(bank.acc_type, "saving") == 0)
        interest = calculate_interest(1.0 / 12.0, bank.balance, 8);
      else if (stricmp(bank.acc_type, "fixed1") == 0)
        interest = calculate_interest(1.0, bank.balance, 9);
      else if (stricmp(bank.acc_type, "fixed2") == 0)
        interest = calculate_interest(2.0, bank.balance, 11);
      else if (stricmp(bank.acc_type, "fixed3") == 0)
        interest = calculate_interest(3.0, bank.balance, 13);

      if (interest > 0)
        printf("\n\tExpected Interest: $%.2f", interest);
      else
        printf("\n\tNo Interest applicable for Current account.");
    }
  }

  fclose(ptr);
  if (test == 0)
    printf("\n\tRecord Not Found!");

  printf("\n\n\tEnter 1 to Main Menu and 0 to Exit: ");
  scanf("%d", &main_exit);
  if (main_exit == 1)
    menu();
  else
    close_app();
}

void erase() {
  FILE *old, *newrec;
  int test = 0;
  header("DELETE ACCOUNT");
  old = fopen(DATA_FILE, "r");
  newrec = fopen("new.dat", "w");

  printf("\n\tEnter Account Number to delete: ");
  scanf("%d", &rem.acc_no);

  while (
      fscanf(old,
             "%d %[^|]| %d %d/%d/%d %[^|]| %[^|]| %[^|]| %[^|]| %f %d/%d/%d\n",
             &bank.acc_no, bank.name, &bank.age, &bank.dob.month, &bank.dob.day,
             &bank.dob.year, bank.address, bank.aadhar, bank.phone,
             bank.acc_type, &bank.balance, &bank.deposit_date.month,
             &bank.deposit_date.day, &bank.deposit_date.year) != EOF) {
    if (bank.acc_no != rem.acc_no) {
      fprintf(newrec, "%d %s| %d %d/%d/%d %s| %s| %s| %s| %.2f %d/%d/%d\n",
              bank.acc_no, bank.name, bank.age, bank.dob.month, bank.dob.day,
              bank.dob.year, bank.address, bank.aadhar, bank.phone,
              bank.acc_type, bank.balance, bank.deposit_date.month,
              bank.deposit_date.day, bank.deposit_date.year);
    } else {
      test++;
      printf("\n\tRecord Deleted Successfully!");
    }
  }

  fclose(old);
  fclose(newrec);
  remove(DATA_FILE);
  rename("new.dat", DATA_FILE);

  if (test == 0)
    printf("\n\tRecord Not Found!");

  printf("\n\n\tEnter 1 to Main Menu and 0 to Exit: ");
  scanf("%d", &main_exit);
  if (main_exit == 1)
    menu();
  else
    close_app();
}

void close_app() {
  header("THANK YOU");
  printf("\t\tDeveloped by Error Terror Team\n");
  printf("\t\tPowered by Antigravity AI\n\n");
  exit(0);
}
