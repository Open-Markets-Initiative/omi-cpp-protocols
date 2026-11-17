// Databento.MarketData.Normalized.Dbn.v3: types/ControlFields.hpp
#pragma once

#include "NullTerminatedString.hpp"
#include <cstddef>

namespace databento::marketdata::normalized::dbn::v3 {


// ASCII key=value pairs separated by the | character, terminated by a newline character
struct ControlFields {

    static constexpr auto       name       = "Control Fields";
    static constexpr std::size_t maximum    = 0;
    static constexpr char       terminator = '\0';

    using Status = ::omi::NullTerminatedStatus;

    ControlFields(const std::byte* data, std::size_t& offset, std::size_t available)
      : data_(data), start_(offset)
    {
        const auto result = ::omi::parse_null_terminated(data, offset, available, maximum, terminator);
        length_ = result.length;
        status_ = result.status;
    }

    [[nodiscard]] std::string_view get()    const { return ::omi::view_of(data_, start_, length_); }
    [[nodiscard]] std::size_t      length() const { return length_; }
    [[nodiscard]] std::size_t      start()  const { return start_; }
    [[nodiscard]] Status           status() const { return status_; }

  private:
    const std::byte* data_;
    std::size_t      start_;
    std::size_t      length_;
    Status           status_;
};
}
