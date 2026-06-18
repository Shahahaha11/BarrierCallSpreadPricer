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

# fixed inputs
is_bull <- 1
expiry <- 0.5
strike1 <- 105
strike2 <- 120
spot <- 110
vol <- 0.23
r <- 0.05
d <- 0.0
number_of_paths <- 100000
number_of_dates <- 126
tolerance <- 0.02

# barrier direction:
# 1 = up barrier
# 0 = down barrier

# price trial
price <- CallSpreadBarrierSpread(
    is_bull = is_bull,
    expiry = expiry,
    strike1 = strike1,
    strike2 = strike2,
    spot = spot,
    vol = vol,
    r = r,
    d = d,
    number_of_paths = 1000000,
    number_of_dates = number_of_dates,
    is_double_barrier = 0,
    is_knock_out = 1,
    barrier1 = 140.0,
    barrier_direction = 1,
    barrier2 = 0.0,
    tolerance = tolerance
)

print(price)

# 1. ALL SINGLE BARRIER VARIANTS

variant_names <- c(
    "Up-and-In",
    "Up-and-Out",
    "Down-and-In",
    "Down-and-Out"
)

variant_direction <- c(1, 1, 0, 0)
variant_knock_out <- c(0, 1, 0, 1)
variant_barrier <- c(140, 140, 80, 80)

variant_prices <- numeric(length(variant_names))

for (i in seq_along(variant_names)) {
    variant_prices[i] <- CallSpreadBarrierSpread(
        is_bull = is_bull,
        expiry = expiry,
        strike1 = strike1,
        strike2 = strike2,
        spot = spot,
        vol = vol,
        r = r,
        d = d,
        number_of_paths = number_of_paths,
        number_of_dates = number_of_dates,
        is_double_barrier = 0,
        is_knock_out = variant_knock_out[i],
        barrier1 = variant_barrier[i],
        barrier_direction = variant_direction[i],
        barrier2 = 0.0,
        tolerance = tolerance
    )
}

print(data.frame(variant = variant_names, price = variant_prices))

barplot(
    variant_prices,
    names.arg = variant_names,
    las = 2,
    ylab = "Option price",
    main = "Single Barrier Call Spread Variants"
)

# 2. AS DOUBLE BARRIERS CONVERGE

lower <- c(70, 80, 90, 95, 100)
upper <- c(150, 140, 130, 125, 120)

prices <- numeric(length(lower))

