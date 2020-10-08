# MetinBot
An old bot for Metin2 orivate servers.<br>
<b>I stopped the development, currently is not working. The Bot needs a big change in the GUI and in some classes in order to become more simple to make changes.</b><br>
I created this bot as way to learn more about reverse engenering alongside OOP code organization and GUI devolpment, as this game as a leaked (old) source client available in the internet making it not too hard to start RE (Reverse Enggener) but still offering some challanges as some private servers implement different
game systems and protection measures, wich some times become fun to bypass.


## Features
- ExpBot
- FarmBot
- Pickup
- SkillBot
- DmgHack
- Collision Detection


## Reminders:
To detected wether a point in the map is movable or not the function CPythonBackground::isAttrOn can be queryied with CTerrain::ATTRIBUTE_BLOCK in the last parameter. To find this function, the easyest way is to search for the string "CTerrain::isAttrOn Coordiante Error! Return false... Input Coord - X : %d, Y : %d ( Limit X : %d, Y : %d)".<br>
The simplest way to call the function is by using a wrapper located at "CMapManager::isAttrOn" wich belongs to the PythonBackground Class.<br>
	
	
-Patterns<br>
CPytonItem class pointer can be found in the function PickCloseItem used in the python interpreter.<br>
The pattern to isAttrOn is relative based.<br>
	
