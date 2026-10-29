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
#include "../enums/ParticipantId.hpp"
#include "../structs/ParticipantTimestamp.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/QuoteCondition.hpp"
#include "../enums/SecurityStatusIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/RetailInterestIndicator.hpp"
#include "../enums/SettlementCondition.hpp"
#include "../enums/MarketCondition.hpp"
#include "../structs/AdfTimestamp.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/SipGeneratedMessageIdentifier.hpp"
#include "../enums/FinraBboLuldIndicator.hpp"
#include "../enums/NationalBboLuldIndicator.hpp"
#include "../enums/NationalBboIndicator.hpp"
#include "../structs/NationalBestBidLongAppendage.hpp"
#include "../structs/NationalBestOfferLongAppendage.hpp"
#include "../structs/NationalBestBidShortAppendage.hpp"
#include "../structs/NationalBestOfferShortAppendage.hpp"

namespace siac::cqs::output::cta::v1_91 {

// The Special Quote (FINRA ADF) with FINRA BBO Information message is used only by FINRA to
// report the FINRA Best Bid and FINRA Best Offer for their Market Makers for Cta eligible
// Equity, Local Issue or Bond information Makers inclusive of changes to any existing FINRA
// BBO.
class SpecialLongQuoteMessage {
  public:
    static constexpr const char* name = "SpecialLongQuoteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SpecialLongQuoteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SpecialLongQuoteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 116;
    std::size_t encoded_size() const { return national_best_offer_short_appendage_end(); }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    ParticipantTimestamp participant_timestamp() const { return ParticipantTimestamp{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol_long() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    QuoteCondition quote_condition() const { return static_cast<QuoteCondition>(wire::read_char(at(34))); }

    SecurityStatusIndicator security_status_indicator() const { return static_cast<SecurityStatusIndicator>(wire::read_char(at(35))); }

    Decimal bid_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(36))), -6); }

    std::uint32_t bid_size_long() const { return wire::read_u32_be(at(44)); }

    Decimal offer_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(48))), -6); }

    std::uint32_t offer_size_long() const { return wire::read_u32_be(at(56)); }

    RetailInterestIndicator retail_interest_indicator() const { return static_cast<RetailInterestIndicator>(wire::read_char(at(60))); }

    SettlementCondition settlement_condition() const { return static_cast<SettlementCondition>(wire::read_char(at(61))); }

    MarketCondition market_condition() const { return static_cast<MarketCondition>(wire::read_char(at(62))); }

    std::string_view finra_market_maker_id() const { return view::text(at(63), 4, ' '); }

    char finra_best_bid_quote_condition() const { return wire::read_char(at(67)); }

    Decimal finra_best_bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(68))), -6); }

    std::uint32_t finra_best_bid_size() const { return wire::read_u32_be(at(76)); }

    std::string_view finra_best_bid_market_maker_id() const { return view::text(at(80), 4, ' '); }

    char finra_best_offer_quote_condition() const { return wire::read_char(at(84)); }

    Decimal finra_best_offer_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(85))), -6); }

    std::uint32_t finra_best_offer_size() const { return wire::read_u32_be(at(93)); }

    std::string_view finra_best_offer_market_maker_id() const { return view::text(at(97), 4, ' '); }

    AdfTimestamp adf_timestamp() const { return AdfTimestamp{ bytes_.subspan(101) }; }

    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const { return static_cast<ShortSaleRestrictionIndicator>(wire::read_char(at(109))); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(110))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(111))); }

    SipGeneratedMessageIdentifier sip_generated_message_identifier() const { return static_cast<SipGeneratedMessageIdentifier>(wire::read_char(at(112))); }

    FinraBboLuldIndicator finra_bbo_luld_indicator() const { return static_cast<FinraBboLuldIndicator>(wire::read_char(at(113))); }

    NationalBboLuldIndicator national_bbo_luld_indicator() const { return static_cast<NationalBboLuldIndicator>(wire::read_char(at(114))); }

    NationalBboIndicator national_bbo_indicator() const { return static_cast<NationalBboIndicator>(wire::read_char(at(115))); }

    std::optional<NationalBestBidLongAppendage> national_best_bid_long_appendage() const {
        if (!(static_cast<char>(national_bbo_indicator()) == 'U')) { return std::nullopt; }
        wire::require("SpecialLongQuoteMessage", 116 + NationalBestBidLongAppendage::minimum_size, bytes_.size());
        return NationalBestBidLongAppendage{ bytes_.subspan(116) };
    }

    std::optional<NationalBestOfferLongAppendage> national_best_offer_long_appendage() const {
        if (!(static_cast<char>(national_bbo_indicator()) == 'U')) { return std::nullopt; }
        wire::require("SpecialLongQuoteMessage", national_best_bid_long_appendage_end() + NationalBestOfferLongAppendage::minimum_size, bytes_.size());
        return NationalBestOfferLongAppendage{ bytes_.subspan(national_best_bid_long_appendage_end()) };
    }

    std::optional<NationalBestBidShortAppendage> national_best_bid_short_appendage() const {
        if (!(static_cast<char>(national_bbo_indicator()) == 'T')) { return std::nullopt; }
        wire::require("SpecialLongQuoteMessage", national_best_offer_long_appendage_end() + NationalBestBidShortAppendage::minimum_size, bytes_.size());
        return NationalBestBidShortAppendage{ bytes_.subspan(national_best_offer_long_appendage_end()) };
    }

    std::optional<NationalBestOfferShortAppendage> national_best_offer_short_appendage() const {
        if (!(static_cast<char>(national_bbo_indicator()) == 'T')) { return std::nullopt; }
        wire::require("SpecialLongQuoteMessage", national_best_bid_short_appendage_end() + NationalBestOfferShortAppendage::minimum_size, bytes_.size());
        return NationalBestOfferShortAppendage{ bytes_.subspan(national_best_bid_short_appendage_end()) };
    }

    void print(std::ostream& out) const {
        out << "SpecialLongQuoteMessage{";
        out << "participant_id=";
        out << participant_id();
        out << ", participant_timestamp=";
        participant_timestamp().print(out);
        out << ", message_id=";
        out << static_cast<int>(message_id());
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << ", security_symbol_long=";
        print::text(out, security_symbol_long());
        out << ", instrument_type=";
        out << instrument_type();
        out << ", quote_condition=";
        out << quote_condition();
        out << ", security_status_indicator=";
        out << security_status_indicator();
        out << ", bid_price_long=";
        out << bid_price_long();
        out << ", bid_size_long=";
        out << bid_size_long();
        out << ", offer_price_long=";
        out << offer_price_long();
        out << ", offer_size_long=";
        out << offer_size_long();
        out << ", retail_interest_indicator=";
        out << retail_interest_indicator();
        out << ", settlement_condition=";
        out << settlement_condition();
        out << ", market_condition=";
        out << market_condition();
        out << ", finra_market_maker_id=";
        print::text(out, finra_market_maker_id());
        out << ", finra_best_bid_quote_condition=";
        print::character(out, finra_best_bid_quote_condition());
        out << ", finra_best_bid_price=";
        out << finra_best_bid_price();
        out << ", finra_best_bid_size=";
        out << finra_best_bid_size();
        out << ", finra_best_bid_market_maker_id=";
        print::text(out, finra_best_bid_market_maker_id());
        out << ", finra_best_offer_quote_condition=";
        print::character(out, finra_best_offer_quote_condition());
        out << ", finra_best_offer_price=";
        out << finra_best_offer_price();
        out << ", finra_best_offer_size=";
        out << finra_best_offer_size();
        out << ", finra_best_offer_market_maker_id=";
        print::text(out, finra_best_offer_market_maker_id());
        out << ", adf_timestamp=";
        adf_timestamp().print(out);
        out << ", short_sale_restriction_indicator=";
        out << short_sale_restriction_indicator();
        out << ", primary_listing_market_participant_id=";
        out << primary_listing_market_participant_id();
        out << ", financial_status_indicator=";
        out << financial_status_indicator();
        out << ", sip_generated_message_identifier=";
        out << sip_generated_message_identifier();
        out << ", finra_bbo_luld_indicator=";
        out << finra_bbo_luld_indicator();
        out << ", national_bbo_luld_indicator=";
        out << national_bbo_luld_indicator();
        out << ", national_bbo_indicator=";
        out << national_bbo_indicator();
        out << ", national_best_bid_long_appendage=";
        print::optional(out, national_best_bid_long_appendage());
        out << ", national_best_offer_long_appendage=";
        print::optional(out, national_best_offer_long_appendage());
        out << ", national_best_bid_short_appendage=";
        print::optional(out, national_best_bid_short_appendage());
        out << ", national_best_offer_short_appendage=";
        print::optional(out, national_best_offer_short_appendage());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t national_best_bid_long_appendage_end() const { return 116 + (national_best_bid_long_appendage() ? national_best_bid_long_appendage()->encoded_size() : 0); }
    std::size_t national_best_offer_long_appendage_end() const { return national_best_bid_long_appendage_end() + (national_best_offer_long_appendage() ? national_best_offer_long_appendage()->encoded_size() : 0); }
    std::size_t national_best_bid_short_appendage_end() const { return national_best_offer_long_appendage_end() + (national_best_bid_short_appendage() ? national_best_bid_short_appendage()->encoded_size() : 0); }
    std::size_t national_best_offer_short_appendage_end() const { return national_best_bid_short_appendage_end() + (national_best_offer_short_appendage() ? national_best_offer_short_appendage()->encoded_size() : 0); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SpecialLongQuoteMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v1_91
