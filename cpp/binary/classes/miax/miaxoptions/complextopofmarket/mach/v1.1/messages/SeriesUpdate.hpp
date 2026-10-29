#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ActiveOnMiax.hpp"
#include "../enums/CallOrPut.hpp"
#include "../enums/LiquidityAcceptanceIncrementIndicator.hpp"
#include "../enums/LongTermOption.hpp"
#include "../enums/MiaxBboPostingIncrementIndicator.hpp"
#include "../enums/OpeningUnderlyingMarketCode.hpp"
#include "../enums/RestrictedOption.hpp"
#include "../messages/Data.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

class DataVisitor;

// This is the message format that will be used to disseminate all Option series traded on MIAX
// for the current session. The product ID sent in this message is what will be disseminated in
// Top of Market BBO and Last Sale messages.
class SeriesUpdate : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::SeriesUpdate;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 72;

    SeriesUpdate() = default;
    SeriesUpdate(std::chrono::nanoseconds nanoseconds, std::uint32_t product_id, const std::string& underlying_symbol, const std::string& security_symbol, const std::string& expiration_date, Decimal strike_price, CallOrPut call_or_put, const std::string& opening_time, const std::string& closing_time, RestrictedOption restricted_option, LongTermOption long_term_option, ActiveOnMiax active_on_miax, MiaxBboPostingIncrementIndicator miax_bbo_posting_increment_indicator, LiquidityAcceptanceIncrementIndicator liquidity_acceptance_increment_indicator, OpeningUnderlyingMarketCode opening_underlying_market_code, Decimal priority_quote_width, const std::array<std::byte, 8>& reserved_8);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Product Id: MIAX Product ID mapped to a given option. It is assigned per trading session
    // and is valid for that session.
    std::uint32_t product_id() const;
    void set_product_id(std::uint32_t value);

    // Underlying Symbol: Stock Symbol for the option.
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Security Symbol: Option Security Symbol
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Expiration Date: Expiration date of the option in YYYYMMDD format
    const std::string& expiration_date() const;
    std::string& expiration_date();
    void set_expiration_date(const std::string& value);

    // Strike Price: Explicit strike price of the option. Refer to data types for field
    // processing notes
    Decimal strike_price() const;
    void set_strike_price(Decimal value);

    // Call Or Put: Option Type: “C” = Call, “P” = Put
    CallOrPut call_or_put() const;
    void set_call_or_put(CallOrPut value);

    // Opening Time: Expressed in HH:MM:SS format. Eg: 09:30:00
    const std::string& opening_time() const;
    std::string& opening_time();
    void set_opening_time(const std::string& value);

    // Closing Time: Expressed in HH:MM:SS format. Eg: 16:15:00
    const std::string& closing_time() const;
    std::string& closing_time();
    void set_closing_time(const std::string& value);

    // Restricted Option: Restricted Option
    RestrictedOption restricted_option() const;
    void set_restricted_option(RestrictedOption value);

    // Long Term Option: Long Term Option
    LongTermOption long_term_option() const;
    void set_long_term_option(LongTermOption value);

    // Active On Miax: Indicates if this symbol is tradable on MIAX in the current session: “A”
    // = Active (tradable) on MIAX “I” = Inactive (not tradable) on MIAX
    ActiveOnMiax active_on_miax() const;
    void set_active_on_miax(ActiveOnMiax value);

    // Miax Bbo Posting Increment Indicator: This is the Minimum Price Variation as agreed to
    // by the Options industry (penny pilot program) and as published by MIAX
    MiaxBboPostingIncrementIndicator miax_bbo_posting_increment_indicator() const;
    void set_miax_bbo_posting_increment_indicator(MiaxBboPostingIncrementIndicator value);

    // Liquidity Acceptance Increment Indicator: This is the Minimum Price Variation for
    // Quote/Order acceptance as per MIAX rules
    LiquidityAcceptanceIncrementIndicator liquidity_acceptance_increment_indicator() const;
    void set_liquidity_acceptance_increment_indicator(LiquidityAcceptanceIncrementIndicator value);

    // Opening Underlying Market Code: Options opening will be triggered on receipt of Opening
    // quote/trade from this Underlying market:
    OpeningUnderlyingMarketCode opening_underlying_market_code() const;
    void set_opening_underlying_market_code(OpeningUnderlyingMarketCode value);

    // Priority Quote Width: Maximum allowable width for a quote for this Option during regular
    // trading in order to be considered as Priority Quote. 0 when Priority Quote Width is not
    // applicable.
    Decimal priority_quote_width() const;
    void set_priority_quote_width(Decimal value);

    // Reserved 8: Reserved for future use
    const std::array<std::byte, 8>& reserved_8() const;
    std::array<std::byte, 8>& reserved_8();
    void set_reserved_8(const std::array<std::byte, 8>& value);

    // Data
    DataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(DataVisitor& visitor) const override;
    std::unique_ptr<Data> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Data& other) const override;

    bool operator==(const SeriesUpdate& other) const;
    bool operator!=(const SeriesUpdate& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t product_id_{};
    std::string underlying_symbol_{};
    std::string security_symbol_{};
    std::string expiration_date_{};
    Decimal strike_price_{ 0, -4 };
    CallOrPut call_or_put_{};
    std::string opening_time_{};
    std::string closing_time_{};
    RestrictedOption restricted_option_{};
    LongTermOption long_term_option_{};
    ActiveOnMiax active_on_miax_{};
    MiaxBboPostingIncrementIndicator miax_bbo_posting_increment_indicator_{};
    LiquidityAcceptanceIncrementIndicator liquidity_acceptance_increment_indicator_{};
    OpeningUnderlyingMarketCode opening_underlying_market_code_{};
    Decimal priority_quote_width_{ 0, -4 };
    std::array<std::byte, 8> reserved_8_{};
};

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
