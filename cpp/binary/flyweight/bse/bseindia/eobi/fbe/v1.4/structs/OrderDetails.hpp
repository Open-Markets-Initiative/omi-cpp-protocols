#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"
#include "../common/Decimal.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// OrderDetails
class OrderDetails {
  public:
    static constexpr const char* name = "OrderDetails";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderDetails(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderDetails has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::chrono::nanoseconds trd_reg_ts_time_priority() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::int64_t display_qty() const { return wire::read_i64_le(at(8)); }

    Side side() const { return static_cast<Side>(wire::read_u8(at(16))); }

    std::span<const std::byte, 7> pad_7() const { return bytes_.subspan(17).template first<7>(); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(24))), -6); }

    void print(std::ostream& out) const {
        out << "OrderDetails{";
        out << "trd_reg_ts_time_priority=";
        out << trd_reg_ts_time_priority().count();
        out << ", display_qty=";
        out << display_qty();
        out << ", side=";
        out << side();
        out << ", pad_7=";
        print::hex(out, pad_7().data(), pad_7().size());
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderDetails& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
