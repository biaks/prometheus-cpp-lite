#include "prometheus/simpleapi.h"

#include "prometheus/registry.h"
#include "prometheus/save_to_file.h"

namespace prometheus {
  namespace simpleapi {

    Registry registry;
    SaveToFile saver = SaveToFile(registry, std::chrono::seconds(5), std::string("./metrics.prom"));

  }
}
