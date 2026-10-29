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
#include "../enums/SideIndicator.hpp"
#include "../common/Decimal.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// An Add Order message represents a newly accepted visible order on the Cboe book.
class AddOrderShortMessage {
  public:
    static constexpr const char* name = "AddOrderShortMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderShortMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderShortMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    SideIndicator side_indicator() const { return static_cast<SideIndicator>(wire::read_char(at(12))); }

    std::uint16_t quantity_short() const { return wire::read_u16_le(at(13)); }

    std::string_view complex_instrument_id() const { return view::text(at(15), 6, ' '); }

    Decimal price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_i16_le(at(21))), -2); }

    std::span<const std::byte, 1> padding() const { return bytes_.subspan(23).template first<1>(); }

    void print(std::ostream& out) const {
        out << "AddOrderShortMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", order_id=";
        out << order_id();
        out << ", side_indicator=";
        out << side_indicator();
        out << ", quantity_short=";
        out << quantity_short();
        out << ", complex_instrument_id=";
        print::text(out, complex_instrument_id());
        out << ", price_short=";
        out << price_short();
        out << ", padding=";
        print::hex(out, padding().data(), padding().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddOrderShortMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
