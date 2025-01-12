#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_NV_MEMORY)

  #include "nvs.h"

  #include <string>

  class NVMNamespace final {
    public:
      NVMNamespace(const char* name, bool writable = false);
      NVMNamespace(const std::string& name, bool writable = false)
        : NVMNamespace(name.c_str(), writable) {}
      ~NVMNamespace();

      void erase();

      bool isWritable();
      void enableWrite(bool writable = true);
      void disableWrite();

      int8_t get(const std::string& key, int8_t& value) {
        return get(key.c_str(), value);
      }

      int8_t get(const char* key, int8_t& value);

      void set(const std::string& key, int8_t value) {
          set(key.c_str(), value);
      }

      void set(const char* key, int8_t value);

      uint8_t get(const std::string& key, uint8_t& value) {
        return get(key.c_str(), value);
      }

      uint8_t get(const char* key, uint8_t& value);

      void set(const std::string& key, uint8_t value) {
        set(key.c_str(), value);
      }

      void set(const char* key, uint8_t value);

      int16_t get(const std::string& key, int16_t& value) {
        return get(key.c_str(), value);
      }

      int16_t get(const char* key, int16_t& value);

      void set(const std::string& key, int16_t value) {
        set(key.c_str(), value);
      }

      void set(const char* key, int16_t value);

      uint16_t get(const std::string& key, uint16_t& value) {
        return get(key.c_str(), value);
      }

      uint16_t get(const char* key, uint16_t& value);

      void set(const std::string& key, uint16_t value) {
        set(key.c_str(), value);
      }

      void set(const char* key, uint16_t value);

      int32_t get(const std::string& key, int32_t& value) {
        return get(key.c_str(), value);
      }

      int32_t get(const char* key, int32_t& value);

      void set(const std::string& key, int32_t value) {
        set(key.c_str(), value);
      }

      void set(const char* key, int32_t value);

      uint32_t get(const std::string& key, uint32_t& value) {
        return get(key.c_str(), value);
      }

      uint32_t get(const char* key, uint32_t& value);

      void set(const std::string& key, uint32_t value) {
        set(key.c_str(), value);
      }

      void set(const char* key, uint32_t value);

      int64_t get(const std::string& key, int64_t& value) {
        return get(key.c_str(), value);
      }

      int64_t get(const char* key, int64_t& value);

      void set(const std::string& key, int64_t value) {
        set(key.c_str(), value);
      }

      void set(const char* key, int64_t value);

      uint64_t get(const std::string& key, uint64_t& value) {
        return get(key.c_str(), value);
      }

      uint64_t get(const char* key, uint64_t& value);

      void set(const std::string& key, uint64_t value) {
        set(key.c_str(), value);
      }

      void set(const char* key, uint64_t value);

      std::string get(const std::string& key) {
        return get(key);
      }

      std::string get(const char* key);

      void set(const std::string& key, const std::string& value) {
        set(key.c_str(), value.c_str());
      }

      void set(const char* key, const char* value);

      size_t getBlobSize(const std::string& key) {
        return getBlobSize(key.c_str());
      }

      size_t getBlobSize(const char* key);

      void* get(const std::string& key, void* value, size_t length) {
        return get(key, value, length);
      }

      void* get(const char* key, void* value, size_t length);

      void set(const std::string& key, const void* value, size_t length) {
        set(key, value, length);
      }

      void set(const char* key, const void* value, size_t length);

      // Read an object from non-volatile memory.
      template <typename T>
      T& get(const std::string& key, T& value) {
        return get<T>(key.c_str(), value);
      }

      // Read an object from non-volatile memory.
      template <typename T>
      T& get(const char* key, T& value) {
        get(key, reinterpret_cast<void*&>(&value), sizeof(T));
        return value;
      }

      // Write an object to non-volatile memory.
      template <typename T>
      const T& set(const std::string& key, const T& value) {
        return set<T>(key.c_str(), value);
      }

      // Write an object to non-volatile memory.
      template <typename T>
      const T& set(const char* key, const T& value) {
        set(key, reinterpret_cast<const void*&>(&value), sizeof(T));
        return value;
      }

    private:
      inline void handleEraseFailure(esp_err_t err);
      inline void handleGetFailure(esp_err_t err);
      inline void handleSetFailure(esp_err_t err);

    private:
      nvs_handle nvm_handle = 0;
      bool is_writable = false;
      std::string nvm_name;
  };

#endif // SERVICE_NV_MEMORY
