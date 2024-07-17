#pragma once

#include "MenuItem.hpp"

class Menu {
private:
    std::vector<MenuItem> items;
    std::string title = "====== Menu ======";
    MenuItem exitItem;
public:
    Menu();

    void addItem(const MenuItem &item);

    void display() const;

    void run();

    void setTitle(std::string newTitle);

    void setExitMessage(std::string newMessage);

    void setExitAction(std::function<void()> action);
};
