#include <utility>

#include "menu/MenuItem.hpp"

MenuItem::MenuItem(std::string text, std::function<void()> action, bool exitAfterExecution) {
    this->text = std::move(text);
    this->action = std::move(action);
    this->exitAfterExecution = exitAfterExecution;
}

MenuItem::MenuItem(std::string text, std::function<bool()> action, bool exitAfterExecution) {
    this->text = std::move(text);
    this->action = std::move(action);
    this->exitAfterExecution = exitAfterExecution;
}

void MenuItem::setAction(std::function<void()> newAction) {
    action = std::move(newAction);
}

void MenuItem::execute() const {
    action();
}

void MenuItem::setText(std::string newText) {
    text = std::move(newText);
}

const std::string &MenuItem::getText() const {
    return text;
}

bool MenuItem::getExitAfterExecution() const {
    return exitAfterExecution;
}