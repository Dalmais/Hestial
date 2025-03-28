# Housebot
This document presents the expected behavior that we want.
The strategy to use in order to code.

## Behavior
- Temperature
- Humidity
- Quality of the air (MQ135)
  - ref: https://www.raspberrypi.com/news/track-air-quality-anywhere-with-raspberry-pi/
- Powered by solar system and battery (powerbank)

## Implementation strategy
1. Create a build of the system
2. Install a database 
3. Get the data and store them in the database
4. send data to a cloud
5. Visualize the data
