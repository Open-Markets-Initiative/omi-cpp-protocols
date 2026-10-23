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
#include "../enums/Side.hpp"
#include "../enums/Printable.hpp"
#include "../enums/OccurredAtCross.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Execution details for normal match events involving non-displayable order types or cross
// trades.
class TradeMessage {
  public:
    static constexpr const char* name = "TradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 49;
    static constexpr std::size_t fixed_size = 49;
    std::size_t encoded_size() const { return 49; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t match_id() const { return wire::read_u64_be(at(4)); }

    std::uint32_t combo_group_id() const { return wire::read_u32_be(at(12)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(16))); }

    std::uint64_t quantity() const { return wire::read_u64_be(at(17)); }

    std::uint32_t order_book_id() const { return wire::read_u32_be(at(25)); }

    std::int32_t trade_price() const { return wire::read_i32_be(at(29)); }

    std::string_view owner_participant_id() const { return view::text(at(33), 7, ' '); }

    std::string_view counterparty_participant_id() const { return view::text(at(40), 7, ' '); }

    Printable printable() const { return static_cast<Printable>(wire::read_char(at(47))); }

    OccurredAtCross occurred_at_cross() const { return static_cast<OccurredAtCross>(wire::read_char(at(48))); }

    void print(std::ostream& out) const {
        out << "TradeMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", match_id=";
        out << match_id();
        out << ", combo_group_id=";
        out << combo_group_id();
        out << ", side=";
        out << side();
        out << ", quantity=";
        out << quantity();
        out << ", order_book_id=";
        out << order_book_id();
        out << ", trade_price=";
        out << trade_price();
        out << ", owner_participant_id=";
        print::text(out, owner_participant_id());
        out << ", counterparty_participant_id=";
        print::text(out, counterparty_participant_id());
        out << ", printable=";
        out << printable();
        out << ", occurred_at_cross=";
        out << occurred_at_cross();
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

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
