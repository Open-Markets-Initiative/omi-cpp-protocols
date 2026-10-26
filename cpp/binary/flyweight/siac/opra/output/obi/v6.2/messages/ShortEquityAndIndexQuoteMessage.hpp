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
#include "../common/Decimal.hpp"
#include "../structs/BestBidAppendage.hpp"
#include "../structs/BestOfferAppendage.hpp"
#include "../structs/BestBidAndOfferAppendage.hpp"

namespace siac::opra::output::obi::v6_2 {

// Short Equity and Index Quote Message
class ShortEquityAndIndexQuoteMessage {
  public:
    static constexpr const char* name = "ShortEquityAndIndexQuoteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ShortEquityAndIndexQuoteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ShortEquityAndIndexQuoteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 26;
    std::size_t encoded_size() const { return best_bid_and_offer_appendage_end(); }

    BboIndicator bbo_indicator() const { return static_cast<BboIndicator>(wire::read_char(at(0))); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(1)); }

    std::uint32_t participant_reference_number() const { return wire::read_u32_be(at(5)); }

    std::string_view security_symbol_short() const { return view::text(at(9), 4, ' '); }

    ExpirationBlock expiration_block() const { return ExpirationBlock{ bytes_.subspan(13) }; }

    Decimal strike_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(16))), -1); }

    Decimal bid_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(18))), -2); }

    std::uint16_t bid_size_short() const { return wire::read_u16_be(at(20)); }

    Decimal offer_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(22))), -2); }

    std::uint16_t offer_size_short() const { return wire::read_u16_be(at(24)); }

    std::optional<BestBidAppendage> best_bid_appendage() const {
        if (!(static_cast<char>(bbo_indicator()) == 'M')) { return std::nullopt; }
        wire::require("ShortEquityAndIndexQuoteMessage", 26 + BestBidAppendage::minimum_size, bytes_.size());
        return BestBidAppendage{ bytes_.subspan(26) };
    }

    std::optional<BestOfferAppendage> best_offer_appendage() const {
        if (!(static_cast<char>(bbo_indicator()) == 'C')) { return std::nullopt; }
        wire::require("ShortEquityAndIndexQuoteMessage", best_bid_appendage_end() + BestOfferAppendage::minimum_size, bytes_.size());
        return BestOfferAppendage{ bytes_.subspan(best_bid_appendage_end()) };
    }

    std::optional<BestBidAndOfferAppendage> best_bid_and_offer_appendage() const {
        if (!(static_cast<char>(bbo_indicator()) == 'O')) { return std::nullopt; }
        wire::require("ShortEquityAndIndexQuoteMessage", best_offer_appendage_end() + BestBidAndOfferAppendage::minimum_size, bytes_.size());
        return BestBidAndOfferAppendage{ bytes_.subspan(best_offer_appendage_end()) };
    }

    void print(std::ostream& out) const {
        out << "ShortEquityAndIndexQuoteMessage{";
        out << "bbo_indicator=";
        out << bbo_indicator();
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << ", security_symbol_short=";
        print::text(out, security_symbol_short());
        out << ", expiration_block=";
        expiration_block().print(out);
        out << ", strike_price_short=";
        out << strike_price_short();
        out << ", bid_price_short=";
        out << bid_price_short();
        out << ", bid_size_short=";
        out << bid_size_short();
        out << ", offer_price_short=";
        out << offer_price_short();
        out << ", offer_size_short=";
        out << offer_size_short();
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
    std::size_t best_bid_appendage_end() const { return 26 + (best_bid_appendage() ? best_bid_appendage()->encoded_size() : 0); }
    std::size_t best_offer_appendage_end() const { return best_bid_appendage_end() + (best_offer_appendage() ? best_offer_appendage()->encoded_size() : 0); }
    std::size_t best_bid_and_offer_appendage_end() const { return best_offer_appendage_end() + (best_bid_and_offer_appendage() ? best_bid_and_offer_appendage()->encoded_size() : 0); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ShortEquityAndIndexQuoteMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
