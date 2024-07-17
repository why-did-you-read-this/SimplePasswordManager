#include "menu/Menu.hpp"
#include "credentials/Credentials.hpp"
#include "main_interactions.hpp"


int main() {
    Credentials credentials;
    Menu pmMenu; // Password Manager Menu
    pmMenu.setTitle("====== Password Manager ======");
    pmMenu.setExitMessage("Save and return to main menu");
    pmMenu.setExitAction([&credentials] {credentials.saveToFile(); credentials.clear();});
    pmMenu.addItem(MenuItem("Show all passwords", [&credentials] { credentials.printAll();}));
    pmMenu.addItem(MenuItem("Find password", [&credentials] { findPasswordByName(credentials);}));
    pmMenu.addItem(MenuItem("Add password", [&credentials] { addPassword(credentials);}));
    pmMenu.addItem(MenuItem("Edit password", [&credentials] { editPassword(credentials);}));
    pmMenu.addItem(MenuItem("Delete password", [&credentials] { deletePassword(credentials);}));
    pmMenu.addItem(MenuItem("Delete file with passwords", [&credentials] { credentials.deleteFile();}, true));
    pmMenu.addItem(MenuItem("Save", [&credentials] { credentials.saveToFile();}));

    Menu mainMenu;
    mainMenu.setTitle("====== Main menu ======");
    mainMenu.addItem(MenuItem("Create file with passwords", [&credentials, &pmMenu] { createSPMFile(credentials); pmMenu.run();}));
    mainMenu.addItem(MenuItem("Open file with passwords", [&credentials, &pmMenu] { openSPMFile(credentials); pmMenu.run(); }));
    mainMenu.addItem(MenuItem("Generate a password", [] { getGeneratedPassword(); }));
    mainMenu.addItem(MenuItem("About the program", [] { showAboutProgram(); }));
    mainMenu.run();
    return 0;
}
