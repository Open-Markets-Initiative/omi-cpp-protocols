#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ImbalanceDirection.hpp"
#include "../common/Decimal.hpp"
#include "../enums/CrossType.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Net order imbalance indicator disseminated during a cross auction
class NoiiMessage {
  public:
    static constexpr const char* name = "NoiiMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NoiiMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NoiiMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 60;
    static constexpr std::size_t fixed_size = 60;
    std::size_t encoded_size() const { return 60; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint64_t paired_quantity() const { return wire::read_u64_be(at(10)); }

    std::uint64_t imbalance_quantity() const { return wire::read_u64_be(at(18)); }

    ImbalanceDirection imbalance_direction() const { return static_cast<ImbalanceDirection>(wire::read_char(at(26))); }

    std::uint32_t order_book() const { return wire::read_u32_be(at(27)); }

    Decimal equilibrium_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(31))), -4); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(35))); }

    Decimal best_bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(36))), -4); }

    std::uint64_t best_bid_quantity() const { return wire::read_u64_be(at(40)); }

    Decimal best_ask_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(48))), -4); }

    std::uint64_t best_ask_quantity() const { return wire::read_u64_be(at(52)); }

    void print(std::ostream& out) const {
        out << "NoiiMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", paired_quantity=";
        out << paired_quantity();
        out << ", imbalance_quantity=";
        out << imbalance_quantity();
        out << ", imbalance_direction=";
        out << imbalance_direction();
        out << ", order_book=";
        out << order_book();
        out << ", equilibrium_price=";
        out << equilibrium_price();
        out << ", cross_type=";
        out << cross_type();
        out << ", best_bid_price=";
        out << best_bid_price();
        out << ", best_bid_quantity=";
        out << best_bid_quantity();
        out << ", best_ask_price=";
        out << best_ask_price();
        out << ", best_ask_quantity=";
        out << best_ask_quantity();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NoiiMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
