


# install the package from .tgz
install.packages("../CallSpreadBarrierPrice_0.1.0.tgz",
                 repos = NULL,
                 type = "source")

# load the package
library(CallSpreadBarrierPrice)


price <- CallSpreadBarrierSpread(
    is_bull = 1,
    expiry = 0.5,
    strike1 = 105,
    strike2 = 120,
    spot = 110,
    vol = 0.23,
    r = 0.05,
    d = 0.0,
    number_of_paths = 1000,
    number_of_dates = 126,
    is_double_barrier = 0,
    is_knock_out = 1,
    barrier1 = 140.0,
    barrier2 = 0.0
)

price
