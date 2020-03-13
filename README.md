#MetinBot
A bot currently under development, might be merged to a clientless bot on future

I created this bot as way to learn more about reverse engeneering alongside OOP code organization and GUI devolpment, as this game as a leaked (old) source client available in the internet making this game not too hard to start RE (Reverse Enggener) but still offering some challanges as some private servers implement different game systems and protection measures, wich some times become fun to bypass.

RE related things:

//Function CPythonCharacterManager::__RenderSortedAliveActorList stores a static vector //that corresponds to the map of every instance //Currently wallhack dont work for game objects - TestActorCollision can be a fix for this, to be analyzed

To do List:

Rethink Bot class, as of now it appears to go into an an explosion of classes for each feature Improve GUI 
- Final long term objective/sideProject, Develop a full working Vulkan GUI engine 
- Do a more safe call and memory reading by checking for null pointer (Still thinking if is worth to sacrifice performance over error checking) 
- Provide an Interface for Patterns class (Low priority)

##Reminders:

-ObjectDetection: To detected wether a point in the map is movable or not the function CPythonBackground::isAttrOn can be queryied with CTerrain::ATTRIBUTE_BLOCK in the last parameter to find this function, the easyest way is to search for the string "CTerrain::isAttrOn Coordiante Error! Return false... Input Coord - X : %d, Y : %d ( Limit X : %d, Y : %d)" The simplest way to call the function is by using a wrapper located at "CMapManager::isAttrOn" wich belongs to the PythonBackground Class

-Patterns CPytonItem class pointer can be found in the function PickCloseItem used in the python interpreter The pattern to isAttrOn is relative based

##ToDoList: 
- GM detection 
- DamageHack check for max radius of attack 
- std::string has an aditional variable in DEBUG mode at the beginning of the structure
- minor bug on drop
