#pragma once
#include "_Banana.h"

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define BIND_BUTTON_EVENT_FN(x) std::bind(&x, this)

namespace Banana
{
  enum class EventType
  {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped, 
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
    GameObjectEvent, GameObjectPressed, GameObjectReleased, GameObjectHoverBegin, GameObjectHoverEnd
  };

  enum EventCategory
  {
    None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyBoard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
		EventCategoryGame			= BIT(5),
		EventCategoryGameObject		= BIT(6)
  };

// this is epic
#define EVENT_CLASS_TYPE(type) static EventType GetStaticEventType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticEventType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

  class Event
  {
    friend class EventDispatcher;
  public:
    virtual ~Event();

    virtual EventType GetEventType() const = 0;
    
    virtual const char* GetName() const = 0;
    
    virtual int GetCategoryFlags() const = 0;
    
    virtual std::string ToString() const { return GetName(); } 

    inline bool IsInCategory(const EventCategory category) const
    {
      return GetCategoryFlags() & category;
    }

    bool handled = false;

  };

  class EventDispatcher
  {
  private:
    Event& event;
  public:
    EventDispatcher(Event& event)
    : event(event){}

    template<typename T>
    bool dispatch(std::function<bool(T&)>)
    {
      if(event.GetEventType() == T::GetStaticEventType)
      {
        event.handled = func(*static_cast<T*>(&event));
      }
    }

  };

  // debugging abbreviation
  inline std::ostream& operator<<(std::ostream& os, const Event& event)
  {
    return os << event.ToString();
  }
  using EventCallbackFunction = std::function<void(Event&)>;

};