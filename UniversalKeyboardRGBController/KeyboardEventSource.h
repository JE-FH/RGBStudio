#pragma once
#include "IEventSource.h"
#include <Windows.h>
#include <set>

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
    
    std::queue<std::unique_ptr<Event>> queued_events;

    void on_key_down(unsigned short code);
    void on_key_up(unsigned short code);

    static std::set<KeyboardEventSource*> _keyboard_hooks;
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

