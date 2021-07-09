#pragma once

#include <thread>
#include <chrono>
#include <string>
#include <fstream>

#include "registry.h"
#include "text_serializer.h"

namespace prometheus {
  class SaveToFile {
    std::chrono::seconds period { 1 };
    std::string          filename;
    std::thread          worker_thread { &SaveToFile::worker_function, this };
    Registry*            registry_ptr { 0 };

    void worker_function() {
      for (;;) {
        std::this_thread::sleep_for(period);
        if (registry_ptr) {
          std::fstream out_file_stream;
          out_file_stream.open(filename, std::fstream::out | std::fstream::binary);
          if (out_file_stream.is_open()) {
            TextSerializer::Serialize(out_file_stream, registry_ptr->Collect());
            out_file_stream.close();
          }
        }
      }
    }
    
  public:
    SaveToFile() = default;

    ~SaveToFile() {
      if (worker_thread.joinable())
        worker_thread.detach();
    }

    SaveToFile(Registry& registry_, const std::chrono::seconds& period_, const std::string& filename_) {
      set_registry(registry_);
      set_delay(period_);
      set_out_file(filename_);
    }

    void set_delay (const std::chrono::seconds& new_period) {
      period = new_period;
    }


    bool set_out_file (const std::string& filename_) {
      filename = filename_;
      std::fstream out_file_stream;
      out_file_stream.open(filename, std::fstream::out | std::fstream::binary);
      bool open_success = out_file_stream.is_open();
      out_file_stream.close();
      return open_success;
    }

    void set_registry (Registry& new_registry) {
      registry_ptr = &new_registry;
    }

  };
}
