<div align="center">
  <p>
    <h1>
      <a href="https://github.com/Dalmais/Housebot">
        <img src="images/general/homebot_200.png" alt="Homebot" />
      </a>
    </h1>
    <h4>Next house management.</h4>
  </p>
  <p>
    <a href="https://github.com/Dalmais/Housebot/actions?query=workflow%3APackaging%28Linux%29">
      <img src="https://img.shields.io/github/actions/workflow/status/Dalmais/Housebot/Linux-pack.yml?branch=master&label=gnu%2Flinux" alt="GNU/Linux Build Status" />
    </a>
    <a href="https://github.com/Dalmais/Housebot/actions?query=workflow%3APackaging%28Windows%29">
      <img src="https://img.shields.io/github/actions/workflow/status/Dalmais/Housebot/Windows-pack.yml?branch=master&label=windows" alt="Windows Build Status" />
    </a>
    <a href="https://github.com/Dalmais/Housebot/actions?query=workflow%3APackaging%28MacOS%29">
      <img src="https://img.shields.io/github/actions/workflow/status/Dalmais/Housebot/MacOS-pack.yml?branch=master&label=macos" alt="MacOS Build Status" />
    </a>
    <a href="https://github.com/Dalmais/Housebot/releases">
      <img src="https://img.shields.io/github/release/Dalmais/Housebot.svg" alt="Latest Stable Release" />
    </a>
    <a href="https://github.com/Dalmais/Housebot/blob/master/LICENSE">
      <img src="https://img.shields.io/github/license/Dalmais/Housebot.svg" alt="License" />
    </a>
  </p>
</div>

# Housebot
This is a bunch of application/bot for the house management.
This currently contain a superviser application and a bunch of tools for gardening
Futurs applications are like monitoring the state of the plantation over other devices, process automatic tasks, camera monitoring services, ...

## Homebase
This application collect data from the different connected devices. 
These device can be from housebot or from other devices with a supported open protocol
Open supported protocol are : None
It also feed data for a web server in order to display this information on a browser.

## Webpage
the webpage provides information about the plantation. the database is feed by the information provided by the homebase.

## HomeGarden
raspberry pi3 with sensor and activator. should be independent with power provided by solar energy.
