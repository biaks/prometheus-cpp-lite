
#pragma once

#include <prometheus/family.h>
#include <prometheus/registry.h>
#include <prometheus/counter.h>
#include <prometheus/gauge.h>
#include <prometheus/benchmark.h>

#include "prometheus/registry.h"
#include "prometheus/save_to_file.h"

#include <thread>
#include <iostream>
#include <memory>
#include <functional>

namespace prometheus {
  namespace simpleapi {

    extern Registry   registry;
    extern SaveToFile saver;

    template <typename CustomMetric>
    class family_wrapper_t;

    template <typename CustomMetric>
    class metric_wrapper_t {

      typename CustomMetric::Family& family_;
      CustomMetric&                  metric_;

      friend family_wrapper_t<CustomMetric>;

      metric_wrapper_t(CustomMetric& cm, typename CustomMetric::Family& family)
        : family_(family), metric_(cm) {}

    public:
      metric_wrapper_t(const std::string& name, const std::string& description)
        : family_(CustomMetric::Family::Build(registry, name, description))
        , metric_(family_.Add({}))
      { }

      typename CustomMetric::Value value() const { return metric_.Get(); }

      void operator++()    { metric_++; }
      void operator++(int) { metric_++; }

      void operator--()    { metric_--; }
      void operator--(int) { metric_--; }

      metric_wrapper_t& operator+=(typename CustomMetric::Value val) {
        metric_.Increment(val);
        return *this;
      }

      metric_wrapper_t& operator-=(typename CustomMetric::Value val) {
        metric_.Decrement(val);
        return *this;
      }

    };

    class benchmark_wrapper_t {

      typename Benchmark::Family& family_;
      Benchmark&                  metric_;

      friend family_wrapper_t<Benchmark>;

      benchmark_wrapper_t(Benchmark& cm, typename Benchmark::Family& family)
        : family_(family), metric_(cm) {}

    public:
      benchmark_wrapper_t(const std::string& name, const std::string& description)
        : family_(Benchmark::Family::Build(registry, name, description))
        , metric_(family_.Add({}))
      { }

      typename Benchmark::Value value() const { return metric_.Get(); }

      void start() { metric_.start(); }
      void stop()  { metric_.stop();  }

    };

    template <typename CustomMetric>
    class family_wrapper_t {

      typename CustomMetric::Family& family_;

    public:
      family_wrapper_t(const std::string& name, const std::string& description)
        : family_(CustomMetric::Family::Build(registry, name, description))
      { }

      metric_wrapper_t<CustomMetric> Add(const typename CustomMetric::Family::Labels& labels) {
        return metric_wrapper_t<CustomMetric>(family_.Add(labels), family_);
      }

      metric_wrapper_t<CustomMetric> Add() {
        return metric_wrapper_t<CustomMetric>(family_.Add({}), family_);
      }
    };


    using counter_family_t = family_wrapper_t<prometheus::Counter<uint64_t>>;
    using counter_metric_t = metric_wrapper_t<prometheus::Counter<uint64_t>>;

    using gauge_family_t = family_wrapper_t<prometheus::Gauge<int64_t>>;
    using gauge_metric_t = metric_wrapper_t<prometheus::Gauge<int64_t>>;

    using benchmark_family_t = family_wrapper_t<prometheus::Benchmark>;
    using benchmark_metric_t = benchmark_wrapper_t;

  }
}
