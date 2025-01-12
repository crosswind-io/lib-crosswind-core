/***************************************************************************************************************************
 * Project:     Crosswind Framework
 * Author:      Kory Herzinger
 * 
 * File:        EventBroker.h
 * Description: Declare the EventBroker service.
 * Date:        04/26/2024
 **************************************************************************************************************************/

#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_EVENT_BROKER)

  #include "Crosswind/Core/CircularQueue/CircularQueue.h"
  #include "Crosswind/Core/Service/Service.h"

  #include "EventBrokerQueueFullException.h"
  #include "EventData.h"
  #include "EventTopic.h"

  #include <functional>
  #include <map>
  #include <mutex>
  #include <string>
  #include <vector>

  typedef std::function<void(EventData*)> EventHandler;

  class EventBroker final : public Service {

    public:
      static const std::string SERVICE_NAME;

    public:
      EventBroker() = default;
      virtual ~EventBroker() = default;

      virtual std::string name() {
        return SERVICE_NAME;
      }

      virtual void init();
      virtual void loop();

    public:
      EventTopic registerTopic(const std::string& topic_name);

      template<typename T>
      void registerEvent() {
        if (sizeof(T) > maxEventSize) {
          maxEventSize = sizeof(T);
        }
      }

      EventTopic findTopic(const std::string& topic_name);

      void subscribe(EventTopic topic, EventHandler handler);
      void subscribe(const std::string& topic_name, EventHandler handler);

      void publish(EventTopic topic, std::function<void(void*)> provider);

    private:
      static const size_t MAX_EVENT_QUEUE_SIZE = 16;

      struct Event {
        EventTopic topic = 0;
        uint8_t* data = nullptr;
      };

    private:
      std::map<std::string, EventTopic> topicMap;
      EventTopic nextEventTopic = 1;
      std::recursive_mutex topicMapMutex;

      CircularQueue<Event, MAX_EVENT_QUEUE_SIZE> eventQueue;
      size_t maxEventSize = sizeof(uint32_t);
      std::recursive_mutex eventQueueMutex;

      std::map<EventTopic, std::vector<EventHandler>*> eventSubscriptions;
      std::mutex eventSubscriptionMutex;

    private:
      static EventBroker* eventBrokerService;

  };

#endif // SERVICE_EVENT_BROKER
