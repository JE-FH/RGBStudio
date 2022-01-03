#pragma once
#include "IEventSource.h"
#include <Windows.h>
#include <set>
#include <mutex>
#include <thread>

class KeyboardEventSource :
    public IEventSource
{
public:
    KeyboardEventSource();
    ~KeyboardEventSource();
    KeyboardEventSource(KeyboardEventSource&& other) noexcept;
    KeyboardEventSource(const KeyboardEventSource& other) = delete;
    
    static void init();
    
    // Inherited via IEventSource
    virtual void poll_events(EventQueue& event_queue) override;
private:
    
    std::mutex queued_events_mutex;
    /// <summary>
    /// Lock queued_events_mutex before accessing
    /// </summary>
    std::queue<std::unique_ptr<Event>> queued_events;


    //These functions will only be called from the event loop thread
    void on_key_down(unsigned long code, unsigned char scancode);
    void on_key_repeat(unsigned long code, unsigned char scancode);
    void on_key_up(unsigned long code, unsigned char scancode);

    /// <summary>
    /// Set of all vk pressed right now
    /// </summary>
    static std::set<DWORD> pressed_keys;
    static std::set<KeyboardEventSource*> _keyboard_hooks;
    //this functions will only be called from the event loop thread
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    static void win32_event_loop();
    static std::thread event_loop_thread;
    static bool inited;
};

