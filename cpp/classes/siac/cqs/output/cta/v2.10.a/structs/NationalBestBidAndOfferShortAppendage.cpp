#include "NationalBestBidAndOfferShortAppendage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cqs::output::cta::v2_10_a {

NationalBestBidAndOfferShortAppendage::NationalBestBidAndOfferShortAppendage(char best_bid_participant_id, Decimal best_bid_price_short, std::uint16_t best_bid_size_short, char best_offer_participant_id, Decimal best_offer_price_short, std::uint16_t best_offer_size_short)
  : best_bid_participant_id_(best_bid_participant_id), best_bid_price_short_(best_bid_price_short), best_bid_size_short_(best_bid_size_short), best_offer_participant_id_(best_offer_participant_id), best_offer_price_short_(best_offer_price_short), best_offer_size_short_(best_offer_size_short) {}

char NationalBestBidAndOfferShortAppendage::best_bid_participant_id() const { return best_bid_participant_id_; }
void NationalBestBidAndOfferShortAppendage::set_best_bid_participant_id(char value) { best_bid_participant_id_ = value; }

Decimal NationalBestBidAndOfferShortAppendage::best_bid_price_short() const { return best_bid_price_short_; }
void NationalBestBidAndOfferShortAppendage::set_best_bid_price_short(Decimal value) { best_bid_price_short_ = value; }

std::uint16_t NationalBestBidAndOfferShortAppendage::best_bid_size_short() const { return best_bid_size_short_; }
void NationalBestBidAndOfferShortAppendage::set_best_bid_size_short(std::uint16_t value) { best_bid_size_short_ = value; }

char NationalBestBidAndOfferShortAppendage::best_offer_participant_id() const { return best_offer_participant_id_; }
void NationalBestBidAndOfferShortAppendage::set_best_offer_participant_id(char value) { best_offer_participant_id_ = value; }

Decimal NationalBestBidAndOfferShortAppendage::best_offer_price_short() const { return best_offer_price_short_; }
void NationalBestBidAndOfferShortAppendage::set_best_offer_price_short(Decimal value) { best_offer_price_short_ = value; }

std::uint16_t NationalBestBidAndOfferShortAppendage::best_offer_size_short() const { return best_offer_size_short_; }
void NationalBestBidAndOfferShortAppendage::set_best_offer_size_short(std::uint16_t value) { best_offer_size_short_ = value; }

std::size_t NationalBestBidAndOfferShortAppendage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NationalBestBidAndOfferShortAppendage", wire_size, length);

    best_bid_participant_id_ = wire::read_char(data + offset);
    offset += 1;

    best_bid_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    best_bid_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    best_offer_participant_id_ = wire::read_char(data + offset);
    offset += 1;

    best_offer_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    best_offer_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t NationalBestBidAndOfferShortAppendage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NationalBestBidAndOfferShortAppendage", wire_size, capacity);

    wire::write_char(data + offset, best_bid_participant_id_);
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(best_bid_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(best_bid_size_short_));
    offset += 2;

    wire::write_char(data + offset, best_offer_participant_id_);
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(best_offer_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(best_offer_size_short_));
    offset += 2;

    return offset;
}

std::size_t NationalBestBidAndOfferShortAppendage::encoded_size() const {
    return wire_size;
}

void NationalBestBidAndOfferShortAppendage::print(std::ostream& out) const {
    out << "NationalBestBidAndOfferShortAppendage{";
    out << "best_bid_participant_id=";
    print::character(out, best_bid_participant_id_);
    out << ", best_bid_price_short=";
    out << best_bid_price_short_;
    out << ", best_bid_size_short=";
    out << best_bid_size_short_;
    out << ", best_offer_participant_id=";
    print::character(out, best_offer_participant_id_);
    out << ", best_offer_price_short=";
    out << best_offer_price_short_;
    out << ", best_offer_size_short=";
    out << best_offer_size_short_;
    out << '}';
}

bool NationalBestBidAndOfferShortAppendage::operator==(const NationalBestBidAndOfferShortAppendage& other) const {
    return best_bid_participant_id_ == other.best_bid_participant_id_
        && best_bid_price_short_ == other.best_bid_price_short_
        && best_bid_size_short_ == other.best_bid_size_short_
        && best_offer_participant_id_ == other.best_offer_participant_id_
        && best_offer_price_short_ == other.best_offer_price_short_
        && best_offer_size_short_ == other.best_offer_size_short_;
}

bool NationalBestBidAndOfferShortAppendage::operator!=(const NationalBestBidAndOfferShortAppendage& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NationalBestBidAndOfferShortAppendage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v2_10_a
