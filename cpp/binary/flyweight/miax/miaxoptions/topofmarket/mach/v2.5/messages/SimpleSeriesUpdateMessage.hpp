#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/CallOrPut.hpp"
#include "../enums/RestrictedOption.hpp"
#include "../enums/LongTermOption.hpp"
#include "../enums/ActiveOnMiax.hpp"
#include "../enums/MiaxBboPostingIncrementIndicator.hpp"
#include "../enums/LiquidityAcceptanceIncrementIndicator.hpp"
#include "../enums/OpeningUnderlyingMarketCode.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// This is the message format that will be used to disseminate all Option series traded on MIAX
// for the current session. The product ID sent in this message is what will be disseminated in
// Top of Market BBO and Last Sale messages.
class SimpleSeriesUpdateMessage {
  public:
    static constexpr const char* name = "SimpleSeriesUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SimpleSeriesUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SimpleSeriesUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 72;
    static constexpr std::size_t fixed_size = 72;
    std::size_t encoded_size() const { return 72; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t product_id() const { return wire::read_u32_le(at(4)); }

    std::string_view underlying_symbol() const { return view::text(at(8), 11, ' '); }

    std::string_view security_symbol() const { return view::text(at(19), 6, ' '); }

    std::string_view expiration_date() const { return view::text(at(25), 8, ' '); }

    Decimal strike_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_le(at(33))), -4); }

    CallOrPut call_or_put() const { return static_cast<CallOrPut>(wire::read_char(at(37))); }

    std::string_view opening_time() const { return view::text(at(38), 8, ' '); }

    std::string_view closing_time() const { return view::text(at(46), 8, ' '); }

    RestrictedOption restricted_option() const { return static_cast<RestrictedOption>(wire::read_char(at(54))); }

    LongTermOption long_term_option() const { return static_cast<LongTermOption>(wire::read_char(at(55))); }

    ActiveOnMiax active_on_miax() const { return static_cast<ActiveOnMiax>(wire::read_char(at(56))); }

    MiaxBboPostingIncrementIndicator miax_bbo_posting_increment_indicator() const { return static_cast<MiaxBboPostingIncrementIndicator>(wire::read_char(at(57))); }

    LiquidityAcceptanceIncrementIndicator liquidity_acceptance_increment_indicator() const { return static_cast<LiquidityAcceptanceIncrementIndicator>(wire::read_char(at(58))); }

    OpeningUnderlyingMarketCode opening_underlying_market_code() const { return static_cast<OpeningUnderlyingMarketCode>(wire::read_char(at(59))); }

    Decimal priority_quote_width() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_le(at(60))), -4); }

    std::span<const std::byte, 8> reserved_8() const { return bytes_.subspan(64).template first<8>(); }

    void print(std::ostream& out) const {
        out << "SimpleSeriesUpdateMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", product_id=";
        out << product_id();
        out << ", underlying_symbol=";
        print::text(out, underlying_symbol());
        out << ", security_symbol=";
        print::text(out, security_symbol());
        out << ", expiration_date=";
        print::text(out, expiration_date());
        out << ", strike_price=";
        out << strike_price();
        out << ", call_or_put=";
        out << call_or_put();
        out << ", opening_time=";
        print::text(out, opening_time());
        out << ", closing_time=";
        print::text(out, closing_time());
        out << ", restricted_option=";
        out << restricted_option();
        out << ", long_term_option=";
        out << long_term_option();
        out << ", active_on_miax=";
        out << active_on_miax();
        out << ", miax_bbo_posting_increment_indicator=";
        out << miax_bbo_posting_increment_indicator();
        out << ", liquidity_acceptance_increment_indicator=";
        out << liquidity_acceptance_increment_indicator();
        out << ", opening_underlying_market_code=";
        out << opening_underlying_market_code();
        out << ", priority_quote_width=";
        out << priority_quote_width();
        out << ", reserved_8=";
        print::hex(out, reserved_8().data(), reserved_8().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SimpleSeriesUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
