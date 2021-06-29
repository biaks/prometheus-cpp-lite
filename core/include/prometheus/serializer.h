#pragma once

#include <iosfwd>
#include <string>
#include <vector>

#include "prometheus/metric_family.h"

#include <sstream>  // IWYU pragma: keep

namespace prometheus {

  class Serializer {

    public:

      virtual ~Serializer() = default;

      virtual void Serialize(std::ostream& out, const std::vector<MetricFamily>& metrics) const = 0;

      virtual std::string Serialize(const std::vector<MetricFamily>& metrics) const {
        std::ostringstream ss;
        Serialize(ss, metrics);
        return ss.str();
      }

  };

}  // namespace prometheus
