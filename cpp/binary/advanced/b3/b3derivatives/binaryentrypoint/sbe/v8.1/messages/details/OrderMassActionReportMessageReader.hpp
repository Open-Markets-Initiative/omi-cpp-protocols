#pragma once

#include "OrderMassActionReportMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;


inline sbe_var_data read_text(const order_mass_action_report_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
