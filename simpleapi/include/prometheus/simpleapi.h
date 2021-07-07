
#pragma once

#include <prometheus/family.h>
#include <prometheus/registry.h>
#include <prometheus/counter.h>
#include <prometheus/gauge.h>

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

      typename CustomMetric::value_type value() const { return metric_.Get(); }

      void operator++()    { metric_++; }
      void operator++(int) { metric_++; }

      void operator--()    { metric_--; }
      void operator--(int) { metric_--; }

      metric_wrapper_t& operator+=(typename CustomMetric::value_type val) {
        metric_.Increment(val);
        return *this;
      }

      metric_wrapper_t& operator-=(typename CustomMetric::value_type val) {
        metric_.Decrement(val);
        return *this;
      }

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

  }
}
