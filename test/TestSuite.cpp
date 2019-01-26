#include <iostream>
#include <errno.h>
#include "../include/EFilesystem/EFilesystem.hpp"
#include "../lib/TestSuite.hpp"


using namespace std;
using namespace efs;

#define TEST_FOLDER_NAME std::string("TestFolder")

void TestName() {
    BEFORE()
    Folder folder = Folder(TEST_FOLDER_NAME);
    string name = folder.GetName();
    assert(name, TEST_FOLDER_NAME);
    AFTER()
}
void TestFullPath() {
    BEFORE()
    Folder folder = Folder(TEST_FOLDER_NAME);
    string fullPath = folder.GetFullPath();
    assert("zee", "fullPath");
    AFTER()
}

void TestChildFolders() {
    BEFORE()
    Folder folder = Folder(TEST_FOLDER_NAME);
    vector<Folder> folders = folder.GetChildFolders();
    assert(2, folders.size());
    AFTER()
}

int main() {
    TestName();
    TestFullPath();
    TestChildFolders();
    return 0;
}