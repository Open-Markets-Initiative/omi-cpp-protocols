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
#include "../common/Day.hpp"
#include "../enums/SymbolState.hpp"
#include "../enums/Extension.hpp"
#include "../enums/Reason.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Indicates the current trading status of a security
class OrderBookTradingActionMessage {
  public:
    static constexpr const char* name = "OrderBookTradingActionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderBookTradingActionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderBookTradingActionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "UTC").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint32_t order_book() const { return wire::read_u32_be(at(10)); }

    SymbolState symbol_state() const { return static_cast<SymbolState>(wire::read_char(at(14))); }

    Extension extension() const { return static_cast<Extension>(wire::read_char(at(15))); }

    std::string_view reason() const { return view::text(at(16), 4, ' '); }

    void print(std::ostream& out) const {
        out << "OrderBookTradingActionMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "UTC");
        out << ", tracking_number=";
        out << tracking_number();
        out << ", order_book=";
        out << order_book();
        out << ", symbol_state=";
        out << symbol_state();
        out << ", extension=";
        out << extension();
        out << ", reason=";
        print::text(out, reason());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderBookTradingActionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
