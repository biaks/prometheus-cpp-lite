#pragma once

#include "prometheus/atomic_floating.h"
#include "prometheus/metric.h"
#include "prometheus/family.h"

#include <atomic>
#include <ctime>

namespace prometheus {

  /// \brief A gauge metric to represent a value that can arbitrarily go up and
  /// down.
  ///
  /// The class represents the metric type gauge:
  /// https://prometheus.io/docs/concepts/metric_types/#gauge
  ///
  /// Gauges are typically used for measured values like temperatures or current
  /// memory usage, but also "counts" that can go up and down, like the number of
  /// running processes.
  ///
  /// The class is thread-safe. No concurrent call to any API of this type causes
  /// a data race.
  template <typename Value_ = uint64_t>
  class Gauge : public Metric {

    std::atomic<Value_> value { 0 };

    public:

      using Value  = Value_;
      using Family = CustomFamily<Gauge<Value>>;

      static const Metric::Type static_type = Metric::Type::Gauge;


      Gauge()                   : Metric (static_type) {}                  ///< \brief Create a gauge that starts at 0.
      Gauge(const Value value_) : Metric(static_type), value{ value_ } {}  ///< \brief Create a gauge that starts at the given amount.

      // original API

      void Increment() { ++value; }                      ///< \brief Increment the gauge by 1.
      void Increment(const Value& val) { value += val; } ///< \brief Increment the gauge by the given amount.

      void Decrement() { --value; }                      ///< \brief Decrement the gauge by 1.
      void Decrement(const Value& val) { value -= val; } ///< \brief Decrement the gauge by the given amount.

      void SetToCurrentTime() {                          ///< \brief Set the gauge to the current unixtime in seconds.
        const time_t time = std::time(nullptr);
        value = static_cast<Value>(time);
      }
      void Set(const Value& val) { value = val; }        ///< \brief Set the gauge to the given value.
      const Value& Get() const { return value; }         ///< \brief Get the current value of the gauge.

      virtual ClientMetric Collect() const {             ///< \brief Get the current value of the gauge. Collect is called by the Registry when collecting metrics.
        ClientMetric metric;
        metric.gauge.value = Get();
        return metric;
      }

      // new API

      Gauge& operator ++() {
        ++value;
        return *this;
      }

      Gauge& operator++ (int) {
        ++value;
        return *this;
      }

      Gauge& operator --() {
        --value;
        return *this;
      }

      Gauge& operator-- (int) {
        --value;
        return *this;
      }

      Gauge& operator+=(const Value& val) {
        value += val;
        return *this;
      }

      Gauge& operator-=(const Value& val) {
        value -= val;
        return *this;
      }

  };

}  // namespace prometheus
