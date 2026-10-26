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
#include "../enums/OccurredAtCross.hpp"
#include "../enums/Printable.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Sent when an order is executed at a price different than the initial display price.
class OrderExecutedWithPriceMessage {
  public:
    static constexpr const char* name = "OrderExecutedWithPriceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedWithPriceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedWithPriceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 57;
    static constexpr std::size_t fixed_size = 57;
    std::size_t encoded_size() const { return 57; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_be(at(4)); }

    std::uint32_t order_book_id() const { return wire::read_u32_be(at(12)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(16))); }

    std::uint64_t executed_quantity() const { return wire::read_u64_be(at(17)); }

    std::uint64_t match_id() const { return wire::read_u64_be(at(25)); }

    std::uint32_t combo_group_id() const { return wire::read_u32_be(at(33)); }

    std::string_view owner_participant_id() const { return view::text(at(37), 7, ' '); }

    std::string_view counterparty_participant_id() const { return view::text(at(44), 7, ' '); }

    std::int32_t trade_price() const { return wire::read_i32_be(at(51)); }

    OccurredAtCross occurred_at_cross() const { return static_cast<OccurredAtCross>(wire::read_char(at(55))); }

    Printable printable() const { return static_cast<Printable>(wire::read_char(at(56))); }

    void print(std::ostream& out) const {
        out << "OrderExecutedWithPriceMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", order_id=";
        out << order_id();
        out << ", order_book_id=";
        out << order_book_id();
        out << ", side=";
        out << side();
        out << ", executed_quantity=";
        out << executed_quantity();
        out << ", match_id=";
        out << match_id();
        out << ", combo_group_id=";
        out << combo_group_id();
        out << ", owner_participant_id=";
        print::text(out, owner_participant_id());
        out << ", counterparty_participant_id=";
        print::text(out, counterparty_participant_id());
        out << ", trade_price=";
        out << trade_price();
        out << ", occurred_at_cross=";
        out << occurred_at_cross();
        out << ", printable=";
        out << printable();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutedWithPriceMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
