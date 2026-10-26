#include "EquityAndIndexEndOfDaySummaryCategory.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::opra::output::obi::v6_2 {

EquityAndIndexEndOfDaySummaryCategory::EquityAndIndexEndOfDaySummaryCategory(const EquityAndIndexEndOfDaySummaryCategory& other)
  : equity_and_index_end_of_day_summary_message_type_(other.equity_and_index_end_of_day_summary_message_type_), equity_and_index_end_of_day_summary_message_payload_(other.equity_and_index_end_of_day_summary_message_payload_ ? other.equity_and_index_end_of_day_summary_message_payload_->clone() : nullptr) {}

EquityAndIndexEndOfDaySummaryCategory& EquityAndIndexEndOfDaySummaryCategory::operator=(const EquityAndIndexEndOfDaySummaryCategory& other) {
    if (this != &other) {
        equity_and_index_end_of_day_summary_message_type_ = other.equity_and_index_end_of_day_summary_message_type_;
        equity_and_index_end_of_day_summary_message_payload_ = other.equity_and_index_end_of_day_summary_message_payload_ ? other.equity_and_index_end_of_day_summary_message_payload_->clone() : nullptr;
    }
    return *this;
}

EquityAndIndexEndOfDaySummaryMessageType EquityAndIndexEndOfDaySummaryCategory::equity_and_index_end_of_day_summary_message_type() const { return equity_and_index_end_of_day_summary_message_type_; }
void EquityAndIndexEndOfDaySummaryCategory::set_equity_and_index_end_of_day_summary_message_type(EquityAndIndexEndOfDaySummaryMessageType value) { equity_and_index_end_of_day_summary_message_type_ = value; }

const EquityAndIndexEndOfDaySummaryMessagePayload* EquityAndIndexEndOfDaySummaryCategory::equity_and_index_end_of_day_summary_message_payload() const { return equity_and_index_end_of_day_summary_message_payload_.get(); }
EquityAndIndexEndOfDaySummaryMessagePayload* EquityAndIndexEndOfDaySummaryCategory::equity_and_index_end_of_day_summary_message_payload() { return equity_and_index_end_of_day_summary_message_payload_.get(); }
void EquityAndIndexEndOfDaySummaryCategory::set_equity_and_index_end_of_day_summary_message_payload(std::unique_ptr<EquityAndIndexEndOfDaySummaryMessagePayload> value) { equity_and_index_end_of_day_summary_message_payload_ = std::move(value); }

MessageCode EquityAndIndexEndOfDaySummaryCategory::type() const { return message_type; }

std::string_view EquityAndIndexEndOfDaySummaryCategory::name() const { return "Equity And Index End Of Day Summary Category"; }

std::size_t EquityAndIndexEndOfDaySummaryCategory::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("EquityAndIndexEndOfDaySummaryCategory", offset + 1, length);
    equity_and_index_end_of_day_summary_message_type_ = static_cast<EquityAndIndexEndOfDaySummaryMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = EquityAndIndexEndOfDaySummaryMessagePayloadFactory::create(equity_and_index_end_of_day_summary_message_type_);
        offset += selected->decode(data + offset, length - offset);
        equity_and_index_end_of_day_summary_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t EquityAndIndexEndOfDaySummaryCategory::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!equity_and_index_end_of_day_summary_message_payload_) { throw EncodeError("EquityAndIndexEndOfDaySummaryCategory", "no equity_and_index_end_of_day_summary_message_payload"); }
    wire::require_capacity("EquityAndIndexEndOfDaySummaryCategory", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto equity_and_index_end_of_day_summary_message_type = equity_and_index_end_of_day_summary_message_type_;
    equity_and_index_end_of_day_summary_message_type = equity_and_index_end_of_day_summary_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(equity_and_index_end_of_day_summary_message_type));
    offset += 1;

    offset += equity_and_index_end_of_day_summary_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t EquityAndIndexEndOfDaySummaryCategory::encoded_size() const {
    return 1 + (equity_and_index_end_of_day_summary_message_payload_ ? equity_and_index_end_of_day_summary_message_payload_->encoded_size() : 0);
}

void EquityAndIndexEndOfDaySummaryCategory::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EquityAndIndexEndOfDaySummaryCategory::clone() const {
    return std::make_unique<EquityAndIndexEndOfDaySummaryCategory>(*this);
}

void EquityAndIndexEndOfDaySummaryCategory::print(std::ostream& out) const {
    out << "EquityAndIndexEndOfDaySummaryCategory{";
    out << "equity_and_index_end_of_day_summary_message_type=";
    out << equity_and_index_end_of_day_summary_message_type_;
    out << ", equity_and_index_end_of_day_summary_message_payload=";
    if (equity_and_index_end_of_day_summary_message_payload_) { equity_and_index_end_of_day_summary_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool EquityAndIndexEndOfDaySummaryCategory::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EquityAndIndexEndOfDaySummaryCategory*>(&other);
    return that != nullptr && *this == *that;
}

bool EquityAndIndexEndOfDaySummaryCategory::operator==(const EquityAndIndexEndOfDaySummaryCategory& other) const {
    return equity_and_index_end_of_day_summary_message_type_ == other.equity_and_index_end_of_day_summary_message_type_
        && ((equity_and_index_end_of_day_summary_message_payload_ == nullptr) == (other.equity_and_index_end_of_day_summary_message_payload_ == nullptr) && (!equity_and_index_end_of_day_summary_message_payload_ || equity_and_index_end_of_day_summary_message_payload_->equals(*other.equity_and_index_end_of_day_summary_message_payload_)));
}

bool EquityAndIndexEndOfDaySummaryCategory::operator!=(const EquityAndIndexEndOfDaySummaryCategory& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
