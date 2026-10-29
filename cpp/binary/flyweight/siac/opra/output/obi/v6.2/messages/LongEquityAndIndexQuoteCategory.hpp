#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/LongEquityAndIndexQuoteMessageType.hpp"
#include "../messages/LongEquityAndIndexQuoteMessage.hpp"

namespace siac::opra::output::obi::v6_2 {

// Long Equity And Index Quote Message
class LongEquityAndIndexQuoteCategory {
  public:
    static constexpr const char* name = "LongEquityAndIndexQuoteCategory";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LongEquityAndIndexQuoteCategory(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LongEquityAndIndexQuoteCategory has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return long_equity_and_index_quote_message_payload_end(); }

    LongEquityAndIndexQuoteMessageType long_equity_and_index_quote_message_type() const { return static_cast<LongEquityAndIndexQuoteMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> long_equity_and_index_quote_message_payload_bytes() const {
        wire::require("LongEquityAndIndexQuoteCategory", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its long_equity_and_index_quote_message_type selects, handed to the handler as its view
    template <typename Handler>
    void long_equity_and_index_quote_message_payload(Handler& handler) const {
        const auto bytes = long_equity_and_index_quote_message_payload_bytes();
        switch (long_equity_and_index_quote_message_type()) {
            case LongEquityAndIndexQuoteMessageType::RegularTrading: case LongEquityAndIndexQuoteMessageType::NonFirmQuote: case LongEquityAndIndexQuoteMessageType::IndicativeValue: case LongEquityAndIndexQuoteMessageType::Rotation: case LongEquityAndIndexQuoteMessageType::TradingHalted: case LongEquityAndIndexQuoteMessageType::EligibleForAutomaticExecution: case LongEquityAndIndexQuoteMessageType::BidContainsCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::OfferContainsCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::BothBidAndOfferContainCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::OfferSideOfQuoteNotFirmBidSideFirm: case LongEquityAndIndexQuoteMessageType::BidSideOfQuoteNotFirmOfferSideFirm: {
                wire::require(LongEquityAndIndexQuoteMessage::name, LongEquityAndIndexQuoteMessage::minimum_size, bytes.size());
                const LongEquityAndIndexQuoteMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(long_equity_and_index_quote_message_type(), bytes); }) { handler.on_unknown(long_equity_and_index_quote_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t long_equity_and_index_quote_message_payload_size() const {
        const auto bytes = long_equity_and_index_quote_message_payload_bytes();
        switch (long_equity_and_index_quote_message_type()) {
            case LongEquityAndIndexQuoteMessageType::RegularTrading: case LongEquityAndIndexQuoteMessageType::NonFirmQuote: case LongEquityAndIndexQuoteMessageType::IndicativeValue: case LongEquityAndIndexQuoteMessageType::Rotation: case LongEquityAndIndexQuoteMessageType::TradingHalted: case LongEquityAndIndexQuoteMessageType::EligibleForAutomaticExecution: case LongEquityAndIndexQuoteMessageType::BidContainsCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::OfferContainsCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::BothBidAndOfferContainCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::OfferSideOfQuoteNotFirmBidSideFirm: case LongEquityAndIndexQuoteMessageType::BidSideOfQuoteNotFirmOfferSideFirm: return LongEquityAndIndexQuoteMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void long_equity_and_index_quote_message_payload_print(std::ostream& out) const {
        const auto bytes = long_equity_and_index_quote_message_payload_bytes();
        switch (long_equity_and_index_quote_message_type()) {
            case LongEquityAndIndexQuoteMessageType::RegularTrading: case LongEquityAndIndexQuoteMessageType::NonFirmQuote: case LongEquityAndIndexQuoteMessageType::IndicativeValue: case LongEquityAndIndexQuoteMessageType::Rotation: case LongEquityAndIndexQuoteMessageType::TradingHalted: case LongEquityAndIndexQuoteMessageType::EligibleForAutomaticExecution: case LongEquityAndIndexQuoteMessageType::BidContainsCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::OfferContainsCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::BothBidAndOfferContainCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::OfferSideOfQuoteNotFirmBidSideFirm: case LongEquityAndIndexQuoteMessageType::BidSideOfQuoteNotFirmOfferSideFirm: LongEquityAndIndexQuoteMessage{ bytes }.print(out); return;
            default:
                out << "UnknownLongEquityAndIndexQuoteMessagePayload{type=" << long_equity_and_index_quote_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "LongEquityAndIndexQuoteCategory{";
        out << "long_equity_and_index_quote_message_type=";
        out << long_equity_and_index_quote_message_type();
        out << ", long_equity_and_index_quote_message_payload=";
        long_equity_and_index_quote_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t long_equity_and_index_quote_message_payload_end() const { return 1 + long_equity_and_index_quote_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LongEquityAndIndexQuoteCategory& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
