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

namespace eurex::t7::eobi::fbe::v13_0 {

class TopOfBook {
  public:
    static constexpr const char* name = "TopOfBook";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TopOfBook(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TopOfBook has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 56;
    static constexpr std::size_t fixed_size = 56;
    std::size_t encoded_size() const { return 56; }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(8)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<Decimal> bid_px() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<Decimal> offer_px() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<Decimal> bid_size() const { return wire::nullable_decimal(wire::read_i64_le(at(32)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<Decimal> offer_size() const { return wire::nullable_decimal(wire::read_i64_le(at(40)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<std::uint16_t> number_of_buy_orders() const { return wire::nullable(wire::read_u16_le(at(48)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::optional<std::uint16_t> number_of_sell_orders() const { return wire::nullable(wire::read_u16_le(at(50)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::span<const std::byte, 4> pad4() const { return bytes_.subspan(52).template first<4>(); }

    void print(std::ostream& out) const {
        out << "TopOfBook{";
        out << "transact_time=";
        print::optional_duration(out, transact_time());
        out << ", security_id=";
        print::optional(out, security_id());
        out << ", bid_px=";
        print::optional(out, bid_px());
        out << ", offer_px=";
        print::optional(out, offer_px());
        out << ", bid_size=";
        print::optional(out, bid_size());
        out << ", offer_size=";
        print::optional(out, offer_size());
        out << ", number_of_buy_orders=";
        print::optional(out, number_of_buy_orders());
        out << ", number_of_sell_orders=";
        print::optional(out, number_of_sell_orders());
        out << ", pad4=";
        print::hex(out, pad4().data(), pad4().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TopOfBook& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
