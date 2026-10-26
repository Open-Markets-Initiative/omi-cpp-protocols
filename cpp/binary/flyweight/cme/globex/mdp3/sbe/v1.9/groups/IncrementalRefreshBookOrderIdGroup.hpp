#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/OrderUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// Number of OrderID entries
class IncrementalRefreshBookOrderIdGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshBookOrderIdGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshBookOrderIdGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshBookOrderIdGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::uint64_t order_id() const { return wire::read_u64_le(at(0)); }

    std::optional<std::uint64_t> md_order_priority() const { return wire::nullable(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<std::int32_t> md_display_qty_optional() const { return wire::nullable(wire::read_i32_le(at(16)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<std::uint8_t> reference_id() const { return wire::nullable(wire::read_u8(at(20)), static_cast<std::uint8_t>(255ULL)); }

    OrderUpdateAction order_update_action() const { return static_cast<OrderUpdateAction>(wire::read_u8(at(21))); }

    std::span<const std::byte, 2> padding_2() const { return bytes_.subspan(22).template first<2>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshBookOrderIdGroup{";
        out << "order_id=";
        out << order_id();
        out << ", md_order_priority=";
        print::optional(out, md_order_priority());
        out << ", md_display_qty_optional=";
        print::optional(out, md_display_qty_optional());
        out << ", reference_id=";
        print::optional(out, reference_id());
        out << ", order_update_action=";
        out << order_update_action();
        out << ", padding_2=";
        print::hex(out, padding_2().data(), padding_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshBookOrderIdGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
