#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SourceVenue.hpp"
#include "../common/Decimal.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Contains a set of statistics that are updated frequently, usually as a result of executions.
class StatisticsMessage {
  public:
    static constexpr const char* name = "StatisticsMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StatisticsMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StatisticsMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 74;
    static constexpr std::size_t fixed_size = 74;
    std::size_t encoded_size() const { return 74; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint64_t instrument() const { return wire::read_u64_le(at(8)); }

    SourceVenue source_venue() const { return static_cast<SourceVenue>(wire::read_u16_le(at(16))); }

    Decimal volume() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(18))), -4); }

    Decimal volume_on_book_only() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(26))), -4); }

    Decimal vwap() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(34))), -4); }

    Decimal vwap_on_book_only() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(42))), -4); }

    std::uint32_t number_of_trades() const { return wire::read_u32_le(at(50)); }

    std::uint32_t number_of_trades_on_book_only() const { return wire::read_u32_le(at(54)); }

    Decimal turnover() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(58))), -4); }

    Decimal turnover_on_book_only() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(66))), -4); }

    void print(std::ostream& out) const {
        out << "StatisticsMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", instrument=";
        out << instrument();
        out << ", source_venue=";
        out << source_venue();
        out << ", volume=";
        out << volume();
        out << ", volume_on_book_only=";
        out << volume_on_book_only();
        out << ", vwap=";
        out << vwap();
        out << ", vwap_on_book_only=";
        out << vwap_on_book_only();
        out << ", number_of_trades=";
        out << number_of_trades();
        out << ", number_of_trades_on_book_only=";
        out << number_of_trades_on_book_only();
        out << ", turnover=";
        out << turnover();
        out << ", turnover_on_book_only=";
        out << turnover_on_book_only();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StatisticsMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
