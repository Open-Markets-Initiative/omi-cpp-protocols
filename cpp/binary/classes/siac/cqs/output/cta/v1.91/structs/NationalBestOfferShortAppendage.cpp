#include "NationalBestOfferShortAppendage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cqs::output::cta::v1_91 {

NationalBestOfferShortAppendage::NationalBestOfferShortAppendage(BestOfferParticipantId best_offer_participant_id, Decimal best_offer_price_short, std::uint16_t best_offer_size_short)
  : best_offer_participant_id_(best_offer_participant_id), best_offer_price_short_(best_offer_price_short), best_offer_size_short_(best_offer_size_short) {}

BestOfferParticipantId NationalBestOfferShortAppendage::best_offer_participant_id() const { return best_offer_participant_id_; }
void NationalBestOfferShortAppendage::set_best_offer_participant_id(BestOfferParticipantId value) { best_offer_participant_id_ = value; }

Decimal NationalBestOfferShortAppendage::best_offer_price_short() const { return best_offer_price_short_; }
void NationalBestOfferShortAppendage::set_best_offer_price_short(Decimal value) { best_offer_price_short_ = value; }

std::uint16_t NationalBestOfferShortAppendage::best_offer_size_short() const { return best_offer_size_short_; }
void NationalBestOfferShortAppendage::set_best_offer_size_short(std::uint16_t value) { best_offer_size_short_ = value; }

std::size_t NationalBestOfferShortAppendage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NationalBestOfferShortAppendage", wire_size, length);

    best_offer_participant_id_ = static_cast<BestOfferParticipantId>(wire::read_char(data + offset));
    offset += 1;

    best_offer_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    best_offer_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t NationalBestOfferShortAppendage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NationalBestOfferShortAppendage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(best_offer_participant_id_));
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(best_offer_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(best_offer_size_short_));
    offset += 2;

    return offset;
}

std::size_t NationalBestOfferShortAppendage::encoded_size() const {
    return wire_size;
}

void NationalBestOfferShortAppendage::print(std::ostream& out) const {
    out << "NationalBestOfferShortAppendage{";
    out << "best_offer_participant_id=";
    out << best_offer_participant_id_;
    out << ", best_offer_price_short=";
    out << best_offer_price_short_;
    out << ", best_offer_size_short=";
    out << best_offer_size_short_;
    out << '}';
}

bool NationalBestOfferShortAppendage::operator==(const NationalBestOfferShortAppendage& other) const {
    return best_offer_participant_id_ == other.best_offer_participant_id_
        && best_offer_price_short_ == other.best_offer_price_short_
        && best_offer_size_short_ == other.best_offer_size_short_;
}

bool NationalBestOfferShortAppendage::operator!=(const NationalBestOfferShortAppendage& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NationalBestOfferShortAppendage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v1_91
