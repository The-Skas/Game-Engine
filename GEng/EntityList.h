#ifndef ENTITYLIST
#define ENTITYLIST
#include "SystemStructure.h"
#include "Entity.h"
#include <map>



class EntityList : public System
{

public:
		EntityList();
	 ~EntityList();
	//System initialization
	 void Initialize();

	 void Update(float timeslice);
	 std::string GetName();

   //Creation and Destruction of Entities
   void AddEntity(Entity *e);
   void DestroyEntity(unsigned ID);
   void DestroyAll(void);

   //Return list size
   int GetSize(void) 
   {
     return eList.size();
   }
   
   std::map<unsigned,Entity*> eList;
private:

  //Create Unique IDs
  unsigned LastId;

};

extern EntityList* ENTLIST;
#endif