
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
ratio <- 12
# barrier direction:
# 1 = up barrier
# 0 = down barrier

# price trial
price <- CallRatioSpreadBarrier(
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
    barrier1 = 90.0,
    barrier_direction = 0,
    barrier2 = 0.0,
    tolerance = tolerance,
    ratio= ratio
)

print(price)

# 2. PRICE CHANGES WHEN VOLATILITY CHANGES
library(ggplot2)

vols <- seq(0.0, 0.5, by = 0.01)

prices <- c()

for (v in vols) {
    
    price <- CallRatioSpreadBarrier(
        is_bull = 1,
        expiry = 0.5,
        strike1 = 105,
        strike2 = 120,
        spot = 110,
        vol = v,
        r = 0.05,
        d = 0.0,
        number_of_paths = 100000,
        number_of_dates = 126,
        is_double_barrier = 0,
        is_knock_out = 1,
        barrier1 = 90.0,
        barrier_direction = 0,
        barrier2 = 0.0,
        tolerance = 0.02,
        ratio = 12
    )
    
    prices <- c(prices, price)
}

df <- data.frame(vol = vols, price = prices)

ggplot(df, aes(x = vol, y = price)) +
    geom_line() +
    geom_point() +
    geom_hline(yintercept = 0, linetype = "dashed") +
    labs(
        title = "Price Sensitivity to Volatility",
        x = "Volatility",
        y = "Option Price"
    )

ggsave("Figures/price_sensitivity_to_volatility.png", width = 8, height = 5, dpi = 300)


# 3. PRICE SENSITIVITY TO BARRIERS
barriers <- seq(30, 125.0, by = 1)

prices <- c()

for (b in barriers) {
    
    price <- CallRatioSpreadBarrier(
        is_bull = 1,
        expiry = 0.5,
        strike1 = 105,
        strike2 = 120,
        spot = 110,
        vol = 0.23,
        r = 0.05,
        d = 0.0,
        number_of_paths = 100000,
        number_of_dates = 126,
        is_double_barrier = 0,
        is_knock_out = 1,
        barrier1 = b,
        barrier_direction = 0,
        barrier2 = 0.0,
        tolerance = 0.02,
        ratio = 12
    )
    
    prices <- c(prices, price)
}

df <- data.frame(barrier = barriers, price = prices)

ggplot(df, aes(x = barrier, y = price)) +
    geom_line() +
    geom_point() +
    geom_hline(yintercept = 0, linetype = "dashed") +
    labs(
        title = "Price Sensitivity to Barrier Level",
        x = "Barrier Level",
        y = "Option Price"
    )

ggsave("Figures/price_sensitivity_to_barrier.png", width = 8, height = 5, dpi = 300)
# 4. PRICE SENSITIVITY TO UNDERLYING PRICE

spots <- seq(30, 200, by = 1)

prices <- c()

for (s in spots) {
    
    price <- CallRatioSpreadBarrier(
        is_bull = 1,
        expiry = 0.5,
        strike1 = 105,
        strike2 = 120,
        spot = s,
        vol = 0.23,
        r = 0.05,
        d = 0.0,
        number_of_paths = 100000,
        number_of_dates = 126,
        is_double_barrier = 0,
        is_knock_out = 1,
        barrier1 = 90.0,
        barrier_direction = 0,
        barrier2 = 0.0,
        tolerance = 0.02,
        ratio = 12
    )
    
    prices <- c(prices, price)
}

df <- data.frame(spot = spots, price = prices)

ggplot(df, aes(x = spot, y = price)) +
    geom_line() +
    geom_point() +
    labs(
        title = "Price Sensitivity to Underlying Price",
        x = "Underlying Price",
        y = "Option Price"
    )

ggsave("Figures/price_sensitivity_to_underlying.png", width = 8, height = 5, dpi = 300)
