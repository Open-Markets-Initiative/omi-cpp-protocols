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
#include "../enums/TradeType.hpp"
#include "../enums/AuctionType.hpp"
#include "../bitfields/TradeFlags.hpp"
#include "../enums/HiddenExecutionIndicator.hpp"
#include "../enums/TradeQualifier.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Sent to indicate trades executed on supported markets.
class TradeMessage {
  public:
    static constexpr const char* name = "TradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 63;
    static constexpr std::size_t fixed_size = 63;
    std::size_t encoded_size() const { return 63; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::chrono::nanoseconds transaction_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(8)))); }

    SourceVenue source_venue() const { return static_cast<SourceVenue>(wire::read_u16_le(at(16))); }

    Decimal executed_size() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(18))), -8); }

    std::uint64_t instrument() const { return wire::read_u64_le(at(26)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(34))), -8); }

    std::span<const std::byte, 8> reserved_8() const { return bytes_.subspan(42).template first<8>(); }

    std::uint64_t trade_id() const { return wire::read_u64_le(at(50)); }

    TradeType trade_type() const { return static_cast<TradeType>(wire::read_u8(at(58))); }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(59))); }

    TradeFlags trade_flags() const { return TradeFlags{ bytes_.subspan(60) }; }

    HiddenExecutionIndicator hidden_execution_indicator() const { return static_cast<HiddenExecutionIndicator>(wire::read_u8(at(61))); }

    TradeQualifier trade_qualifier() const { return static_cast<TradeQualifier>(wire::read_char(at(62))); }

    void print(std::ostream& out) const {
        out << "TradeMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", transaction_time=";
        out << transaction_time().count();
        out << ", source_venue=";
        out << source_venue();
        out << ", executed_size=";
        out << executed_size();
        out << ", instrument=";
        out << instrument();
        out << ", price=";
        out << price();
        out << ", reserved_8=";
        print::hex(out, reserved_8().data(), reserved_8().size());
        out << ", trade_id=";
        out << trade_id();
        out << ", trade_type=";
        out << trade_type();
        out << ", auction_type=";
        out << auction_type();
        out << ", trade_flags=";
        trade_flags().print(out);
        out << ", hidden_execution_indicator=";
        out << hidden_execution_indicator();
        out << ", trade_qualifier=";
        out << trade_qualifier();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
