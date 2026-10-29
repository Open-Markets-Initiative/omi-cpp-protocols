#pragma once

namespace packet {

    enum class result {
        nyse_nationalequities_trades_pillar_v2_6,
        error,
        end_of_file,
        unknown
    };

}