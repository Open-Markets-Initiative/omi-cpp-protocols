#include "ImbalanceMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

ImbalanceMsg::ImbalanceMsg(std::optional<std::chrono::nanoseconds> ts_recv, std::optional<Decimal> ref_price, std::optional<std::chrono::nanoseconds> auction_time, std::optional<Decimal> cont_book_clr_price, std::optional<Decimal> auct_interest_clr_price, std::optional<Decimal> ssr_filling_price, std::optional<Decimal> ind_match_price, std::optional<Decimal> upper_collar, std::optional<Decimal> lower_collar, std::uint32_t paired_qty, std::uint32_t total_imbalance_qty, std::uint32_t market_imbalance_qty, std::uint32_t unpaired_qty, char auction_type, Side side, std::uint8_t auction_status, std::uint8_t freeze_status, std::uint8_t num_extensions, UnpairedSide unpaired_side, char significant_imbalance, const std::array<std::byte, 1>& reserved_1)
  : ts_recv_(ts_recv), ref_price_(ref_price), auction_time_(auction_time), cont_book_clr_price_(cont_book_clr_price), auct_interest_clr_price_(auct_interest_clr_price), ssr_filling_price_(ssr_filling_price), ind_match_price_(ind_match_price), upper_collar_(upper_collar), lower_collar_(lower_collar), paired_qty_(paired_qty), total_imbalance_qty_(total_imbalance_qty), market_imbalance_qty_(market_imbalance_qty), unpaired_qty_(unpaired_qty), auction_type_(auction_type), side_(side), auction_status_(auction_status), freeze_status_(freeze_status), num_extensions_(num_extensions), unpaired_side_(unpaired_side), significant_imbalance_(significant_imbalance), reserved_1_(reserved_1) {}

std::optional<std::chrono::nanoseconds> ImbalanceMsg::ts_recv() const { return ts_recv_; }
void ImbalanceMsg::set_ts_recv(std::optional<std::chrono::nanoseconds> value) { ts_recv_ = value; }

std::optional<Decimal> ImbalanceMsg::ref_price() const { return ref_price_; }
void ImbalanceMsg::set_ref_price(std::optional<Decimal> value) { ref_price_ = value; }

std::optional<std::chrono::nanoseconds> ImbalanceMsg::auction_time() const { return auction_time_; }
void ImbalanceMsg::set_auction_time(std::optional<std::chrono::nanoseconds> value) { auction_time_ = value; }

std::optional<Decimal> ImbalanceMsg::cont_book_clr_price() const { return cont_book_clr_price_; }
void ImbalanceMsg::set_cont_book_clr_price(std::optional<Decimal> value) { cont_book_clr_price_ = value; }

std::optional<Decimal> ImbalanceMsg::auct_interest_clr_price() const { return auct_interest_clr_price_; }
void ImbalanceMsg::set_auct_interest_clr_price(std::optional<Decimal> value) { auct_interest_clr_price_ = value; }

std::optional<Decimal> ImbalanceMsg::ssr_filling_price() const { return ssr_filling_price_; }
void ImbalanceMsg::set_ssr_filling_price(std::optional<Decimal> value) { ssr_filling_price_ = value; }

std::optional<Decimal> ImbalanceMsg::ind_match_price() const { return ind_match_price_; }
void ImbalanceMsg::set_ind_match_price(std::optional<Decimal> value) { ind_match_price_ = value; }

std::optional<Decimal> ImbalanceMsg::upper_collar() const { return upper_collar_; }
void ImbalanceMsg::set_upper_collar(std::optional<Decimal> value) { upper_collar_ = value; }

std::optional<Decimal> ImbalanceMsg::lower_collar() const { return lower_collar_; }
void ImbalanceMsg::set_lower_collar(std::optional<Decimal> value) { lower_collar_ = value; }

