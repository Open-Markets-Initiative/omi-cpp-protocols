#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/BboIndicator.hpp"
#include "../structs/ExpirationBlock.hpp"
#include "../enums/StrikePriceDenominatorCode.hpp"
#include "../common/Decimal.hpp"
#include "../enums/PremiumPriceDenominatorCode.hpp"
#include "../structs/BestBidAppendage.hpp"
#include "../structs/BestOfferAppendage.hpp"
#include "../structs/BestBidAndOfferAppendage.hpp"

namespace siac::opra::output::obi::v6_2 {

// Long Equity and Index Quote Message
class LongEquityAndIndexQuoteMessage {
  public:
    static constexpr const char* name = "LongEquityAndIndexQuoteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LongEquityAndIndexQuoteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LongEquityAndIndexQuoteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    std::size_t encoded_size() const { return best_bid_and_offer_appendage_end(); }

    BboIndicator bbo_indicator() const { return static_cast<BboIndicator>(wire::read_char(at(0))); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(1)); }

    std::uint32_t participant_reference_number() const { return wire::read_u32_be(at(5)); }

    std::string_view security_symbol() const { return view::text(at(9), 5, ' '); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(14).template first<1>(); }

    ExpirationBlock expiration_block() const { return ExpirationBlock{ bytes_.subspan(15) }; }

    StrikePriceDenominatorCode strike_price_denominator_code() const { return static_cast<StrikePriceDenominatorCode>(wire::read_char(at(18))); }

    // the exponent strike_price_denominator_code states, or 0 for a code it does not state
    static constexpr int strike_price_exponent(char code) {
        switch (code) {
            case 'A': return -1;
            case 'B': return -2;
            case 'C': return -3;
            case 'D': return -4;
            case 'E': return -5;
            case 'I': return 0;
            default: return 0;
        }
    }
    Decimal strike_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(19))), strike_price_exponent(static_cast<char>(strike_price_denominator_code()))); }

    PremiumPriceDenominatorCode premium_price_denominator_code() const { return static_cast<PremiumPriceDenominatorCode>(wire::read_char(at(23))); }

    std::int32_t bid_price() const { return wire::read_i32_be(at(24)); }

    std::uint32_t bid_size() const { return wire::read_u32_be(at(28)); }

    std::int32_t offer_price() const { return wire::read_i32_be(at(32)); }

    std::uint32_t offer_size() const { return wire::read_u32_be(at(36)); }

    std::optional<BestBidAppendage> best_bid_appendage() const {
        if (!(static_cast<char>(bbo_indicator()) == 'M')) { return std::nullopt; }
        wire::require("LongEquityAndIndexQuoteMessage", 40 + BestBidAppendage::minimum_size, bytes_.size());
        return BestBidAppendage{ bytes_.subspan(40) };
    }

    std::optional<BestOfferAppendage> best_offer_appendage() const {
        if (!(static_cast<char>(bbo_indicator()) == 'C')) { return std::nullopt; }
        wire::require("LongEquityAndIndexQuoteMessage", best_bid_appendage_end() + BestOfferAppendage::minimum_size, bytes_.size());
        return BestOfferAppendage{ bytes_.subspan(best_bid_appendage_end()) };
    }

    std::optional<BestBidAndOfferAppendage> best_bid_and_offer_appendage() const {
        if (!(static_cast<char>(bbo_indicator()) == 'O')) { return std::nullopt; }
        wire::require("LongEquityAndIndexQuoteMessage", best_offer_appendage_end() + BestBidAndOfferAppendage::minimum_size, bytes_.size());
        return BestBidAndOfferAppendage{ bytes_.subspan(best_offer_appendage_end()) };
    }

    void print(std::ostream& out) const {
        out << "LongEquityAndIndexQuoteMessage{";
        out << "bbo_indicator=";
        out << bbo_indicator();
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << ", security_symbol=";
        print::text(out, security_symbol());
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", expiration_block=";
        expiration_block().print(out);
        out << ", strike_price_denominator_code=";
        out << strike_price_denominator_code();
        out << ", strike_price=";
        out << strike_price();
        out << ", premium_price_denominator_code=";
        out << premium_price_denominator_code();
        out << ", bid_price=";
        out << bid_price();
        out << ", bid_size=";
        out << bid_size();
        out << ", offer_price=";
        out << offer_price();
        out << ", offer_size=";
        out << offer_size();
        out << ", best_bid_appendage=";
        print::optional(out, best_bid_appendage());
        out << ", best_offer_appendage=";
        print::optional(out, best_offer_appendage());
        out << ", best_bid_and_offer_appendage=";
        print::optional(out, best_bid_and_offer_appendage());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t best_bid_appendage_end() const { return 40 + (best_bid_appendage() ? best_bid_appendage()->encoded_size() : 0); }
    std::size_t best_offer_appendage_end() const { return best_bid_appendage_end() + (best_offer_appendage() ? best_offer_appendage()->encoded_size() : 0); }
    std::size_t best_bid_and_offer_appendage_end() const { return best_offer_appendage_end() + (best_bid_and_offer_appendage() ? best_bid_and_offer_appendage()->encoded_size() : 0); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LongEquityAndIndexQuoteMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
