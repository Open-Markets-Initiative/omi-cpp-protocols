#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/AggressingSide.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Summary information disseminated before the individual trades
class ExecutionSummaryMessage {
  public:
    static constexpr const char* name = "ExecutionSummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionSummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionSummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 37;
    static constexpr std::size_t fixed_size = 37;
    std::size_t encoded_size() const { return 37; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint32_t order_book() const { return wire::read_u32_be(at(10)); }

    AggressingSide aggressing_side() const { return static_cast<AggressingSide>(wire::read_char(at(14))); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(15)); }

    std::uint32_t hidden_quantity() const { return wire::read_u32_be(at(19)); }

    std::uint32_t stp_cancel_quantity() const { return wire::read_u32_be(at(23)); }

    Decimal far_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(27))), -4); }

    std::uint32_t add_quantity() const { return wire::read_u32_be(at(31)); }

    std::uint16_t number_of_lit_executions() const { return wire::read_u16_be(at(35)); }

    void print(std::ostream& out) const {
        out << "ExecutionSummaryMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", order_book=";
        out << order_book();
        out << ", aggressing_side=";
        out << aggressing_side();
        out << ", quantity=";
        out << quantity();
        out << ", hidden_quantity=";
        out << hidden_quantity();
        out << ", stp_cancel_quantity=";
        out << stp_cancel_quantity();
        out << ", far_price=";
        out << far_price();
        out << ", add_quantity=";
        out << add_quantity();
        out << ", number_of_lit_executions=";
        out << number_of_lit_executions();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExecutionSummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
