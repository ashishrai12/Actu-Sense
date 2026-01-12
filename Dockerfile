# Build stage
FROM ubuntu:22.04 AS builder

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libsfml-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy the project
COPY . .

# Build the project (disable visualization for headless docker environment by default)
RUN mkdir build && cd build && \
    cmake .. -DENABLE_VISUALIZATION=OFF -DBUILD_TESTS=ON && \
    make -j$(nproc)

# Test stage
RUN cd build && ctest --output-on-failure

# Final stage
FROM ubuntu:22.04

WORKDIR /app

# Copy the executable from builder
COPY --from=builder /app/build/ActuSenseApp .

# Run the application
CMD ["./ActuSenseApp"]
