#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published whenever there is a change in the daily price range of the instrument.
class InstrumentInfoMessage {
  public:
    static constexpr const char* name = "InstrumentInfoMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrumentInfoMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrumentInfoMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::int64_t security_id() const { return wire::read_i64_le(at(0)); }

    std::optional<Decimal> close_price() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(0x8000000000000000LL), -6); }

    std::optional<Decimal> prev_close_price() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(0x8000000000000000LL), -6); }

    std::optional<Decimal> upper_ckt_limit() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL), -6); }

    std::optional<Decimal> lower_ckt_limit() const { return wire::nullable_decimal(wire::read_i64_le(at(32)), static_cast<std::int64_t>(0x8000000000000000LL), -6); }

    void print(std::ostream& out) const {
        out << "InstrumentInfoMessage{";
        out << "security_id=";
        out << security_id();
        out << ", close_price=";
        print::optional(out, close_price());
        out << ", prev_close_price=";
        print::optional(out, prev_close_price());
        out << ", upper_ckt_limit=";
        print::optional(out, upper_ckt_limit());
        out << ", lower_ckt_limit=";
        print::optional(out, lower_ckt_limit());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrumentInfoMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
