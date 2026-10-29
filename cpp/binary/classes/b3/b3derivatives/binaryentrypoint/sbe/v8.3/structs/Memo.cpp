#include "Memo.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

Memo::Memo(std::uint8_t memo_length, const std::string& memo_data)
  : memo_length_(memo_length), memo_data_(memo_data) {}

std::uint8_t Memo::memo_length() const { return memo_length_; }
void Memo::set_memo_length(std::uint8_t value) { memo_length_ = value; }

const std::string& Memo::memo_data() const { return memo_data_; }
std::string& Memo::memo_data() { return memo_data_; }
void Memo::set_memo_data(const std::string& value) { memo_data_ = value; }

std::size_t Memo::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("Memo", offset + 1, length);
    memo_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(memo_length_);
        wire::require("Memo", offset + count, length);
        memo_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t Memo::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Memo", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto memo_length = memo_length_;
    memo_length = static_cast<std::uint8_t>(memo_data_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(memo_length));
    offset += 1;

    wire::require_capacity("encode", offset + memo_data_.size(), capacity);
    wire::write_text(data + offset, memo_data_.size(), ' ', memo_data_);
    offset += memo_data_.size();

    return offset;
}

std::size_t Memo::encoded_size() const {
    return 1 + memo_data_.size();
}

void Memo::print(std::ostream& out) const {
    out << "Memo{";
    out << "memo_length=";
    out << static_cast<int>(memo_length_);
    out << ", memo_data=";
    print::text(out, memo_data_);
    out << '}';
}

bool Memo::operator==(const Memo& other) const {
    return memo_length_ == other.memo_length_
        && memo_data_ == other.memo_data_;
}

bool Memo::operator!=(const Memo& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Memo& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
