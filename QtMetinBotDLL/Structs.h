#pragma once
#include <cmath>
#include <iterator>
#include <Windows.h>
#include <stdlib.h>
#include <set>
#define PI 3.14

#define ITEM_SOCKET_SLOT_MAX_NUM 6
#define ITEM_ATTRIBUTE_SLOT_MAX_NUM 7

#define MAX_RANGE_TELEPORT_HORSE 3000
#define MAX_RANGE_TELEPORT_GROUND 3000
#define PY_FUNCTION 1
#define C_FUNCTION 0

//#define IMPERUS_SERVER
//#define ORIGINS_SERVER
#define AELDRA_SERVER

//Python Modules
#define CHR_PYTHON_MODULE "chr"
#define NET_PYTHON_MODULE "net" 
#define PLAYER_PYTHON_MODULE "player" 
#define CHAT_PYTHON_MODULE "chat"
#define CHRMGR_PYTHON_MODULE "chrmgr"

//PHASES
#define OFFLINE_PHASE "OffLine"
#define GAME_PHASE "Game"
#define LOADING_PHASE "Loading"
#define LOGIN_PHASE "Login"
#define SELECT_PHASE "Select"
#define HANDSHAKE_PHASE "HandShake"

#ifdef IMPERUS_SERVER
#define NET_PYTHON_MODULE "flexionet" 
#define PLAYER_PYTHON_MODULE "flexioplayer" 
#define CHAT_PYTHON_MODULE "flexiochat"
#endif

#ifdef ORIGINS_SERVER
#define NET_PYTHON_MODULE "x7naf55d7drjbd6m4zgqrn" 
#define PLAYER_PYTHON_MODULE "ase72nzwadtwydwz2qdudm" 
#define CHAT_PYTHON_MODULE "asdzxcvfsqwrdgasd"
#endif

enum MonsterIDs {
	NINE_TAILS_ID = 1901,
	GIANT_TURTLE_ID = 2191,
	ORC_CHEF = 691,
	GHOST_TREE_LORD = 2307
};

enum TypeComboAttack {
	FIRST_WARRIOR_ATTACK = 14,
	SECOND_WARRIOR_ATTACK = 15,
	THIRD_WARRIOR_ATTACK = 16,
	LAST_WARRIOR_ATTACK = 17,
	COMBO_FIRST_WARRIOR_ATTACK = 18,
	COMBO_SECOND_WARRIOR_ATTACK = 19,
	FIRST_HORSE_ATTACK = 15,
	SECOND_HORSE_ATTACK = 16,
};

enum TypeStateAttack{
	FUNC_WAIT,
	FUNC_MOVE,
	FUNC_ATTACK,
	FUNC_COMBO,
	FUNC_MOB_SKILL,
	FUNC_EMOTION,
	FUNC_SKILL = 0x80,
};

enum MapFlags
{
	ATTRIBUTE_BLOCK = (1 << 0),
	ATTRIBUTE_WATER = (1 << 1),
	ATTRIBUTE_BANPK = (1 << 2),
};


const std::set<DWORD> BossMap({ NINE_TAILS_ID ,GIANT_TURTLE_ID ,ORC_CHEF,GHOST_TREE_LORD });


typedef DWORD* CLASS_POINTER;


class Point2D {
public:
	Point2D(float x = 0.f, float y= 0.f) { this->x = x; this->y = y; }

	inline float distance(Point2D* p) { return sqrt((p->x - x)*(p->x - x) + (p->y - y)*(p->y - y)); }
	float angle(Point2D *p);
	inline void absoluteY() { y = abs(y); }

	inline int getIntX() { return (int)x; }
	inline int getIntY() { return (int)y; }

	inline void setIntX(int x) { this->x = x; }
	inline void setIntY(int y) { this->y = y; }

	float x;
	float y;
};

class Point3D{
public:
	Point3D(float x = 0.f, float y = 0.f, float z = 0.f){
		this->x = x; this->y = y; this->z = z;
	}
	inline float distance(Point3D* p) { return sqrt((p->x - x)*(p->x - x) + (p->y - y)*(p->y - y) +(p->z - z)*(p->z - z)); }

	inline int getIntX() { return (int)x; }
	inline int getIntY() { return (int)y; }
	inline int getIntZ() { return (int)z; }

