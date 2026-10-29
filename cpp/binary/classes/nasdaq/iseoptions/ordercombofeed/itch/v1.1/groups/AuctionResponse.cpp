#include "AuctionResponse.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

AuctionResponse::AuctionResponse(Decimal response_price, std::uint32_t response_size)
  : response_price_(response_price), response_size_(response_size) {}

Decimal AuctionResponse::response_price() const { return response_price_; }
void AuctionResponse::set_response_price(Decimal value) { response_price_ = value; }

std::uint32_t AuctionResponse::response_size() const { return response_size_; }
void AuctionResponse::set_response_size(std::uint32_t value) { response_size_ = value; }

std::size_t AuctionResponse::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionResponse", wire_size, length);

    response_price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    response_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t AuctionResponse::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionResponse", wire_size, capacity);

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(response_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(response_size_));
    offset += 4;

    return offset;
}

std::size_t AuctionResponse::encoded_size() const {
    return wire_size;
}

void AuctionResponse::print(std::ostream& out) const {
    out << "AuctionResponse{";
    out << "response_price=";
    out << response_price_;
    out << ", response_size=";
    out << response_size_;
    out << '}';
}

bool AuctionResponse::operator==(const AuctionResponse& other) const {
    return response_price_ == other.response_price_
        && response_size_ == other.response_size_;
}

bool AuctionResponse::operator!=(const AuctionResponse& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const AuctionResponse& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
