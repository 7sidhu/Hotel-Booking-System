#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <string>

using namespace std;

void bookRoom(sql::Connection* con) {
    string name, phone, id_proof;
    int room_number;

    cout << "\n--- Booking Room ---\n";
    cin.ignore(); // clear buffer before taking full-line inputs
    cout << "Enter Customer Name: ";
    getline(cin, name);

    cout << "Enter Phone Number: ";
    getline(cin, phone);

    cout << "Enter ID Proof: ";
    getline(cin, id_proof);

    // Show available rooms
    sql::PreparedStatement* pstmt = con->prepareStatement(
        "SELECT room_number, type, floor FROM rooms WHERE status='available'");
    sql::ResultSet* res = pstmt->executeQuery();

    bool found = false;
    cout << "\nAvailable Rooms:\n";
    while (res->next()) {
        found = true;
        cout << "Room: " << res->getInt("room_number")
            << "   Floor: " << res->getInt("floor")
            << "   Type: " << res->getString("type") << endl;
    }

    delete res;
    delete pstmt;

    if (!found) {
        cout << "No available rooms at the moment.\n";
        return;
    }

    cout << "Enter Room Number to book: ";
    cin >> room_number;

    // Insert booking into customers
    pstmt = con->prepareStatement(
        "INSERT INTO customers(name, phone, id_proof, room_number) VALUES (?, ?, ?, ?)");
    pstmt->setString(1, name);
    pstmt->setString(2, phone);
    pstmt->setString(3, id_proof);
    pstmt->setInt(4, room_number);
    pstmt->execute();
    delete pstmt;

    // Update room status
    pstmt = con->prepareStatement("UPDATE rooms SET status='booked' WHERE room_number=?");
    pstmt->setInt(1, room_number);
    pstmt->execute();
    delete pstmt;

    cout << "Booking successful!\n";
}

int main() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "reception", "Reception@123");
        con->setSchema("myhotel_db");

        int choice;
        do {
            cout << "\n--- Reception Menu ---\n";
            cout << "1. Book Room\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                bookRoom(con);
                break;
            case 0:
                cout << "Reception panel closed.\n";
                break;
            default:
                cout << "Invalid input.\n";
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
