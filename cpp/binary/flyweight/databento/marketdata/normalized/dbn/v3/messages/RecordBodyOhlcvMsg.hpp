// Databento.MarketData.Normalized.Dbn.v3: messages/RecordBodyOhlcvMsg.hpp
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

namespace databento::marketdata::normalized::dbn::v3 {

// Open, high, low, close, and volume; the record of the ohlcv schemas
class RecordBodyOhlcvMsg {
  public:
    static constexpr const char* name = "RecordBodyOhlcvMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecordBodyOhlcvMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecordBodyOhlcvMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::optional<Decimal> open() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> high() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> low() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> close() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::uint64_t volume() const { return wire::read_u64_le(at(32)); }

    void print(std::ostream& out) const {
        out << "RecordBodyOhlcvMsg{";
        out << "open=";
        print::optional(out, open());
        out << ", high=";
        print::optional(out, high());
        out << ", low=";
        print::optional(out, low());
        out << ", close=";
        print::optional(out, close());
        out << ", volume=";
        out << volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RecordBodyOhlcvMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v3
