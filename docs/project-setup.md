# Set up the project

## Set up the IDE
If you had not done so before, install VS Code and PlatformIO Extension:
- Download and install [Visual Studio Code](https://code.visualstudio.com/) for your operating system.
- Open VS Code, go to the Extensions tab (or press `Ctrl+Shift+X`), search for "PlatformIO IDE" and install it.

For more detailed instructions, there are numerous tutorials available online.

## Clone the Reposiotry

VS Code’s **Source Control** feature (`Ctrl+Shift+G`) allows you to clone a Git repository directly from the interface, making it easy to set up without using the command line. This [YouTube video](https://youtu.be/LfrzGQimd4U?si=7r09vz8c8HuNGeU) provides a step-by-step guide.

This method has a few advantages:
- the steps are the same across supported operating systems (Windows, Linux, Mac OS X).
- it allows you to open the project right after cloning.


Alternatively, you could just [download the repository as a ZIP file](https://docs.github.com/en/get-started/start-your-journey/downloading-files-from-github), extract it, and open it in VS Code.

Of course, you could use your terminal to clone and open the project from a command line.


## Build and Upload

To verify everything is working, open the PlatformIO sidebar, click on `Project Tasks`, expand your project name, and select `Build`.

When ready, connect your ESP32 device and select `Upload` to flash the firmware.