for (i in seq_along(lower)) {
    prices[i] <- CallSpreadBarrierSpread(
        is_bull = is_bull,
        expiry = expiry,
        strike1 = strike1,
        strike2 = strike2,
        spot = spot,
        vol = vol,
        r = r,
        d = d,
        number_of_paths = number_of_paths,
        number_of_dates = number_of_dates,
        is_double_barrier = 1,
        is_knock_out = 1,
        barrier1 = lower[i],
        barrier_direction = 1,
        barrier2 = upper[i],
        tolerance = tolerance
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

# 3. LOWER BARRIER MOVES UP, UPPER BARRIER FIXED

upper_fixed <- 150
lower_values <- c(70, 80, 90, 100, 105)

lower_prices <- numeric(length(lower_values))

for (i in seq_along(lower_values)) {
    lower_prices[i] <- CallSpreadBarrierSpread(
        is_bull = is_bull,
        expiry = expiry,
        strike1 = strike1,
        strike2 = strike2,
        spot = spot,
        vol = vol,
        r = r,
        d = d,
        number_of_paths = number_of_paths,
        number_of_dates = number_of_dates,
        is_double_barrier = 1,
        is_knock_out = 1,
        barrier1 = lower_values[i],
        barrier_direction = 1,
        barrier2 = upper_fixed,
        tolerance = tolerance
    )
}

plot(
    lower_values, lower_prices,
    type = "b",
    xlab = "Lower barrier",
    ylab = "Option price",
    main = "Lower Barrier Moves Up"
)

# 4. UPPER BARRIER MOVES DOWN, LOWER BARRIER FIXED

lower_fixed <- 70
upper_values <- c(160, 150, 140, 130, 125)

upper_prices <- numeric(length(upper_values))

for (i in seq_along(upper_values)) {
    upper_prices[i] <- CallSpreadBarrierSpread(
        is_bull = is_bull,
        expiry = expiry,
        strike1 = strike1,
        strike2 = strike2,
        spot = spot,
        vol = vol,
        r = r,
        d = d,
        number_of_paths = number_of_paths,
        number_of_dates = number_of_dates,
        is_double_barrier = 1,
        is_knock_out = 1,
        barrier1 = lower_fixed,
        barrier_direction = 1,
        barrier2 = upper_values[i],
        tolerance = tolerance
    )
}

plot(
    upper_values, upper_prices,
    type = "b",
    xlab = "Upper barrier",
    ylab = "Option price",
    main = "Upper Barrier Moves Down"
)

# 5. SPOT PRICE SENSITIVITY

spot_values <- c(90, 100, 105, 110, 115, 120, 130)

spot_prices <- numeric(length(spot_values))

for (i in seq_along(spot_values)) {
    spot_prices[i] <- CallSpreadBarrierSpread(
        is_bull = is_bull,
        expiry = expiry,
        strike1 = strike1,
        strike2 = strike2,
        spot = spot_values[i],
        vol = vol,
        r = r,
        d = d,
        number_of_paths = number_of_paths,
        number_of_dates = number_of_dates,
        is_double_barrier = 1,
        is_knock_out = 1,
        barrier1 = 70,
        barrier_direction = 1,
        barrier2 = 150,
        tolerance = tolerance
    )
}

plot(
    spot_values, spot_prices,
    type = "b",
    xlab = "Spot price",
    ylab = "Option price",
    main = "Spot Price Sensitivity"
)

# 6. VOLATILITY SENSITIVITY

vol_values <- c(0.10, 0.15, 0.20, 0.23, 0.30, 0.40, 0.50)

vol_prices <- numeric(length(vol_values))

for (i in seq_along(vol_values)) {
    vol_prices[i] <- CallSpreadBarrierSpread(
        is_bull = is_bull,
        expiry = expiry,
        strike1 = strike1,
        strike2 = strike2,
        spot = spot,
        vol = vol_values[i],
        r = r,
        d = d,
        number_of_paths = number_of_paths,
        number_of_dates = number_of_dates,
        is_double_barrier = 1,
        is_knock_out = 1,
        barrier1 = 70,
        barrier_direction = 1,
        barrier2 = 150,
        tolerance = tolerance
    )
}

plot(
    vol_values, vol_prices,
    type = "b",
    xlab = "Volatility",
    ylab = "Option price",
    main = "Volatility Sensitivity"
)

# 7. MATURITY SENSITIVITY

expiry_values <- c(0.1, 0.25, 0.5, 0.75, 1.0)

expiry_prices <- numeric(length(expiry_values))

for (i in seq_along(expiry_values)) {
    expiry_prices[i] <- CallSpreadBarrierSpread(
        is_bull = is_bull,
        expiry = expiry_values[i],
        strike1 = strike1,
        strike2 = strike2,
        spot = spot,
        vol = vol,
        r = r,
        d = d,
        number_of_paths = number_of_paths,
        number_of_dates = number_of_dates,
        is_double_barrier = 1,
        is_knock_out = 1,
        barrier1 = 70,
        barrier_direction = 1,
        barrier2 = 150,
        tolerance = tolerance
    )
}

plot(
    expiry_values, expiry_prices,
    type = "b",
    xlab = "Maturity",
    ylab = "Option price",
    main = "Maturity Sensitivity"
)

# 8. TOLERANCE SENSITIVITY

tolerance_values <- c(0.5, 0.4, 0.3, 0.2, 0.1, 0.05, 0.02, 0.01, 0.005)

tolerance_prices <- numeric(length(tolerance_values))

for (i in seq_along(tolerance_values)) {
    tolerance_prices[i] <- CallSpreadBarrierSpread(
        is_bull = is_bull,
        expiry = expiry,
        strike1 = strike1,
        strike2 = strike2,
        spot = spot,
        vol = vol,
        r = r,
        d = d,
        number_of_paths = number_of_paths,
        number_of_dates = number_of_dates,
        is_double_barrier = 1,
        is_knock_out = 1,
        barrier1 = 70,
        barrier_direction = 1,
        barrier2 = 150,
        tolerance = tolerance_values[i]
    )
}

plot(
    tolerance_values, tolerance_prices,
    type = "b",
    xlab = "Tolerance",
    ylab = "Option price",
    main = "Tolerance Sensitivity"
)
