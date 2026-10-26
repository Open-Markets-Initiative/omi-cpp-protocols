#include "NationalBestBidAndOfferLongAppendage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cqs::output::cta::v2_10_a {

NationalBestBidAndOfferLongAppendage::NationalBestBidAndOfferLongAppendage(char best_bid_participant_id, char best_bid_quote_condition, Decimal best_bid_price_long, std::uint32_t best_bid_size_long, const std::string& finra_best_bid_market_maker_id, char best_offer_participant_id, char best_offer_quote_condition, Decimal best_offer_price_long, std::uint32_t best_offer_size_long, const std::string& finra_best_offer_market_maker_id)
  : best_bid_participant_id_(best_bid_participant_id), best_bid_quote_condition_(best_bid_quote_condition), best_bid_price_long_(best_bid_price_long), best_bid_size_long_(best_bid_size_long), finra_best_bid_market_maker_id_(finra_best_bid_market_maker_id), best_offer_participant_id_(best_offer_participant_id), best_offer_quote_condition_(best_offer_quote_condition), best_offer_price_long_(best_offer_price_long), best_offer_size_long_(best_offer_size_long), finra_best_offer_market_maker_id_(finra_best_offer_market_maker_id) {}

char NationalBestBidAndOfferLongAppendage::best_bid_participant_id() const { return best_bid_participant_id_; }
void NationalBestBidAndOfferLongAppendage::set_best_bid_participant_id(char value) { best_bid_participant_id_ = value; }

char NationalBestBidAndOfferLongAppendage::best_bid_quote_condition() const { return best_bid_quote_condition_; }
void NationalBestBidAndOfferLongAppendage::set_best_bid_quote_condition(char value) { best_bid_quote_condition_ = value; }

Decimal NationalBestBidAndOfferLongAppendage::best_bid_price_long() const { return best_bid_price_long_; }
void NationalBestBidAndOfferLongAppendage::set_best_bid_price_long(Decimal value) { best_bid_price_long_ = value; }

std::uint32_t NationalBestBidAndOfferLongAppendage::best_bid_size_long() const { return best_bid_size_long_; }
void NationalBestBidAndOfferLongAppendage::set_best_bid_size_long(std::uint32_t value) { best_bid_size_long_ = value; }

const std::string& NationalBestBidAndOfferLongAppendage::finra_best_bid_market_maker_id() const { return finra_best_bid_market_maker_id_; }
std::string& NationalBestBidAndOfferLongAppendage::finra_best_bid_market_maker_id() { return finra_best_bid_market_maker_id_; }
void NationalBestBidAndOfferLongAppendage::set_finra_best_bid_market_maker_id(const std::string& value) { finra_best_bid_market_maker_id_ = value; }

char NationalBestBidAndOfferLongAppendage::best_offer_participant_id() const { return best_offer_participant_id_; }
void NationalBestBidAndOfferLongAppendage::set_best_offer_participant_id(char value) { best_offer_participant_id_ = value; }

char NationalBestBidAndOfferLongAppendage::best_offer_quote_condition() const { return best_offer_quote_condition_; }
void NationalBestBidAndOfferLongAppendage::set_best_offer_quote_condition(char value) { best_offer_quote_condition_ = value; }

Decimal NationalBestBidAndOfferLongAppendage::best_offer_price_long() const { return best_offer_price_long_; }
void NationalBestBidAndOfferLongAppendage::set_best_offer_price_long(Decimal value) { best_offer_price_long_ = value; }

std::uint32_t NationalBestBidAndOfferLongAppendage::best_offer_size_long() const { return best_offer_size_long_; }
void NationalBestBidAndOfferLongAppendage::set_best_offer_size_long(std::uint32_t value) { best_offer_size_long_ = value; }

