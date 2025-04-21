### **C++ Code Style Template**

```markdown
# 🧑‍💻 C++ Code Style Guide

This document defines the conventions to follow for clean, readable, and maintainable C++ code.

## 📏 General Rules
- Use **descriptive variable names**.
- Always **comment code** to explain complex or non-obvious logic.
- Use **3 spaces** for indentation, and **avoid tabs**.
- Use **`const` and `constexpr`** wherever applicable to define constant values.

## 🔠 Naming Conventions
- **Class names** should be written in **CamelCase**, starting with a capital letter. Example: `SensorManager`
- **Function names** should use **camelCase**, starting with a lowercase letter. Example: `initializeSensors()`
- **Variable names** should be written in **snake_case** prefixed with m_. Example: `m_sensor_temperature`

## 🚫 Best Practices
- **Avoid global variables** whenever possible.
- Always **initialize variables** before use.
- Prefer **smart pointers** (`std::unique_ptr`, `std::shared_ptr`) over raw pointers.
- Follow the **Single Responsibility Principle**: each function or method should have a clearly defined and limited purpose.

## ⚡ Optimization
- Prefer **references (`const&`)** for passing large objects to avoid unnecessary copies.
- Avoid excessive use of `new` and `delete`; prefer STL containers like `std::vector`, `std::map`, etc.

## 💻 Examples
### 1. **Class**:
```cpp
class SensorManager {
public:
    SensorManager();
    ~SensorManager();

    void readTemperature();
    void displayResults();

private:_
    double m_temperature;
};
```

### 2. **Implementation of `readTemperature()`**:
```cpp
#include "SensorManager.h"
#include <iostream>

SensorManager::SensorManager() : temperature(0.0) {}

SensorManager::~SensorManager() {}

void SensorManager::readTemperature() {
    // Simulated sensor reading
    double raw_sensor_value = 25.3; // Replace with actual sensor reading logic

    // Store the value in the member variable
    temperature = raw_sensor_value;

    // Debug output
    std::cout << "Temperature read: " << temperature << "°C" << std::endl;
}
```cpp
class SensorManager {
public:
    SensorManager();
    ~SensorManager();

    void readTemperature();
    void displayResults();

private:
    double temperature;
};
```
```
