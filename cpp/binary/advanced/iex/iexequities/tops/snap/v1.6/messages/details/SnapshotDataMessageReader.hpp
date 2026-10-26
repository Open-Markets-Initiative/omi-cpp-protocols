#pragma once

#include "SnapshotDataMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace iex::iexequities::tops::snap::v1_6 {

namespace snap_tops = ::iex::iexequities::tops::snap::v1_6;


inline external_var_data read_iex_tp_message_data(const snapshot_data_message& msg) {
    return { msg.tail_begin(), static_cast<std::size_t>(msg.fields.iex_tp_message_length.get().value() - 1), msg.tail_end() };
}

}
