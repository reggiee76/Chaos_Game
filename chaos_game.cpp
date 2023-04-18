#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chaos Game - Sierpinski Triangle");
    const int MAX_POINT = 10000;
    vector<sf::Vector2f> vertices;
    sf::VertexArray point(sf::Points, MAX_POINT);
    sf::Font font;
    if (!font.loadFromFile("font/Roboto-Light.ttf"))
    {
        cout << "Font failed to load" << endl;
    }

    sf::Text message;
    message.setFont(font);
    message.setString("Click on three points to create the triangle");
    message.setCharacterSize(24);
    message.setFillColor(sf::Color::White);
    message.setPosition(10.f, 10.f);

    window.draw(message);
        window.display();

    // Handle mouse click events to assign coordinates to the vertices
    int vertexCount = 0;
    while (vertexCount < 3)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f clickPosition(sf::Mouse::getPosition(window));
                vertices.push_back(clickPosition);
                vertexCount++;

                // #TODO: Change to bigger point.
//                sf::VertexArray point(sf::Points, 1);
                point[0] = clickPosition;
                window.draw(point);
                window.display();
            }
        }

    }
    window.clear(sf::Color::Black);

    sf::VertexArray triangle(sf::LineStrip, 4);

    // DEBUGGING ***REMOVE LATER****
    for (int i = 0; i < vertices.size(); i++) {
        std::cout << "Vertex " << i << ": " << vertices[i].x << ", " << vertices[i].y << std::endl;
        triangle[i].position = vertices[i];
    }
    triangle[3].position = vertices[0];
    window.draw(triangle);

    // Display a message to the user asking them to click on a fourth point to start the algorithm

    message.setString("Click on a fourth point to start the algorithm");

    message.setFillColor(sf::Color::Yellow);
    window.draw(message);
    window.display();
    // Use the Chaos Game algorithm to draw the Sierpinski Triangle

    sf::Vector2f algV;
    vertexCount = 0;
    while (vertexCount < 1) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f clickPosition(sf::Mouse::getPosition(window));
//                vertices.push_back(clickPosition);
                algV = clickPosition;
                vertexCount++;
            }
        }
    }


// #TODO: Change to bigger point.

//    point[0] = algV;
//    window.draw(point);
//    window.display();

    int pointCount = 0;

//    vector<sf::Vector2f> v2;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (pointCount < MAX_POINT)
        {
            int randomIndex = rand() % 3;
            sf::Vector2f midpoint((algV.x + vertices[randomIndex].x) / 2.f, (algV.y + vertices[randomIndex].y) / 2.f);

            algV = midpoint;

            point[pointCount] = algV;
            window.clear();
            window.draw(point);
//            window.draw(message);
            window.draw(triangle);
            window.display();

            pointCount++;
        }
    }

    return 0;
}
