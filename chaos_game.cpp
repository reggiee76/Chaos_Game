#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // Set up the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chaos Game - Sierpinski Triangle");

    // Create a vector to store the vertices of the triangle
    vector<sf::Vector2f> vertices;

    // Display a message to the user asking them to click on three points to create the triangle
    sf::Font font;
    if (!font.loadFromFile("Orbitron.ttf"))
    {
        cout << "Font failed to load" << endl;
    }

    sf::Text message;
    message.setFont(font);
    message.setString("Click on three points to create the triangle");
    message.setCharacterSize(24);
    message.setFillColor(sf::Color::White);
    message.setPosition(10.f, 10.f);

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

                cout << "got it" << endl; // REMOVE LATER*****
            }
        }
        window.clear(sf::Color::Black);
        window.draw(message);
        window.display();
    }

    // DEBUGGING ***REMOVE LATER****
    for (int i = 0; i < vertices.size(); i++) {
        std::cout << "Vertex " << i << ": " << vertices[i].x << ", " << vertices[i].y << std::endl;
    }


    // Display a message to the user asking them to click on a fourth point to start the algorithm
    sf::Text startMessage;
    startMessage.setFont(font);
    startMessage.setString("Click on a fourth point to start the algorithm");
    startMessage.setCharacterSize(24);
    startMessage.setFillColor(sf::Color::Yellow);
    startMessage.setPosition(10.f, 50.f);

    // Use the Chaos Game algorithm to draw the Sierpinski Triangle
    sf::RectangleShape point(sf::Vector2f(1.f, 1.f));
    point.setFillColor(sf::Color::Yellow);
    sf::Vector2f currentPosition(sf::Mouse::getPosition(window));

    int pointCount = 0;
    while (window.isOpen())
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
                cout << "point recieved" << endl; //****remove later ****
                currentPosition = sf::Vector2f(sf::Mouse::getPosition(window));
            }
        }

        if (pointCount < 10000)
        {
            // Generate a random number between 0 and 2
            int randomIndex = rand() % 3;

            // Calculate the midpoint between the current position and the vertex
            sf::Vector2f midpoint((currentPosition.x + vertices[randomIndex].x) / 2.f, (currentPosition.y + vertices[randomIndex].y) / 2.f);

            // Update the current position
            currentPosition = midpoint;

            // Draw the point
            point.setPosition(midpoint);
            window.draw(point);

            pointCount++;
        }

        window.clear(sf::Color::Black);
        window.draw(startMessage);
        window.display();
    }

    return 0;
}
