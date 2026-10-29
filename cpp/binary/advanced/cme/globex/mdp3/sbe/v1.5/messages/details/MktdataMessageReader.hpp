#pragma once

#include "MktdataMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;


inline sbe_var_data read_mktdata_payload(const mktdata_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
