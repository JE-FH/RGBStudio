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

    void on_key_down(unsigned long code, unsigned char scancode);
    void on_key_repeat(unsigned long code, unsigned char scancode);
    void on_key_up(unsigned long code, unsigned char scancode);

    /// <summary>
    /// Set of all vk pressed right now
    /// </summary>
    static std::set<DWORD> pressed_keys;
    static std::set<KeyboardEventSource*> _keyboard_hooks;
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

