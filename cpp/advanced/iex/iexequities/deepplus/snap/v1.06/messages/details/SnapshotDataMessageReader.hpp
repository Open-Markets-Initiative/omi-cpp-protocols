#pragma once

#include "SnapshotDataMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace iex::iexequities::deepplus::snap::v1_06 {

namespace snap_deepplus = ::iex::iexequities::deepplus::snap::v1_06;


inline external_var_data read_iex_tp_message_data(const snapshot_data_message& msg) {
    return { msg.tail_begin(), static_cast<std::size_t>(msg.fields.iex_tp_message_length.get().value() - 1), msg.tail_end() };
}

}
