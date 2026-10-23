#include "SchemaId.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

std::string_view to_string(SchemaId value) {
    switch (value) {
        case SchemaId::Mktdata: return "Mktdata";
        case SchemaId::Mdpsessionmgmt: return "Mdpsessionmgmt";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SchemaId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_9
