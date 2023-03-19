#pragma once
#include "raylib.h"
#include <string>
#include <mutex>

class GamingWindow
{
public:
    static GamingWindow* getInstance()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if(!instance)
        {
            // height = 384;
            // width = 384;
            title = "Classy Clash!!";
            InitWindow(width,height,title.c_str());
        }
        return instance;
    }

    static const int height;
    static const int width;
private:
    GamingWindow(){};
    GamingWindow(GamingWindow &other){};
    GamingWindow operator=(GamingWindow &other);
    ~GamingWindow()
    {
        delete instance;
    }
    static std::mutex mutex_;

    static std::string title;
    static GamingWindow* instance;
};

GamingWindow* GamingWindow::instance = nullptr;
std::mutex GamingWindow::mutex_;
const int GamingWindow::height = 384;
const int GamingWindow::width = 384;;
std::string GamingWindow::title;