std::uint32_t ImbalanceMsg::paired_qty() const { return paired_qty_; }
void ImbalanceMsg::set_paired_qty(std::uint32_t value) { paired_qty_ = value; }

std::uint32_t ImbalanceMsg::total_imbalance_qty() const { return total_imbalance_qty_; }
void ImbalanceMsg::set_total_imbalance_qty(std::uint32_t value) { total_imbalance_qty_ = value; }

std::uint32_t ImbalanceMsg::market_imbalance_qty() const { return market_imbalance_qty_; }
void ImbalanceMsg::set_market_imbalance_qty(std::uint32_t value) { market_imbalance_qty_ = value; }

std::uint32_t ImbalanceMsg::unpaired_qty() const { return unpaired_qty_; }
void ImbalanceMsg::set_unpaired_qty(std::uint32_t value) { unpaired_qty_ = value; }

char ImbalanceMsg::auction_type() const { return auction_type_; }
void ImbalanceMsg::set_auction_type(char value) { auction_type_ = value; }

Side ImbalanceMsg::side() const { return side_; }
void ImbalanceMsg::set_side(Side value) { side_ = value; }

std::uint8_t ImbalanceMsg::auction_status() const { return auction_status_; }
void ImbalanceMsg::set_auction_status(std::uint8_t value) { auction_status_ = value; }

std::uint8_t ImbalanceMsg::freeze_status() const { return freeze_status_; }
void ImbalanceMsg::set_freeze_status(std::uint8_t value) { freeze_status_ = value; }

std::uint8_t ImbalanceMsg::num_extensions() const { return num_extensions_; }
void ImbalanceMsg::set_num_extensions(std::uint8_t value) { num_extensions_ = value; }

UnpairedSide ImbalanceMsg::unpaired_side() const { return unpaired_side_; }
void ImbalanceMsg::set_unpaired_side(UnpairedSide value) { unpaired_side_ = value; }

char ImbalanceMsg::significant_imbalance() const { return significant_imbalance_; }
void ImbalanceMsg::set_significant_imbalance(char value) { significant_imbalance_ = value; }

const std::array<std::byte, 1>& ImbalanceMsg::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& ImbalanceMsg::reserved_1() { return reserved_1_; }
void ImbalanceMsg::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

MessageCode ImbalanceMsg::type() const { return message_type; }

std::string_view ImbalanceMsg::name() const { return "Imbalance Msg"; }

