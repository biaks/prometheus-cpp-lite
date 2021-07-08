#include <prometheus/registry.h>
#include <prometheus/counter.h>
#include <prometheus/save_to_file.h>

#include <array>
#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>
#include <thread>
#include <iostream>

int main() {

  using namespace prometheus;

  // for clarity, we deduce the required types
  using Metric = Counter<uint64_t>;

  using Family = Metric::Family;

  // create a metrics registry
  // @note it's the users responsibility to keep the object alive
  Registry registry;

  SaveToFile saver = SaveToFile( registry, std::chrono::seconds(5), std::string("./metrics.prom") );

  // add a new counter family to the registry (families combine values with the
  // same name, but distinct label dimensions)
  //
  // @note please follow the metric-naming best-practices:
  // https://prometheus.io/docs/practices/naming/
  Family& family { Family::Build(registry, "our_metric", "some metric") };

  // add and remember dimensional data, incrementing those is very cheap
  Metric& metric { family.Add({}) };

  for (;; ) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    const int random_value = std::rand();
    metric += random_value % 10;
  }

  return 0;

}