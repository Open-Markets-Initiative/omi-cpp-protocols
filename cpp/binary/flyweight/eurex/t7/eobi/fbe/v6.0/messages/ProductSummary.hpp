#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TradingSessionId.hpp"
#include "../enums/TradingSessionSubId.hpp"
#include "../enums/TradSesStatus.hpp"
#include "../enums/MarketCondition.hpp"
#include "../enums/FastMarketIndicator.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

class ProductSummary {
  public:
    static constexpr const char* name = "ProductSummary";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ProductSummary(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ProductSummary has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::optional<std::uint32_t> last_msg_seq_num_processed() const { return wire::nullable(wire::read_u32_le(at(0)), static_cast<std::uint32_t>(0xFFFFFFFFULL)); }

    std::optional<TradingSessionId> trading_session_id() const { return wire::nullable_enum<TradingSessionId>(wire::read_u8(at(4)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<TradingSessionSubId> trading_session_sub_id() const { return wire::nullable_enum<TradingSessionSubId>(wire::read_u8(at(5)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<TradSesStatus> trad_ses_status() const { return wire::nullable_enum<TradSesStatus>(wire::read_u8(at(6)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<MarketCondition> market_condition() const { return wire::nullable_enum<MarketCondition>(wire::read_u8(at(7)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<FastMarketIndicator> fast_market_indicator() const { return wire::nullable_enum<FastMarketIndicator>(wire::read_u8(at(8)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 7> pad7() const { return bytes_.subspan(9).template first<7>(); }

    void print(std::ostream& out) const {
        out << "ProductSummary{";
        out << "last_msg_seq_num_processed=";
        print::optional(out, last_msg_seq_num_processed());
        out << ", trading_session_id=";
        print::optional(out, trading_session_id());
        out << ", trading_session_sub_id=";
        print::optional(out, trading_session_sub_id());
        out << ", trad_ses_status=";
        print::optional(out, trad_ses_status());
        out << ", market_condition=";
        print::optional(out, market_condition());
        out << ", fast_market_indicator=";
        print::optional(out, fast_market_indicator());
        out << ", pad7=";
        print::hex(out, pad7().data(), pad7().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ProductSummary& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v6_0
