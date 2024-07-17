#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <functional>

class MenuItem {
private:
    std::string text;
    std::function<void()> action;
    bool exitAfterExecution = false;
public:
    MenuItem(std::string text, std::function<void()> action, bool exitAfterExecution = false);

    MenuItem(std::string text, std::function<bool()> action, bool exitAfterExecution = false);

    void setAction(std::function<void()> newAction);

    void execute() const;

    void setText(std::string newText);

    [[nodiscard]] const std::string& getText() const;

    bool getExitAfterExecution() const;
};