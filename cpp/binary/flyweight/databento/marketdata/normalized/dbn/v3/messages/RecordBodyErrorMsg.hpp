// Databento.MarketData.Normalized.Dbn.v3: messages/RecordBodyErrorMsg.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ErrorCode.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// An error message from the Databento Live Subscription Gateway (LSG)
class RecordBodyErrorMsg {
  public:
    static constexpr const char* name = "RecordBodyErrorMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecordBodyErrorMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecordBodyErrorMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 304;
    static constexpr std::size_t fixed_size = 304;
    std::size_t encoded_size() const { return 304; }

    std::string_view err() const { return view::text(at(0), 302, '\0'); }

    ErrorCode error_code() const { return static_cast<ErrorCode>(wire::read_u8(at(302))); }

    std::uint8_t is_last() const { return wire::read_u8(at(303)); }

    void print(std::ostream& out) const {
        out << "RecordBodyErrorMsg{";
        out << "err=";
        print::text(out, err());
        out << ", error_code=";
        out << error_code();
        out << ", is_last=";
        out << static_cast<int>(is_last());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RecordBodyErrorMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v3
