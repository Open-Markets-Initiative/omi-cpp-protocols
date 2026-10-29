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
#include "../bitfields/AddOrderFlags.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

// An Add Order message represents a newly accepted visible order on the Cboe book. Expanded
// version accommodates larger symbol sizes possible through the ISRA plan.
class AddOrderExpandedMessage {
  public:
    static constexpr const char* name = "AddOrderExpandedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderExpandedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderExpandedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 39;
    static constexpr std::size_t fixed_size = 39;
    std::size_t encoded_size() const { return 39; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    SideIndicator side_indicator() const { return static_cast<SideIndicator>(wire::read_char(at(12))); }

    std::uint32_t quantity() const { return wire::read_u32_le(at(13)); }

    std::string_view symbol_long() const { return view::text(at(17), 8, ' '); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(25))), -4); }

    AddOrderFlags add_order_flags() const { return AddOrderFlags{ bytes_.subspan(33) }; }

    std::string_view participant_id() const { return view::text(at(34), 4, ' '); }

    char customer_indicator() const { return wire::read_char(at(38)); }

    void print(std::ostream& out) const {
        out << "AddOrderExpandedMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", order_id=";
        out << order_id();
        out << ", side_indicator=";
        out << side_indicator();
        out << ", quantity=";
        out << quantity();
        out << ", symbol_long=";
        print::text(out, symbol_long());
        out << ", price=";
        out << price();
        out << ", add_order_flags=";
        add_order_flags().print(out);
        out << ", participant_id=";
        print::text(out, participant_id());
        out << ", customer_indicator=";
        print::character(out, customer_indicator());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddOrderExpandedMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
