#include "EquityAndIndexLastSaleCategory.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::opra::output::obi::v6_2 {

EquityAndIndexLastSaleCategory::EquityAndIndexLastSaleCategory(const EquityAndIndexLastSaleCategory& other)
  : equity_and_index_last_sale_message_type_(other.equity_and_index_last_sale_message_type_), equity_and_index_last_sale_message_payload_(other.equity_and_index_last_sale_message_payload_ ? other.equity_and_index_last_sale_message_payload_->clone() : nullptr) {}

EquityAndIndexLastSaleCategory& EquityAndIndexLastSaleCategory::operator=(const EquityAndIndexLastSaleCategory& other) {
    if (this != &other) {
        equity_and_index_last_sale_message_type_ = other.equity_and_index_last_sale_message_type_;
        equity_and_index_last_sale_message_payload_ = other.equity_and_index_last_sale_message_payload_ ? other.equity_and_index_last_sale_message_payload_->clone() : nullptr;
    }
    return *this;
}

EquityAndIndexLastSaleMessageType EquityAndIndexLastSaleCategory::equity_and_index_last_sale_message_type() const { return equity_and_index_last_sale_message_type_; }
void EquityAndIndexLastSaleCategory::set_equity_and_index_last_sale_message_type(EquityAndIndexLastSaleMessageType value) { equity_and_index_last_sale_message_type_ = value; }

const EquityAndIndexLastSaleMessagePayload* EquityAndIndexLastSaleCategory::equity_and_index_last_sale_message_payload() const { return equity_and_index_last_sale_message_payload_.get(); }
EquityAndIndexLastSaleMessagePayload* EquityAndIndexLastSaleCategory::equity_and_index_last_sale_message_payload() { return equity_and_index_last_sale_message_payload_.get(); }
void EquityAndIndexLastSaleCategory::set_equity_and_index_last_sale_message_payload(std::unique_ptr<EquityAndIndexLastSaleMessagePayload> value) { equity_and_index_last_sale_message_payload_ = std::move(value); }

MessageCode EquityAndIndexLastSaleCategory::type() const { return message_type; }

std::string_view EquityAndIndexLastSaleCategory::name() const { return "Equity And Index Last Sale Category"; }

std::size_t EquityAndIndexLastSaleCategory::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("EquityAndIndexLastSaleCategory", offset + 1, length);
    equity_and_index_last_sale_message_type_ = static_cast<EquityAndIndexLastSaleMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = EquityAndIndexLastSaleMessagePayloadFactory::create(equity_and_index_last_sale_message_type_);
        offset += selected->decode(data + offset, length - offset);
        equity_and_index_last_sale_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t EquityAndIndexLastSaleCategory::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!equity_and_index_last_sale_message_payload_) { throw EncodeError("EquityAndIndexLastSaleCategory", "no equity_and_index_last_sale_message_payload"); }
    wire::require_capacity("EquityAndIndexLastSaleCategory", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto equity_and_index_last_sale_message_type = equity_and_index_last_sale_message_type_;
    equity_and_index_last_sale_message_type = equity_and_index_last_sale_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(equity_and_index_last_sale_message_type));
    offset += 1;

    offset += equity_and_index_last_sale_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t EquityAndIndexLastSaleCategory::encoded_size() const {
    return 1 + (equity_and_index_last_sale_message_payload_ ? equity_and_index_last_sale_message_payload_->encoded_size() : 0);
}

void EquityAndIndexLastSaleCategory::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EquityAndIndexLastSaleCategory::clone() const {
    return std::make_unique<EquityAndIndexLastSaleCategory>(*this);
}

void EquityAndIndexLastSaleCategory::print(std::ostream& out) const {
    out << "EquityAndIndexLastSaleCategory{";
    out << "equity_and_index_last_sale_message_type=";
    out << equity_and_index_last_sale_message_type_;
    out << ", equity_and_index_last_sale_message_payload=";
    if (equity_and_index_last_sale_message_payload_) { equity_and_index_last_sale_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool EquityAndIndexLastSaleCategory::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EquityAndIndexLastSaleCategory*>(&other);
    return that != nullptr && *this == *that;
}

bool EquityAndIndexLastSaleCategory::operator==(const EquityAndIndexLastSaleCategory& other) const {
    return equity_and_index_last_sale_message_type_ == other.equity_and_index_last_sale_message_type_
        && ((equity_and_index_last_sale_message_payload_ == nullptr) == (other.equity_and_index_last_sale_message_payload_ == nullptr) && (!equity_and_index_last_sale_message_payload_ || equity_and_index_last_sale_message_payload_->equals(*other.equity_and_index_last_sale_message_payload_)));
}

bool EquityAndIndexLastSaleCategory::operator!=(const EquityAndIndexLastSaleCategory& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
