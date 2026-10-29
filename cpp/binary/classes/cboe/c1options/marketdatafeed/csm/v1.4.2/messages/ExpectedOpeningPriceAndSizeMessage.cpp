#include "ExpectedOpeningPriceAndSizeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

ExpectedOpeningPriceAndSizeMessage::ExpectedOpeningPriceAndSizeMessage(std::uint32_t class_key, std::uint32_t security_id, const Eop& eop, std::uint32_t eos, EopType eop_type, LegalMarket legal_market)
  : class_key_(class_key), security_id_(security_id), eop_(eop), eos_(eos), eop_type_(eop_type), legal_market_(legal_market) {}

std::uint32_t ExpectedOpeningPriceAndSizeMessage::class_key() const { return class_key_; }
void ExpectedOpeningPriceAndSizeMessage::set_class_key(std::uint32_t value) { class_key_ = value; }

std::uint32_t ExpectedOpeningPriceAndSizeMessage::security_id() const { return security_id_; }
void ExpectedOpeningPriceAndSizeMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

const Eop& ExpectedOpeningPriceAndSizeMessage::eop() const { return eop_; }
Eop& ExpectedOpeningPriceAndSizeMessage::eop() { return eop_; }
void ExpectedOpeningPriceAndSizeMessage::set_eop(const Eop& value) { eop_ = value; }

std::uint32_t ExpectedOpeningPriceAndSizeMessage::eos() const { return eos_; }
void ExpectedOpeningPriceAndSizeMessage::set_eos(std::uint32_t value) { eos_ = value; }

EopType ExpectedOpeningPriceAndSizeMessage::eop_type() const { return eop_type_; }
void ExpectedOpeningPriceAndSizeMessage::set_eop_type(EopType value) { eop_type_ = value; }

LegalMarket ExpectedOpeningPriceAndSizeMessage::legal_market() const { return legal_market_; }
void ExpectedOpeningPriceAndSizeMessage::set_legal_market(LegalMarket value) { legal_market_ = value; }

MessageCode ExpectedOpeningPriceAndSizeMessage::type() const { return message_type; }

std::string_view ExpectedOpeningPriceAndSizeMessage::name() const { return "Expected Opening Price And Size Message"; }

std::size_t ExpectedOpeningPriceAndSizeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ExpectedOpeningPriceAndSizeMessage", wire_size, length);

    class_key_ = wire::read_u32_be(data + offset);
    offset += 4;

    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += eop_.decode(data + offset, length - offset);

    eos_ = wire::read_u32_be(data + offset);
    offset += 4;

    eop_type_ = static_cast<EopType>(wire::read_u8(data + offset));
    offset += 1;

    legal_market_ = static_cast<LegalMarket>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t ExpectedOpeningPriceAndSizeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExpectedOpeningPriceAndSizeMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(class_key_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    offset += eop_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(eos_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(eop_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(legal_market_));
    offset += 1;

    return offset;
}

std::size_t ExpectedOpeningPriceAndSizeMessage::encoded_size() const {
    return wire_size;
}

void ExpectedOpeningPriceAndSizeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExpectedOpeningPriceAndSizeMessage::clone() const {
    return std::make_unique<ExpectedOpeningPriceAndSizeMessage>(*this);
}

void ExpectedOpeningPriceAndSizeMessage::print(std::ostream& out) const {
    out << "ExpectedOpeningPriceAndSizeMessage{";
    out << "class_key=";
    out << class_key_;
    out << ", security_id=";
    out << security_id_;
    out << ", eop=";
    eop_.print(out);
    out << ", eos=";
    out << eos_;
    out << ", eop_type=";
    out << eop_type_;
    out << ", legal_market=";
    out << legal_market_;
    out << '}';
}

bool ExpectedOpeningPriceAndSizeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExpectedOpeningPriceAndSizeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ExpectedOpeningPriceAndSizeMessage::operator==(const ExpectedOpeningPriceAndSizeMessage& other) const {
    return class_key_ == other.class_key_
        && security_id_ == other.security_id_
        && eop_ == other.eop_
        && eos_ == other.eos_
        && eop_type_ == other.eop_type_
        && legal_market_ == other.legal_market_;
}

bool ExpectedOpeningPriceAndSizeMessage::operator!=(const ExpectedOpeningPriceAndSizeMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
