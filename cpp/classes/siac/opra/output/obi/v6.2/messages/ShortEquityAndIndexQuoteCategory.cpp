#include "ShortEquityAndIndexQuoteCategory.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::opra::output::obi::v6_2 {

ShortEquityAndIndexQuoteCategory::ShortEquityAndIndexQuoteCategory(const ShortEquityAndIndexQuoteCategory& other)
  : short_equity_and_index_quote_message_type_(other.short_equity_and_index_quote_message_type_), short_equity_and_index_quote_message_payload_(other.short_equity_and_index_quote_message_payload_ ? other.short_equity_and_index_quote_message_payload_->clone() : nullptr) {}

ShortEquityAndIndexQuoteCategory& ShortEquityAndIndexQuoteCategory::operator=(const ShortEquityAndIndexQuoteCategory& other) {
    if (this != &other) {
        short_equity_and_index_quote_message_type_ = other.short_equity_and_index_quote_message_type_;
        short_equity_and_index_quote_message_payload_ = other.short_equity_and_index_quote_message_payload_ ? other.short_equity_and_index_quote_message_payload_->clone() : nullptr;
    }
    return *this;
}

ShortEquityAndIndexQuoteMessageType ShortEquityAndIndexQuoteCategory::short_equity_and_index_quote_message_type() const { return short_equity_and_index_quote_message_type_; }
void ShortEquityAndIndexQuoteCategory::set_short_equity_and_index_quote_message_type(ShortEquityAndIndexQuoteMessageType value) { short_equity_and_index_quote_message_type_ = value; }

const ShortEquityAndIndexQuoteMessagePayload* ShortEquityAndIndexQuoteCategory::short_equity_and_index_quote_message_payload() const { return short_equity_and_index_quote_message_payload_.get(); }
ShortEquityAndIndexQuoteMessagePayload* ShortEquityAndIndexQuoteCategory::short_equity_and_index_quote_message_payload() { return short_equity_and_index_quote_message_payload_.get(); }
void ShortEquityAndIndexQuoteCategory::set_short_equity_and_index_quote_message_payload(std::unique_ptr<ShortEquityAndIndexQuoteMessagePayload> value) { short_equity_and_index_quote_message_payload_ = std::move(value); }

MessageCode ShortEquityAndIndexQuoteCategory::type() const { return message_type; }

std::string_view ShortEquityAndIndexQuoteCategory::name() const { return "Short Equity And Index Quote Category"; }

std::size_t ShortEquityAndIndexQuoteCategory::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ShortEquityAndIndexQuoteCategory", offset + 1, length);
    short_equity_and_index_quote_message_type_ = static_cast<ShortEquityAndIndexQuoteMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = ShortEquityAndIndexQuoteMessagePayloadFactory::create(short_equity_and_index_quote_message_type_);
        offset += selected->decode(data + offset, length - offset);
        short_equity_and_index_quote_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t ShortEquityAndIndexQuoteCategory::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!short_equity_and_index_quote_message_payload_) { throw EncodeError("ShortEquityAndIndexQuoteCategory", "no short_equity_and_index_quote_message_payload"); }
    wire::require_capacity("ShortEquityAndIndexQuoteCategory", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto short_equity_and_index_quote_message_type = short_equity_and_index_quote_message_type_;
    short_equity_and_index_quote_message_type = short_equity_and_index_quote_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(short_equity_and_index_quote_message_type));
    offset += 1;

    offset += short_equity_and_index_quote_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ShortEquityAndIndexQuoteCategory::encoded_size() const {
    return 1 + (short_equity_and_index_quote_message_payload_ ? short_equity_and_index_quote_message_payload_->encoded_size() : 0);
}

void ShortEquityAndIndexQuoteCategory::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ShortEquityAndIndexQuoteCategory::clone() const {
    return std::make_unique<ShortEquityAndIndexQuoteCategory>(*this);
}

void ShortEquityAndIndexQuoteCategory::print(std::ostream& out) const {
    out << "ShortEquityAndIndexQuoteCategory{";
    out << "short_equity_and_index_quote_message_type=";
    out << short_equity_and_index_quote_message_type_;
    out << ", short_equity_and_index_quote_message_payload=";
    if (short_equity_and_index_quote_message_payload_) { short_equity_and_index_quote_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool ShortEquityAndIndexQuoteCategory::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ShortEquityAndIndexQuoteCategory*>(&other);
    return that != nullptr && *this == *that;
}

bool ShortEquityAndIndexQuoteCategory::operator==(const ShortEquityAndIndexQuoteCategory& other) const {
    return short_equity_and_index_quote_message_type_ == other.short_equity_and_index_quote_message_type_
        && ((short_equity_and_index_quote_message_payload_ == nullptr) == (other.short_equity_and_index_quote_message_payload_ == nullptr) && (!short_equity_and_index_quote_message_payload_ || short_equity_and_index_quote_message_payload_->equals(*other.short_equity_and_index_quote_message_payload_)));
}

bool ShortEquityAndIndexQuoteCategory::operator!=(const ShortEquityAndIndexQuoteCategory& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
