#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <typeinfo>
#include <typeinfo.h>
class GameObject {
public:
    virtual ~GameObject() {} //基类里面有虚函数，派生类继承后，使用typeid().name才能取得对应的class name

};
class SpaceShip : public GameObject {};
class SpaceStation : public GameObject {};
class Asteroid : public GameObject {};

//匿名namespace
namespace {
    using std::string;
    using std::map;
    using std::make_pair;
    using std::pair;
    using std::cout;
    using std::endl;
    // 增加
    void shipAsteroid(GameObject& spaceShip, GameObject& asteroid) { cout << "spaceShip collide with asteroid" << endl; };
    void shipStation(GameObject& spaceShip, GameObject& spaceStation) { cout << "spaceShip collide with spaceStation" << endl; };
    void asteroidStation(GameObject& asteroid, GameObject& spaceStation) { cout << "asteroid collide with spaceStation" << endl; };

    void asteroidShip(GameObject& asteroid, GameObject& spaceShip) { shipAsteroid(spaceShip, asteroid); };
    void stationShip(GameObject& spaceStation, GameObject& spaceShip) { shipStation(spaceShip, spaceStation); };
    void stationAsteroid(GameObject& spaceStation, GameObject& asteroid) { asteroidStation(asteroid, spaceStation); };
}

//碰撞map
class CollisionMap {
public:
    //这里使用单例
    static CollisionMap* theCollisionMap() {
        static CollisionMap CM;
        return &CM;
    };

    typedef void (*HitFunctionPtr)(GameObject&, GameObject&);

    //这里添加新的碰撞处理函数，成对处理
    void addEntry(const string& type1, const string& type2, HitFunctionPtr collisionFunction)
    {
        if (collisionMap.find(std::make_pair(type1, type2)) != collisionMap.end()) return;
        //成对添加
                // printf("%p\n",collisionFunction);

        collisionMap[std::make_pair(type1, type2)] = collisionFunction;
        collisionMap[std::make_pair(type2, type1)] = collisionFunction;
        
    }

    //这里移除碰撞函数
    void removeEntry(const string& type1, const string& type2) {
        if (collisionMap.find(std::make_pair(type1, type2)) != collisionMap.end()) return;

        //成对移除
        collisionMap.erase(std::make_pair(type1, type2));
        collisionMap.erase(std::make_pair(type2, type1));
    }

    //查找有没有对应的碰撞函数
    HitFunctionPtr lookup(const string& class1, const string& class2) {
        HitMap::iterator it = collisionMap.find(make_pair(class1, class2));
        
        if (it == collisionMap.end()) {
            return 0;
        }

        return (*it).second;
    }
private:
    typedef map<pair<string, string>, HitFunctionPtr> HitMap;
    HitMap collisionMap;

    CollisionMap() { initializeCollisionMap(); };
    CollisionMap(const CollisionMap&);

    // 这里可以内部初始化，也可以改为一个函数，来注册一下函数
    void initializeCollisionMap() {
        collisionMap.clear();
        // 增加
        addEntry("9SpaceShip", "8Asteroid", &shipAsteroid);
        addEntry("9SpaceShip", "12SpaceStation", &shipStation);
        // ...
    }
};

//匿名namespace
namespace
{
    //这里处理碰撞，会查找碰撞map，如果有函数就执行，没有的话就抛出异常
    void processCollision(GameObject& object1, GameObject& object2) {  
        CollisionMap* CM = CollisionMap::theCollisionMap();
        CollisionMap::HitFunctionPtr phf = CM->lookup(typeid(object1).name(), typeid(object2).name());
        if (phf) phf(object1, object2);
        else cout << "UnkowCollision! " << typeid(object1).name() << " - " << typeid(object2).name() << endl;
    }
}

int main() {
    SpaceShip spaceShip;
    Asteroid asteroid;
    SpaceStation spaceStation;

    processCollision(spaceShip, asteroid);  //spaceShip collide with asteroid
    processCollision(asteroid, spaceShip);  //UnkowCollision! class Asteroid - class SpaceShip
    processCollision(spaceShip, spaceStation); //spaceShip collide with spaceStation
    processCollision(asteroid, spaceStation); //UnkowCollision! class Asteroid - class SpaceStation

    return 0;
}