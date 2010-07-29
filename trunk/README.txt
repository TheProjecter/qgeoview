=== SOFTWARE ===
Name: QGeoView
Description: Reads, organizes and transfers groundspeak geocaching gpx files
Author: Doug Penner <darwinsurvivor@gmail.com>
Copyright: GPLv3


=== INSTALLING FROM REPO ===
Arch Linux: install "qgeoview-svn" from AUR
Others: comming soon.

If anyone would be willing to build and host/maintain versions for other
distrobutions (or OS's), please let me know as I currently run mainly Arch
Linux.


=== BUILDING FROM SOURCE===
run the following
    qmake
    make


=== INSTALLING FROM SOURCE ===
for *nix run the following
    sudo make install
for windows please see "BUILDING FOR WINDOWS" below.


=== BUILDING FOR WINDOWS ===
I have not tested this application on windows, though I am not aware of any
reason why it would not compile and run in Windows. Please do note that
you may need to manually move the binary files to "c:\Program Files" as I have
not added "install" values for windows into the qgeoview.pro file.
