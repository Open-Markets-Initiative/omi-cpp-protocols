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

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Sent whenever an order on the book is executed in whole or in part.
class OrderExecutedMessage {
  public:
    static constexpr const char* name = "OrderExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 51;
    static constexpr std::size_t fixed_size = 51;
    std::size_t encoded_size() const { return 51; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_be(at(4)); }

    std::uint32_t order_book_id() const { return wire::read_u32_be(at(12)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(16))); }

    std::uint64_t executed_quantity() const { return wire::read_u64_be(at(17)); }

    std::uint64_t match_id() const { return wire::read_u64_be(at(25)); }

    std::uint32_t combo_group_id() const { return wire::read_u32_be(at(33)); }

    std::string_view participant_id_owner() const { return view::text(at(37), 7, ' '); }

    std::string_view participant_id_counterparty() const { return view::text(at(44), 7, ' '); }

    void print(std::ostream& out) const {
        out << "OrderExecutedMessage{";
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
        out << ", participant_id_owner=";
        print::text(out, participant_id_owner());
        out << ", participant_id_counterparty=";
        print::text(out, participant_id_counterparty());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutedMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
