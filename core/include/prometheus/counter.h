#pragma once

#include "prometheus/atomic_floating.h"
#include "prometheus/metric.h"
#include "prometheus/family.h"

#include <atomic>

namespace prometheus {

  /// \brief A counter metric to represent a monotonically increasing value.
  ///
  /// This class represents the metric type counter:
  /// https://prometheus.io/docs/concepts/metric_types/#counter
  ///
  /// The value of the counter can only increase. Example of counters are:
  /// - the number of requests served
  /// - tasks completed
  /// - errors
  ///
  /// Do not use a counter to expose a value that can decrease - instead use a
  /// Gauge.
  ///
  /// The class is thread-safe. No concurrent call to any API of this type causes
  /// a data race.
  template <typename Value = uint64_t>
  class Counter : public Metric {

    std::atomic<Value> value { 0 };

  public:
    using value_type = Value;
    using Family = CustomFamily<Counter<Value>>;

    static const Metric::Type static_type = Metric::Type::Counter;

    Counter() : Metric (Metric::Type::Counter) {}  ///< \brief Create a counter that starts at 0.

    // original API

    void Increment() { ///< \brief Increment the counter by 1.
      ++value;
    }

    void Increment(const Value& val) { ///< \brief Increment the counter by a given amount. The counter will not change if the given amount is negative.
      if (val > 0)
        value += val;
    }

    const Value& Get() const { ///< \brief Get the current value of the counter.
      return value;
    }

    virtual ClientMetric Collect() const { ///< /// \brief Get the current value of the counter. Collect is called by the Registry when collecting metrics.
      ClientMetric metric;
      metric.counter.value = static_cast<double>(value);
      return metric;
    }

    // new API

    Counter& operator ++() {
      ++value;
      return *this;
    }

    Counter& operator++ (int) {
      ++value;
      return *this;
    }

    Counter& operator += (const Value& val) {
      value += val;
      return *this;
    }

  };



}  // namespace prometheus
