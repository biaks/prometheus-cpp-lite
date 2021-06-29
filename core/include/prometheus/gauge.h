#pragma once

#include <atomic>
#include <ctime>

#include "prometheus/metric.h"
#include "prometheus/family.h"

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
  template <typename Value = uint64_t>
  class Gauge : public Metric {

    std::atomic<Value> value_{ 0 };

    public:

      //void Change(const value_type_t value) {
        // compare_exchange_weak используется здесь не по назначению
        // https://habr.com/ru/post/328348/
        // его идея: копировали в локальную переменную через load(), превратили старую локальную переменную в новую локальную переменную,
        // затем одновременно проверяем, что старая локальная переменная совпадает со значением в atomic и, если совпадает, записать туда
        // значение новой локальной переменной
        // а можно просто сделать value_++, будет вызван атомарный masgine increment for long long
        //value_type_t current = value_.load(); value_.operator++();
        //while (!value_.compare_exchange_weak(current, current + value));
      //}

    public:

      static const Metric::Type static_type = Metric::Type::Gauge;

      /// \brief Create a gauge that starts at 0.
      Gauge() : Metric (static_type) {}

      /// \brief Create a gauge that starts at the given amount.
      Gauge(const Value value) : Metric(static_type), value_{ value } {}

      /// \brief Increment the gauge by 1.
      void Increment() { value_++; }

      /// \brief Increment the gauge by the given amount.
      void Increment(const Value value) { value_ += value; }

      /// \brief Decrement the gauge by 1.
      void Decrement() { value_--; }

      /// \brief Decrement the gauge by the given amount.
      void Decrement(const Value value) { value_ -= value; }

      /// \brief Set the gauge to the given value.
      void Set(const Value value) { value_ = value; }

      /// \brief Set the gauge to the current unixtime in seconds.
      void SetToCurrentTime() {
        const time_t time = std::time(nullptr);
        Set(static_cast<Value>(time));
      }

      /// \brief Get the current value of the gauge.
      Value Get() const { return value_; }

      /// \brief Get the current value of the gauge.
      ///
      /// Collect is called by the Registry when collecting metrics.
      virtual ClientMetric Collect() const {
        ClientMetric metric;
        metric.gauge.value = Get();
        return metric;
      }

  };

  template <typename Value = uint64_t>
  using GaugeFamily = CustomFamily<Gauge<Value>>;


}  // namespace prometheus
