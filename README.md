# Display-Radar-SFML-

🟢 SFML Radar Visualization

This is a simple radar visualization system built with C++, SFML, and Boost.Asio. It reads angle and distance data from a serial port (e.g., from an Arduino with a servo + ultrasonic sensor) and visualizes the detected objects on a 2D radar-like interface.

🚀 Features

-Reads serial data in real-time (format: angle,distance\n)
-Converts polar coordinates to Cartesian for display
-Visually sweeps and marks detected objects on a radar
-Displays a radar line that follows the scanning angle
-Fades/clears detections after a full sweep (180°)

🧰 Technologies Used

-SFML – for 2D graphics and rendering
-Boost.Asio – for serial communication
-Standard C++ STL

🔧 Setup
Requirements

-A working C++ compiler (e.g. g++)
-CMake (recommended)
-SFML library
-Boost library (Asio module)
-A serial device that sends angle,distance\n (e.g., Arduino)

Building

You can build the project using CMake:

`mkdir build
cd build
cmake ..
make`

`Alternatively, compile manually:

g++ main.cpp -o radar -lsfml-graphics -lsfml-window -lsfml-system -lboost_system

Run

./radar`

⚠️ Don't forget to change the serial port in the code:

`serial_port serial(io, "COM8"); // <-- Set this to match your device`

🧪 Example Arduino Output

The radar expects serial data in this format:

`45,120
46,118
...`

You can simulate this with a simple Arduino sketch using a servo and distance sensor (e.g., HC-SR04), rotating between 0° and 180°.

📄 License

This project is open-source and available under the MIT License.