std::size_t ImbalanceMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ImbalanceMsg", wire_size, length);

    ts_recv_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    ref_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    auction_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    cont_book_clr_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    auct_interest_clr_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    ssr_filling_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    ind_match_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    upper_collar_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    lower_collar_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    paired_qty_ = wire::read_u32_le(data + offset);
    offset += 4;

    total_imbalance_qty_ = wire::read_u32_le(data + offset);
    offset += 4;

    market_imbalance_qty_ = wire::read_u32_le(data + offset);
    offset += 4;

    unpaired_qty_ = wire::read_u32_le(data + offset);
    offset += 4;

    auction_type_ = wire::read_char(data + offset);
    offset += 1;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    auction_status_ = wire::read_u8(data + offset);
    offset += 1;

    freeze_status_ = wire::read_u8(data + offset);
    offset += 1;

    num_extensions_ = wire::read_u8(data + offset);
    offset += 1;

    unpaired_side_ = static_cast<UnpairedSide>(wire::read_char(data + offset));
    offset += 1;

    significant_imbalance_ = wire::read_char(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t ImbalanceMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ImbalanceMsg", wire_size, capacity);

    wire::write_u64_le(data + offset, ts_recv_ ? static_cast<std::uint64_t>(ts_recv_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_i64_le(data + offset, ref_price_ ? static_cast<std::int64_t>(ref_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u64_le(data + offset, auction_time_ ? static_cast<std::uint64_t>(auction_time_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_i64_le(data + offset, cont_book_clr_price_ ? static_cast<std::int64_t>(cont_book_clr_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, auct_interest_clr_price_ ? static_cast<std::int64_t>(auct_interest_clr_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, ssr_filling_price_ ? static_cast<std::int64_t>(ssr_filling_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, ind_match_price_ ? static_cast<std::int64_t>(ind_match_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, upper_collar_ ? static_cast<std::int64_t>(upper_collar_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, lower_collar_ ? static_cast<std::int64_t>(lower_collar_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(paired_qty_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(total_imbalance_qty_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(market_imbalance_qty_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(unpaired_qty_));
    offset += 4;

    wire::write_char(data + offset, auction_type_);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(auction_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(freeze_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(num_extensions_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(unpaired_side_));
    offset += 1;

    wire::write_char(data + offset, significant_imbalance_);
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t ImbalanceMsg::encoded_size() const {
    return wire_size;
}

void ImbalanceMsg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ImbalanceMsg::clone() const {
    return std::make_unique<ImbalanceMsg>(*this);
}

void ImbalanceMsg::print(std::ostream& out) const {
    out << "ImbalanceMsg{";
    out << "ts_recv=";
    print::optional_duration(out, ts_recv_);
    out << ", ref_price=";
    print::optional(out, ref_price_);
    out << ", auction_time=";
    print::optional_duration(out, auction_time_);
    out << ", cont_book_clr_price=";
    print::optional(out, cont_book_clr_price_);
    out << ", auct_interest_clr_price=";
    print::optional(out, auct_interest_clr_price_);
    out << ", ssr_filling_price=";
    print::optional(out, ssr_filling_price_);
    out << ", ind_match_price=";
    print::optional(out, ind_match_price_);
    out << ", upper_collar=";
    print::optional(out, upper_collar_);
    out << ", lower_collar=";
    print::optional(out, lower_collar_);
    out << ", paired_qty=";
    out << paired_qty_;
    out << ", total_imbalance_qty=";
    out << total_imbalance_qty_;
    out << ", market_imbalance_qty=";
    out << market_imbalance_qty_;
    out << ", unpaired_qty=";
    out << unpaired_qty_;
    out << ", auction_type=";
    print::character(out, auction_type_);
    out << ", side=";
    out << side_;
    out << ", auction_status=";
    out << static_cast<int>(auction_status_);
    out << ", freeze_status=";
    out << static_cast<int>(freeze_status_);
    out << ", num_extensions=";
    out << static_cast<int>(num_extensions_);
    out << ", unpaired_side=";
    out << unpaired_side_;
    out << ", significant_imbalance=";
    print::character(out, significant_imbalance_);
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << '}';
}

bool ImbalanceMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ImbalanceMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool ImbalanceMsg::operator==(const ImbalanceMsg& other) const {
    return ts_recv_ == other.ts_recv_
        && ref_price_ == other.ref_price_
        && auction_time_ == other.auction_time_
        && cont_book_clr_price_ == other.cont_book_clr_price_
        && auct_interest_clr_price_ == other.auct_interest_clr_price_
        && ssr_filling_price_ == other.ssr_filling_price_
        && ind_match_price_ == other.ind_match_price_
        && upper_collar_ == other.upper_collar_
        && lower_collar_ == other.lower_collar_
        && paired_qty_ == other.paired_qty_
        && total_imbalance_qty_ == other.total_imbalance_qty_
        && market_imbalance_qty_ == other.market_imbalance_qty_
        && unpaired_qty_ == other.unpaired_qty_
        && auction_type_ == other.auction_type_
        && side_ == other.side_
        && auction_status_ == other.auction_status_
        && freeze_status_ == other.freeze_status_
        && num_extensions_ == other.num_extensions_
        && unpaired_side_ == other.unpaired_side_
        && significant_imbalance_ == other.significant_imbalance_
        && reserved_1_ == other.reserved_1_;
}

bool ImbalanceMsg::operator!=(const ImbalanceMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v3
