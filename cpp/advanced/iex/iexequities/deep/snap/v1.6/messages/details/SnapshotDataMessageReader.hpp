#pragma once

#include "SnapshotDataMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace iex::iexequities::deep::snap::v1_6 {

namespace snap_deep = ::iex::iexequities::deep::snap::v1_6;


inline sbe_var_data read_iex_tp_message_data(const snapshot_data_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
