#include <iostream>
#include "webui.hpp"
#include "ScannerManager.hpp"
#include "MemScanner.hpp"
#include "ScanResVisitor.hpp"

#include <thread>
#include <chrono>
#include <atomic>

std::atomic<bool> running{true};

void scan_thread_func(webui::window* win_ptr)
{
    ScannerManager manager;
    manager.scan();     // zero scan for stability
    while(running)
    {
        auto update = manager.scan().dump();
        if (win_ptr->is_shown())
            win_ptr->run("updateUI('" + update + "');");
        else
            continue;
        std::cout<<"Sent: " << update<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    webui::window main_window;
    std::thread updater(scan_thread_func, &main_window);
    main_window.set_root_folder("public");
    main_window.show("index.html");
    webui::wait();
    running = false;
    updater.join();
    return 0;
}
