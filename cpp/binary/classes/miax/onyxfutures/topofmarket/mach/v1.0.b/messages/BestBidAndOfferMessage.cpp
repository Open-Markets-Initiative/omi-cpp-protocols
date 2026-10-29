#include "BestBidAndOfferMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

BestBidAndOfferMessage::BestBidAndOfferMessage(std::chrono::nanoseconds timestamp, std::uint32_t instrument_id, Decimal mbb_price, std::uint32_t mbb_size, Decimal mbo_price, std::uint32_t mbo_size)
  : timestamp_(timestamp), instrument_id_(instrument_id), mbb_price_(mbb_price), mbb_size_(mbb_size), mbo_price_(mbo_price), mbo_size_(mbo_size) {}

std::chrono::nanoseconds BestBidAndOfferMessage::timestamp() const { return timestamp_; }
void BestBidAndOfferMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t BestBidAndOfferMessage::instrument_id() const { return instrument_id_; }
void BestBidAndOfferMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

Decimal BestBidAndOfferMessage::mbb_price() const { return mbb_price_; }
void BestBidAndOfferMessage::set_mbb_price(Decimal value) { mbb_price_ = value; }

std::uint32_t BestBidAndOfferMessage::mbb_size() const { return mbb_size_; }
void BestBidAndOfferMessage::set_mbb_size(std::uint32_t value) { mbb_size_ = value; }

Decimal BestBidAndOfferMessage::mbo_price() const { return mbo_price_; }
void BestBidAndOfferMessage::set_mbo_price(Decimal value) { mbo_price_ = value; }

std::uint32_t BestBidAndOfferMessage::mbo_size() const { return mbo_size_; }
void BestBidAndOfferMessage::set_mbo_size(std::uint32_t value) { mbo_size_ = value; }

DataCode BestBidAndOfferMessage::type() const { return message_type; }

std::string_view BestBidAndOfferMessage::name() const { return "Best Bid And Offer Message"; }

std::size_t BestBidAndOfferMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BestBidAndOfferMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    mbb_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    mbb_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    mbo_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    mbo_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t BestBidAndOfferMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BestBidAndOfferMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(mbb_price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(mbb_size_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(mbo_price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(mbo_size_));
    offset += 4;

    return offset;
}

std::size_t BestBidAndOfferMessage::encoded_size() const {
    return wire_size;
}

void BestBidAndOfferMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> BestBidAndOfferMessage::clone() const {
    return std::make_unique<BestBidAndOfferMessage>(*this);
}

void BestBidAndOfferMessage::print(std::ostream& out) const {
    out << "BestBidAndOfferMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", mbb_price=";
    out << mbb_price_;
    out << ", mbb_size=";
    out << mbb_size_;
    out << ", mbo_price=";
    out << mbo_price_;
    out << ", mbo_size=";
    out << mbo_size_;
    out << '}';
}

bool BestBidAndOfferMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const BestBidAndOfferMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool BestBidAndOfferMessage::operator==(const BestBidAndOfferMessage& other) const {
    return timestamp_ == other.timestamp_
        && instrument_id_ == other.instrument_id_
        && mbb_price_ == other.mbb_price_
        && mbb_size_ == other.mbb_size_
        && mbo_price_ == other.mbo_price_
        && mbo_size_ == other.mbo_size_;
}

bool BestBidAndOfferMessage::operator!=(const BestBidAndOfferMessage& other) const {
    return !(*this == other);
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
