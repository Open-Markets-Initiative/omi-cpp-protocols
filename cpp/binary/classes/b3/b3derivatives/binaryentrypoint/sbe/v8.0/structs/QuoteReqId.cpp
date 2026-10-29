#include "QuoteReqId.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

QuoteReqId::QuoteReqId(std::uint8_t quote_req_id_length, const std::string& quote_req_id_data)
  : quote_req_id_length_(quote_req_id_length), quote_req_id_data_(quote_req_id_data) {}

std::uint8_t QuoteReqId::quote_req_id_length() const { return quote_req_id_length_; }
void QuoteReqId::set_quote_req_id_length(std::uint8_t value) { quote_req_id_length_ = value; }

const std::string& QuoteReqId::quote_req_id_data() const { return quote_req_id_data_; }
std::string& QuoteReqId::quote_req_id_data() { return quote_req_id_data_; }
void QuoteReqId::set_quote_req_id_data(const std::string& value) { quote_req_id_data_ = value; }

std::size_t QuoteReqId::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("QuoteReqId", offset + 1, length);
    quote_req_id_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(quote_req_id_length_);
        wire::require("QuoteReqId", offset + count, length);
        quote_req_id_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t QuoteReqId::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteReqId", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto quote_req_id_length = quote_req_id_length_;
    quote_req_id_length = static_cast<std::uint8_t>(quote_req_id_data_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(quote_req_id_length));
    offset += 1;

    wire::require_capacity("encode", offset + quote_req_id_data_.size(), capacity);
    wire::write_text(data + offset, quote_req_id_data_.size(), ' ', quote_req_id_data_);
    offset += quote_req_id_data_.size();

    return offset;
}

std::size_t QuoteReqId::encoded_size() const {
    return 1 + quote_req_id_data_.size();
}

void QuoteReqId::print(std::ostream& out) const {
    out << "QuoteReqId{";
    out << "quote_req_id_length=";
    out << static_cast<int>(quote_req_id_length_);
    out << ", quote_req_id_data=";
    print::text(out, quote_req_id_data_);
    out << '}';
}

bool QuoteReqId::operator==(const QuoteReqId& other) const {
    return quote_req_id_length_ == other.quote_req_id_length_
        && quote_req_id_data_ == other.quote_req_id_data_;
}

bool QuoteReqId::operator!=(const QuoteReqId& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const QuoteReqId& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
