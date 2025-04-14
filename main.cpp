#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <boost/asio.hpp>
#include <iostream>
#include <sstream>

using namespace boost::asio;

const float RADAR_RADIUS = 200.f;  // Max scanning distance
const sf::Vector2f RADAR_CENTER(400.f, 300.f); // Radar center position
const float PI = 3.14159265358979323846;

struct DetectedObject {
    sf::CircleShape dot;
    float angle;
    float distance;
};


std::vector<DetectedObject> objects;

void displayValues(double, double, sf::RenderWindow&){}

int main() {


    io_context io;
    serial_port serial(io, "COM8"); // Change to your port (Windows: "COM3")
    
    serial.set_option(serial_port_base::baud_rate(115200));

    std::string line;


    sf::RenderWindow window(sf::VideoMode(800, 600), "Radar System");
    sf::VertexArray radarLine(sf::Lines, 2);
    radarLine[0].position = RADAR_CENTER;
    radarLine[0].color = sf::Color::Green;
    std::vector<DetectedObject> objects;


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        char c;
        read(serial, buffer(&c, 1));  // Read one character at a time

        if (c == '\n') {  // Full line received
            std::stringstream ss(line);
            float angle, distance;
            char comma;
            ss >> angle >> comma >> distance;
            
        



            // Convert angle to radians
        float rad = (angle+180) * PI / 180.0f;

        if (distance>RADAR_RADIUS){
            distance = RADAR_RADIUS*25;
        }

        // Calculate (x, y) coordinates
        float x = RADAR_CENTER.x + (distance*2.4) * std::cos(rad);
        float y = RADAR_CENTER.y + (distance*2.4) * std::sin(rad);

        // Create detected object
        DetectedObject obj;
        obj.dot.setRadius(2.f);
        obj.dot.setFillColor(sf::Color::Red);
        obj.dot.setPosition(x, y);
        obj.angle = angle;
        obj.distance = distance;

        // Update radar line position
        radarLine[1].position = sf::Vector2f(
            RADAR_CENTER.x + RADAR_RADIUS * std::cos(rad),
            RADAR_CENTER.y + RADAR_RADIUS * std::sin(rad)
        );
        radarLine[1].color = sf::Color::Green;


        if (angle >= 180) {
            objects.clear();
         } // Reset angle after full sweep


         objects.push_back(obj);



        // Drawing
        window.clear();
        
        // Draw radar background
        sf::CircleShape radarCircle(RADAR_RADIUS);
        radarCircle.setFillColor(sf::Color(0, 255, 0, 50)); // Transparent green
        radarCircle.setOrigin(RADAR_RADIUS, RADAR_RADIUS);
        radarCircle.setPosition(RADAR_CENTER);
        window.draw(radarCircle);

        // Draw radar line
        window.draw(radarLine);

        // Draw detected objects
        for (const auto& obj : objects)
            window.draw(obj.dot);

        window.display();

            








            line.clear();
        } else {
            line += c;
        }
    }



    /*sf::RenderWindow window(sf::VideoMode(800, 600), "Radar System");

    sf::VertexArray radarLine(sf::Lines, 2);
    radarLine[0].position = RADAR_CENTER;
    radarLine[0].color = sf::Color::Green;

    std::vector<DetectedObject> objects;

    float angle = 0; // Start scanning from 0 degrees

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Simulate new detection data
        float distance = static_cast<float>(rand() % static_cast<int>(RADAR_RADIUS)); // Random distance

        // Convert angle to radians
        float rad = angle * PI / 180.0f;

        // Calculate (x, y) coordinates
        float x = RADAR_CENTER.x + distance * std::cos(rad);
        float y = RADAR_CENTER.y + distance * std::sin(rad);

        // Create detected object
        DetectedObject obj;
        obj.dot.setRadius(2.f);
        obj.dot.setFillColor(sf::Color::Red);
        obj.dot.setPosition(x, y);
        obj.angle = angle;
        obj.distance = distance;

        // Update radar line position
        radarLine[1].position = sf::Vector2f(
            RADAR_CENTER.x + RADAR_RADIUS * std::cos(rad),
            RADAR_CENTER.y + RADAR_RADIUS * std::sin(rad)
        );
        radarLine[1].color = sf::Color::Green;

        angle += 1; // Move radar by 5 degrees each frame
        if (angle >= 360) {
            angle = 0;
            objects.clear();
         } // Reset angle after full sweep


         objects.push_back(obj);



        // Drawing
        window.clear();
        
        // Draw radar background
        sf::CircleShape radarCircle(RADAR_RADIUS);
        radarCircle.setFillColor(sf::Color(0, 255, 0, 50)); // Transparent green
        radarCircle.setOrigin(RADAR_RADIUS, RADAR_RADIUS);
        radarCircle.setPosition(RADAR_CENTER);
        window.draw(radarCircle);

        // Draw radar line
        window.draw(radarLine);

        // Draw detected objects
        for (const auto& obj : objects)
            window.draw(obj.dot);

        window.display();
    }*/

    return 0;
}


void displayValues(float angle, float distance, sf::RenderWindow& window ){

    sf::VertexArray radarLine(sf::Lines, 2);
    radarLine[0].position = RADAR_CENTER;
    radarLine[0].color = sf::Color::Green;

    // Convert angle to radians
    float rad = angle * PI / 180.0f;

    // Calculate (x, y) coordinates
    float x = RADAR_CENTER.x + distance * std::cos(rad);
    float y = RADAR_CENTER.y + distance * std::sin(rad);

    // Create detected object
    DetectedObject obj;
    obj.dot.setRadius(2.f);
    obj.dot.setFillColor(sf::Color::Red);
    obj.dot.setPosition(x, y);
    obj.angle = angle;
    obj.distance = distance;

    // Update radar line position
    radarLine[1].position = sf::Vector2f(
        RADAR_CENTER.x + RADAR_RADIUS * std::cos(rad),
        RADAR_CENTER.y + RADAR_RADIUS * std::sin(rad)
    );
    radarLine[1].color = sf::Color::Green;

    angle += 1; // Move radar by 5 degrees each frame
    if (angle >= 180 || angle <= 0) {
        objects.clear();
        } // Reset angle after full sweep


        objects.push_back(obj);



    // Drawing
    window.clear();
    
    // Draw radar background
    sf::CircleShape radarCircle(RADAR_RADIUS);
    radarCircle.setFillColor(sf::Color(0, 255, 0, 50)); // Transparent green
    radarCircle.setOrigin(RADAR_RADIUS, RADAR_RADIUS);
    radarCircle.setPosition(RADAR_CENTER);
    window.draw(radarCircle);

    // Draw radar line
    window.draw(radarLine);

    // Draw detected objects
    for (const auto& obj : objects)
        window.draw(obj.dot);

    window.display();


        
}
