#ifndef __FILESYSTEM_UTILS_HPP__
#define __FILESYSTEM_UTILS_HPP__

#ifdef __unix__
#define USING_LINUX
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define USING_WINDOWS
#else
#error Only Windows and Linux are supported.
#endif

#ifdef USING_LINUX
#error Linux not yet supported.
#endif

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#ifdef USING_WINDOWS
#include <Windows.h>
#include "../../lib/windows/dirent.h"
#else
#include <dirent.h>
#endif

namespace efs {
namespace util {

#ifdef USING_WINDOWS

static std::wstring s2ws(const std::string &s) {
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t *buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

static std::string DWORDToString(DWORD dword) {
    std::stringstream s;
    s << dword;
    return s.str();
}

#endif

/**
 * This function is useful to know if a given path is either a folder, directory
 * or none (?) return 1 if it's a folder, -1 if it's a file, 0 if none or -2 on
 * error
 **/
int FolderOrFile(std::string path) {
    struct stat s;
    const char *c_path = path.c_str();
    if (stat(c_path, &s) == 0)
        if (s.st_mode & S_IFDIR)
            return 1;  // It's folder
        else if (s.st_mode & S_IFREG)
            return -1;  // It's file
        else
            return 0;
    else
        return -2;
}

/**
 * Scan a given directory and save all the files and folders on each argument
 **/
int GetDirectoryContent(std::string dir, std::vector<std::string> &files,
                        std::vector<std::string> &folders) {
    DIR *dp;
    struct dirent *dirp;

    if ((dp = opendir(dir.c_str())) == NULL) {
        std::cerr << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        std::string fdname = dir + "/" + std::string(dirp->d_name);
        std::string dname = std::string(dirp->d_name);
        if (dname != "." && dname != "..") {
            int r = FolderOrFile(fdname);
            if (r == 1)
                folders.push_back(fdname);
            else if (r == -1)
                files.push_back(fdname);
        }
    }

    closedir(dp);
    return 0;
}

std::string GetDirectoryFullPath(std::string name) {
    const char *filename = name.c_str();
    char fullFilename[MAX_PATH];

#ifdef USING_WINDOWS
    DWORD dword = GetFullPathNameA(filename, MAX_PATH, fullFilename, nullptr);
    return DWORDToString(dword);
#elif defined(USING_LINUX)
    // TODO: write Linux version
#endif

}

void RenameDirectory(std::string path, std::string newPath) {
    rename(newPath.c_str(), path.c_str());
}

void RemoveDirectory(std::string path) {
    remove(path.c_str());
}

void SetDirectoryHidden(std::string path, bool b) {
    if (b) {

#ifdef USING_WINDOWS
        SetFileAttributesA(path.c_str(), FILE_ATTRIBUTE_HIDDEN);
#elif defined(USING_LINUX)
        // TODO: implement Linux version
#endif
        
    } else {

#ifdef USING_WINDOWS
        SetFileAttributesA(path.c_str(), FILE_ATTRIBUTE_NORMAL);
#elif defined(USING_LINUX)
        // TODO: implement Linux version
#endif

    }
}

}  // namespace util
}  // namespace efs

#endif  // __FILESYSTEM_UTILS_HPP