const std::string& NationalBestBidAndOfferLongAppendage::finra_best_offer_market_maker_id() const { return finra_best_offer_market_maker_id_; }
std::string& NationalBestBidAndOfferLongAppendage::finra_best_offer_market_maker_id() { return finra_best_offer_market_maker_id_; }
void NationalBestBidAndOfferLongAppendage::set_finra_best_offer_market_maker_id(const std::string& value) { finra_best_offer_market_maker_id_ = value; }

std::size_t NationalBestBidAndOfferLongAppendage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NationalBestBidAndOfferLongAppendage", wire_size, length);

    best_bid_participant_id_ = wire::read_char(data + offset);
    offset += 1;

    best_bid_quote_condition_ = wire::read_char(data + offset);
    offset += 1;

    best_bid_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    best_bid_size_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    finra_best_bid_market_maker_id_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    best_offer_participant_id_ = wire::read_char(data + offset);
    offset += 1;

    best_offer_quote_condition_ = wire::read_char(data + offset);
    offset += 1;

    best_offer_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    best_offer_size_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    finra_best_offer_market_maker_id_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t NationalBestBidAndOfferLongAppendage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NationalBestBidAndOfferLongAppendage", wire_size, capacity);

    wire::write_char(data + offset, best_bid_participant_id_);
    offset += 1;

    wire::write_char(data + offset, best_bid_quote_condition_);
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(best_bid_price_long_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(best_bid_size_long_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', finra_best_bid_market_maker_id_);
    offset += 4;

    wire::write_char(data + offset, best_offer_participant_id_);
    offset += 1;

    wire::write_char(data + offset, best_offer_quote_condition_);
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(best_offer_price_long_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(best_offer_size_long_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', finra_best_offer_market_maker_id_);
    offset += 4;

    return offset;
}

std::size_t NationalBestBidAndOfferLongAppendage::encoded_size() const {
    return wire_size;
}

void NationalBestBidAndOfferLongAppendage::print(std::ostream& out) const {
    out << "NationalBestBidAndOfferLongAppendage{";
    out << "best_bid_participant_id=";
    print::character(out, best_bid_participant_id_);
    out << ", best_bid_quote_condition=";
    print::character(out, best_bid_quote_condition_);
    out << ", best_bid_price_long=";
    out << best_bid_price_long_;
    out << ", best_bid_size_long=";
    out << best_bid_size_long_;
    out << ", finra_best_bid_market_maker_id=";
    print::text(out, finra_best_bid_market_maker_id_);
    out << ", best_offer_participant_id=";
    print::character(out, best_offer_participant_id_);
    out << ", best_offer_quote_condition=";
    print::character(out, best_offer_quote_condition_);
    out << ", best_offer_price_long=";
    out << best_offer_price_long_;
    out << ", best_offer_size_long=";
    out << best_offer_size_long_;
    out << ", finra_best_offer_market_maker_id=";
    print::text(out, finra_best_offer_market_maker_id_);
    out << '}';
}

bool NationalBestBidAndOfferLongAppendage::operator==(const NationalBestBidAndOfferLongAppendage& other) const {
    return best_bid_participant_id_ == other.best_bid_participant_id_
        && best_bid_quote_condition_ == other.best_bid_quote_condition_
        && best_bid_price_long_ == other.best_bid_price_long_
        && best_bid_size_long_ == other.best_bid_size_long_
        && finra_best_bid_market_maker_id_ == other.finra_best_bid_market_maker_id_
        && best_offer_participant_id_ == other.best_offer_participant_id_
        && best_offer_quote_condition_ == other.best_offer_quote_condition_
        && best_offer_price_long_ == other.best_offer_price_long_
        && best_offer_size_long_ == other.best_offer_size_long_
        && finra_best_offer_market_maker_id_ == other.finra_best_offer_market_maker_id_;
}

bool NationalBestBidAndOfferLongAppendage::operator!=(const NationalBestBidAndOfferLongAppendage& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NationalBestBidAndOfferLongAppendage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v2_10_a
