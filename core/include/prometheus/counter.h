#pragma once

#include "prometheus/gauge.h"
#include "prometheus/metric.h"
#include "prometheus/family.h"


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

  Gauge<Value> gauge_{ 0 };

public:

  using Family = CustomFamily<Counter<Value>>;

  static const Metric::Type static_type = Metric::Type::Counter;

  /// \brief Create a counter that starts at 0.
  Counter() : Metric (Metric::Type::Counter) {}

  /// \brief Increment the counter by 1.
  void Increment() { gauge_.Increment(); }

  /// \brief Increment the counter by a given amount.
  ///
  /// The counter will not change if the given amount is negative.
  void Increment(const Value val) {
  if (val < 0) {
    return;
  }
  gauge_.Increment(val);
}

  /// \brief Get the current value of the counter.
  Value Get() const { return gauge_.Value(); }

  /// \brief Get the current value of the counter.
  ///
  /// Collect is called by the Registry when collecting metrics.
  virtual ClientMetric Collect() const {
    ClientMetric metric;
    metric.counter.value = Get();
    return metric;
  }

};

}  // namespace prometheus
