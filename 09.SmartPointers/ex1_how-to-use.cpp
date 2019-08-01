#include <iostream>

using namespace std;

class Entity {
public:
	Entity() {
		std::cout << "Create entity!" << std::endl;
	}

	~Entity() {
		std::cout << "Destroy entity!" << std::endl;
	}
};

int main() {

	// unique_ptr
	//std::unique_ptr<int> p = std::make_unique<int>(42);
	{
		std::unique_ptr<Entity> e1(new Entity()); // because of explicit
		//std::unique_ptr<Entity> e3 = e1; // Compile ERROR
		
		std::unique_ptr<Entity> e2 = std::move(e1);

	}


	// shared_ptr
	{
		std::shared_ptr<Entity> e4;
		{
			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
			std::shared_ptr<Entity> e3 = sharedEntity;
			e4 = sharedEntity;
		}
	} // NOT deallocate object until go out of this scope

	// weak_ptr
	{
		std::weak_ptr<Entity> e6;
		{
			std::shared_ptr<Entity> sharedEntity2 = std::make_shared<Entity>();
			std::weak_ptr<Entity> e5 = sharedEntity2;
			e6 = e5;
		} // Deallocate object if go out of this scope
	} 


	return 0;
}