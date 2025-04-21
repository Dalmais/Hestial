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
- **Variable names** should be written in **camelCase** prefixed with m_. Example: `m_temperatureSensor`

## 🚫 Best Practices
- **Avoid global variables** whenever possible.
- **Avoid goto** and prefer exception
- Always **initialize variables** before use.
- Prefer **smart pointers** (`std::unique_ptr`, `std::shared_ptr`) over raw pointers.
- Follow the **Single Responsibility Principle**: each function or method should have a clearly defined and limited purpose.
- Always declare a virtual destructor in inherited class
- Include local path first then system path (ex: "SensorManager.h" before <ioctl.h>) 

## ⚡ Optimization
- Prefer **references (`const&`)** for passing large objects to avoid unnecessary copies.
- Avoid excessive use of `new` and `delete`; prefer STL containers like `std::vector`, `std::map`, etc.

## 💻 Examples
### 1. **Class style**:
```cpp
class SensorManager : public Manager {
public:
    SensorManager();
    virtual ~SensorManager();

    void readTemperature();
    void displayResults();

private:
    double m_temperature;
};
```

### 2. **Implementation style**:
```cpp
#include "SensorManager.h"
#include "TemperatureManager.h"

#include <iostream>

SensorManager::SensorManager() : Manager(), m_temperature(0.0) {}

SensorManager::~SensorManager() {}

void SensorManager::readTemperature() {
    // Simulated sensor reading
    m_temperature = TemperatureSensor::getInstance().getValue();

    // Debug output
    if(m_verbose){
      std::cout << "Temperature read: " << m_temperature << "°C" << std::endl;
    }
}
```
