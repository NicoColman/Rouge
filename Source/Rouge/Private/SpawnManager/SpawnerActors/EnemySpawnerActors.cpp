// Rouge


#include "SpawnManager/SpawnerActors/EnemySpawnerActors.h"


AEnemySpawnerActors::AEnemySpawnerActors()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.AddUnique("EnemySpawnerPoint");

}



