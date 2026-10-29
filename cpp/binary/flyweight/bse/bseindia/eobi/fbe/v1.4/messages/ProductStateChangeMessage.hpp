#pragma once

#include <chrono>
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

// Provides updates on the trading state for all instruments in a particular product.
class ProductStateChangeMessage {
  public:
    static constexpr const char* name = "ProductStateChangeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ProductStateChangeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ProductStateChangeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    TradingSessionId trading_session_id() const { return static_cast<TradingSessionId>(wire::read_u8(at(0))); }

    TradingSessionSubId trading_session_sub_id() const { return static_cast<TradingSessionSubId>(wire::read_u8(at(1))); }

    TradSesStatus trad_ses_status() const { return static_cast<TradSesStatus>(wire::read_u8(at(2))); }

    FastMarketIndicator fast_market_indicator() const { return static_cast<FastMarketIndicator>(wire::read_u8(at(3))); }

    std::span<const std::byte, 4> pad_4() const { return bytes_.subspan(4).template first<4>(); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(8)))); }

    void print(std::ostream& out) const {
        out << "ProductStateChangeMessage{";
        out << "trading_session_id=";
        out << trading_session_id();
        out << ", trading_session_sub_id=";
        out << trading_session_sub_id();
        out << ", trad_ses_status=";
        out << trad_ses_status();
        out << ", fast_market_indicator=";
        out << fast_market_indicator();
        out << ", pad_4=";
        print::hex(out, pad_4().data(), pad_4().size());
        out << ", transact_time=";
        out << transact_time().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ProductStateChangeMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
