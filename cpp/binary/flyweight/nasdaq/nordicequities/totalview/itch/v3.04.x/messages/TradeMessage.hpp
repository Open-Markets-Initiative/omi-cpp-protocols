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
#include "../enums/TradeType.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Execution details for a match involving non displayable order types
class TradeMessage {
  public:
    static constexpr const char* name = "TradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 43;
    static constexpr std::size_t fixed_size = 43;
    std::size_t encoded_size() const { return 43; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "UTC").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(10)); }

    TradeType trade_type() const { return static_cast<TradeType>(wire::read_char(at(18))); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(19)); }

    std::uint32_t order_book() const { return wire::read_u32_be(at(23)); }

    std::uint32_t match_number() const { return wire::read_u32_be(at(27)); }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(31))), -4); }

    std::string_view participant_id_buyer() const { return view::text(at(35), 4, ' '); }

    std::string_view participant_id_seller() const { return view::text(at(39), 4, ' '); }

    void print(std::ostream& out) const {
        out << "TradeMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "UTC");
        out << ", tracking_number=";
        out << tracking_number();
        out << ", order_reference_number=";
        out << order_reference_number();
        out << ", trade_type=";
        out << trade_type();
        out << ", quantity=";
        out << quantity();
        out << ", order_book=";
        out << order_book();
        out << ", match_number=";
        out << match_number();
        out << ", trade_price=";
        out << trade_price();
        out << ", participant_id_buyer=";
        print::text(out, participant_id_buyer());
        out << ", participant_id_seller=";
        print::text(out, participant_id_seller());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
