#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <string>

using namespace std;

void ViewCustomers(sql::Connection* con) {
    cout << "\n--- Current Customers ---\n";
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM customers");
    sql::ResultSet* res = pstmt->executeQuery();

    while (res->next()) {
        cout << "ID: " << res->getInt("customer_id")
            << " | Name: " << res->getString("name")
            << " | Phone: " << res->getString("phone")
            << " | Room: " << res->getInt("room_number")
            << " | Check-In: " << res->getString("IN_TIME")
            << " | Bill: " << res->getDouble("bill_amt") << endl;
    }

    delete res;
    delete pstmt;
}

void ViewArchivedCustomers(sql::Connection* con) {
    cout << "\n--- Archived Customer Records ---\n";
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM archived_customers");
    sql::ResultSet* res = pstmt->executeQuery();

    while (res->next()) {
        cout << "Archive ID: " << res->getInt("archive_id")
            << " | Customer ID: " << res->getInt("customer_id")
            << " | Name: " << res->getString("name")
            << " | Phone: " << res->getString("phone")
            << " | Room: " << res->getInt("room_number")
            << " | Check in Time: " << res->getString("IN_TIME")
            << " | Bill: " << res->getDouble("bill_amt")
            << " | Operation: " << res->getString("operation_type")
            << " | Check out Time: " << res->getString("operation_time") << endl;
    }

    delete res;
    delete pstmt;
}

int main() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "admin", "Loginmysql@1");
        con->setSchema("myhotel_db");

        int choice;
        do {
            cout << "\n--- Owner Panel ---\n";
            cout << "1. View Customers\n";
            cout << "2. View Archived Customers\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                ViewCustomers(con);
                break;
            case 2:
                ViewArchivedCustomers(con);
                break;
            case 0:
                cout << "Exiting Owner Panel.\n";
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 0);

        delete con;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }

    system("pause");
    return 0;
}
