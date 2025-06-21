-- 0. Create Database
CREATE DATABASE IF NOT EXISTS myhotel_db;
USE myhotel_db;

-- 1. Table: rooms
CREATE TABLE IF NOT EXISTS rooms (
    room_number INT PRIMARY KEY,
    floor INT,
    type VARCHAR(20),
    status VARCHAR(20) DEFAULT 'available'
);

-- 2. Insert initial rooms
INSERT INTO rooms (room_number, floor, type) VALUES
(101, 1, 'Single'), (102, 1, 'Single'), (103, 1, 'Double'), (104, 1, 'Double'),  (105, 1, 'Deluxe'),
(106, 1, 'Single'), (107, 1, 'Double'), (108, 1, 'Deluxe'), (109, 1, 'Single'), (110, 1, 'Double'),
(201, 2, 'Single'), (202, 2, 'Double'), (203, 2, 'Single'), (204, 2, 'Deluxe'), (205, 2, 'Double'),
(206, 2, 'Single'), (207, 2, 'Deluxe'), (208, 2, 'Single'), (209, 2, 'Double'), (210, 2, 'Single'),
(301, 3, 'Single'), (302, 3, 'Double'), (303, 3, 'Deluxe'), (304, 3, 'Single'), (305, 3, 'Double'),
(306, 3, 'Single'), (307, 3, 'Double'), (308, 3, 'Deluxe'), (309, 3, 'Single'), (310, 3, 'Double'),
(401, 4, 'Single'), (402, 4, 'Double'), (403, 4, 'Single'), (404, 4, 'Double'), (405, 4, 'Deluxe'),
(406, 4, 'Single'), (407, 4, 'Deluxe'), (408, 4, 'Double'), (409, 4, 'Single'), (410, 4, 'Double'),
(501, 5, 'Single'), (502, 5, 'Double'), (503, 5, 'Deluxe'), (504, 5, 'Single'), (505, 5, 'Double'),
(506, 5, 'Deluxe'), (507, 5, 'Single'), (508, 5, 'Double'), (509, 5, 'Single'), (510, 5, 'Double');

-- 3. Table: customers
CREATE TABLE IF NOT EXISTS customers (
    customer_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    phone VARCHAR(15),
    id_proof VARCHAR(50),
    IN_TIME TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    out_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    room_number INT,
    bill_amt DOUBLE,
    FOREIGN KEY (room_number) REFERENCES rooms(room_number) ON DELETE CASCADE
);

-- 4. Table: archived_customers
CREATE TABLE IF NOT EXISTS archived_customers (
    archive_id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT,
    name VARCHAR(100),
    phone VARCHAR(15),
    id_proof VARCHAR(50),
    IN_TIME TIME,
    out_time TIME,
    room_number INT,
    bill_amt DOUBLE,
    operation_type VARCHAR(20),
    operation_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 5. Table: cash_counter
DROP TABLE IF EXISTS cash_counter;

CREATE TABLE cash_counter (
    payment_id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT,
    payment_status BOOLEAN,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id) ON DELETE CASCADE
);

-- 6. Triggers
DROP TRIGGER IF EXISTS after_customer_insert;
DROP TRIGGER IF EXISTS after_bill_payment;

DELIMITER //

CREATE TRIGGER after_customer_insert
AFTER INSERT ON customers
FOR EACH ROW
BEGIN
    INSERT INTO archived_customers(customer_id, name, phone, id_proof, IN_TIME, room_number, bill_amt, operation_type)
    VALUES (NEW.customer_id, NEW.name, NEW.phone, NEW.id_proof, CURTIME(), NEW.room_number, NEW.bill_amt, 'INSERT');
END;
//

CREATE TRIGGER after_bill_payment
AFTER UPDATE ON customers
FOR EACH ROW
BEGIN
    IF NEW.bill_amt > 0 AND OLD.bill_amt = 0 THEN
        INSERT INTO archived_customers(customer_id, name, phone, id_proof, out_time, room_number, bill_amt, operation_type)
        VALUES (NEW.customer_id, NEW.name, NEW.phone, NEW.id_proof, CURTIME(), NEW.room_number, NEW.bill_amt, 'CHECKOUT');
    END IF;
END;
//

DELIMITER ;

-- 7. Users & Privileges
CREATE USER IF NOT EXISTS 'admin'@'localhost' IDENTIFIED BY 'Loginmysql@1';
CREATE USER IF NOT EXISTS 'cashier'@'localhost' IDENTIFIED BY 'Cashier@123';
CREATE USER IF NOT EXISTS 'reception'@'localhost' IDENTIFIED BY 'Reception@123';

GRANT SELECT, INSERT, UPDATE, DELETE ON myhotel_db.customers TO 'cashier'@'localhost';
GRANT SELECT, INSERT, UPDATE ON myhotel_db.customers TO 'reception'@'localhost';
GRANT SELECT, UPDATE ON myhotel_db.rooms TO 'reception'@'localhost';
GRANT INSERT ON myhotel_db.archived_customers TO 'cashier'@'localhost';
GRANT DELETE ON myhotel_db.cash_counter TO 'cashier'@'localhost';
GRANT ALL PRIVILEGES ON myhotel_db.* TO 'admin'@'localhost';
FLUSH PRIVILEGES;

-- Test queries
SELECT * FROM customers;
SELECT * FROM archived_customers;
