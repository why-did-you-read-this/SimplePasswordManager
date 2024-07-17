#pragma once

#include "credentials/Credentials.hpp"

void showAboutProgram();

void getGeneratedPassword();

void createSPMFile(Credentials &credentials);

void openSPMFile(Credentials &credentials);

void findPasswordByName(Credentials &credentials);

void addPassword(Credentials &credentials);

void editPassword(Credentials &credentials);

void deletePassword(Credentials &credentials);

