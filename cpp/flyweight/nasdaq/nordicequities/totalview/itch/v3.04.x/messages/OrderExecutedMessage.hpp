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

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Sent whenever an order on the book is executed in whole or in part
class OrderExecutedMessage {
  public:
    static constexpr const char* name = "OrderExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 34;
    static constexpr std::size_t fixed_size = 34;
    std::size_t encoded_size() const { return 34; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(10)); }

    std::uint32_t executed_quantity() const { return wire::read_u32_be(at(18)); }

    std::uint32_t match_number() const { return wire::read_u32_be(at(22)); }

    std::string_view mpid() const { return view::text(at(26), 4, ' '); }

    std::string_view mpid_counterparty() const { return view::text(at(30), 4, ' '); }

    void print(std::ostream& out) const {
        out << "OrderExecutedMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", order_reference_number=";
        out << order_reference_number();
        out << ", executed_quantity=";
        out << executed_quantity();
        out << ", match_number=";
        out << match_number();
        out << ", mpid=";
        print::text(out, mpid());
        out << ", mpid_counterparty=";
        print::text(out, mpid_counterparty());
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

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
