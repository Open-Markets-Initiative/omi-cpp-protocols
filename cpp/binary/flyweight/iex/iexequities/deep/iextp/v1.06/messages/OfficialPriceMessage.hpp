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
#include "../enums/PriceType.hpp"
#include "../common/Decimal.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

// Official Price Messages are sent for each IEX-listed security to indicate the IEX Official
// Opening Price and IEX Official Closing Price.
class OfficialPriceMessage {
  public:
    static constexpr const char* name = "OfficialPriceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OfficialPriceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OfficialPriceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    PriceType price_type() const { return static_cast<PriceType>(wire::read_char(at(0))); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(1)))); }

    std::string_view symbol() const { return view::text(at(9), 8, ' '); }

    Decimal official_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(17))), -4); }

    void print(std::ostream& out) const {
        out << "OfficialPriceMessage{";
        out << "price_type=";
        out << price_type();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", official_price=";
        out << official_price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OfficialPriceMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deep::iextp::v1_06
