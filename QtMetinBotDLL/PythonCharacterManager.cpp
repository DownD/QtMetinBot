#include "PythonCharacterManager.h"



CPythonCharacterManager::CPythonCharacterManager(Memory* mem)
{
	classPointer = mem->GetCMethod<CLASS_POINTER*>("CPythonCharacterManager",DEREFERENCE,CRITICAL);
	mainInstanceOffset = mem->GetCMethod<BYTE>("m_instMain", DEREFERENCE, CRITICAL);
	//startOfInstanceList = mem->GetCMethod<DWORD*>("m_InstanceArray", DEREFERENCE, CRITICAL);
#ifdef ORIGINS_SERVER
	mapOffset = 0x20;
#else
	mapOffset = mem->GetCMethod<BYTE>("m_InstanceMapBase", DEREFERENCE, CRITICAL);
#endif
	DEBUG_INFO(COLOR_GREEN, "CPythonCharacterManager Sucessfully set");
}


CPythonCharacterManager::~CPythonCharacterManager()
{
}



CInstanceBase * CPythonCharacterManager::getInstanceByVID(int vid)
{
	auto map = getInstanceMap();
	InstanceMap::iterator begin = map->begin();
	InstanceMap::iterator end = map->end();

	for(; begin != end; ++begin) {
		if (begin.getKey() == vid)
			return begin.getValue();
	}
	return nullptr;
}

void CPythonCharacterManager::getPlayerList(std::vector<CInstanceBase*>* vec) {
	auto begin = getInstanceMap()->begin();
	auto end = getInstanceMap()->end();

	CInstanceBase* main = getMainInstance();

	for (; begin != end; ++begin) {
		CInstanceBase * current = begin.getValue();
		if (current != main) {
			if (current->isPlayerOrGM())
				vec->push_back(current);
		}
	}
}