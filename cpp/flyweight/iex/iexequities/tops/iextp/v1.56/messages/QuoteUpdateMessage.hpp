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
#include "../bitfields/QuoteUpdateFlags.hpp"
#include "../common/Decimal.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

// Tops broadcasts a real-time Quote Update Message each time IEX's best bid or offer quotation
// is updated during the trading day
class QuoteUpdateMessage {
  public:
    static constexpr const char* name = "QuoteUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 41;
    static constexpr std::size_t fixed_size = 41;
    std::size_t encoded_size() const { return 41; }

    QuoteUpdateFlags quote_update_flags() const { return QuoteUpdateFlags{ bytes_.subspan(0) }; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(1)))); }

    std::string_view symbol() const { return view::text(at(9), 8, ' '); }

    std::uint32_t bid_size() const { return wire::read_u32_le(at(17)); }

    Decimal bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(21))), -4); }

    Decimal ask_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(29))), -4); }

    std::uint32_t ask_size() const { return wire::read_u32_le(at(37)); }

    void print(std::ostream& out) const {
        out << "QuoteUpdateMessage{";
        out << "quote_update_flags=";
        quote_update_flags().print(out);
        out << ", timestamp=";
        out << timestamp().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", bid_size=";
        out << bid_size();
        out << ", bid_price=";
        out << bid_price();
        out << ", ask_price=";
        out << ask_price();
        out << ", ask_size=";
        out << ask_size();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::tops::iextp::v1_56
