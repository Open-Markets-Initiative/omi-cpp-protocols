#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ShortSalePriceTestStatus.hpp"
#include "../enums/Detail.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

// The Short Sale Price Test Message is used to indicate when a short sale price test
// restriction is in effect for a security.
class ShortSalePriceTestStatusMessage {
  public:
    static constexpr const char* name = "ShortSalePriceTestStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ShortSalePriceTestStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ShortSalePriceTestStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    ShortSalePriceTestStatus short_sale_price_test_status() const { return static_cast<ShortSalePriceTestStatus>(wire::read_u8(at(0))); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(1)))); }

    std::string_view symbol() const { return view::text(at(9), 8, ' '); }

    Detail detail() const { return static_cast<Detail>(wire::read_char(at(17))); }

    void print(std::ostream& out) const {
        out << "ShortSalePriceTestStatusMessage{";
        out << "short_sale_price_test_status=";
        out << short_sale_price_test_status();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", detail=";
        out << detail();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ShortSalePriceTestStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::tops::iextp::v1_66
