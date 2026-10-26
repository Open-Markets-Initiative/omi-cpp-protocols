#include "LongEquityAndIndexQuoteCategory.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::opra::output::obi::v6_2 {

LongEquityAndIndexQuoteCategory::LongEquityAndIndexQuoteCategory(const LongEquityAndIndexQuoteCategory& other)
  : long_equity_and_index_quote_message_type_(other.long_equity_and_index_quote_message_type_), long_equity_and_index_quote_message_payload_(other.long_equity_and_index_quote_message_payload_ ? other.long_equity_and_index_quote_message_payload_->clone() : nullptr) {}

LongEquityAndIndexQuoteCategory& LongEquityAndIndexQuoteCategory::operator=(const LongEquityAndIndexQuoteCategory& other) {
    if (this != &other) {
        long_equity_and_index_quote_message_type_ = other.long_equity_and_index_quote_message_type_;
        long_equity_and_index_quote_message_payload_ = other.long_equity_and_index_quote_message_payload_ ? other.long_equity_and_index_quote_message_payload_->clone() : nullptr;
    }
    return *this;
}

LongEquityAndIndexQuoteMessageType LongEquityAndIndexQuoteCategory::long_equity_and_index_quote_message_type() const { return long_equity_and_index_quote_message_type_; }
void LongEquityAndIndexQuoteCategory::set_long_equity_and_index_quote_message_type(LongEquityAndIndexQuoteMessageType value) { long_equity_and_index_quote_message_type_ = value; }

const LongEquityAndIndexQuoteMessagePayload* LongEquityAndIndexQuoteCategory::long_equity_and_index_quote_message_payload() const { return long_equity_and_index_quote_message_payload_.get(); }
LongEquityAndIndexQuoteMessagePayload* LongEquityAndIndexQuoteCategory::long_equity_and_index_quote_message_payload() { return long_equity_and_index_quote_message_payload_.get(); }
void LongEquityAndIndexQuoteCategory::set_long_equity_and_index_quote_message_payload(std::unique_ptr<LongEquityAndIndexQuoteMessagePayload> value) { long_equity_and_index_quote_message_payload_ = std::move(value); }

MessageCode LongEquityAndIndexQuoteCategory::type() const { return message_type; }

std::string_view LongEquityAndIndexQuoteCategory::name() const { return "Long Equity And Index Quote Category"; }

std::size_t LongEquityAndIndexQuoteCategory::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("LongEquityAndIndexQuoteCategory", offset + 1, length);
    long_equity_and_index_quote_message_type_ = static_cast<LongEquityAndIndexQuoteMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = LongEquityAndIndexQuoteMessagePayloadFactory::create(long_equity_and_index_quote_message_type_);
        offset += selected->decode(data + offset, length - offset);
        long_equity_and_index_quote_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t LongEquityAndIndexQuoteCategory::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!long_equity_and_index_quote_message_payload_) { throw EncodeError("LongEquityAndIndexQuoteCategory", "no long_equity_and_index_quote_message_payload"); }
    wire::require_capacity("LongEquityAndIndexQuoteCategory", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto long_equity_and_index_quote_message_type = long_equity_and_index_quote_message_type_;
    long_equity_and_index_quote_message_type = long_equity_and_index_quote_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(long_equity_and_index_quote_message_type));
    offset += 1;

    offset += long_equity_and_index_quote_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t LongEquityAndIndexQuoteCategory::encoded_size() const {
    return 1 + (long_equity_and_index_quote_message_payload_ ? long_equity_and_index_quote_message_payload_->encoded_size() : 0);
}

void LongEquityAndIndexQuoteCategory::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> LongEquityAndIndexQuoteCategory::clone() const {
    return std::make_unique<LongEquityAndIndexQuoteCategory>(*this);
}

void LongEquityAndIndexQuoteCategory::print(std::ostream& out) const {
    out << "LongEquityAndIndexQuoteCategory{";
    out << "long_equity_and_index_quote_message_type=";
    out << long_equity_and_index_quote_message_type_;
    out << ", long_equity_and_index_quote_message_payload=";
    if (long_equity_and_index_quote_message_payload_) { long_equity_and_index_quote_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool LongEquityAndIndexQuoteCategory::equals(const Message& other) const {
    const auto* that = dynamic_cast<const LongEquityAndIndexQuoteCategory*>(&other);
    return that != nullptr && *this == *that;
}

bool LongEquityAndIndexQuoteCategory::operator==(const LongEquityAndIndexQuoteCategory& other) const {
    return long_equity_and_index_quote_message_type_ == other.long_equity_and_index_quote_message_type_
        && ((long_equity_and_index_quote_message_payload_ == nullptr) == (other.long_equity_and_index_quote_message_payload_ == nullptr) && (!long_equity_and_index_quote_message_payload_ || long_equity_and_index_quote_message_payload_->equals(*other.long_equity_and_index_quote_message_payload_)));
}

bool LongEquityAndIndexQuoteCategory::operator!=(const LongEquityAndIndexQuoteCategory& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
