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
#include "../bitfields/AddFlags.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// An Add Order message represents a newly accepted visible order on the Cboe book.
class AddOrderLongMessage {
  public:
    static constexpr const char* name = "AddOrderLongMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderLongMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderLongMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    SideIndicator side_indicator() const { return static_cast<SideIndicator>(wire::read_char(at(12))); }

    std::uint32_t long_quantity() const { return wire::read_u32_le(at(13)); }

    std::string_view symbol() const { return view::text(at(17), 6, ' '); }

    Decimal long_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(23))), -4); }

    AddFlags add_flags() const { return AddFlags{ bytes_.subspan(31) }; }

    void print(std::ostream& out) const {
        out << "AddOrderLongMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", order_id=";
        out << order_id();
        out << ", side_indicator=";
        out << side_indicator();
        out << ", long_quantity=";
        out << long_quantity();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", long_price=";
        out << long_price();
        out << ", add_flags=";
        add_flags().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddOrderLongMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
