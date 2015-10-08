STALLED: Please note that development of this project has stalled. I may look into it again in the future but am currently overrun with other projects. Feel free to contact me if you have any questions about the project.


This is starting off as a GPX viewer compatible is GroundSpeak's GPX format.

Arch Linux users can now install the svn version from AUR
http://aur.archlinux.org/packages.php?ID=39230

The current version of QGeoView does nothing much. I am in the middle of implementing a plugin system so that users can customize the application for the type of device they are using (ex: leaving out Map support for low-powered devices, custom load/export plugins, etc)

[Revision 17](https://code.google.com/p/qgeoview/source/detail?r=17) has the old working code (allows you to load a gpx file, select individual caches and see them on a map, then export to a new gpx files). Newer better code is coming :D

I have tried both QMapControl and MarbleWidget and found neither of them 100% suitable for all my uses, so I am planning on making each an optional plugin, allowing the user to chose which (if any) map plugin they would like to use.