![](resources/banner.png)

[![Translation status](https://hosted.weblate.org/widgets/nickvision-tube-converter/-/app/svg-badge.svg)](https://hosted.weblate.org/engage/nickvision-tube-converter/) ✨Powered by [Weblate](https://weblate.org/en/)✨

# Features
- A basic yt-dlp frontend ([supported sites](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md))
- Supports downloading videos in multiple formats (mp4, webm, mp3, opus, flac, and wav)
- Run multiple downloads at a time
- Supports downloading metadata and video subtitles

# Disclaimer
The authors of Nickvision Parabolic are not responsible/liable for any misuse of this program that may violate local copyright/DMCA laws. Users use this application at their own risk.

# Installation
<p><a href='https://flathub.org/apps/details/org.nickvision.tubeconverter'><img width='150' alt='Download on Flathub' src='https://dl.flathub.org/assets/badges/flathub-badge-en.png'/></a></p>
<p><a href="https://snapcraft.io/tube-converter"><img width='150' alt="Get it from the Snap Store" src="https://snapcraft.io/static/images/badges/en/snap-store-black.svg" /></a></p>
<p><a href="https://aur.archlinux.org/packages/parabolic"><img width='140' alt="Download from AUR" src="https://aur.archlinux.org/static/css/archnavbar/aurlogo.png"/></a></p>
<p><a href="https://github.com/NickvisionApps/Parabolic/releases"><img width='140' alt="Download from Releases" src="https://upload.wikimedia.org/wikipedia/commons/e/e2/Windows_logo_and_wordmark_-_2021.svg"/></a></p>

# Chat
<a href='https://matrix.to/#/#nickvision:matrix.org'><img width='140' alt='Join our room' src='https://user-images.githubusercontent.com/17648453/196094077-c896527d-af6d-4b43-a5d8-e34a00ffd8f6.png'/></a>

# Contributing
See [CONTRIBUTING.md](CONTRIBUTING.md) for details on how can you help the project and how to provide information so we can help you in case of troubles with the app.

# Screenshots
<details>
 <summary>GNOME</summary>
</details>

<details>
 <summary>WinUI</summary>
</details>

## Building Manually
Parabolic uses `vcpkg` to manage its dependencies and `cmake` as its build system.

Ensure both `vcpkg` and `cmake` are installed on your system before building.

A C++20 compiler is also required to build Parabolic.

### Configuring vcpkg
1. Set the `VCPKG_ROOT` environment variable to the path of your vcpkg installation's root directory.
#### Windows
1. Set the `VCPKG_DEFAULT_TRIPLET` environment variable to `x64-windows`
1. Run `vcpkg install boost-date-time libnick`
#### Linux
1. Set the `VCPKG_DEFAULT_TRIPLET` environment variable to `x64-linux`
1. Run `vcpkg install boost-date-time libnick libxmlpp`

### Building
1. First, clone/download the repo.
1. Open a terminal and navigate to the repo's root directory.
1. Create a new `build` directory and `cd` into it. 
#### Windows
1. From the `build` folder, run `cmake .. -G "Visual Studio 17 2022"`.
1. From the `build` folder, run `cmake --build . --config Release`.
1. After these commands complete, Parabolic will be successfully built and its binaries can be found in the `org.nickvision.tubeconverter.winui/Release` folder of the `build` folder.
#### Linux
1. From the `build` folder, run `cmake .. -DCMAKE_BUILD_TYPE=Release`.
1. From the `build` folder, run `cmake --build .`.
1. After these commands complete, Parabolic will be successfully built and its binaries can be found in the `org.nickvision.tubeconverter.gnome` folder of the `build` folder.

# Code of Conduct
This project follows the [GNOME Code of Conduct](https://wiki.gnome.org/Foundation/CodeOfConduct).
