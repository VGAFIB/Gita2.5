#include "GameObject.hpp"
#include "Game.hpp"

std::map<std::string,GameObject*> GameObject::nameMap;
std::map<int,GameObject*> GameObject::idMap;
int GameObject::idCounter = 1;
int GameObject::objectCount = 0;

GameObject::GameObject(GameObject* parent) :
	id(idCounter++), isAlive(true), parent(parent),
	transform(1.0f), fullTransform(1.0), drawPriority(0), name("") {
	Game::drawTasks.insert(this);
	++objectCount;
	idMap.insert(std::pair<int,GameObject*>(id,this));
}

GameObject::~GameObject() {
	--objectCount;
	Game::drawTasks.erase(this);
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		delete *it;
	if(!name.empty())
		nameMap.erase(name);
	idMap.erase(id);
}

void GameObject::update(float deltaTime) {
	(void) deltaTime;
}

void GameObject::draw() const {
}

void GameObject::addObject(GameObject *object) {
	children.push_back(object);
}

void GameObject::setName(std::string newName) {
	if(name == newName) return;
	if(nameMap.insert(std::pair<std::string,GameObject*>(newName,this)).second) {
		if(!name.empty()) nameMap.erase(name);
		name = newName;
	}
	else {VBE_LOG("#WARNING Can't set name for node " << this << ". This name is already in use." );}
}

void GameObject::setDrawPriority(int newPriority) {
	if(drawPriority == newPriority) return;
	Game::drawTasks.erase(this);
	drawPriority = newPriority;
	Game::drawTasks.insert(this);
}

int GameObject::getDrawPriority() {
	return drawPriority;
}

std::string GameObject::getName() {
	return name;
}

GameObject* GameObject::getObjectByName(std::string name) {
	return nameMap.at(name);
}

GameObject* GameObject::getObjectByID(int id) {
	return idMap.at(id);
}

int GameObject::getObjectCount() {
	return objectCount;
}

void GameObject::calcFullTransform(mat4f parentFullTransform) {
	fullTransform = parentFullTransform * transform;
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->calcFullTransform(fullTransform);
}

void GameObject::doUpdate(float deltaTime) {
	update(deltaTime);
	for(std::list<GameObject*>::iterator it = children.begin(); it != children.end();) {
		(*it)->doUpdate(deltaTime);
		if (!(*it)->isAlive) {
			delete *it;
			it = children.erase(it);
		}
		else
			++it;
	}
}