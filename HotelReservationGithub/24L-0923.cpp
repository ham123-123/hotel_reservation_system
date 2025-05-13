// Hotel Reservation System using C++ and SFML (Simple Graphics Version without vector)
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

const int MAX_USERS = 10;
const int MAX_ROOMS = 5;
const int MAX_RESERVATIONS = 10;

class User {
public:
    string username, password;
    User() : username(""), password("") {}
    User(string u, string p) : username(u), password(p) {}
};

class Room {
public:
    int roomNumber;
    bool isBooked;
    Room() : roomNumber(0), isBooked(false) {}
    Room(int num) : roomNumber(num), isBooked(false) {}
};

class Reservation {
public:
    string username;
    int roomNumber;
    Reservation() : username(""), roomNumber(0) {}
    Reservation(string u, int r) : username(u), roomNumber(r) {}
};

class HotelSystem {
    User users[MAX_USERS];
    Room rooms[MAX_ROOMS];
    Reservation reservations[MAX_RESERVATIONS];
    int userCount = 0;
    int reservationCount = 0;
    string currentUser;

public:
    HotelSystem() {
        for (int i = 0; i < MAX_ROOMS; i++) {
            rooms[i] = Room(i + 1);
        }
    }

    bool registerUser(string u, string p) {
        if (userCount >= MAX_USERS) return false;
        users[userCount++] = User(u, p);
        return true;
    }

    bool loginUser(string u, string p) {
        for (int i = 0; i < userCount; i++) {
            if (users[i].username == u && users[i].password == p) {
                currentUser = u;
                return true;
            }
        }
        return false;
    }

    void viewRooms() {
        cout << "\nAvailable Rooms:\n";
        for (int i = 0; i < MAX_ROOMS; i++) {
            cout << "Room " << rooms[i].roomNumber << " - " << (rooms[i].isBooked ? "Booked" : "Available") << endl;
        }
    }

    bool bookRoom(int num) {
        if (reservationCount >= MAX_RESERVATIONS) return false;
        for (int i = 0; i < MAX_ROOMS; i++) {
            if (rooms[i].roomNumber == num && !rooms[i].isBooked) {
                rooms[i].isBooked = true;
                reservations[reservationCount++] = Reservation(currentUser, num);
                return true;
            }
        }
        return false;
    }

    bool cancelReservation(int num) {
        for (int i = 0; i < reservationCount; i++) {
            if (reservations[i].username == currentUser && reservations[i].roomNumber == num) {
                for (int j = i; j < reservationCount - 1; j++) {
                    reservations[j] = reservations[j + 1];
                }
                reservationCount--;
                for (int k = 0; k < MAX_ROOMS; k++) {
                    if (rooms[k].roomNumber == num) rooms[k].isBooked = false;
                }
                return true;
            }
        }
        return false;
    }
};

void drawMenu(sf::RenderWindow& window, sf::Font& font, const string options[], int size, int selected) {
    window.clear(sf::Color::White);
    for (int i = 0; i < size; ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(24);
        text.setFillColor(i == selected ? sf::Color::Blue : sf::Color::Black);
        text.setPosition(100, 100 + i * 40);
        window.draw(text);
    }
    window.display();
}

int main() {
    HotelSystem system;

    sf::RenderWindow window(sf::VideoMode(600, 400), "Hotel Reservation System");
    sf::Font font;
    font.loadFromFile("Hello Valentina.ttf");

    string menu[] = { "Register", "Login", "View Rooms", "Book Room", "Cancel Reservation", "Exit" };
    const int menuSize = 6;
    int selected = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) selected = (selected + menuSize - 1) % menuSize;
                if (event.key.code == sf::Keyboard::Down) selected = (selected + 1) % menuSize;
                if (event.key.code == sf::Keyboard::Enter) {
                    switch (selected) {
                    case 0: {
                        string u, p;
                        cout << "Enter username: "; cin >> u;
                        cout << "Enter password: "; cin >> p;
                        system.registerUser(u, p);
                        break;
                    }
                    case 1: {
                        string u, p;
                        cout << "Username: "; cin >> u;
                        cout << "Password: "; cin >> p;
                        if (system.loginUser(u, p))
                            cout << "Login successful!\n";
                        else
                            cout << "Login failed.\n";
                        break;
                    }
                    case 2:
                        system.viewRooms();
                        break;
                    case 3: {
                        int room;
                        cout << "Enter room number to book: "; cin >> room;
                        if (system.bookRoom(room))
                            cout << "Room booked!\n";
                        else
                            cout << "Booking failed.\n";
                        break;
                    }
                    case 4: {
                        int room;
                        cout << "Enter room number to cancel: "; cin >> room;
                        if (system.cancelReservation(room))
                            cout << "Reservation cancelled.\n";
                        else
                            cout << "Cancellation failed.\n";
                        break;
                    }
                    case 5:
                        window.close();
                        break;
                    }
                }
            }
        }
        drawMenu(window, font, menu, menuSize, selected);
    }
    return 0;
}
