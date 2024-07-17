#include <utility>

#include "menu/Menu.hpp"

void Menu::addItem(const MenuItem &item) {
    items.push_back(item);
}

void Menu::display() const {
    std::cout << std::endl << title << std::endl;
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". " << items[i].getText() << std::endl;
    }
    std::cout << items.size() + 1 << ". " << exitItem.getText() << std::endl << std::endl;
    std::cout << "Enter menu item:" << std::endl;
}

void Menu::setExitMessage(std::string newMessage) {
    exitItem.setText(std::move(newMessage));
}

void Menu::setExitAction(std::function<void()> action) {
    exitItem.setAction(std::move(action));
}


void Menu::setTitle(std::string newTitle) {
    title = std::move(newTitle);
}


void Menu::run() {
    unsigned int choice;
    bool running = true;

    while (running) {
        display();
        std::cin >> choice;
        std::cout << std::endl;
        if (choice > 0 && choice <= items.size()) {
            items[choice - 1].execute();
            if (items[choice-1].getExitAfterExecution()) {
                running = false;
            }
        } else if (choice == items.size() + 1) {
            running = false;
            exitItem.execute();
        } else {
            std::cout << "An incorrect command was entered" << std::endl;
        }
    }
}

Menu::Menu() : exitItem("Exit", [] { return; }) {}