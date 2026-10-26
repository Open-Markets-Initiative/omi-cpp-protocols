#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../structs/OrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class OrderModifySamePrio {
  public:
    static constexpr const char* name = "OrderModifySamePrio";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderModifySamePrio(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderModifySamePrio has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 64;
    static constexpr std::size_t fixed_size = 64;
    std::size_t encoded_size() const { return 64; }

    std::optional<std::chrono::nanoseconds> request_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<Decimal> prev_display_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    OrderDetailsComp order_details_comp() const { return OrderDetailsComp{ bytes_.subspan(32) }; }

    void print(std::ostream& out) const {
        out << "OrderModifySamePrio{";
        out << "request_time=";
        print::optional_duration(out, request_time());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << ", prev_display_qty=";
        print::optional(out, prev_display_qty());
        out << ", security_id=";
        print::optional(out, security_id());
        out << ", order_details_comp=";
        order_details_comp().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderModifySamePrio& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v15_0
