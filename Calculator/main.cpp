#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <stack>
#include <queue>
#include <cctype>
#include <cmath>

class Calculator {
public:
    Calculator() {
        // Initialize the window
        window.create(sf::VideoMode(400, 600), "Calculator");

        // Load icon
        sf::Image icon;
        if (!icon.loadFromFile("icon/C-icon.png")) {
            std::cerr << "Failed to load icon 'iconok.png'" << std::endl;
            exit(EXIT_FAILURE);
        }
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        // Load font
        if (!font.loadFromFile("fonts/Roboto-Light.ttf")) {
            std::cerr << "Failed to load font 'Roboto-Light.ttf'" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Initialize display
        display.setFont(font);
        display.setCharacterSize(30);
        display.setFillColor(sf::Color::White);
        display.setPosition(20, 20);
        updateDisplay();

        // Initialize buttons
        initButtons();
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text display;
    sf::RectangleShape displayBox;
    std::string currentInput;
    bool resetInput = false;

    struct Button {
        sf::RectangleShape shape;
        sf::Text text;
    };

    std::vector<Button> buttons;

    void initButtons() {
        std::vector<std::string> labels = {
            "7", "8", "9", "/", 
            "4", "5", "6", "*", 
            "1", "2", "3", "-", 
            "0", ".", "=", "+",
            "C"
        };

        float buttonWidth = 80;
        float buttonHeight = 80;
        float startX = 10;
        float startY = 100;
        float padding = 10;

        for (int i = 0; i < labels.size(); ++i) {
            Button button;
            button.shape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
            button.shape.setFillColor(sf::Color::Blue);
            button.shape.setPosition(startX + (i % 4) * (buttonWidth + padding), startY + (i / 4) * (buttonHeight + padding));
            button.shape.setOutlineThickness(2);
            button.shape.setOutlineColor(sf::Color::White);

            button.text.setFont(font);
            button.text.setString(labels[i]);
            button.text.setCharacterSize(30);
            button.text.setFillColor(sf::Color::White);
            button.text.setPosition(button.shape.getPosition().x + 30, button.shape.getPosition().y + 20);

            buttons.push_back(button);
        }

        // Initialize display box
        displayBox.setSize(sf::Vector2f(360, 50));
        displayBox.setFillColor(sf::Color::Black);
        displayBox.setOutlineThickness(2);
        displayBox.setOutlineColor(sf::Color::White);
        displayBox.setPosition(20, 20);
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }

    void handleMouseClick(int x, int y) {
        for (const auto& button : buttons) {
            if (button.shape.getGlobalBounds().contains(x, y)) {
                std::string label = button.text.getString();
                if (label == "=") {
                    calculateResult();
                } else if (label == "C") {
                    clearInput();
                } else {
                    appendInput(label);
                }
                break;
            }
        }
    }

    void appendInput(const std::string& input) {
        if (resetInput) {
            currentInput.clear();
            resetInput = false;
        }
        currentInput += input;
        updateDisplay();
    }

    void calculateResult() {
        if (!currentInput.empty()) {
            try {
                double result = evaluateExpression(currentInput);
                currentInput = std::to_string(result);
            } catch (const std::exception& e) {
                currentInput = "Error";
            }
            resetInput = true;
            updateDisplay();
        }
    }

    void clearInput() {
        currentInput.clear();
        resetInput = false;
        updateDisplay();
    }

    void updateDisplay() {
        display.setString(currentInput);
    }

    void render() {
        window.clear();

        window.draw(displayBox);

        window.draw(display);

        for (const auto& button : buttons) {
            window.draw(button.shape);
            window.draw(button.text);
        }

        window.display();
    }

    int getPrecedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    double applyOperation(double a, double b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            default: throw std::invalid_argument("Invalid operator");
        }
    }

    double evaluateExpression(const std::string& expression) {
        std::stack<double> values;
        std::stack<char> ops;

        for (std::size_t i = 0; i < expression.length(); i++) {
            if (std::isspace(expression[i])) continue;

            if (std::isdigit(expression[i])) {
                double value = 0;
                while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.')) {
                    if (expression[i] == '.') {
                        i++;
                        double decimalPlace = 0.1;
                        while (i < expression.length() && std::isdigit(expression[i])) {
                            value += (expression[i] - '0') * decimalPlace;
                            decimalPlace *= 0.1;
                            i++;
                        }
                    } else {
                        value = (value * 10) + (expression[i] - '0');
                        i++;
                    }
                }
                values.push(value);
                i--;
            } else {
                while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(expression[i])) {
                    double b = values.top(); values.pop();
                    double a = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOperation(a, b, op));
                }
                ops.push(expression[i]);
            }
        }

        while (!ops.empty()) {
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            char op = ops.top(); ops.pop();
            values.push(applyOperation(a, b, op));
        }

        return values.top();
    }
};

int main() {
    Calculator calculator;
    calculator.run();
    return 0;
}