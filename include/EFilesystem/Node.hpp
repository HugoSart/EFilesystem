#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <iostream>
#include <vector>
#include "FilesystemUtils.hpp"

using namespace std;

namespace efs {

class Folder;

class Node {
   public:
    Node(std::string path) : path(path) {}
    ~Node() {}

    std::string GetName() {
        const char *cstr = path.c_str();
        for (int i = path.length() - 1; i >= 0; i--) {
            if (cstr[i] == '/' || cstr[i] == '\\')
                return path.substr(i + 1, path.length());
        }
        return path;
    }

    std::string GetPath() {
        return path;
    }

    std::string GetFullPath() {
        return util::GetDirectoryFullPath(this->path);
    }

    void MoveTo(Folder &folder) {}

    void Rename(std::string newName) {
        util::RenameDirectory(newName, path);
        this->path = newName;
    }

    void Delete() {
        util::RemoveDirectory(path);
        delete this;
    }

    void SetHidden(bool b) { util::SetDirectoryHidden(path, b); }
    bool IsHidden() { return false; }

   private:
    std::string path;

};

class File : public Node {
   public:
    File(std::string path) : Node(path) {}
    ~File() {}
};

class Folder : public Node {
   public:
    Folder(std::string path) : Node(path) {}
    ~Folder() {}

    std::vector<Node> GetChildNodes() {
        std::vector<std::string> filePaths = std::vector<std::string>();
        std::vector<std::string> folderPaths = std::vector<std::string>();
        std::vector<Node> nodes = std::vector<Node>();
        util::GetDirectoryContent(this->GetName(), filePaths, folderPaths);
        for (auto &path : filePaths) nodes.push_back(File(path));
        for (auto &path : folderPaths) nodes.push_back(Folder(path));
        return nodes;
    }

    std::vector<File> GetChildFiles() {
        std::vector<std::string> filePaths = std::vector<std::string>(),
                                 folderPaths = std::vector<std::string>();
        std::vector<File> files = std::vector<File>();
        util::GetDirectoryContent(this->GetName(), filePaths, folderPaths);
        for (auto &path : filePaths) files.push_back(File(path));
        return files;
    }

    std::vector<Folder> GetChildFolders() {
        std::vector<std::string> filePaths = std::vector<std::string>(),
                                 folderPaths = std::vector<std::string>();
        std::vector<Folder> folders = std::vector<Folder>();
        util::GetDirectoryContent(this->GetName(), filePaths, folderPaths);
        for (auto &path : folderPaths) folders.push_back(Folder(path));
        return folders;
    }
};

}  // namespace efs

#endif