	inline void setIntX(int x) { this->x = x; }
	inline void setIntY(int y) { this->y = y; }
	inline void setIntZ(int y) { this->z = y; }

	float x,y,z;
};

//This can be used to call __stdcall and __cdecl call conventions, by assigning null to the classpointer
template<class Return, class ClassPointer, class... Args>
using FunctionPtr = Return(__thiscall*)(ClassPointer, Args...);

typedef bool FunctionType;



//Ignore alignment
#pragma pack(push,1)
struct TPlayerItemAttribute {
	BYTE        bType;
	short       sValue;
};
//size = 0x3E
struct TItemData {
	DWORD		vnum;
	BYTE		count;
	long		bind;
	DWORD		flags;
	DWORD		anti_flags;
	long		alSockets[6];
	TPlayerItemAttribute aAttr[7];
};

struct TItemPos {
	BYTE windowType;
	WORD itemSlot;
};
#pragma pack(pop)

struct SGroundItemInstance {
	DWORD					structPointer;
	DWORD					dwVirtualNumber;
	Point3D					v3EndPosition;

	Point2D getItemPosition2D() { return { v3EndPosition.x,-v3EndPosition.y }; }
};

struct ItemGround {
	SGroundItemInstance* item;
	DWORD vnum;
};



//If node has no child then it points to root node
//Root left is the smaller value, right is the bigger value, 
template<class K,class V>
class Map {

	struct MapNode {
		MapNode * left;
		MapNode* parent;
		MapNode* right;
		DWORD uknown;
		K key;
		V value;
	};
public:
	class iterator : public std::iterator< std::output_iterator_tag, std::pair<K, V>> {
	public:
		explicit iterator(MapNode *node, MapNode* rootNode ) : pos(node), rootNode(rootNode)  {}
		iterator& operator++() { 
			if (isEmptyNode(pos))
				return *this;
			if (!isEmptyNode(pos->right)) {
				pos = pos->right;

				while (!isEmptyNode(pos->left)) {
					pos = pos->left;
				}
			}
			else {
				MapNode* parent = pos->parent;
				if (isEmptyNode(parent)) {
					pos = parent;
					return *this;
				}

				while (pos == parent->right) {
					pos = parent;
					parent = parent->parent;
				}
				if (pos->right != parent)
					pos = parent;
			}
		return *this; 
		}
		iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
		bool operator==(iterator other) const { return pos == other.pos; }
		bool operator!=(iterator other) const { return !(*this == other); }
		std::pair<K,V> operator*() const { return std::make_pair<K, V>(pos->key, pos->value); }
		K getKey() { return pos->key; }
		V getValue() { return pos->value; }

	private:

		bool isEmptyNode(MapNode* node) { return rootNode == node; } 

	public:
		MapNode* pos;
	private:
		MapNode* rootNode;
	};

	inline iterator begin() { return iterator(rootNode->left,rootNode); }
	inline iterator end() { return iterator(rootNode, rootNode); }

	inline int getSize() { return numberElements; }

	//Because errors occur if a template function is defined separated
	iterator find(K key) {
		MapNode* curr = rootNode->parent;

		while (curr != rootNode) {
			if (curr->key > key) {
				curr = curr->left;
				continue;
			}

			if (curr->key < key) {
				curr = curr->right;
				continue;
			}

			if (curr->key == key)
				return iterator(curr, rootNode);
		}

		return iterator(rootNode, rootNode);
	}

private:

	MapNode* rootNode;
	DWORD numberElements;
};


//NOT THREAD SAFE
template<class T>
class Vector {
	class iterator : public std::iterator< std::output_iterator_tag, T> {
	public:
		explicit iterator(T *pos) : pos(pos) {}
		iterator& operator++() { pos += sizeof(T*); }
		iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
		bool operator==(iterator other) const { return pos == other.pos; }
		bool operator!=(iterator other) const { return !(*this == other); }
		T operator*() const { return *pos; }
		T getValue() { return *pos; }

	private:

	public:
		T* pos;
	};

public:

	inline iterator begin() { return iterator(arrayStart); }
	inline iterator end() { return iterator(arrayEnd); }

	inline int getSize() { return (*arrayEnd - *arrayStart)/4; }

private:
	T* arrayStart;
	T* arrayEnd;
	T* arrayMaxCapacity;

};

