<h1 align="center">🏨 Hotel Booking System</h1>

<p align="center">
  The <b>Hotel Booking System</b> is a locally hosted <b>desktop application</b> designed to streamline hotel management operations in an <b>offline environment</b>.
</p>

<hr>

<h2>📖 Project Overview</h2>
<p>
This project is a <b>desktop-based application</b> developed in <b>C++ (Visual Studio 2022)</b> and integrated with a <b>MySQL database</b>. It allows hotel staff to efficiently handle:
</p>
<ul>
  <li>Reservations</li>
  <li>Guest records</li>
  <li>Billing</li>
  <li>Administrative tasks</li>
</ul>
<p>
⚡ Designed for <b>small to medium-sized hotels</b>, this system provides a reliable solution for <b>day-to-day management</b> while ensuring <b>data security</b> and <b>multi-terminal support</b>.
</p>

<hr>

<h2>✨ Features</h2>
<ul>
  <li>🔌 <b>Offline Operation</b> – Works entirely on a local system or intranet server; no internet required.</li>
  <li>👥 <b>Role-Based Access Terminals</b>
    <ul>
      <li><b>Owner Terminal</b> → Full admin controls, reports, configurations.</li>
      <li><b>Reception Terminal</b> → Room bookings, check-ins & check-outs.</li>
      <li><b>Cash Counter Terminal</b> → Billing, invoices, and payments.</li>
    </ul>
  </li>
  <li>🗄️ <b>Database Integration</b> – Built on <b>MySQL</b> with <b>C++ SQL connectors</b>.</li>
  <li>🔐 <b>User Authentication</b> – Secure login for each terminal.</li>
  <li>🏷️ <b>Efficient Room & Booking Management</b> – Real-time availability, guest info, reservation history.</li>
  <li>⚙️ <b>Scalable & Maintainable</b> – Modular codebase for easy updates.</li>
</ul>

<hr>

<h2>🛠️ Technologies Used</h2>
<ul>
  <li><b>Programming Language:</b> C++</li>
  <li><b>IDE:</b> Visual Studio 2022</li>
  <li><b>Database:</b> MySQL</li>
  <li><b>Connector/API:</b> MySQL Connector/C++</li>
</ul>

<hr>

<h2>📂 Project Structure</h2>

<pre>
HotelBookingSystem/
│
├── src/           # Three C++ source code files for 3 user terminals
├── include/       # C++ and MySQL connector files
├── sql/           # SQL scripts for database setup
├── config.ini     # Database configuration (if used)
└── README.md      # Project description
</pre>

<hr>

<h2>🚀 How to Run</h2>
<ol>
  <li>Clone the repository:
    <pre>git clone https://github.com/your-username/Hotel-Booking-System.git</pre>
  </li>
  <li>Set up the MySQL database using scripts in the <b>/sql</b> folder.</li>
  <li>Download and install the MySQL Connector/C++. Then, configure config.ini with your database credentials.</li>
  <li>Build and run the project in <b>Visual Studio 2022</b>.</li>
</ol>

<hr>

<h2>📌 Future Enhancements</h2>
<ul>
  <li>Web-based version with remote access.</li>
  <li>Advanced reporting & analytics dashboard.</li>
</ul>
