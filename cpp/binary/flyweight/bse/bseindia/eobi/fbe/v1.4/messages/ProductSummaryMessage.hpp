#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TradingSessionId.hpp"
#include "../enums/TradingSessionSubId.hpp"
#include "../enums/TradSesStatus.hpp"
#include "../enums/FastMarketIndicator.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published once each snapshot cycle, carrying attributes that are equal for all instruments
// in the product.
class ProductSummaryMessage {
  public:
    static constexpr const char* name = "ProductSummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ProductSummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ProductSummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint32_t last_msg_seq_num_processed() const { return wire::read_u32_le(at(0)); }

    TradingSessionId trading_session_id() const { return static_cast<TradingSessionId>(wire::read_u8(at(4))); }

    TradingSessionSubId trading_session_sub_id() const { return static_cast<TradingSessionSubId>(wire::read_u8(at(5))); }

    TradSesStatus trad_ses_status() const { return static_cast<TradSesStatus>(wire::read_u8(at(6))); }

    FastMarketIndicator fast_market_indicator() const { return static_cast<FastMarketIndicator>(wire::read_u8(at(7))); }

    void print(std::ostream& out) const {
        out << "ProductSummaryMessage{";
        out << "last_msg_seq_num_processed=";
        out << last_msg_seq_num_processed();
        out << ", trading_session_id=";
        out << trading_session_id();
        out << ", trading_session_sub_id=";
        out << trading_session_sub_id();
        out << ", trad_ses_status=";
        out << trad_ses_status();
        out << ", fast_market_indicator=";
        out << fast_market_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ProductSummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
