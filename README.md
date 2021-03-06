# ESP8266_ARDUINO_IDE
We are going to use ESP8266 with different sensors as well as sending the real time data of sensor to different online servers

## But before going to execute 

First check and create the setup which help us to connect the I2C or any kind of connection protocol with different ESP8266, node MCU, ESP01, ESP12E etc development boards.

  - Download Arduino IDE
  - Open you IDE and click on "File -> Preferences"
  - In  "Aditional Boards Manager URLs" add - "http://arduino.esp8266.com/stable/package_esp8266com_index.json"
  - Click on "OK"
  - Go to "Tools -> Board -> Boards Manager", type "ESP8266" and install by selecting the latest version(If require)
  - Go again to "Tools -> Board" and select "Generic ESP8266 Module" for common node MCUs
  
  ### Note: For adafruit huzzah and many other boards are also available in you can search by using scroll down
  
  - Now  you're ready to use your ESP8266 as a standalone device. Finally you are no longer to use microcontroller easpecially for ESP8266 boards 
  
  ## Issues 
  
     Error downloading http://downloads.arduino.cc/packages/package_index.json
     java.lang.RuntimeException: java.lang.Exception: Error downloading http://downloads.arduino.cc/packages/package_index.json
	   at cc.arduino.contributions.packages.ui.ContributionManagerUI.lambda$onUpdatePressed$1(ContributionManagerUI.java:150)
	   at java.lang.Thread.run(Thread.java:748)
     Caused by: java.lang.Exception: Error downloading http://downloads.arduino.cc/packages/package_index.json
	   at cc.arduino.contributions.DownloadableContributionsDownloader.download(DownloadableContributionsDownloader.java:139)
	   at cc.arduino.contributions.packages.ContributionInstaller.download(ContributionInstaller.java:333)
	   at cc.arduino.contributions.packages.ContributionInstaller.downloadIndexAndSignature(ContributionInstaller.java:307)
	   at cc.arduino.contributions.packages.ContributionInstaller.updateIndex(ContributionInstaller.java:285)
	   at cc.arduino.contributions.packages.ui.ContributionManagerUI.lambda$onUpdatePressed$1(ContributionManagerUI.java:146)
	   ... 1 more
  
  ### Issue 1
  If mentioned above issue appears on the black console and while installing, the esp8266 board does not appears, then use the following steps:
  
 - Open Arduino IDE and click on "File -> Preferences"
 - In preferences on the link mentioned below in snap
 
 ![alt text](https://github.com/varul29/ESP8266/blob/master/ESP8266_Snaps/Issue.PNG)
 
 - Instead of "packages folder" delete all the other files present in the folder.
 - Restart Arduino IDE
 - Finally You will be able to Install the boards
 
 ### Issue 2 
 
 If still not resolved with "Issue 1" then
 
 - Click on "Windows Start Button"
 - Search Configure proxy settings"
 - Click "ON" "Automatic Proxy Setup"
 
  ![alt text](https://github.com/varul29/ESP8266/blob/master/ESP8266_Snaps/Issue%202.PNG)
 
 - Restart Arduino IDE
 
  Finally, we will be able to install the ESP8266 board and run the code.
