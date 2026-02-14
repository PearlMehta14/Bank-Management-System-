# Advanced Bank Management System

An improved and robust Bank Management System written in C.

## Features
- **Admin Password Protection**: Secure login for bank administrators (Default Password: `admin123`).
- **Enhanced UI**: Clean headers, loading animations, and colored console output.
- **Robust Input Handling**: Supports full names and addresses with spaces (fixes common `scanf` bugs).
- **Comprehensive Account Management**:
  - Create New Accounts
  - Update Existing Information (Address/Phone)
  - Perform Transactions (Deposit/Withdraw)
  - View Customer List
  - Search Accounts by Number or Name
  - Automatic Interest Calculation (Saving/Fixed Accounts)
  - Safe Record Deletion
- **Persistent Storage**: Saves all data to `records.dat` using a pipe-delimited format for reliability.

## How to Run
1. Ensure you have a C compiler installed (like `gcc`).
2. Compile the code:
   ```bash
   gcc bank_system.c -o bank_system
   ```
3. Run the executable:
   ```bash
   ./bank_system
   ```

## Development
Created by **Error Terror Team** and enhanced by **Antigravity AI**.
