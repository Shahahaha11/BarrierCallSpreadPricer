# basic R output test
2 + 3

# install local package
install.packages(
    "../CallSpreadBarrierPrice_0.1.0.tgz",
    repos = NULL,
    type = "source"
)

# load package
library(CallSpreadBarrierPrice)

# check function exists
ls("package:CallSpreadBarrierPrice")

# price trial
price <- CallSpreadBarrierSpread(
    is_bull = 1,
    expiry = 0.5,
    strike1 = 105,
    strike2 = 120,
    spot = 110,
    vol = 0.23,
    r = 0.05,
    d = 0.0,
    number_of_paths = 1000000,
    number_of_dates = 126,
    is_double_barrier = 0,
    is_knock_out = 1,
    barrier1 = 140.0,
    barrier2 = 0.0
)

print(price)

# AS BARRIERS CONVERGE
lower <- c(70, 80, 90, 95, 100)
upper <- c(150, 140, 130, 125, 120)

prices <- numeric(length(lower))

for (i in seq_along(lower)) {
    prices[i] <- CallSpreadBarrierSpread(
        is_bull = 1,
        expiry = 0.5,
        strike1 = 105,
        strike2 = 120,
        spot = 110,
        vol = 0.23,
        r = 0.05,
        d = 0.0,
        number_of_paths = 10000,
        number_of_dates = 126,
        is_double_barrier = 1,
        is_knock_out = 1,
        barrier1 = lower[i],
        barrier2 = upper[i]
    )
}

plot(
    1:length(prices), prices,
    type = "b",
    xlab = "Narrowing barrier case",
    ylab = "Option price",
    main = "Double Barrier Sensitivity"
)

axis(1, at = 1:length(prices), labels = paste0(lower, "-", upper))
# 1 = 70–150
# 2 = 80–140
# 3 = 90–130
# 4 = 95–125
# 5 = 100–120



# 2. AS ONE BARRIER CONVERGES

library(CallSpreadBarrierPrice)

# fixed inputs
    is_bull <- 1
    expiry <- 0.5
    strike1 <- 105
    strike2 <- 120
    spot <- 110
    vol <- 0.23
    r <- 0.05
    d <- 0.0
    number_of_paths <- 10000
    number_of_dates <- 126
    is_double_barrier <- 1
    is_knock_out <- 1

# 1) lower barrier moves up, upper barrier fixed
upper_fixed <- 150
lower_values <- c(70, 80, 90, 100, 105)

lower_prices <- numeric(length(lower_values))

for (i in seq_along(lower_values)) {
    lower_prices[i] <- CallSpreadBarrierSpread(
        is_bull, expiry, strike1, strike2, spot, vol,
        r, d, number_of_paths, number_of_dates,
        is_double_barrier, is_knock_out,
        lower_values[i], upper_fixed
    )
}

plot(
    lower_values, lower_prices,
    type = "b",
    xlab = "Lower barrier",
    ylab = "Option price",
    main = "Lower Barrier Moves Up"
)

# 2) upper barrier moves down, lower barrier fixed
lower_fixed <- 70
upper_values <- c(160, 150, 140, 130, 125)

upper_prices <- numeric(length(upper_values))

for (i in seq_along(upper_values)) {
    upper_prices[i] <- CallSpreadBarrierSpread(
        is_bull, expiry, strike1, strike2, spot, vol,
        r, d, number_of_paths, number_of_dates,
        is_double_barrier, is_knock_out,
        lower_fixed, upper_values[i]
    )
}

plot(
    upper_values, upper_prices,
    type = "b",
    xlab = "Upper barrier",
    ylab = "Option price",
    main = "Upper Barrier Moves Down"
)


