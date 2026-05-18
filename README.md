# 🚗 RideX — Console-Based Ride Booking System

> A C++ Data Structures & Algorithms project simulating a real-world ride-hailing system like Uber/Careem — built entirely from scratch using core DSA concepts.

---

## 📌 About

RideX is a console-based ride booking system that models a city as a weighted graph. Passengers can request rides, drivers are managed through a linked list, routes are calculated using Dijkstra's Algorithm, and ride history is tracked using a stack. The project also includes a visual web-based UI demo built in HTML/CSS/JS.

---

## ✨ Features

- 🗺️ City map modeled as a **weighted graph** with 10 locations and 20+ roads
- 🧭 **Dijkstra's Algorithm** to find the shortest route between any two locations
- 🚖 **Ride request queue** — passengers served in first-come-first-served order
- 👨‍✈️ **Driver management** via a singly linked list
- 📋 **Ride history** stored in a stack (most recent first)
- 🔍 **BFS & DFS** traversal to explore the city graph
- 💰 Automatic fare calculation (Rs. 20 per km)
- 🖥️ Clean menu-driven console interface with formatted tables
- 🌐 Bonus: Interactive HTML/JS UI for visual demo

---

## 🧠 Data Structures Used

| Data Structure | Where Used |
|---|---|
| Graph (Adjacency Matrix) | City map with locations and roads |
| Dijkstra's Algorithm | Shortest path calculation |
| Queue | Ride request management (FIFO) |
| Linked List | Driver records management |
| Stack | Ride history (most recent first) |
| BFS | Level-by-level city traversal |
| DFS | Depth-first city exploration |

---

## 🗂️ Project Structure

```
RideX/
│
├── ride_booking_system.cpp   # Complete C++ source code
├── ride_booking_ui.html      # Visual HTML/JS demo UI
└── README.md                 # Project documentation
```

---

## 🚀 How to Run

### Requirements
- GCC / G++ compiler
- VS Code (recommended) with C/C++ extension by Microsoft

### Compile & Run

```bash
g++ ride_booking_system.cpp -o ride_booking_system
./ride_booking_system
```

### For the HTML UI
Just open `ride_booking_ui.html` in any browser — no setup needed.

---

## 🗺️ City Locations

```
[0] Airport        [1] City Center    [2] University
[3] Hospital       [4] Mall           [5] Train Station
[6] Park           [7] Market         [8] Hotel
[9] Bus Terminal
```

---

## 📋 Menu Options

```
[1]  Add Driver
[2]  Show All Drivers
[3]  Request a Ride
[4]  Show Ride Queue
[5]  Process Next Ride
[6]  Show Ride History
[7]  Show City Map
[8]  BFS Traversal
[9]  DFS Traversal
[10] Find Shortest Path
[11] Mark Driver Available
[0]  Exit
```

---

## 🖼️ Demo UI Preview

The included `ride_booking_ui.html` provides a visual demo with:
- Interactive city map with clickable nodes
- Shortest path highlighted in real time
- Live ride queue and driver panels
- Ride history log

---

## 👤 Author

**Jon Abbas Kazmi**  
BS Electrical Engineering  
COMSATS University Islamabad

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
