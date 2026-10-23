#include "SaleCondition4.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_11_b {

SaleCondition4::SaleCondition4(Category1 category_1, Category2 category_2, Category3 category_3, Category4 category_4)
  : category_1_(category_1), category_2_(category_2), category_3_(category_3), category_4_(category_4) {}

Category1 SaleCondition4::category_1() const { return category_1_; }
void SaleCondition4::set_category_1(Category1 value) { category_1_ = value; }

Category2 SaleCondition4::category_2() const { return category_2_; }
void SaleCondition4::set_category_2(Category2 value) { category_2_ = value; }

Category3 SaleCondition4::category_3() const { return category_3_; }
void SaleCondition4::set_category_3(Category3 value) { category_3_ = value; }

Category4 SaleCondition4::category_4() const { return category_4_; }
void SaleCondition4::set_category_4(Category4 value) { category_4_ = value; }

std::size_t SaleCondition4::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SaleCondition4", wire_size, length);

    category_1_ = static_cast<Category1>(wire::read_char(data + offset));
    offset += 1;

    category_2_ = static_cast<Category2>(wire::read_char(data + offset));
    offset += 1;

    category_3_ = static_cast<Category3>(wire::read_char(data + offset));
    offset += 1;

    category_4_ = static_cast<Category4>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SaleCondition4::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SaleCondition4", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(category_1_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(category_2_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(category_3_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(category_4_));
    offset += 1;

    return offset;
}

std::size_t SaleCondition4::encoded_size() const {
    return wire_size;
}

void SaleCondition4::print(std::ostream& out) const {
    out << "SaleCondition4{";
    out << "category_1=";
    out << category_1_;
    out << ", category_2=";
    out << category_2_;
    out << ", category_3=";
    out << category_3_;
    out << ", category_4=";
    out << category_4_;
    out << '}';
}

bool SaleCondition4::operator==(const SaleCondition4& other) const {
    return category_1_ == other.category_1_
        && category_2_ == other.category_2_
        && category_3_ == other.category_3_
        && category_4_ == other.category_4_;
}

bool SaleCondition4::operator!=(const SaleCondition4& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SaleCondition4& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
