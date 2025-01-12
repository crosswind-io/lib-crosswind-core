#include "EventBroker.h"

#if defined(SERVICE_EVENT_BROKER)

const std::string EventBroker::SERVICE_NAME = "EventBroker";

void EventBroker::init() {
  std::lock_guard<std::recursive_mutex> lock(eventQueueMutex);
    
  for (size_t x = 0; x < MAX_EVENT_QUEUE_SIZE; x++) {
    auto event = eventQueue.enqueue();
    event->topic = 0;
    event->data = new uint8_t[maxEventSize];
  }
  for (size_t x = 0; x < MAX_EVENT_QUEUE_SIZE; x++) {
    eventQueue.dequeue();
  }
}

void EventBroker::loop() {
  std::lock_guard<std::recursive_mutex> lock(eventQueueMutex);

  while(eventQueue.size() > 0) {
    auto event = eventQueue.dequeue();
    {
      std::lock_guard<std::mutex> lock(eventSubscriptionMutex);

      auto subscriptions = eventSubscriptions.find(event.topic);
      if (subscriptions != eventSubscriptions.end()) {
        for (auto handler : *(subscriptions->second)) {
          if (handler != nullptr) {
            handler(reinterpret_cast<EventData*> (event.data));
          }
        }
      }
    }
  }
}

EventTopic EventBroker::registerTopic(const std::string& topic_name) {
  std::lock_guard<std::recursive_mutex> lock(topicMapMutex);

  auto topic = topicMap.find(topic_name);
  if (topic == topicMap.end()) {
    auto eventTopic = nextEventTopic;
    nextEventTopic++;

    topicMap.insert(std::pair<std::string, EventTopic> (topic_name, eventTopic));
    return eventTopic;
  } else {
    return topic->second;
  }
}

EventTopic EventBroker::findTopic(const std::string& topic_name) {
  std::lock_guard<std::recursive_mutex> lock(topicMapMutex);

  auto eventTopic = TOPIC_NONE;
  auto topic = topicMap.find(topic_name);
  if (topic != topicMap.end()) {
    eventTopic = topic->second;
  }

  return eventTopic;
}

void EventBroker::subscribe(EventTopic topic, EventHandler handler) {
  std::lock_guard<std::mutex> lock(eventSubscriptionMutex);

  auto subscription = eventSubscriptions.find(topic);
  if (subscription == eventSubscriptions.end()) {
    eventSubscriptions.insert(std::pair<EventTopic, std::vector<EventHandler>*> (topic, new std::vector<EventHandler>()));
  }

  subscription = eventSubscriptions.find(topic);
  subscription->second->push_back(handler);
}

void EventBroker::subscribe(const std::string& topic_name, EventHandler handler) {
  subscribe(findTopic(topic_name), handler);
}

void EventBroker::publish(EventTopic topic, std::function<void(void*)> provider) {
  std::lock_guard<std::recursive_mutex> lock (eventQueueMutex);

  try {
    auto event = eventQueue.enqueue();
    event->topic = topic;
    provider(event->data);
  } catch (const CircularQueueFullException& ex) {
    throw EventBrokerQueueFullException();
  }
}

#else
  #pragma message("Feature [Service/EventBroker]: DISABLED")
#endif // SERVICE_EVENT_BROKER
