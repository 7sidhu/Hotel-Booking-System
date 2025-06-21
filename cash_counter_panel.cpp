#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <string>

using namespace std;

void processCheckout(sql::Connection* con) {
    int customer_id;
    double bill_amt;
    int payment_status;

    cout << "\n--- Process Customer Checkout ---\n";
    cout << "Enter Customer ID: ";
    cin >> customer_id;
    cout << "Enter Bill Amount: ";
    cin >> bill_amt;
    cout << "Enter Payment Status (1 for Successful, 0 for Failed): ";
    cin >> payment_status;

    try {
        // 1. Update bill in customers table
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "UPDATE customers SET bill_amt = ?, out_time = CURRENT_TIMESTAMP WHERE customer_id = ?");
        pstmt->setDouble(1, bill_amt);
        pstmt->setInt(2, customer_id);
        pstmt->execute();
        delete pstmt;

        // 2. Insert into cash_counter table
        pstmt = con->prepareStatement(
            "INSERT INTO cash_counter (customer_id, payment_status) VALUES (?, ?)");
        pstmt->setInt(1, customer_id);
        pstmt->setBoolean(2, payment_status);
        pstmt->execute();
        delete pstmt;

        // 3. Delete from cash_counter before deleting customer
        if (payment_status == 1) {

             pstmt = con->prepareStatement("DELETE FROM cash_counter WHERE customer_id = ?");
             pstmt->setInt(1, customer_id);
             pstmt->execute();
             delete pstmt;

            // 4. Now delete customer
            pstmt = con->prepareStatement("DELETE FROM customers WHERE customer_id = ?");
            pstmt->setInt(1, customer_id);
            pstmt->execute();
            delete pstmt;
            cout << "Checkout successful. Customer archived and removed.\n";
        }
        else {
            cout << "Payment Failed. Checkout aborted.\n";
        }
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error during checkout: " << e.what() << endl;
    }
}

int main() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "cashier", "Cashier@123");
        con->setSchema("myhotel_db");

        int choice;
        do {
            cout << "\n--- Cash Counter Menu ---\n";
            cout << "1. Process Checkout\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                processCheckout(con);
                break;
            case 0:
                cout << "Cash counter closed.\n";
                break;
            default:
                cout << "Invalid input.\n";
            }
        } while (choice != 0);

        delete con;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Connection Error: " << e.what() << endl;
    }

    system("pause");
    return 0;
}
